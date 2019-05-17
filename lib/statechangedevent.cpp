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

COM_WRAP_IFC(IStateChangedEvent)
COM_WRAP_IFC(IAdditionsStateChangedEvent)
COM_WRAP_IFC(IUSBDeviceStateChangedEvent)
COM_WRAP_IFC(IVBoxSVCAvailabilityChangedEvent)

VBox::MachineState VBox::IStateChangedEvent::state() const
{
    COM_Enum(::MachineState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<MachineState>(result);
}

VBox::COMPtr<VBox::IUSBDevice> VBox::IUSBDeviceStateChangedEvent::device() const
{
    COMPtr<IUSBDevice> result;
    COM_GetValue_Wrap(get_IFC(), Device, result);
    return result;
}

bool VBox::IUSBDeviceStateChangedEvent::attached() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Attached, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo>
VBox::IUSBDeviceStateChangedEvent::error() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), Error, result);
    return result;
}

bool VBox::IVBoxSVCAvailabilityChangedEvent::available() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Available, result);
    return static_cast<bool>(result);
}
