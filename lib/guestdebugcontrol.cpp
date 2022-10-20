/* This file is part of libvbox
 * Copyright (C) 2022  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
COM_WRAP_IFC(IGuestDebugControl)

VBox::GuestDebugProvider VBox::IGuestDebugControl::debugProvider() const
{
    COM_Enum(::GuestDebugProvider) result;
    COM_GetValue(get_IFC(), DebugProvider, result);
    return static_cast<GuestDebugProvider>(result);
}

void VBox::IGuestDebugControl::set_debugProvider(GuestDebugProvider value)
{
    COM_SetValue(get_IFC(), DebugProvider,
                 static_cast<COM_Enum(::GuestDebugProvider)>(value));
}

VBox::GuestDebugIoProvider VBox::IGuestDebugControl::debugIoProvider() const
{
    COM_Enum(::GuestDebugIoProvider) result;
    COM_GetValue(get_IFC(), DebugIoProvider, result);
    return static_cast<GuestDebugIoProvider>(result);
}

void VBox::IGuestDebugControl::set_debugIoProvider(GuestDebugIoProvider value)
{
    COM_SetValue(get_IFC(), DebugIoProvider,
                 static_cast<COM_Enum(::GuestDebugIoProvider)>(value));
}

std::u16string VBox::IGuestDebugControl::debugAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DebugAddress, result);
    return result;
}

void VBox::IGuestDebugControl::set_debugAddress(const std::u16string &value)
{
    COM_SetString(get_IFC(), DebugAddress, value);
}

uint32_t VBox::IGuestDebugControl::debugPort() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), DebugPort, result);
    return static_cast<uint32_t>(result);
}

void VBox::IGuestDebugControl::set_debugPort(uint32_t value)
{
    COM_SetValue(get_IFC(), DebugPort, value);
}
#endif
