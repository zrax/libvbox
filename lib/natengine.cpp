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

COM_WRAP_IFC(INATEngine)

std::u16string VBox::INATEngine::network() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Network, result);
    return result;
}

void VBox::INATEngine::set_network(const std::u16string &value)
{
    COM_SetString(get_IFC(), Network, value);
}

std::u16string VBox::INATEngine::hostIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HostIP, result);
    return result;
}

void VBox::INATEngine::set_hostIP(const std::u16string &value)
{
    COM_SetString(get_IFC(), HostIP, value);
}

std::u16string VBox::INATEngine::TFTPPrefix() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TFTPPrefix, result);
    return result;
}

void VBox::INATEngine::set_TFTPPrefix(const std::u16string &value)
{
    COM_SetString(get_IFC(), TFTPPrefix, value);
}

std::u16string VBox::INATEngine::TFTPBootFile() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TFTPBootFile, result);
    return result;
}

void VBox::INATEngine::set_TFTPBootFile(const std::u16string &value)
{
    COM_SetString(get_IFC(), TFTPBootFile, value);
}

std::u16string VBox::INATEngine::TFTPNextServer() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TFTPNextServer, result);
    return result;
}

void VBox::INATEngine::set_TFTPNextServer(const std::u16string &value)
{
    COM_SetString(get_IFC(), TFTPNextServer, value);
}

uint32_t VBox::INATEngine::aliasMode() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AliasMode, result);
    return static_cast<uint32_t>(result);
}

void VBox::INATEngine::set_aliasMode(uint32_t value)
{
    COM_SetValue(get_IFC(), AliasMode, value);
}

bool VBox::INATEngine::DNSPassDomain() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), DNSPassDomain, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_DNSPassDomain(bool value)
{
    COM_SetValue(get_IFC(), DNSPassDomain, value);
}

bool VBox::INATEngine::DNSProxy() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), DNSProxy, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_DNSProxy(bool value)
{
    COM_SetValue(get_IFC(), DNSProxy, value);
}

bool VBox::INATEngine::DNSUseHostResolver() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), DNSUseHostResolver, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_DNSUseHostResolver(bool value)
{
    COM_SetValue(get_IFC(), DNSUseHostResolver, value);
}

std::vector<std::u16string> VBox::INATEngine::redirects() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Redirects, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
bool VBox::INATEngine::localhostReachable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), LocalhostReachable, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_localhostReachable(bool value)
{
    COM_SetValue(get_IFC(), LocalhostReachable, value);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 6)
bool VBox::INATEngine::forwardBroadcast() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ForwardBroadcast, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_forwardBroadcast(bool value)
{
    COM_SetValue(get_IFC(), ForwardBroadcast, value);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
bool VBox::INATEngine::enableTFTP() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), EnableTFTP, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_enableTFTP(bool value)
{
    COM_SetValue(get_IFC(), EnableTFTP, value);
}

uint32_t VBox::INATEngine::natMRU() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), NatMRU, result);
    return static_cast<uint32_t>(result);
}

void VBox::INATEngine::set_natMRU(uint32_t value)
{
    COM_SetValue(get_IFC(), NatMRU, static_cast<COM_ULong>(value));
}

bool VBox::INATEngine::IPv6Enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IPv6Enabled, result);
    return static_cast<bool>(result);
}

void VBox::INATEngine::set_IPv6Enabled(bool value)
{
    COM_SetValue(get_IFC(), IPv6Enabled, value);
}

std::u16string VBox::INATEngine::IPv6Prefix() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IPv6Prefix, result);
    return result;
}

void VBox::INATEngine::set_IPv6Prefix(const std::u16string &value)
{
    COM_SetString(get_IFC(), IPv6Prefix, value);
}
#endif

void VBox::INATEngine::setNetworkSettings(uint32_t mtu, uint32_t sockSnd,
        uint32_t sockRcv, uint32_t TcpWndSnd, uint32_t TcpWndRcv)
{
    auto rc = get_IFC()->SetNetworkSettings(mtu, sockSnd, sockRcv, TcpWndSnd,
                TcpWndRcv);
    COM_ERROR_CHECK(rc);
}

void VBox::INATEngine::getNetworkSettings(uint32_t *mtu, uint32_t *sockSnd,
        uint32_t *sockRcv, uint32_t *TcpWndSnd, uint32_t *TcpWndRcv)
{
    COM_ULong cMtu;
    COM_ULong cSockSnd;
    COM_ULong cSockRcv;
    COM_ULong cTcpWndSnd;
    COM_ULong cTcpWndRcv;

    auto rc = get_IFC()->GetNetworkSettings(&cMtu, &cSockSnd, &cSockRcv,
                &cTcpWndSnd, &cTcpWndRcv);
    COM_ERROR_CHECK(rc);

    if (mtu)
        *mtu = static_cast<uint32_t>(cMtu);
    if (sockSnd)
        *sockSnd = static_cast<uint32_t>(cSockSnd);
    if (sockRcv)
        *sockRcv = static_cast<uint32_t>(cSockRcv);
    if (TcpWndSnd)
        *TcpWndSnd = static_cast<uint32_t>(cTcpWndSnd);
    if (TcpWndRcv)
        *TcpWndRcv = static_cast<uint32_t>(cTcpWndRcv);
}

void VBox::INATEngine::addRedirect(const std::u16string &name,
        NATProtocol proto, const std::u16string &hostIP, uint16_t hostPort,
        const std::u16string &guestIP, uint16_t guestPort)
{
    COM_StringProxy pName(name);
    auto cProto = static_cast<COM_Enum(::NATProtocol)>(proto);
    COM_StringProxy pHostIP(hostIP);
    COM_StringProxy pGuestIP(guestIP);

    auto rc = get_IFC()->AddRedirect(pName.m_text, cProto, pHostIP.m_text,
                hostPort, pGuestIP.m_text, guestPort);
    COM_ERROR_CHECK(rc);
}

void VBox::INATEngine::removeRedirect(const std::u16string &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->RemoveRedirect(pName.m_text);
    COM_ERROR_CHECK(rc);
}
