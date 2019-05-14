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

#ifndef _LIBVBOX_H
#define _LIBVBOX_H

#include "libvbox_interfaces.h"
#include "libvbox_errors.h"

namespace VBox
{
    LIBVBOX_API COMPtr<IVirtualBoxClient> virtualBoxClient();
    LIBVBOX_API COMPtr<COMErrorInfo> currentError();

    // Provided by MSCOM/XPCOM
    LIBVBOX_API std::string utf16ToUtf8(const std::u16string &text);
    LIBVBOX_API std::u16string utf8ToUtf16(const std::string &text);
    LIBVBOX_API std::u16string utf8ToUtf16(const char *text, size_t size);
    LIBVBOX_API std::u16string utf8ToUtf16(const char *text);

    // Provided by libvbox
    LIBVBOX_API std::wstring utf16ToWide(const std::u16string &text);
    LIBVBOX_API std::u16string wideToUtf16(const std::wstring &text);
    LIBVBOX_API std::u16string wideToUtf16(const wchar_t *text, size_t size);
    LIBVBOX_API std::u16string wideToUtf16(const wchar_t *text);
}

#endif /* _LIBVBOX_H */
