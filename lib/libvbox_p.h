/* This file is part of libvbox
 * Copyright (C) 2019  Michael Hansen
 *
 * libvbox is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * libvbox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libvbox; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "libvbox.h"

#include <type_traits>

#define BADCHAR_SUBSTITUTE  wchar_t(0xFFFD)

#if defined(VBOX_XPCOM)
#   include <nsMemory.h>
#   include <VirtualBox_XPCOM.h>

#   define COM_ERROR_CHECK(rc)                                          \
        do {                                                            \
            if (NS_FAILED(rc))                                          \
                throw COMError(rc);                                     \
        } while (0)

    typedef PRBool      COM_Bool;
    typedef PRInt32     COM_Long;
    typedef PRUint32    COM_ULong;
    typedef PRInt64     COM_Long64;
    typedef PRUint64    COM_ULong64;

#   define COM_Type(XPCOM_Type, MSCOM_Type)  XPCOM_Type

    template <typename WcType>
    typename std::enable_if<sizeof(WcType) == sizeof(PRUnichar), std::wstring>::type
    nsToWString(const PRUnichar *text)
    {
        return std::wstring(reinterpret_cast<const WcType *>(text));
    }

    template <typename WcType>
    typename std::enable_if<sizeof(WcType) >= sizeof(uint32_t), std::wstring>::type
    nsToWString(const PRUnichar *text)
    {
        // C++11 provides a way to convert UTF-16 to std::wstring, but
        // it's cumbersome to use and is deprecated in C++17 with no
        // obvious replacement.
        std::wstring result;
        size_t inSize = std::char_traits<char16_t>::length(reinterpret_cast<const char16_t *>(text));
        result.reserve(inSize);

        const PRUnichar *pch = text;
        const PRUnichar *pend = text + inSize;
        for (; pch < pend; ++pch) {
            if (*pch >= 0xD800 && *pch <= 0xDFFF) {
                // Surrogate pair
                if (pch + 1 >= pend) {
                    result.push_back(BADCHAR_SUBSTITUTE);
                } else if (*pch < 0xDC00) {
                    if (pch[1] >= 0xDC00 && pch[1] <= 0xDFFF)
                        result.push_back(0x10000 + ((pch[0] & 0x3FF) << 10) + (pch[1] & 0x3FF));
                    else
                        result.push_back(BADCHAR_SUBSTITUTE);
                    ++pch;
                } else {
                    if (pch[1] >= 0xD800 && pch[1] <= 0xDBFF)
                        result.push_back(0x10000 + (pch[0] & 0x3FF) + ((pch[1] & 0x3FF) << 10));
                    else
                        result.push_back(BADCHAR_SUBSTITUTE);
                    ++pch;
                }
            } else {
                result.push_back(*pch);
            }
        }

        return result;
    }

    template <typename WcType>
    typename std::enable_if<sizeof(WcType) == sizeof(PRUnichar), PRUnichar *>::type
    nsFromWString(const std::wstring &string)
    {
        PRUnichar *buffer = reinterpret_cast<PRUnichar *>(nsMemory::Alloc((string.size() + 1) * sizeof(PRUnichar)));
        std::char_traits<WcType>::copy(buffer, string.data(), string.size());
        buffer[string.size()] = PRUnichar(0);
        return buffer;
    }

    template <typename WcType>
    typename std::enable_if<sizeof(WcType) >= sizeof(uint32_t), PRUnichar *>::type
    nsFromWString(const std::wstring &string)
    {
        // C++11 provides a way to convert std::wstring UTF-16, but
        // it's cumbersome to use and is deprecated in C++17 with no
        // obvious replacement.
        size_t utf16_length = 0;
        for (wchar_t wch : string) {
            if (static_cast<uint32_t>(wch) >= 0x10000) {
                // Encode with surrogate pair
                utf16_length += 2;
            } else {
                utf16_length += 1;
            }
        }

        PRUnichar *buffer = reinterpret_cast<PRUnichar *>(nsMemory::Alloc((utf16_length + 1) * sizeof(PRUnichar)));
        PRUnichar *bufp = buffer;
        for (wchar_t wch : string) {
            auto uch = static_cast<uint32_t>(wch);
            if (uch >= 0x10000) {
                *bufp++ = static_cast<PRUnichar>(0xD800 | ((uch >> 10) & 0x3FF));
                *bufp++ = static_cast<PRUnichar>(0xDC00 | ((uch      ) & 0x3FF));
            } else {
                *bufp++ = static_cast<PRUnichar>(uch);
            }
        }
        buffer[utf16_length] = PRUnichar(0);

        return buffer;
    }

#   define COM_ToWString(text)      nsToWString<wchar_t>(text)
#   define COM_FromWString(string)  nsFromWString<wchar_t>(string)
#   define COM_FreeString(text)     nsMemory::Free(reinterpret_cast<void *>(text))

#   define COM_GetValue(obj, name, result)                              \
        do {                                                            \
            auto rc = obj->Get##name(&result);                          \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_SetValue(obj, name, value)                               \
        do {                                                            \
            auto rc = obj->Set##name(value);                            \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_GetValue_Wrap(obj, name, result)                         \
        do {                                                            \
            typedef decltype(result) Ptr;                               \
            Ptr::element_type::COM_Ifc *pValue;                         \
            auto rc = obj->Get##name(&pValue);                          \
            COM_ERROR_CHECK(rc);                                        \
            result = Ptr::wrap(pValue);                                 \
        } while (0)

#   define COM_SetValue_Wrap(obj, name, value)                          \
        do {                                                            \
            auto rc = obj->Set##name(value->get_IFC());                 \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_GetString(obj, name, result)                             \
        do {                                                            \
            PRUnichar *buffer;                                          \
            auto rc = obj->Get##name(&buffer);                          \
            COM_ERROR_CHECK(rc);                                        \
            result = nsToWString<wchar_t>(buffer);                      \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_SetString(obj, name, value)                              \
        do {                                                            \
            PRUnichar *buffer = nsFromWString<wchar_t>(value);          \
            auto rc = obj->Set##name(buffer);                           \
            COM_ERROR_CHECK(rc);                                        \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_GetArray_Wrap(obj, name, result)                         \
        do {                                                            \
            PRUint32 count;                                             \
            typedef decltype(result)::value_type Ptr;                   \
            typedef Ptr::element_type::COM_Ifc COM_Ifc;                 \
            COM_Ifc **pArray;                                           \
            auto rc = obj->Get##name(&count, &pArray);                  \
            COM_ERROR_CHECK(rc);                                        \
            COM_ArrayProxy<COM_Ifc *> proxy(count, pArray);             \
            proxy.toVector(result);                                     \
        } while (0)

#   define COM_SetArray_Wrap(obj, name, value)                          \
        do {                                                            \
            typedef decltype(result)::value_type Ptr;                   \
            typedef Ptr::element_type::COM_Ifc COM_Ifc;                 \
            COM_ArrayProxy<COM_Ifc *> proxy;                            \
            proxy.fromVector(value);                                    \
            auto rc = obj->Set##name(proxy.m_count, proxy.m_array);     \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_GetStringArray(obj, name, result)                        \
        do {                                                            \
            PRUint32 count;                                             \
            PRUnichar **buffer;                                         \
            auto rc = obj->Get##name(&count, &buffer);                  \
            COM_ERROR_CHECK(rc);                                        \
            COM_StringArrayProxy proxy(count, buffer);                  \
            proxy.toVector(result);                                     \
        } while (0)

#   define COM_SetStringArray(obj, name, value)                         \
        do {                                                            \
            COM_StringArrayProxy proxy;                                 \
            proxy.fromVector(value);                                    \
            auto rc = obj->Set##name(proxy.m_count,                     \
                        const_cast<const PRUnichar **>(proxy.m_array)); \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_DeclareArray(XPCOM_Type, name)                           \
        PRUint32 name##Count;                                           \
        XPCOM_Type *name##Array

#   define COM_ArrayParameterOut(name)  name##Count, name##Array
#   define COM_ArrayParameterIn(name)   &name##Count, &name##Array

    // Error code compatibility with MSCOM
#   define E_NOINTERFACE    NS_NOINTERFACE

#elif defined(VBOX_MSCOM)
#   define WIN32_LEAN_AND_MEAN
#   include <VirtualBox.h>

#   define COM_ERROR_CHECK(rc)                                          \
        do {                                                            \
            if (FAILED(rc))                                             \
                throw COMError(rc);                                     \
        } while (0)

    typedef BOOL        COM_Bool;
    typedef LONG        COM_Long;
    typedef ULONG       COM_ULong;
    typedef LONG64      COM_Long64;
    typedef ULONG64     COM_ULong64;

#   define COM_Type(XPCOM_Type, MSCOM_Type)  MSCOM_Type

    inline std::wstring BSTRToWString(BSTR text)
    {
        return std::wstring(text, SysStringLen(text));
    }

    inline BSTR BSTRFromWString(const std::wstring &string)
    {
        return SysAllocStringLen(string.data(), static_cast<UINT>(string.size()));
    }

#   define COM_ToWString(text)      BSTRToWString(text)
#   define COM_FromWString(string)  BSTRFromWString(string)
#   define COM_FreeString(text)     SysFreeString(text)

#   define COM_GetValue(obj, name, result)                              \
        do {                                                            \
            auto rc = obj->get_##name(&result);                         \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_SetValue(obj, name, value)                               \
        do {                                                            \
            auto rc = obj->put_##name(value);                           \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_GetValue_Wrap(obj, name, result)                         \
        do {                                                            \
            typedef decltype(result) Ptr;                               \
            Ptr::element_type::COM_Ifc *pValue;                         \
            auto rc = obj->get_##name(&pValue);                         \
            COM_ERROR_CHECK(rc);                                        \
            result = Ptr::wrap(pValue);                                 \
        } while (0)

#   define COM_SetValue_Wrap(obj, name, value)                          \
        do {                                                            \
            auto rc = obj->put_##name(value->get_IFC());                \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_GetString(obj, name, result)                             \
        do {                                                            \
            BSTR buffer;                                                \
            auto rc = obj->get_##name(&buffer);                         \
            COM_ERROR_CHECK(rc);                                        \
            result = BSTRToWString(buffer);                             \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_SetString(obj, name, value)                              \
        do {                                                            \
            BSTR buffer = BSTRFromWString(value);                       \
            auto rc = obj->put_##name(buffer);                          \
            COM_ERROR_CHECK(rc);                                        \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_GetArray_Wrap(obj, name, result)                         \
        do {                                                            \
            SAFEARRAY *array = nullptr;                                 \
            auto rc = obj->get_##name(&array);                          \
            COM_ERROR_CHECK(rc);                                        \
            typedef decltype(result)::value_type Ptr;                   \
            typedef Ptr::element_type::COM_Ifc COM_Ifc;                 \
            COM_ArrayProxy<COM_Ifc *> proxy(array);                     \
            proxy.toVector(result);                                     \
        } while (0)

#   define COM_SetArray_Wrap(obj, name, value)                          \
        do {                                                            \
            typedef decltype(result)::value_type Ptr;                   \
            typedef Ptr::element_type::COM_Ifc COM_Ifc;                 \
            COM_ArrayProxy<COM_Ifc *> proxy;                            \
            proxy.fromVector(value);                                    \
            auto rc = obj->put_##name(proxy.m_array);                   \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_GetStringArray(obj, name, result)                        \
        do {                                                            \
            SAFEARRAY *array = nullptr;                                 \
            auto rc = obj->get_##name(&array);                          \
            COM_ERROR_CHECK(rc);                                        \
            COM_StringArrayProxy proxy(array);                          \
            proxy.toVector(result);                                     \
        } while (0)

#   define COM_SetStringArray(obj, name, value)                         \
        do {                                                            \
            COM_StringArrayProxy proxy;                                 \
            proxy.fromVector(value);                                    \
            auto rc = obj->put_##name(proxy.m_array);                   \
            COM_ERROR_CHECK(rc);                                        \
        } while (0)

#   define COM_DeclareArray(XPCOM_Type, name)                           \
        SAFEARRAY *name;

#   define COM_ArrayParameterOut(name)  name
#   define COM_ArrayParameterIn(name)   &name

#else
#   error Unsupported COM configuration
#endif

namespace VBox
{
    template <typename Element>
    class COM_ArrayProxy
    {
    public:
#if defined(VBOX_XPCOM)
        COM_ArrayProxy() : m_count(), m_array() { }

        COM_ArrayProxy(PRUint32 count, Element *array)
            : m_count(count), m_array(array) { }
#elif defined(VBOX_MSCOM)
        COM_ArrayProxy() : m_array() { }

        COM_ArrayProxy(SAFEARRAY *array)
            : m_array(array) { }
#endif

        ~COM_ArrayProxy() { Release(); }

        void Release()
        {
#if defined(VBOX_XPCOM)
            if (m_array)
                nsMemory::Free(reinterpret_cast<void *>(m_array));
#elif defined(VBOX_MSCOM)
            if (m_array)
                SafeArrayDestroy(m_array);
#endif

            m_array = nullptr;
        }

        template <typename Wrap>
        void toVector(std::vector<COMPtr<Wrap>> &result)
        {
            if (!m_array) {
                result.resize(0);
                return;
            }

#if defined(VBOX_XPCOM)
            result.resize(m_count);
            for (PRUint32 i = 0; i < m_count; ++i)
                result[i] = COMPtr<Wrap>::wrap(m_array[i]);
#elif defined(VBOX_MSCOM)
            COMPtr<Wrap>::element_type::COM_Ifc **pArray = nullptr;
            auto rc = SafeArrayAccessData(m_array, reinterpret_cast<void **>(&pArray));
            COM_ERROR_CHECK(rc);                                        \
            result.resize(m_array->rgsabound[0].cElements);
            for (size_t i = 0; i < result.size(); ++i) {
                pArray[i]->AddRef();
                result[i] = COMPtr<Wrap>::wrap(pArray[i]);
            }
            SafeArrayUnaccessData(m_array);
#endif
        }

        template <typename Wrap>
        void fromVector(const std::vector<COMPtr<Wrap>> &vector)
        {
            Release();

#if defined(VBOX_XPCOM)
            m_count = vector.size();
            m_array = reinterpret_cast<Element *>(nsMemory::Alloc(m_count * sizeof(Element)));
            for (size_t i = 0; i < vector.size(); ++i)
                m_array[i] = vector[i]->get_IFC();
#elif defined(VBOX_MSCOM)
            m_array = SafeArrayCreateVector(VT_UNKNOWN, 0, static_cast<ULONG>(vector.size()));
            COMPtr<Wrap>::element_type::COM_Ifc **pArray = nullptr;
            HRESULT rc = SafeArrayAccessData(m_array, reinterpret_cast<void **>(&pArray));
            COM_ERROR_CHECK(rc);                                        \
            for (size_t i = 0; i < vector.size(); ++i) {
                pArray[i] = vector[i]->get_IFC();
                pArray[i]->AddRef();
            }
            SafeArrayUnaccessData(array);
#endif
        }

    private:
#if defined(VBOX_XPCOM)
        PRUint32 m_count;
        Element *m_array;
#elif defined (VBOX_MSCOM)
        SAFEARRAY *m_array;
#endif
    };

    class COM_StringArrayProxy
    {
    public:
#if defined(VBOX_XPCOM)
        COM_StringArrayProxy() : m_count(), m_array() { }

        COM_StringArrayProxy(PRUint32 count, PRUnichar **array)
            : m_count(count), m_array(array) { }
#elif defined(VBOX_MSCOM)
        COM_StringArrayProxy() : m_array() { }

        COM_StringArrayProxy(SAFEARRAY *array)
            : m_array(array) { }
#endif

        ~COM_StringArrayProxy() { Release(); }

        void Release()
        {
#if defined(VBOX_XPCOM)
            if (m_array) {
                for (PRUint32 i = 0; i < m_count; ++i)
                    nsMemory::Free(reinterpret_cast<void *>(m_array[i]));
                nsMemory::Free(reinterpret_cast<void *>(m_array));
            }
#elif defined(VBOX_MSCOM)
            if (m_array)
                SafeArrayDestroy(m_array);
#endif

            m_array = nullptr;
        }

        void toVector(std::vector<std::wstring> &result)
        {
            if (!m_array) {
                result.resize(0);
                return;
            }

#if defined(VBOX_XPCOM)
            result.resize(m_count);
            for (PRUint32 i = 0; i < m_count; ++i)
                result[i] = nsToWString<wchar_t>(m_array[i]);
#elif defined(VBOX_MSCOM)
            BSTR *pArray = nullptr;
            auto rc = SafeArrayAccessData(m_array, reinterpret_cast<void **>(&pArray));
            COM_ERROR_CHECK(rc);                                        \
            result.resize(m_array->rgsabound[0].cElements);
            for (size_t i = 0; i < result.size(); ++i)
                result[i] = BSTRToWString(pArray[i]);
            SafeArrayUnaccessData(m_array);
#endif
        }

        void fromVector(const std::vector<std::wstring> &vector)
        {
            Release();

#if defined(VBOX_XPCOM)
            m_count = vector.size();
            m_array = reinterpret_cast<PRUnichar **>(nsMemory::Alloc(m_count * sizeof(PRUnichar *)));
            for (size_t i = 0; i < vector.size(); ++i)
                m_array[i] = nsFromWString<wchar_t>(vector[i]);
#elif defined(VBOX_MSCOM)
            m_array = SafeArrayCreateVector(VT_BSTR, 0, static_cast<ULONG>(vector.size()));
            BSTR *pArray = nullptr;
            HRESULT rc = SafeArrayAccessData(m_array, reinterpret_cast<void **>(&pArray));
            COM_ERROR_CHECK(rc);                                        \
            for (size_t i = 0; i < vector.size(); ++i)
                pArray[i] = BSTRFromWString(vector[i]);
            SafeArrayUnaccessData(m_array);
#endif
        }

    public:
#if defined(VBOX_XPCOM)
        PRUint32 m_count;
        PRUnichar **m_array;
#elif defined (VBOX_MSCOM)
        SAFEARRAY *m_array;
#endif
    };
}
