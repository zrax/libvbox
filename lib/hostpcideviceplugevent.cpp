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

COM_WRAP_IFC(IHostPCIDevicePlugEvent)

bool VBox::IHostPCIDevicePlugEvent::plugged() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Plugged, result);
    return result;
}

bool VBox::IHostPCIDevicePlugEvent::success() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Success, result);
    return result;
}

VBox::COMPtr<VBox::IPCIDeviceAttachment>
VBox::IHostPCIDevicePlugEvent::attachment() const
{
    COMPtr<IPCIDeviceAttachment> result;
    COM_GetValue_Wrap(get_IFC(), Attachment, result);
    return result;
}

std::u16string VBox::IHostPCIDevicePlugEvent::message() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Message, result);
    return result;
}
