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

COM_WRAP_IFC(IHost)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
COM_WRAP_IFC(IHostUpdate)
#endif

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IHost::DVDDrives() const
{
    std::vector<COMPtr<IMedium>> result;
    COM_GetArray_Wrap(get_IFC(), DVDDrives, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IHost::floppyDrives() const
{
    std::vector<COMPtr<IMedium>> result;
    COM_GetArray_Wrap(get_IFC(), FloppyDrives, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IHostUSBDevice>> VBox::IHost::USBDevices() const
{
    std::vector<COMPtr<IHostUSBDevice>> result;
    COM_GetArray_Wrap(get_IFC(), USBDevices, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IHostUSBDeviceFilter>> VBox::IHost::USBDeviceFilters() const
{
    std::vector<COMPtr<IHostUSBDeviceFilter>> result;
    COM_GetArray_Wrap(get_IFC(), USBDeviceFilters, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IHostNetworkInterface>> VBox::IHost::networkInterfaces() const
{
    std::vector<COMPtr<IHostNetworkInterface>> result;
    COM_GetArray_Wrap(get_IFC(), NetworkInterfaces, result);
    return result;
}

std::vector<std::u16string> VBox::IHost::nameServers() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), NameServers, result);
    return result;
}

std::u16string VBox::IHost::domainName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DomainName, result);
    return result;
}

std::vector<std::u16string> VBox::IHost::searchStrings() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), SearchStrings, result);
    return result;
}

uint32_t VBox::IHost::processorCount() const
{
    COM_ULong cResult;
    COM_GetValue(get_IFC(), ProcessorCount, cResult);
    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IHost::processorOnlineCount() const
{
    COM_ULong cResult;
    COM_GetValue(get_IFC(), ProcessorOnlineCount, cResult);
    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IHost::processorCoreCount() const
{
    COM_ULong cResult;
    COM_GetValue(get_IFC(), ProcessorCoreCount, cResult);
    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IHost::processorOnlineCoreCount() const
{
    COM_ULong cResult;
    COM_GetValue(get_IFC(), ProcessorOnlineCoreCount, cResult);
    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IHost::memorySize() const
{
    COM_ULong cResult;
    COM_GetValue(get_IFC(), MemorySize, cResult);
    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IHost::memoryAvailable() const
{
    COM_ULong cResult;
    COM_GetValue(get_IFC(), MemoryAvailable, cResult);
    return static_cast<uint32_t>(cResult);
}

std::u16string VBox::IHost::operatingSystem() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OperatingSystem, result);
    return result;
}

std::u16string VBox::IHost::OSVersion() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OSVersion, result);
    return result;
}

int64_t VBox::IHost::UTCTime() const
{
    COM_Long64 cResult;
    COM_GetValue(get_IFC(), UTCTime, cResult);
    return static_cast<int64_t>(cResult);
}

bool VBox::IHost::acceleration3DAvailable() const
{
    COM_Bool cResult;
    COM_GetValue(get_IFC(), Acceleration3DAvailable, cResult);
    return static_cast<bool>(cResult);
}

std::vector<VBox::COMPtr<VBox::IHostVideoInputDevice>> VBox::IHost::videoInputDevices() const
{
    std::vector<COMPtr<IHostVideoInputDevice>> result;
    COM_GetArray_Wrap(get_IFC(), VideoInputDevices, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox::COMPtr<VBox::IHostUpdate> VBox::IHost::update() const
{
    COMPtr<IHostUpdate> result;
    COM_GetValue_Wrap(get_IFC(), Update, result);
    return result;
}
#endif

uint32_t VBox::IHost::getProcessorSpeed(uint32_t cpuId)
{
    COM_ULong cResult;

    auto rc = get_IFC()->GetProcessorSpeed(cpuId, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

bool VBox::IHost::getProcessorFeature(ProcessorFeature feature)
{
    COM_Bool cResult;
    auto cFeature = static_cast<COM_Enum(::ProcessorFeature)>(feature);

    auto rc = get_IFC()->GetProcessorFeature(cFeature, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

std::u16string VBox::IHost::getProcessorDescription(uint32_t cpuId)
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->GetProcessorDescription(cpuId, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IHost::getProcessorCPUIDLeaf(uint32_t cpuId, uint32_t leaf,
        uint32_t subLeaf, uint32_t *valEax, uint32_t *valEbx, uint32_t *valEcx,
        uint32_t *valEdx)
{
    COM_ULong cValEax;
    COM_ULong cValEbx;
    COM_ULong cValEcx;
    COM_ULong cValEdx;

    auto rc = get_IFC()->GetProcessorCPUIDLeaf(cpuId, leaf, subLeaf,
                    &cValEax, &cValEbx, &cValEcx, &cValEdx);
    COM_ERROR_CHECK(rc);

    if (valEax)
        *valEax = static_cast<uint32_t>(cValEax);
    if (valEbx)
        *valEbx = static_cast<uint32_t>(cValEbx);
    if (valEcx)
        *valEcx = static_cast<uint32_t>(cValEcx);
    if (valEdx)
        *valEdx = static_cast<uint32_t>(cValEdx);
}

VBox::COMPtr<VBox::IProgress> VBox::IHost::createHostOnlyNetworkInterface(
        COMPtr<IHostNetworkInterface> *hostInterface)
{
    ::IProgress *cResult = nullptr;
    ::IHostNetworkInterface *cHostInterface = nullptr;

    auto rc = get_IFC()->CreateHostOnlyNetworkInterface(&cHostInterface, &cResult);
    COM_ERROR_CHECK(rc);

    if (hostInterface)
        *hostInterface = COMPtr<IHostNetworkInterface>::wrap(cHostInterface);
    else if (cHostInterface)
        cHostInterface->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IHost::removeHostOnlyNetworkInterface(
        const std::u16string &id)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->RemoveHostOnlyNetworkInterface(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IHostUSBDeviceFilter> VBox::IHost::createUSBDeviceFilter(
        const std::u16string name)
{
    ::IHostUSBDeviceFilter *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->CreateUSBDeviceFilter(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IHostUSBDeviceFilter>::wrap(cResult);
}

void VBox::IHost::insertUSBDeviceFilter(uint32_t position,
        const COMPtr<IHostUSBDeviceFilter> &filter)
{
    auto rc = get_IFC()->InsertUSBDeviceFilter(position, filter->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IHost::removeUSBDeviceFilter(uint32_t position)
{
    auto rc = get_IFC()->RemoveUSBDeviceFilter(position);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IMedium> VBox::IHost::findHostDVDDrive(const std::u16string &name)
{
    ::IMedium *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindHostDVDDrive(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(cResult);
}

VBox::COMPtr<VBox::IMedium> VBox::IHost::findHostFloppyDrive(const std::u16string &name)
{
    ::IMedium *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindHostFloppyDrive(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(cResult);
}

VBox::COMPtr<VBox::IHostNetworkInterface> VBox::IHost::findHostNetworkInterfaceByName(
        const std::u16string &name)
{
    ::IHostNetworkInterface *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindHostNetworkInterfaceByName(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IHostNetworkInterface>::wrap(cResult);
}

VBox::COMPtr<VBox::IHostNetworkInterface> VBox::IHost::findHostNetworkInterfaceById(
        const std::u16string &id)
{
    ::IHostNetworkInterface *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->FindHostNetworkInterfaceById(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IHostNetworkInterface>::wrap(cResult);
}

std::vector<VBox::COMPtr<VBox::IHostNetworkInterface>>
VBox::IHost::findHostNetworkInterfacesOfType(HostNetworkInterfaceType type)
{
    COM_ArrayProxy<::IHostNetworkInterface *> pResult;
    auto cType = static_cast<COM_Enum(::HostNetworkInterfaceType)>(type);

    auto rc = get_IFC()->FindHostNetworkInterfacesOfType(cType, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IHostNetworkInterface>> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IHostUSBDevice> VBox::IHost::findUSBDeviceById(
        const std::u16string &id)
{
    ::IHostUSBDevice *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->FindUSBDeviceById(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IHostUSBDevice>::wrap(cResult);
}

VBox::COMPtr<VBox::IHostUSBDevice> VBox::IHost::findUSBDeviceByAddress(
        const std::u16string &name)
{
    ::IHostUSBDevice *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindUSBDeviceByAddress(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IHostUSBDevice>::wrap(cResult);
}

std::u16string VBox::IHost::generateMACAddress()
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->GenerateMACAddress(&pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
void VBox::IHost::addUSBDeviceSource(const std::u16string &backend,
        const std::u16string &id, const std::u16string &address,
        const std::vector<std::u16string> &propertyNames,
        const std::vector<std::u16string> &propertyValues)
{
    COM_StringProxy pBackend(backend);
    COM_StringProxy pId(id);
    COM_StringProxy pAddress(address);
    COM_StringArrayProxy pPropertyNames(propertyNames);
    COM_StringArrayProxy pPropertyValues(propertyValues);

    auto rc = get_IFC()->AddUSBDeviceSource(pBackend.m_text, pId.m_text,
                    pAddress.m_text, COM_ArrayParameter(pPropertyNames),
                    COM_ArrayParameter(pPropertyValues));
    COM_ERROR_CHECK(rc);
}

void VBox::IHost::removeUSBDeviceSource(const std::u16string &id)
{
    COM_StringProxy pId(id);

    auto rc = get_IFC()->RemoveUSBDeviceSource(pId.m_text);
    COM_ERROR_CHECK(rc);
}
#endif
