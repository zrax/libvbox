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

#   define COM_FAILED(x)    NS_FAILED(x)
#   define COM_SUCCEEDED(x) NS_SUCCEEDED(x)

    typedef PRBool      COM_Bool;
    typedef PRInt32     COM_Long;
    typedef PRUint32    COM_ULong;
    typedef PRInt64     COM_Long64;
    typedef PRUint64    COM_ULong64;

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
        PRUnichar *buffer = reinterpret_cast<PRUnichar *>(nsMemory::Alloc(string.size() + 1));
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

        PRUnichar *buffer = reinterpret_cast<PRUnichar *>(nsMemory::Alloc(utf16_length + 1));
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
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_SetValue(obj, name, value)                               \
        do {                                                            \
            auto rc = obj->Set##name(value);                            \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_GetValue_Wrap(obj, name, result)                         \
        do {                                                            \
            typedef decltype(result) Ptr;                               \
            Ptr::element_type::COM_Ifc *pValue;                         \
            auto rc = obj->Get##name(&pValue);                          \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            result = Ptr::wrap(pValue);                                 \
        } while (0)

#   define COM_SetValue_Wrap(obj, name, value)                          \
        do {                                                            \
            auto rc = obj->Set##name(value->get_IFC());                 \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_GetString(obj, name, result)                             \
        do {                                                            \
            PRUnichar *buffer;                                          \
            auto rc = obj->Get##name(&buffer);                          \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            result = nsToWString<wchar_t>(buffer);                      \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_SetString(obj, name, value)                              \
        do {                                                            \
            PRUnichar *buffer = nsFromWString<wchar_t>(value);          \
            auto rc = obj->Set##name(buffer);                           \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_GetArray_Wrap(obj, name, result)                         \
        do {                                                            \
            PRUint32 count;                                             \
            typedef decltype(result)::value_type Ptr;                   \
            Ptr::element_type::COM_Ifc **pArray;                        \
            auto rc = obj->Get##name(&count, &pArray);                  \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            result.resize(count);                                       \
            for (PRUint32 i = 0; i < count; ++i)                        \
                result[i] = Ptr::wrap(pArray[i]);                       \
            nsMemory::Free(reinterpret_cast<void *>(pArray));           \
        } while (0)

#   define COM_SetArray_Wrap(obj, name, value)                          \
        do {                                                            \
            typedef decltype(result)::value_type Ptr;                   \
            std::vector<Ptr::element_type::COM_Ifc *> array;            \
            array.resize(value.size());                                 \
            for (size_t i = 0; i < value.size(); ++i)                   \
                array[i] = value[i]->get_IFC());                        \
            auto rc = obj->Set##name(array.size(), array.data());       \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_GetStringArray(obj, name, result)                        \
        do {                                                            \
            PRUint32 count;                                             \
            PRUnichar **buffer;                                         \
            auto rc = obj->Get##name(&count, &buffer);                  \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            result.resize(count);                                       \
            for (PRUint32 i = 0; i < count; ++i) {                      \
                result[i] = nsToWString<wchar_t>(buffer[i]);            \
                COM_FreeString(buffer[i]);                              \
            }                                                           \
            nsMemory::Free(reinterpret_cast<void *>(buffer));           \
        } while (0)

#   define COM_SetStringArray(obj, name, value)                         \
        do {                                                            \
            std::vector<PRUnichar *> buffer;                            \
            buffer.resize(value.size());                                \
            for (size_t i = 0; i < value.size(); ++i)                   \
                buffer[i] = nsFromWString<wchar_t>(value[i]);           \
            auto rc = obj->Set##name(buffer.size(),                     \
                        const_cast<const PRUnichar **>(buffer.data())); \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            for (size_t i = 0; i < value.size(); ++i)                   \
                COM_FreeString(buffer[i]);                              \
        } while (0)

#elif defined(VBOX_MSCOM)
#   define WIN32_LEAN_AND_MEAN
#   include <VirtualBox.h>

#   define COM_FAILED(x)    FAILED(x)
#   define COM_SUCCEEDED(x) SUCCEEDED(x)

    typedef BOOL        COM_Bool;
    typedef LONG        COM_Long;
    typedef ULONG       COM_ULong;
    typedef LONG64      COM_Long64;
    typedef ULONG64     COM_ULong64;

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
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_SetValue(obj, name, value)                               \
        do {                                                            \
            auto rc = obj->put_##name(value);                           \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_GetValue_Wrap(obj, name, result)                         \
        do {                                                            \
            typedef decltype(result) Ptr;                               \
            Ptr::element_type::COM_Ifc *pValue;                         \
            auto rc = obj->get_##name(&pValue);                         \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            result = Ptr::wrap(pValue);                                 \
        } while (0)

#   define COM_SetValue_Wrap(obj, name, value)                          \
        do {                                                            \
            auto rc = obj->put_##name(value->get_IFC());                \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_GetString(obj, name, result)                             \
        do {                                                            \
            BSTR buffer;                                                \
            auto rc = obj->get_##name(&buffer);                         \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            result = BSTRToWString(buffer);                             \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_SetString(obj, name, value)                              \
        do {                                                            \
            BSTR buffer = BSTRFromWString(value);                       \
            auto rc = obj->put_##name(buffer);                          \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            COM_FreeString(buffer);                                     \
        } while (0)

#   define COM_GetArray_Wrap(obj, name, result)                         \
        do {                                                            \
            SAFEARRAY *array;                                           \
            auto rc = obj->get_##name(&array);                          \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            typedef decltype(result)::value_type Ptr;                   \
            Ptr::element_type::COM_Ifc **pArray;                        \
            rc = SafeArrayAccessData(array, reinterpret_cast<void **>(&pArray)); \
            if (COM_FAILED(rc)) {                                       \
                SafeArrayDestroy(array);                                \
                throw COMError(rc);                                     \
            }                                                           \
            result.resize(array->rgsabound[0].cElements);               \
            for (size_t i = 0; i < result.size(); ++i)                  \
                result[i] = Ptr::wrap(pArray[i]);                       \
            SafeArrayUnaccessData(array);                               \
            SafeArrayDestroy(array);                                    \
        } while (0)

#   define COM_SetArray_Wrap(obj, name, value)                          \
        do {                                                            \
            SAFEARRAY *array = SafeArrayCreateVector(VT_UNKNOWN, 0,     \
                                    static_cast<ULONG>(value.size()));  \
            typedef decltype(result)::value_type Ptr;                   \
            Ptr::element_type::COM_Ifc **pArray;                        \
            HRESULT rc = SafeArrayAccessData(array, reinterpret_cast<void **>(&pArray)); \
            if (COM_FAILED(rc)) {                                       \
                SafeArrayDestroy(array);                                \
                throw COMError(rc);                                     \
            }                                                           \
            for (size_t i = 0; i < value.size(); ++i)                   \
                pArray[i] = value[i]->get_IFC());                       \
            SafeArrayUnaccessData(array);                               \
            auto result = obj->put_##name(array);                       \
            SafeArrayDestroy(array);                                    \
            if (COM_FAILED(result))                                     \
                throw COMError(result);                                 \
        } while (0)

#   define COM_GetStringArray(obj, name, result)                        \
        do {                                                            \
            SAFEARRAY *array;                                           \
            auto rc = obj->get_##name(&array);                          \
            if (COM_FAILED(rc))                                         \
                throw COMError(rc);                                     \
            BSTR *pArray;                                               \
            rc = SafeArrayAccessData(array, reinterpret_cast<void **>(&pArray)); \
            if (COM_FAILED(rc)) {                                       \
                SafeArrayDestroy(array);                                \
                throw COMError(rc);                                     \
            }                                                           \
            result.resize(array->rgsabound[0].cElements);               \
            for (size_t i = 0; i < result.size(); ++i) {                \
                result[i] = BSTRToWString(pArray[i]);                   \
                COM_FreeString(pArray[i]);                              \
            }                                                           \
            SafeArrayUnaccessData(array);                               \
            SafeArrayDestroy(array);                                    \
        } while (0)

#   define COM_SetStringArray(obj, name, value)                         \
        do {                                                            \
            SAFEARRAY *array = SafeArrayCreateVector(VT_BSTR, 0,        \
                                    static_cast<ULONG>(value.size()));  \
            BSTR *pArray;                                               \
            HRESULT rc = SafeArrayAccessData(array, reinterpret_cast<void **>(&pArray)); \
            if (COM_FAILED(rc)) {                                       \
                SafeArrayDestroy(array);                                \
                throw COMError(rc);                                     \
            }                                                           \
            for (size_t i = 0; i < value.size(); ++i)                   \
                pArray[i] = BSTRFromWString(value[i]);                  \
            SafeArrayUnaccessData(array);                               \
            auto result = obj->put_##name(array);                       \
            rc = SafeArrayAccessData(array, reinterpret_cast<void **>(&pArray)); \
            if (COM_FAILED(rc)) {                                       \
                SafeArrayDestroy(array);                                \
                throw COMError(rc);                                     \
            }                                                           \
            for (size_t i = 0; i < value.size(); ++i)                   \
                COM_FreeString(pArray[i]);                              \
            SafeArrayUnaccessData(array);                               \
            SafeArrayDestroy(array);                                    \
            if (COM_FAILED(result))                                     \
                throw COMError(result);                                 \
        } while (0)

#else
#   error Unsupported COM configuration
#endif
