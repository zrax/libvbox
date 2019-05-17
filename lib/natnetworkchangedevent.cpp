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

COM_WRAP_IFC(INATNetworkChangedEvent)
COM_WRAP_IFC(INATNetworkStartStopEvent)
COM_WRAP_IFC(INATNetworkAlterEvent)
COM_WRAP_IFC(INATNetworkCreationDeletionEvent)
COM_WRAP_IFC(INATNetworkSettingEvent)
COM_WRAP_IFC(INATNetworkPortForwardEvent)

std::u16string VBox::INATNetworkChangedEvent::networkName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkName, result);
    return result;
}

bool VBox::INATNetworkStartStopEvent::startEvent() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), StartEvent, result);
    return static_cast<bool>(result);
}

bool VBox::INATNetworkCreationDeletionEvent::creationEvent() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), CreationEvent, result);
    return static_cast<bool>(result);
}

bool VBox::INATNetworkSettingEvent::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

std::u16string VBox::INATNetworkSettingEvent::network() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Network, result);
    return result;
}

std::u16string VBox::INATNetworkSettingEvent::gateway() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Gateway, result);
    return result;
}

bool VBox::INATNetworkSettingEvent::advertiseDefaultIPv6RouteEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AdvertiseDefaultIPv6RouteEnabled, result);
    return static_cast<bool>(result);
}

bool VBox::INATNetworkSettingEvent::needDhcpServer() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), NeedDhcpServer, result);
    return static_cast<bool>(result);
}

bool VBox::INATNetworkPortForwardEvent::create() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Create, result);
    return static_cast<bool>(result);
}

bool VBox::INATNetworkPortForwardEvent::ipv6() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Ipv6, result);
    return static_cast<bool>(result);
}

std::u16string VBox::INATNetworkPortForwardEvent::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

VBox::NATProtocol VBox::INATNetworkPortForwardEvent::proto() const
{
    COM_Enum(::NATProtocol) result;
    COM_GetValue(get_IFC(), Proto, result);
    return static_cast<NATProtocol>(result);
}

std::u16string VBox::INATNetworkPortForwardEvent::hostIp() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HostIp, result);
    return result;
}

int32_t VBox::INATNetworkPortForwardEvent::hostPort() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), HostPort, result);
    return static_cast<int32_t>(result);
}

std::u16string VBox::INATNetworkPortForwardEvent::guestIp() const
{
    std::u16string result;
    COM_GetString(get_IFC(), GuestIp, result);
    return result;
}

int32_t VBox::INATNetworkPortForwardEvent::guestPort() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), GuestPort, result);
    return static_cast<int32_t>(result);
}
