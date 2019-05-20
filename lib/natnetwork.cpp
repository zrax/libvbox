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

COM_WRAP_IFC(INATNetwork)

std::u16string VBox::INATNetwork::networkName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkName, result);
    return result;
}

void VBox::INATNetwork::set_networkName(const std::u16string &value)
{
    COM_SetString(get_IFC(), NetworkName, value);
}

bool VBox::INATNetwork::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::INATNetwork::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

std::u16string VBox::INATNetwork::network() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Network, result);
    return result;
}

void VBox::INATNetwork::set_network(const std::u16string &value)
{
    COM_SetString(get_IFC(), Network, value);
}

std::u16string VBox::INATNetwork::gateway() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Gateway, result);
    return result;
}

bool VBox::INATNetwork::IPv6Enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IPv6Enabled, result);
    return static_cast<bool>(result);
}

void VBox::INATNetwork::set_IPv6Enabled(bool value)
{
    COM_SetValue(get_IFC(), IPv6Enabled, value);
}

std::u16string VBox::INATNetwork::IPv6Prefix() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IPv6Prefix, result);
    return result;
}

void VBox::INATNetwork::set_IPv6Prefix(const std::u16string &value)
{
    COM_SetString(get_IFC(), IPv6Prefix, value);
}

bool VBox::INATNetwork::advertiseDefaultIPv6RouteEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AdvertiseDefaultIPv6RouteEnabled, result);
    return static_cast<bool>(result);
}

void VBox::INATNetwork::set_advertiseDefaultIPv6RouteEnabled(bool value)
{
    COM_SetValue(get_IFC(), AdvertiseDefaultIPv6RouteEnabled, value);
}

bool VBox::INATNetwork::needDhcpServer() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), NeedDhcpServer, result);
    return static_cast<bool>(result);
}

void VBox::INATNetwork::set_needDhcpServer(bool value)
{
    COM_SetValue(get_IFC(), NeedDhcpServer, value);
}

VBox::COMPtr<VBox::IEventSource> VBox::INATNetwork::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

std::vector<std::u16string> VBox::INATNetwork::portForwardRules4() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), PortForwardRules4, result);
    return result;
}

std::vector<std::u16string> VBox::INATNetwork::localMappings() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), LocalMappings, result);
    return result;
}

int32_t VBox::INATNetwork::loopbackIp6() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), LoopbackIp6, result);
    return static_cast<int32_t>(result);
}

void VBox::INATNetwork::set_loopbackIp6(int32_t value)
{
    COM_SetValue(get_IFC(), LoopbackIp6, static_cast<COM_Long>(value));
}

std::vector<std::u16string> VBox::INATNetwork::portForwardRules6() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), PortForwardRules6, result);
    return result;
}

void VBox::INATNetwork::addLocalMapping(const std::u16string &hostid,
        int32_t offset)
{
    COM_StringProxy pHostid(hostid);

    auto rc = get_IFC()->AddLocalMapping(pHostid.m_text, offset);
    COM_ERROR_CHECK(rc);
}

void VBox::INATNetwork::addPortForwardRule(bool isIpv6,
        const std::u16string &ruleName, NATProtocol proto,
        const std::u16string &hostIP, uint16_t hostPort,
        const std::u16string &guestIP, uint16_t guestPort)
{
    COM_StringProxy pRuleName(ruleName);
    auto cProto = static_cast<COM_Enum(::NATProtocol)>(proto);
    COM_StringProxy pHostIP(hostIP);
    COM_StringProxy pGuestIP(guestIP);

    auto rc = get_IFC()->AddPortForwardRule(isIpv6, pRuleName.m_text, cProto,
                pHostIP.m_text, hostPort, pGuestIP.m_text, guestPort);
    COM_ERROR_CHECK(rc);
}

void VBox::INATNetwork::removePortForwardRule(bool iSipv6,
        const std::u16string &ruleName)
{
    COM_StringProxy pRuleName(ruleName);

    auto rc = get_IFC()->RemovePortForwardRule(iSipv6, pRuleName.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::INATNetwork::start(const std::u16string &trunkType)
{
    COM_StringProxy pTrunkType(trunkType);

    auto rc = get_IFC()->Start(pTrunkType.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::INATNetwork::stop()
{
    auto rc = get_IFC()->Stop();
    COM_ERROR_CHECK(rc);
}
