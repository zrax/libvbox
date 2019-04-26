
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

#ifndef _LIBVBOX_STRING_H
#define _LIBVBOX_STRING_H

#include <string>

#include "libvbox_vboxsdk_version.h"

namespace VBox
{
    class LIBVBOX_API COMString
    {
    public:
        COMString() { }
        COMString(const COMString &other) : m_string(other.m_string) { }
        COMString(COMString &&other) : m_string(std::move(other.m_string)) { }

        COMString(const std::u16string &string) : m_string(string) { }
        COMString(std::u16string &&string) : m_string(std::move(string)) { }

        COMString(const char16_t *cstring) : m_string(cstring) { }
        COMString(const char16_t *cstring, size_t size) : m_string(cstring, size) { }

        COMString &operator=(const COMString &other)
        {
            m_string = other.m_string;
            return *this;
        }

        COMString &operator=(COMString &&other)
        {
            m_string = std::move(other.m_string);
            return *this;
        }

        COMString &operator=(const std::u16string &other)
        {
            m_string = other;
            return *this;
        }

        COMString &operator=(std::u16string &&other)
        {
            m_string = std::move(other);
            return *this;
        }

        COMString &operator=(const char16_t *cstring)
        {
            m_string = cstring;
            return *this;
        }

        inline bool operator==(const VBox::COMString &other) const
        {
            return m_string == other.m_string;
        }

        inline bool operator!=(const VBox::COMString &other) const
        {
            return m_string != other.m_string;
        }

        inline bool operator<(const VBox::COMString &other) const
        {
            return m_string < other.m_string;
        }

        static COMString fromUtf8(const std::string &string);
        static COMString fromUtf8(const char *cstring);
        static COMString fromUtf8(const char *cstring, size_t size);

        static COMString fromUtf16(const std::u16string &string)
        {
            return COMString(string);
        }

        static COMString fromUtf16(std::u16string &&string)
        {
            return COMString(std::move(string));
        }

        static COMString fromUtf16(const char16_t *cstring)
        {
            return COMString(cstring);
        }

        static COMString fromUtf16(const char16_t *cstring, size_t size)
        {
             return COMString(cstring, size);
        }

        static COMString fromWString(const std::wstring &string);
        static COMString fromWString(const wchar_t *cstring);
        static COMString fromWString(const wchar_t *cstring, size_t size);

        std::string toUtf8() const;
        std::u16string toUtf16() const { return m_string; }
        std::wstring toWString() const;

        std::u16string &get() { return m_string; }
        const std::u16string &get() const { return m_string; }

        const char16_t *c_str() const { return m_string.c_str(); }
        const char16_t *data() const { return m_string.data(); }
        size_t size() const { return m_string.size(); }

    private:
#if _MSC_VER
        // We already rely on STL in the public interfaces, which is brought in
        // by the MSVC runtime, so this warning is meaningless to us.
#       pragma warning(push)
#       pragma warning(disable: 4251)
#endif
        std::u16string m_string;
#if _MSC_VER
#       pragma warning(pop)
#endif
    };
}

namespace std
{
    template <>
    struct hash<VBox::COMString>
    {
        size_t operator()(const VBox::COMString &value) const noexcept
        {
            return std::hash<std::u16string>{}(value.get());
        }
    };
}

#endif // _LIBVBOX_STRING_H
