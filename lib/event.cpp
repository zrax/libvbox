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

const void *VBox::IEvent::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IEvent);
}

VBox::VBoxEventType VBox::IEvent::type() const
{
    COM_Type(PRUint32, ::VBoxEventType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<VBoxEventType>(result);
}

VBox::COMPtr<VBox::IEventSource> VBox::IEvent::source() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), Source, result);
    return result;
}

bool VBox::IEvent::waitable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Waitable, result);
    return result;
}

void VBox::IEvent::setProcessed()
{
    auto rc = get_IFC()->SetProcessed();
    COM_ERROR_CHECK(rc);
}

bool VBox::IEvent::waitProcessed(int32_t timeout)
{
    COM_Bool result;
    auto rc = get_IFC()->WaitProcessed(timeout, &result);
    COM_ERROR_CHECK(rc);
    return result;
}
