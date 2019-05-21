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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
COM_WRAP_IFC(IGuestScreenInfo)

uint32_t VBox::IGuestScreenInfo::screenId() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ScreenId, result);
    return static_cast<uint32_t>(result);
}

VBox::GuestMonitorStatus VBox::IGuestScreenInfo::guestMonitorStatus() const
{
    COM_Enum(::GuestMonitorStatus) result;
    COM_GetValue(get_IFC(), GuestMonitorStatus, result);
    return static_cast<GuestMonitorStatus>(result);
}

bool VBox::IGuestScreenInfo::primary() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Primary, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestScreenInfo::origin() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Origin, result);
    return static_cast<bool>(result);
}

int32_t VBox::IGuestScreenInfo::originX() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), OriginX, result);
    return static_cast<int32_t>(result);
}

int32_t VBox::IGuestScreenInfo::originY() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), OriginY, result);
    return static_cast<int32_t>(result);
}

uint32_t VBox::IGuestScreenInfo::width() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Width, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestScreenInfo::height() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Height, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestScreenInfo::bitsPerPixel() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), BitsPerPixel, result);
    return static_cast<uint32_t>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
std::u16string VBox::IGuestScreenInfo::extendedInfo() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ExtendedInfo, result);
    return result;
}
#endif
#endif
