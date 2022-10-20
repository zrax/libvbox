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
COM_WRAP_IFC(IHostOnlyNetwork)

std::u16string VBox::IHostOnlyNetwork::networkName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkName, result);
    return result;
}

void VBox::IHostOnlyNetwork::set_networkName(const std::u16string &value)
{
    COM_SetString(get_IFC(), NetworkName, value);
}

bool VBox::IHostOnlyNetwork::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IHostOnlyNetwork::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

std::u16string VBox::IHostOnlyNetwork::networkMask() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkMask, result);
    return result;
}

void VBox::IHostOnlyNetwork::set_networkMask(const std::u16string &value)
{
    COM_SetString(get_IFC(), NetworkMask, value);
}

std::u16string VBox::IHostOnlyNetwork::hostIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HostIP, result);
    return result;
}

std::u16string VBox::IHostOnlyNetwork::lowerIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LowerIP, result);
    return result;
}

void VBox::IHostOnlyNetwork::set_lowerIP(const std::u16string &value)
{
    COM_SetString(get_IFC(), LowerIP, value);
}

std::u16string VBox::IHostOnlyNetwork::upperIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), UpperIP, result);
    return result;
}

void VBox::IHostOnlyNetwork::set_upperIP(const std::u16string &value)
{
    COM_SetString(get_IFC(), UpperIP, value);
}

std::u16string VBox::IHostOnlyNetwork::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

void VBox::IHostOnlyNetwork::set_id(const std::u16string &value)
{
    COM_SetString(get_IFC(), Id, value);
}
#endif
