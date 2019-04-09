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

const void *VBox::IMachine::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IMachine);
}

VBox::COMPtr<VBox::IVirtualBox> VBox::IMachine::parent() const
{
    COMPtr<IVirtualBox> result;
    COM_GetValue_Wrap(get_IFC(), Parent, result);
    return result;
}

std::vector<uint8_t> VBox::IMachine::icon() const
{
    std::vector<uint8_t> result;
    COM_GetArray(get_IFC(), Icon, result);
    return result;
}

void VBox::IMachine::set_icon(const std::vector<uint8_t> &value)
{
    COM_SetArray(get_IFC(), Icon, value);
}

bool VBox::IMachine::accessible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accessible, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo> VBox::IMachine::accessError() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), AccessError, result);
    return result;
}

std::wstring VBox::IMachine::name() const
{
    std::wstring result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IMachine::set_name(const std::wstring &value)
{
    COM_SetString(get_IFC(), Name, value);
}

std::wstring VBox::IMachine::description() const
{
    std::wstring result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

void VBox::IMachine::set_description(const std::wstring &value)
{
    COM_SetString(get_IFC(), Description, value);
}

std::wstring VBox::IMachine::id() const
{
    std::wstring result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::vector<std::wstring> VBox::IMachine::groups() const
{
    std::vector<std::wstring> result;
    COM_GetStringArray(get_IFC(), Groups, result);
    return result;
}

void VBox::IMachine::set_groups(const std::vector<std::wstring> &value)
{
    COM_SetStringArray(get_IFC(), Groups, value);
}
