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

#include "libvbox_string.h"

#if defined(VBOX_XPCOM)
#   include <nsString.h>
#elif defined(VBOX_MSCOM)
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#endif

#define BADCHAR_SUBSTITUTE  wchar_t(0xFFFD)

template <typename WcType>
typename std::enable_if<sizeof(WcType) == sizeof(char16_t), std::wstring>::type
COM_ToWString(const char16_t *text, size_t size)
{
    return std::wstring(reinterpret_cast<const WcType *>(text), size);
}

template <typename WcType>
typename std::enable_if<sizeof(WcType) >= sizeof(uint32_t), std::wstring>::type
COM_ToWString(const char16_t *text, size_t size)
{
    // C++11 provides a way to convert UTF-16 to std::wstring, but
    // it's cumbersome to use and is deprecated in C++17 with no
    // obvious replacement.
    std::wstring result;
    result.reserve(size);

    const char16_t *pch = text;
    const char16_t *pend = text + size;
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
typename std::enable_if<sizeof(WcType) == sizeof(char16_t), std::u16string>::type
COM_FromWString(const WcType *text, size_t size)
{
    return std::u16string(reinterpret_cast<const char16_t *>(text), size);
}

template <typename WcType>
typename std::enable_if<sizeof(WcType) >= sizeof(uint32_t), std::u16string>::type
COM_FromWString(const WcType *text, size_t size)
{
    // C++11 provides a way to convert std::wstring UTF-16, but
    // it's cumbersome to use and is deprecated in C++17 with no
    // obvious replacement.
    size_t utf16_length = 0;
    const WcType *end = text + size;
    for (const WcType *wch = text; wch != end; ++wch) {
        if (static_cast<uint32_t>(*wch) >= 0x10000) {
            // Encode with surrogate pair
            utf16_length += 2;
        } else {
            utf16_length += 1;
        }
    }

    std::u16string buffer;
    buffer.reserve(utf16_length);
    for (const WcType *wch = text; wch != end; ++wch) {
        auto uch = static_cast<uint32_t>(*wch);
        if (uch >= 0x10000) {
            buffer.push_back(static_cast<char16_t>(0xD800 | ((uch >> 10) & 0x3FF)));
            buffer.push_back(static_cast<char16_t>(0xDC00 | ((uch      ) & 0x3FF)));
        } else {
            buffer.push_back(static_cast<char16_t>(uch));
        }
    }

    return buffer;
}

static std::string COM_ToUtf8(const char16_t *text, size_t size)
{
#if defined(VBOX_XPCOM)
    NS_ConvertUTF16toUTF8 conv(reinterpret_cast<const PRUnichar *>(text), size);
    return std::string(conv.get(), conv.Length());
#elif defined(VBOX_MSCOM)
    std::string result;
    int u8size = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t *>(text),
                                     static_cast<int>(size), nullptr, 0,
                                     nullptr, nullptr);
    if (u8size == 0)
        return result;

    result.resize(u8size);
    WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t *>(text),
                        static_cast<int>(size), &result[0], u8size,
                        nullptr, nullptr);
    return result;
#endif
}

static std::u16string COM_FromUtf8(const char *text, size_t size)
{
#if defined(VBOX_XPCOM)
    NS_ConvertUTF8toUTF16 conv(text, size);
    return std::u16string(reinterpret_cast<const char16_t *>(conv.get()), conv.Length());
#elif defined(VBOX_MSCOM)
    std::u16string result;
    int u16size = MultiByteToWideChar(CP_UTF8, 0, text, static_cast<int>(size),
                                      nullptr, 0);
    if (u16size == 0)
        return result;

    result.resize(u16size);
    MultiByteToWideChar(CP_UTF8, 0, text, static_cast<int>(size),
                        reinterpret_cast<LPWSTR>(&result[0]), u16size);
    return result;
#endif
}

VBox::COMString::COMString(const std::wstring &string)
    : m_string(COM_FromWString(string.c_str(), string.size()))
{ }

VBox::COMString::COMString(const wchar_t *cstring)
    : m_string(COM_FromWString(cstring, std::char_traits<wchar_t>::length(cstring)))
{ }

VBox::COMString::COMString(const wchar_t *cstring, size_t size)
    : m_string(COM_FromWString(cstring, size))
{ }

VBox::COMString &VBox::COMString::operator=(const std::wstring &other)
{
    m_string = COM_FromWString(other.c_str(), other.size());
    return *this;
}

VBox::COMString &VBox::COMString::operator=(const wchar_t *other)
{
    m_string = COM_FromWString(other, std::char_traits<wchar_t>::length(other));
    return *this;
}

VBox::COMString VBox::COMString::fromUtf8(const std::string &string)
{
    return COM_FromUtf8(string.data(), string.size());
}

VBox::COMString VBox::COMString::fromUtf8(const char *cstring)
{
    return COM_FromUtf8(cstring, std::char_traits<char>::length(cstring));
}

VBox::COMString VBox::COMString::fromUtf8(const char *cstring, size_t size)
{
    return COM_FromUtf8(cstring, size);
}

std::string VBox::COMString::toUtf8() const
{
    return COM_ToUtf8(data(), size());
}

std::wstring VBox::COMString::toWString() const
{
    return COM_ToWString<wchar_t>(data(), size());
}
