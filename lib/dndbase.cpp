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

#include "libvbox_p.h"

COM_WRAP_IFC(IDnDBase)

std::vector<std::u16string> VBox::IDnDBase::formats() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Formats, result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
uint32_t VBox::IDnDBase::protocolVersion() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ProtocolVersion, result);
    return static_cast<uint32_t>(result);
}
#endif

bool VBox::IDnDBase::isFormatSupported(const std::u16string &format)
{
    COM_Bool cResult;
    COM_StringProxy pFormat(format);

    auto rc = get_IFC()->IsFormatSupported(pFormat.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IDnDBase::addFormats(const std::vector<std::u16string> &formats)
{
    COM_StringArrayProxy pFormats(formats);

    auto rc = get_IFC()->AddFormats(COM_ArrayParameter(pFormats));
    COM_ERROR_CHECK(rc);
}

void VBox::IDnDBase::removeFormats(const std::vector<std::u16string> &formats)
{
    COM_StringArrayProxy pFormats(formats);

    auto rc = get_IFC()->RemoveFormats(COM_ArrayParameter(pFormats));
    COM_ERROR_CHECK(rc);
}
