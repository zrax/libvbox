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

const void *VBox::ISession::get_IID()
{
    return reinterpret_cast<const void *>(&IID_ISession);
}

VBox::SessionState VBox::ISession::state() const
{
    COM_Type(PRUint32, ::SessionState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<SessionState>(result);
}

VBox::SessionType VBox::ISession::type() const
{
    COM_Type(PRUint32, ::SessionType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<SessionType>(result);
}

std::wstring VBox::ISession::name() const
{
    std::wstring result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::ISession::set_name(const std::wstring &value)
{
    COM_SetString(get_IFC(), Name, value);
}

VBox::COMPtr<VBox::IMachine> VBox::ISession::machine() const
{
    COMPtr<IMachine> result;
    COM_GetValue_Wrap(get_IFC(), Machine, result);
    return result;
}

VBox::COMPtr<VBox::IConsole> VBox::ISession::console() const
{
    COMPtr<IConsole> result;
    COM_GetValue_Wrap(get_IFC(), Console, result);
    return result;
}

void VBox::ISession::unlockMachine()
{
    auto rc = get_IFC()->UnlockMachine();
    COM_ERROR_CHECK(rc);
}
