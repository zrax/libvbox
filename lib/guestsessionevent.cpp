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

COM_WRAP_IFC(IGuestSessionEvent)
COM_WRAP_IFC(IGuestSessionStateChangedEvent)
COM_WRAP_IFC(IGuestSessionRegisteredEvent)

VBox::COMPtr<VBox::IGuestSession> VBox::IGuestSessionEvent::session() const
{
    COMPtr<IGuestSession> result;
    COM_GetValue_Wrap(get_IFC(), Session, result);
    return result;
}

uint32_t VBox::IGuestSessionStateChangedEvent::id() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Id, result);
    return static_cast<uint32_t>(result);
}

VBox::GuestSessionStatus VBox::IGuestSessionStateChangedEvent::status() const
{
    COM_Enum(::GuestSessionStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<GuestSessionStatus>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo>
VBox::IGuestSessionStateChangedEvent::error() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), Error, result);
    return result;
}

bool VBox::IGuestSessionRegisteredEvent::registered() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Registered, result);
    return result;
}
