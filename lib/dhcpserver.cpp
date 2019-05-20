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

COM_WRAP_IFC(IDHCPServer)

VBox::COMPtr<VBox::IEventSource> VBox::IDHCPServer::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

bool VBox::IDHCPServer::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IDHCPServer::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

std::u16string VBox::IDHCPServer::IPAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IPAddress, result);
    return result;
}

std::u16string VBox::IDHCPServer::networkMask() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkMask, result);
    return result;
}

std::u16string VBox::IDHCPServer::networkName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NetworkName, result);
    return result;
}

std::u16string VBox::IDHCPServer::lowerIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LowerIP, result);
    return result;
}

std::u16string VBox::IDHCPServer::upperIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), UpperIP, result);
    return result;
}

std::vector<std::u16string> VBox::IDHCPServer::globalOptions() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), GlobalOptions, result);
    return result;
}

std::vector<std::u16string> VBox::IDHCPServer::vmConfigs() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), VmConfigs, result);
    return result;
}

void VBox::IDHCPServer::addGlobalOption(DhcpOpt option,
        const std::u16string &value)
{
    auto cOption = static_cast<COM_Enum(::DhcpOpt)>(option);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->AddGlobalOption(cOption, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::IDHCPServer::removeGlobalOption(DhcpOpt option)
{
    auto cOption = static_cast<COM_Enum(::DhcpOpt)>(option);

    auto rc = get_IFC()->RemoveGlobalOption(cOption);
    COM_ERROR_CHECK(rc);
}

void VBox::IDHCPServer::removeGlobalOptions()
{
    auto rc = get_IFC()->RemoveGlobalOptions();
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IDHCPServer::addVmSlotOption(const std::u16string &vmname,
        int32_t slot, DhcpOpt option, const std::u16string &value)
{
    COM_StringProxy pVmname(vmname);
    auto cOption = static_cast<COM_Enum(::DhcpOpt)>(option);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->AddVmSlotOption(pVmname.m_text, slot, cOption, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::IDHCPServer::removeVmSlotOption(const std::u16string& vmname,
        int32_t slot, DhcpOpt option)
{
    COM_StringProxy pVmname(vmname);
    auto cOption = static_cast<COM_Enum(::DhcpOpt)>(option);

    auto rc = get_IFC()->RemoveVmSlotOption(pVmname.m_text, slot, cOption);
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IDHCPServer::removeVmSlotOptions(const std::u16string &vmname,
        int32_t slot)
{
    COM_StringProxy pVmname(vmname);

    auto rc = get_IFC()->RemoveVmSlotOptions(pVmname.m_text, slot);
    COM_ERROR_CHECK(rc);
}

std::vector<std::u16string> VBox::IDHCPServer::getVmSlotOptions(
        const std::u16string &vmname, int32_t slot)
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pVmname(vmname);

    auto rc = get_IFC()->GetVmSlotOptions(pVmname.m_text, slot,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

std::vector<std::u16string> VBox::IDHCPServer::getMacOptions(
        const std::u16string &mac)
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pMac(mac);

    auto rc = get_IFC()->GetMacOptions(pMac.m_text, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

void VBox::IDHCPServer::setConfiguration(const std::u16string &IPAddress,
        const std::u16string &networkMask, const std::u16string &FromIPAddress,
        const std::u16string &ToIPAddress)
{
    COM_StringProxy pIPAddress(IPAddress);
    COM_StringProxy pNetworkMask(networkMask);
    COM_StringProxy pFromIPAddress(FromIPAddress);
    COM_StringProxy pToIPAddress(ToIPAddress);

    auto rc = get_IFC()->SetConfiguration(pIPAddress.m_text, pNetworkMask.m_text,
                pFromIPAddress.m_text, pToIPAddress.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IDHCPServer::start(const std::u16string &networkName,
        const std::u16string &trunkName, const std::u16string &trunkType)
{
    COM_StringProxy pNetworkName(networkName);
    COM_StringProxy pTrunkName(trunkName);
    COM_StringProxy pTrunkType(trunkType);

    auto rc = get_IFC()->Start(pNetworkName.m_text, pTrunkName.m_text,
                pTrunkType.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IDHCPServer::stop()
{
    auto rc = get_IFC()->Stop();
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::IDHCPServer::restart()
{
    auto rc = get_IFC()->Restart();
    COM_ERROR_CHECK(rc);
}
#endif
