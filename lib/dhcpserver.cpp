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

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
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
#else
VBox::COMPtr<VBox::IDHCPGlobalConfig> VBox::IDHCPServer::globalConfig() const
{
    COMPtr<IDHCPGlobalConfig> result;
    COM_GetValue_Wrap(get_IFC(), GlobalConfig, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IDHCPGroupConfig>>
VBox::IDHCPServer::groupConfigs() const
{
    std::vector<COMPtr<IDHCPGroupConfig>> result;
    COM_GetArray_Wrap(get_IFC(), GroupConfigs, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IDHCPIndividualConfig>>
VBox::IDHCPServer::individualConfigs() const
{
    std::vector<COMPtr<IDHCPIndividualConfig>> result;
    COM_GetArray_Wrap(get_IFC(), IndividualConfigs, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
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
#endif

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

void VBox::IDHCPServer::start(
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        const std::u16string &networkName,
#endif
        const std::u16string &trunkName, const std::u16string &trunkType)
{
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
    COM_StringProxy pNetworkName(networkName);
#endif
    COM_StringProxy pTrunkName(trunkName);
    COM_StringProxy pTrunkType(trunkType);

    auto rc = get_IFC()->Start(
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
                pNetworkName.m_text,
#endif
                pTrunkName.m_text, pTrunkType.m_text);
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
void VBox::IDHCPServer::findLeaseByMAC(const std::u16string &mac, int32_t type,
        std::u16string *address, std::u16string *state, int64_t *issued,
        int64_t *expire)
{
    COM_StringProxy pMac(mac);
    COM_StringProxy pAddress;
    COM_StringProxy pState;
    COM_Long64 cIssued;
    COM_Long64 cExpire;

    auto rc = get_IFC()->FindLeaseByMAC(pMac.m_text, type, &pAddress.m_text,
                &pState.m_text, &cIssued, &cExpire);
    COM_ERROR_CHECK(rc);

    if (address)
        *address = pAddress.toString();
    if (state)
        *state = pState.toString();
    if (issued)
        *issued = static_cast<int64_t>(cIssued);
    if (expire)
        *expire = static_cast<int64_t>(cExpire);
}

VBox::COMPtr<VBox::IDHCPConfig> VBox::IDHCPServer::getConfig(
        DHCPConfigScope scope, const std::u16string &name, uint32_t slot,
        bool mayAdd)
{
    ::IDHCPConfig *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetConfig(static_cast<COM_Enum(::DHCPConfigScope)>(scope),
                pName.m_text, slot, mayAdd, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IDHCPConfig>::wrap(cResult);
}
#endif
