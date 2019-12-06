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

COM_WRAP_IFC(INetworkAdapter)

VBox::NetworkAdapterType VBox::INetworkAdapter::adapterType() const
{
    COM_Enum(::NetworkAdapterType) result;
    COM_GetValue(get_IFC(), AdapterType, result);
    return static_cast<NetworkAdapterType>(result);
}

void VBox::INetworkAdapter::set_adapterType(NetworkAdapterType value)
{
    COM_SetValue(get_IFC(), AdapterType,
                 static_cast<COM_Enum(::NetworkAdapterType)>(value));
}

uint32_t VBox::INetworkAdapter::slot() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Slot, result);
    return static_cast<uint32_t>(result);
}

bool VBox::INetworkAdapter::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::INetworkAdapter::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

std::u16string VBox::INetworkAdapter::MACAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MACAddress, result);
    return result;
}

void VBox::INetworkAdapter::set_MACAddress(const std::u16string &value)
{
    COM_SetString(get_IFC(), MACAddress, value);
}

VBox::NetworkAttachmentType VBox::INetworkAdapter::attachmentType() const
{
    COM_Enum(::NetworkAttachmentType) result;
    COM_GetValue(get_IFC(), AttachmentType, result);
    return static_cast<NetworkAttachmentType>(result);
}

void VBox::INetworkAdapter::set_attachmentType(NetworkAttachmentType value)
{
    COM_SetValue(get_IFC(), AttachmentType,
                 static_cast<COM_Enum(::NetworkAttachmentType)>(value));
}

std::u16string VBox::INetworkAdapter::bridgedInterface() const
{
    std::u16string result;
    COM_GetString(get_IFC(), BridgedInterface, result);
    return result;
}

void VBox::INetworkAdapter::set_bridgedInterface(const std::u16string &value)
{
    COM_SetString(get_IFC(), BridgedInterface, value);
}

std::u16string VBox::INetworkAdapter::hostOnlyInterface() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HostOnlyInterface, result);
    return result;
}

void VBox::INetworkAdapter::set_hostOnlyInterface(const std::u16string &value)
{
    COM_SetString(get_IFC(), HostOnlyInterface, value);
}

std::u16string VBox::INetworkAdapter::internalNetwork() const
{
    std::u16string result;
    COM_GetString(get_IFC(), InternalNetwork, result);
    return result;
}

void VBox::INetworkAdapter::set_internalNetwork(const std::u16string &value)
{
    COM_SetString(get_IFC(), InternalNetwork, value);
}

std::u16string VBox::INetworkAdapter::NATNetwork() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NATNetwork, result);
    return result;
}

void VBox::INetworkAdapter::set_NATNetwork(const std::u16string &value)
{
    COM_SetString(get_IFC(), NATNetwork, value);
}

std::u16string VBox::INetworkAdapter::genericDriver() const
{
    std::u16string result;
    COM_GetString(get_IFC(), GenericDriver, result);
    return result;
}

void VBox::INetworkAdapter::set_genericDriver(const std::u16string &value)
{
    COM_SetString(get_IFC(), GenericDriver, value);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
std::u16string VBox::INetworkAdapter::cloudNetwork() const
{
    std::u16string result;
    COM_GetString(get_IFC(), CloudNetwork, result);
    return result;
}

void VBox::INetworkAdapter::set_cloudNetwork(const std::u16string &value)
{
    COM_SetString(get_IFC(), CloudNetwork, value);
}
#endif

bool VBox::INetworkAdapter::cableConnected() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), CableConnected, result);
    return static_cast<bool>(result);
}

void VBox::INetworkAdapter::set_cableConnected(bool value)
{
    COM_SetValue(get_IFC(), CableConnected, value);
}

uint32_t VBox::INetworkAdapter::lineSpeed() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), LineSpeed, result);
    return static_cast<uint32_t>(result);
}

void VBox::INetworkAdapter::set_lineSpeed(uint32_t value)
{
    COM_SetValue(get_IFC(), LineSpeed, value);
}

VBox::NetworkAdapterPromiscModePolicy VBox::INetworkAdapter::promiscModePolicy() const
{
    COM_Enum(::NetworkAdapterPromiscModePolicy) result;
    COM_GetValue(get_IFC(), PromiscModePolicy, result);
    return static_cast<NetworkAdapterPromiscModePolicy>(result);
}

void VBox::INetworkAdapter::set_promiscModePolicy(NetworkAdapterPromiscModePolicy value)
{
    COM_SetValue(get_IFC(), PromiscModePolicy,
                 static_cast<COM_Enum(::NetworkAdapterPromiscModePolicy)>(value));
}

bool VBox::INetworkAdapter::traceEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), TraceEnabled, result);
    return static_cast<bool>(result);
}

void VBox::INetworkAdapter::set_traceEnabled(bool value)
{
    COM_SetValue(get_IFC(), TraceEnabled, value);
}

std::u16string VBox::INetworkAdapter::traceFile() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TraceFile, result);
    return result;
}

void VBox::INetworkAdapter::set_traceFile(const std::u16string &value)
{
    COM_SetString(get_IFC(), TraceFile, value);
}

VBox::COMPtr<VBox::INATEngine> VBox::INetworkAdapter::NATEngine() const
{
    COMPtr<INATEngine> result;
    COM_GetValue_Wrap(get_IFC(), NATEngine, result);
    return result;
}

uint32_t VBox::INetworkAdapter::bootPriority() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), BootPriority, result);
    return static_cast<uint32_t>(result);
}

void VBox::INetworkAdapter::set_bootPriority(uint32_t value)
{
    COM_SetValue(get_IFC(), BootPriority, value);
}

VBox::COMPtr<VBox::IBandwidthGroup> VBox::INetworkAdapter::bandwidthGroup() const
{
    COMPtr<IBandwidthGroup> result;
    COM_GetValue_Wrap(get_IFC(), BandwidthGroup, result);
    return result;
}

void VBox::INetworkAdapter::set_bandwidthGroup(const COMPtr<IBandwidthGroup> &value)
{
    COM_SetValue_Wrap(get_IFC(), BandwidthGroup, value);
}

std::u16string VBox::INetworkAdapter::getProperty(const std::u16string &key) const
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetProperty(pKey.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::INetworkAdapter::setProperty(const std::u16string &key,
        const std::u16string &value)
{
    COM_StringProxy pKey(key);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetProperty(pKey.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

std::vector<std::u16string> VBox::INetworkAdapter::getProperties(
        const std::u16string &names, std::vector<std::u16string> *returnNames) const
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pNames(names);
    COM_StringArrayProxy pReturnNames;

    auto rc = get_IFC()->GetProperties(pNames.m_text,
                COM_ArrayParameterRef(pReturnNames),
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (returnNames)
        pReturnNames.toVector(*returnNames);
    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}
