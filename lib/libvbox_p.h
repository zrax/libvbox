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

#   define COM_GetValue(obj, name, result)                              \
        do {                                                            \
            auto rc = obj->Get##name(&result);                          \
            if (NS_FAILED(rc))                                          \
                throw COMError(rc);                                     \
        } while (0)

#   define COM_GetValue_Wrap(obj, name, result)                         \
        do {                                                            \
            typedef decltype(result) Ptr;                               \
            Ptr::element_type::COM_Ifc *pValue;                         \
            auto rc = obj->Get##name(&pValue);                          \
            if (NS_FAILED(rc))                                          \
                throw COMError(rc);                                     \
            result = Ptr::wrap(pValue);                                 \
        } while (0)

#   define COM_GetString(obj, name, result)                             \
        do {                                                            \
            PRUnichar *buffer;                                          \
            auto rc = obj->Get##name(&buffer);                          \
            if (NS_FAILED(rc))                                          \
                throw COMError(rc);                                     \
            result = nsToWString<wchar_t>(buffer);                      \
            nsMemory::Free(reinterpret_cast<void *>(buffer));           \
        } while (0)

#   define COM_GetArray_Wrap(obj, name, result)                         \
        do {                                                            \
            PRUint32 count;                                             \
            typedef decltype(result)::value_type Ptr;                   \
            Ptr::element_type::COM_Ifc **pArray;                        \
            auto rc = obj->Get##name(&count, &pArray);                  \
            if (NS_FAILED(rc))                                          \
                throw COMError(rc);                                     \
            result.resize(count);                                       \
            for (PRUint32 i = 0; i < count; ++i)                        \
                result[i] = Ptr::wrap(pArray[i]);                       \
            nsMemory::Free(reinterpret_cast<void *>(pArray));           \
        } while (0)

#   define COM_GetStringArray(obj, name, result)                        \
        do {                                                            \
            PRUint32 count;                                             \
            PRUnichar **buffer;                                         \
            auto rc = obj->Get##name(&count, &buffer);                  \
            if (NS_FAILED(rc))                                          \
                throw COMError(rc);                                     \
            result.resize(count);                                       \
            for (PRUint32 i = 0; i < count; ++i) {                      \
                result[i] = nsToWString<wchar_t>(buffer[i]);            \
                nsMemory::Free(reinterpret_cast<void *>(buffer[i]));    \
            }                                                           \
            nsMemory::Free(reinterpret_cast<void *>(buffer));           \
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

#else
#   error Unsupported COM configuration
#endif
