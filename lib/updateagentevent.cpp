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
COM_WRAP_IFC(IUpdateAgentEvent)
COM_WRAP_IFC(IUpdateAgentSettingsChangedEvent)
COM_WRAP_IFC(IUpdateAgentErrorEvent)
COM_WRAP_IFC(IUpdateAgentStateChangedEvent)

VBox::COMPtr<VBox::IUpdateAgent> VBox::IUpdateAgentEvent::agent() const
{
    COMPtr<IUpdateAgent> result;
    COM_GetValue_Wrap(get_IFC(), Agent, result);
    return result;
}

std::u16string VBox::IUpdateAgentSettingsChangedEvent::attributeHint() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AttributeHint, result);
    return result;
}

std::u16string VBox::IUpdateAgentErrorEvent::msg() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Msg, result);
    return result;
}

int32_t VBox::IUpdateAgentErrorEvent::rcError() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), RcError, result);
    return result;
}

VBox::UpdateState VBox::IUpdateAgentStateChangedEvent::state() const
{
    COM_Enum(::UpdateState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<UpdateState>(result);
}
#endif
