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

COM_WRAP_IFC(IHostNetworkInterface)

std::u16string VBox::IHostNetworkInterface::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::IHostNetworkInterface::shortName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ShortName, result);
    return result;
}

std::u16string VBox::IHostNetworkInterface::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::IHostNetworkInterface::networkName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkName, result);
    return result;
}

bool VBox::IHostNetworkInterface::DHCPEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), DHCPEnabled, result);
    return static_cast<bool>(result);
}

std::u16string VBox::IHostNetworkInterface::IPAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IPAddress, result);
    return result;
}

std::u16string VBox::IHostNetworkInterface::networkMask() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkMask, result);
    return result;
}

bool VBox::IHostNetworkInterface::IPV6Supported() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IPV6Supported, result);
    return static_cast<bool>(result);
}

std::u16string VBox::IHostNetworkInterface::IPV6Address() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IPV6Address, result);
    return result;
}

uint32_t VBox::IHostNetworkInterface::IPV6NetworkMaskPrefixLength() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IPV6NetworkMaskPrefixLength, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IHostNetworkInterface::hardwareAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HardwareAddress, result);
    return result;
}

VBox::HostNetworkInterfaceMediumType VBox::IHostNetworkInterface::mediumType() const
{
    COM_Enum(::HostNetworkInterfaceMediumType) result;
    COM_GetValue(get_IFC(), MediumType, result);
    return static_cast<HostNetworkInterfaceMediumType>(result);
}

VBox::HostNetworkInterfaceStatus VBox::IHostNetworkInterface::status() const
{
    COM_Enum(::HostNetworkInterfaceStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<HostNetworkInterfaceStatus>(result);
}

VBox::HostNetworkInterfaceType VBox::IHostNetworkInterface::interfaceType() const
{
    COM_Enum(::HostNetworkInterfaceType) result;
    COM_GetValue(get_IFC(), InterfaceType, result);
    return static_cast<HostNetworkInterfaceType>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
bool VBox::IHostNetworkInterface::wireless() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Wireless, result);
    return static_cast<bool>(result);
}
#endif

void VBox::IHostNetworkInterface::enableStaticIPConfig(
        const std::u16string &IPAddress, const std::u16string &networkMask)
{
    COM_StringProxy pIPAddress(IPAddress);
    COM_StringProxy pNetworkMask(networkMask);

    auto rc = get_IFC()->EnableStaticIPConfig(pIPAddress.m_text, pNetworkMask.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IHostNetworkInterface::enableStaticIPConfigV6(
        const std::u16string &IPV6Address, uint32_t IPV6NetworkMaskPrefixLength)
{
    COM_StringProxy pIPV6Address(IPV6Address);

    auto rc = get_IFC()->EnableStaticIPConfigV6(pIPV6Address.m_text,
                IPV6NetworkMaskPrefixLength);
    COM_ERROR_CHECK(rc);
}

void VBox::IHostNetworkInterface::enableDynamicIPConfig()
{
    auto rc = get_IFC()->EnableDynamicIPConfig();
    COM_ERROR_CHECK(rc);
}

void VBox::IHostNetworkInterface::DHCPRediscover()
{
    auto rc = get_IFC()->DHCPRediscover();
    COM_ERROR_CHECK(rc);
}
