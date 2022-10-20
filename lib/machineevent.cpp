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

COM_WRAP_IFC(IMachineEvent)
COM_WRAP_IFC(IMachineStateChangedEvent)
COM_WRAP_IFC(IMachineDataChangedEvent)
COM_WRAP_IFC(IMachineRegisteredEvent)
COM_WRAP_IFC(ISessionStateChangedEvent)
COM_WRAP_IFC(IGuestPropertyChangedEvent)

std::u16string VBox::IMachineEvent::machineId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MachineId, result);
    return result;
}

VBox::MachineState VBox::IMachineStateChangedEvent::state() const
{
    COM_Enum(::MachineState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<MachineState>(result);
}

bool VBox::IMachineDataChangedEvent::temporary() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Temporary, result);
    return static_cast<bool>(result);
}

bool VBox::IMachineRegisteredEvent::registered() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Registered, result);
    return static_cast<bool>(result);
}

VBox::SessionState VBox::ISessionStateChangedEvent::state() const
{
    COM_Enum(::SessionState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<SessionState>(result);
}

std::u16string VBox::IGuestPropertyChangedEvent::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::IGuestPropertyChangedEvent::value() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Value, result);
    return result;
}

std::u16string VBox::IGuestPropertyChangedEvent::flags() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Flags, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
bool VBox::IGuestPropertyChangedEvent::fWasDeleted() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), FWasDeleted, result);
    return static_cast<bool>(result);
}
#endif
