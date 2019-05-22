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

COM_WRAP_IFC(IPCIDeviceAttachment)

std::u16string VBox::IPCIDeviceAttachment::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

bool VBox::IPCIDeviceAttachment::isPhysicalDevice() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsPhysicalDevice, result);
    return static_cast<bool>(result);
}

int32_t VBox::IPCIDeviceAttachment::hostAddress() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), HostAddress, result);
    return static_cast<int32_t>(result);
}

int32_t VBox::IPCIDeviceAttachment::guestAddress() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), GuestAddress, result);
    return static_cast<int32_t>(result);
}
