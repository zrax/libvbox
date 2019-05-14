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

const void *VBox::IVirtualBox::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IVirtualBox);
}

std::u16string VBox::IVirtualBox::version() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Version, result);
    return result;
}

std::u16string VBox::IVirtualBox::versionNormalized() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VersionNormalized, result);
    return result;
}

uint32_t VBox::IVirtualBox::revision() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Revision, result);
    return result;
}

std::u16string VBox::IVirtualBox::packageType() const
{
    std::u16string result;
    COM_GetString(get_IFC(), PackageType, result);
    return result;
}

std::u16string VBox::IVirtualBox::APIVersion() const
{
    std::u16string result;
    COM_GetString(get_IFC(), APIVersion, result);
    return result;
}

int64_t VBox::IVirtualBox::APIRevision() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), APIRevision, result);
    return result;
}

std::u16string VBox::IVirtualBox::homeFolder() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HomeFolder, result);
    return result;
}

std::u16string VBox::IVirtualBox::settingsFilePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SettingsFilePath, result);
    return result;
}

VBox::COMPtr<VBox::IHost> VBox::IVirtualBox::host() const
{
    COMPtr<IHost> result;
    COM_GetValue_Wrap(get_IFC(), Host, result);
    return result;
}

VBox::COMPtr<VBox::ISystemProperties> VBox::IVirtualBox::systemProperties() const
{
    COMPtr<ISystemProperties> result;
    COM_GetValue_Wrap(get_IFC(), SystemProperties, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMachine>> VBox::IVirtualBox::machines() const
{
    std::vector<COMPtr<IMachine>> result;
    COM_GetArray_Wrap(get_IFC(), Machines, result);
    return result;
}

std::vector<std::u16string> VBox::IVirtualBox::machineGroups() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), MachineGroups, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IVirtualBox::hardDisks() const
{
    std::vector<COMPtr<IMedium>> result;
    COM_GetArray_Wrap(get_IFC(), HardDisks, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IVirtualBox::DVDImages() const
{
    std::vector<COMPtr<IMedium>> result;
    COM_GetArray_Wrap(get_IFC(), DVDImages, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IVirtualBox::floppyImages() const
{
    std::vector<COMPtr<IMedium>> result;
    COM_GetArray_Wrap(get_IFC(), FloppyImages, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IProgress>> VBox::IVirtualBox::progressOperations() const
{
    std::vector<COMPtr<IProgress>> result;
    COM_GetArray_Wrap(get_IFC(), ProgressOperations, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IGuestOSType>> VBox::IVirtualBox::guestOSTypes() const
{
    std::vector<COMPtr<IGuestOSType>> result;
    COM_GetArray_Wrap(get_IFC(), GuestOSTypes, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::ISharedFolder>> VBox::IVirtualBox::sharedFolders() const
{
    std::vector<COMPtr<ISharedFolder>> result;
    COM_GetArray_Wrap(get_IFC(), SharedFolders, result);
    return result;
}

VBox::COMPtr<VBox::IPerformanceCollector> VBox::IVirtualBox::performanceCollector() const
{
    COMPtr<IPerformanceCollector> result;
    COM_GetValue_Wrap(get_IFC(), PerformanceCollector, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IDHCPServer>> VBox::IVirtualBox::DHCPServers() const
{
    std::vector<COMPtr<IDHCPServer>> result;
    COM_GetArray_Wrap(get_IFC(), DHCPServers, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::INATNetwork>> VBox::IVirtualBox::NATNetworks() const
{
    std::vector<COMPtr<INATNetwork>> result;
    COM_GetArray_Wrap(get_IFC(), NATNetworks, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IVirtualBox::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

VBox::COMPtr<VBox::IExtPackManager> VBox::IVirtualBox::extensionPackManager() const
{
    COMPtr<IExtPackManager> result;
    COM_GetValue_Wrap(get_IFC(), ExtensionPackManager, result);
    return result;
}

std::vector<std::u16string> VBox::IVirtualBox::internalNetworks() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), InternalNetworks, result);
    return result;
}

std::vector<std::u16string> VBox::IVirtualBox::genericNetworkDrivers() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), GenericNetworkDrivers, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::ICloudProviderManager> VBox::IVirtualBox::cloudProviderManager() const
{
    COMPtr<ICloudProviderManager> result;
    COM_GetValue_Wrap(get_IFC(), CloudProviderManager, result);
    return result;
}
#endif

std::u16string VBox::IVirtualBox::composeMachineFilename(
        const std::u16string &name, const std::u16string &group,
        const std::u16string &createFlags, const std::u16string &baseFolder)
{
    COM_StringProxy result;
    COM_StringProxy pName(name);
    COM_StringProxy pGroup(group);
    COM_StringProxy pCreateFlags(createFlags);
    COM_StringProxy pBaseFolder(baseFolder);

    auto rc = get_IFC()->ComposeMachineFilename(pName.m_text, pGroup.m_text,
                                                pCreateFlags.m_text,
                                                pBaseFolder.m_text,
                                                &result.m_text);
    COM_ERROR_CHECK(rc);
    return result.toString();
}

VBox::COMPtr<VBox::IMachine> VBox::IVirtualBox::createMachine(
        const std::u16string &settingsFile, const std::u16string &name,
        const std::vector<std::u16string> &groups, const std::u16string &osTypeId,
        const std::u16string &flags)
{
    ::IMachine *cResult = nullptr;
    COM_StringProxy pSettingsFile(settingsFile);
    COM_StringProxy pName(name);
    COM_StringArrayProxy pGroups(groups);
    COM_StringProxy pOsTypeId(osTypeId);
    COM_StringProxy pFlags(flags);

    auto rc = get_IFC()->CreateMachine(pSettingsFile.m_text, pName.m_text,
                                       COM_ArrayParameter(pGroups),
                                       pOsTypeId.m_text, pFlags.m_text,
                                       &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IMachine>::wrap(cResult);
}

VBox::COMPtr<VBox::IMachine> VBox::IVirtualBox::openMachine(
        const std::u16string &settingsFile)
{
    ::IMachine *cResult = nullptr;
    COM_StringProxy pSettingsFile(settingsFile);

    auto rc = get_IFC()->OpenMachine(pSettingsFile.m_text, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IMachine>::wrap(cResult);
}

void VBox::IVirtualBox::registerMachine(const COMPtr<IMachine> &machine)
{
    auto rc = get_IFC()->RegisterMachine(machine->get_IFC());
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IMachine> VBox::IVirtualBox::findMachine(
        const std::u16string &nameOrId)
{
    ::IMachine *cResult = nullptr;
    COM_StringProxy pNameOrId(nameOrId);

    auto rc = get_IFC()->FindMachine(pNameOrId.m_text, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IMachine>::wrap(cResult);
}

std::vector<VBox::COMPtr<VBox::IMachine>> VBox::IVirtualBox::getMachinesByGroups(
        const std::vector<std::u16string> &groups)
{
    COM_ArrayProxy<::IMachine *> pResult;
    COM_StringArrayProxy pGroups(groups);

    auto rc = get_IFC()->GetMachinesByGroups(COM_ArrayParameter(pGroups),
                                             COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<VBox::COMPtr<VBox::IMachine>> result;
    pResult.toVector(result);
    return result;
}

std::vector<VBox::MachineState> VBox::IVirtualBox::getMachineStates(
        const std::vector<COMPtr<IMachine>> &machines)
{
    COM_ArrayProxy<COM_Enum(::MachineState)> pResult;
    COM_ArrayProxy<::IMachine *> pMachines(machines);

    auto rc = get_IFC()->GetMachineStates(COM_ArrayParameter(pMachines),
                                          COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<VBox::MachineState> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IAppliance> VBox::IVirtualBox::createAppliance()
{
    ::IAppliance *cResult = nullptr;
    auto rc = get_IFC()->CreateAppliance(&cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IAppliance>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox::COMPtr<VBox::IUnattended> VBox::IVirtualBox::createUnattendedInstaller()
{
    ::IUnattended *cResult = nullptr;
    auto rc = get_IFC()->CreateUnattendedInstaller(&cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IUnattended>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IMedium> VBox::IVirtualBox::createMedium(
        const std::u16string &format, const std::u16string &location,
        AccessMode accessMode, DeviceType aADeviceTypeType)
{
    ::IMedium *cResult = nullptr;
    COM_StringProxy pFormat(format);
    COM_StringProxy pLocation(location);
    auto cAccessMode = static_cast<COM_Enum(::AccessMode)>(accessMode);
    auto cDeviceType = static_cast<COM_Enum(::DeviceType)>(aADeviceTypeType);

    auto rc = get_IFC()->CreateMedium(pFormat.m_text, pLocation.m_text,
                                      cAccessMode, cDeviceType, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(cResult);
}

VBox::COMPtr<VBox::IMedium> VBox::IVirtualBox::openMedium(
        const std::u16string &location, DeviceType deviceType,
        AccessMode accessMode, bool forceNewUuid)
{
    ::IMedium *cResult = nullptr;
    COM_StringProxy pLocation(location);
    auto cDeviceType = static_cast<COM_Enum(::DeviceType)>(deviceType);
    auto cAccessMode = static_cast<COM_Enum(::AccessMode)>(accessMode);
    auto cForceNewUuid = static_cast<COM_Bool>(forceNewUuid);

    auto rc = get_IFC()->OpenMedium(pLocation.m_text, cDeviceType, cAccessMode,
                                    cForceNewUuid, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(cResult);
}

VBox::COMPtr<VBox::IGuestOSType> VBox::IVirtualBox::getGuestOSType(
        const std::u16string &id)
{
    ::IGuestOSType *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->GetGuestOSType(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestOSType>::wrap(cResult);
}

void VBox::IVirtualBox::createSharedFolder(const std::u16string &name,
        const std::u16string &hostPath, bool writable, bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
      , const std::u16string &autoMountPoint
#endif
        )
{
    COM_StringProxy pName(name);
    COM_StringProxy pHostPath(hostPath);
    auto cWritable = static_cast<COM_Bool>(writable);
    auto cAutomount = static_cast<COM_Bool>(automount);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_StringProxy pAutoMountPoint(autoMountPoint);
#endif

    auto rc = get_IFC()->CreateSharedFolder(pName.m_text, pHostPath.m_text,
                                            cWritable, cAutomount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
                                          , pAutoMountPoint.m_text
#endif
                                            );
    COM_ERROR_CHECK(rc);
}

void VBox::IVirtualBox::removeSharedFolder(const std::u16string &name)
{
    COM_StringProxy pName(name);
    auto rc = get_IFC()->RemoveSharedFolder(pName.m_text);
    COM_ERROR_CHECK(rc);
}

std::vector<std::u16string> VBox::IVirtualBox::getExtraDataKeys()
{
    COM_StringArrayProxy pResult;
    auto rc = get_IFC()->GetExtraDataKeys(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

std::u16string VBox::IVirtualBox::getExtraData(const std::u16string &key)
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetExtraData(pKey.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IVirtualBox::setExtraData(const std::u16string &key,
        const std::u16string &value)
{
    COM_StringProxy pKey(key);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetExtraData(pKey.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IVirtualBox::setSettingsSecret(const std::u16string &password)
{
    COM_StringProxy pPassword(password);
    auto rc = get_IFC()->SetSettingsSecret(pPassword.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IDHCPServer> VBox::IVirtualBox::createDHCPServer(
        const std::u16string &name)
{
    ::IDHCPServer *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->CreateDHCPServer(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IDHCPServer>::wrap(cResult);
}

VBox::COMPtr<VBox::IDHCPServer> VBox::IVirtualBox::findDHCPServerByNetworkName(
        const std::u16string &name)
{
    ::IDHCPServer *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindDHCPServerByNetworkName(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IDHCPServer>::wrap(cResult);
}

void VBox::IVirtualBox::removeDHCPServer(const COMPtr<IDHCPServer> &server)
{
    auto rc = get_IFC()->RemoveDHCPServer(server->get_IFC());
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::INATNetwork> VBox::IVirtualBox::createNATNetwork(
        const std::u16string &networkName)
{
    ::INATNetwork *cResult = nullptr;
    COM_StringProxy pNetworkName(networkName);

    auto rc = get_IFC()->CreateNATNetwork(pNetworkName.m_text, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<INATNetwork>::wrap(cResult);
}

VBox::COMPtr<VBox::INATNetwork> VBox::IVirtualBox::findNATNetworkByName(
        const std::u16string &networkName)
{
    ::INATNetwork *cResult = nullptr;
    COM_StringProxy pNetworkName(networkName);

    auto rc = get_IFC()->FindNATNetworkByName(pNetworkName.m_text, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<INATNetwork>::wrap(cResult);
}

void VBox::IVirtualBox::removeNATNetwork(const COMPtr<INATNetwork> &network)
{
    auto rc = get_IFC()->RemoveNATNetwork(network->get_IFC());
    COM_ERROR_CHECK(rc);
}

bool VBox::IVirtualBox::checkFirmwarePresent(FirmwareType firmwareType,
        const std::u16string &version, std::u16string *url, std::u16string *file)
{
    COM_Bool cResult;
    auto cFirmwareType = static_cast<COM_Enum(::FirmwareType)>(firmwareType);
    COM_StringProxy pVersion(version);
    COM_StringProxy pUrl;
    COM_StringProxy pFile;

    auto rc = get_IFC()->CheckFirmwarePresent(cFirmwareType, pVersion.m_text,
                                              &pUrl.m_text, &pFile.m_text,
                                              &cResult);
    COM_ERROR_CHECK(rc);

    if (url)
        *url = pUrl.toString();
    if (file)
        *file = pFile.toString();
    return static_cast<bool>(cResult);
}
