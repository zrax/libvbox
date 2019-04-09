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

std::wstring VBox::IVirtualBox::version() const
{
    std::wstring result;
    COM_GetString(get_IFC(), Version, result);
    return result;
}

std::wstring VBox::IVirtualBox::versionNormalized() const
{
    std::wstring result;
    COM_GetString(get_IFC(), VersionNormalized, result);
    return result;
}

uint32_t VBox::IVirtualBox::revision() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Revision, result);
    return result;
}

std::wstring VBox::IVirtualBox::packageType() const
{
    std::wstring result;
    COM_GetString(get_IFC(), PackageType, result);
    return result;
}

std::wstring VBox::IVirtualBox::APIVersion() const
{
    std::wstring result;
    COM_GetString(get_IFC(), APIVersion, result);
    return result;
}

int64_t VBox::IVirtualBox::APIRevision() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), APIRevision, result);
    return result;
}

std::wstring VBox::IVirtualBox::homeFolder() const
{
    std::wstring result;
    COM_GetString(get_IFC(), HomeFolder, result);
    return result;
}

std::wstring VBox::IVirtualBox::settingsFilePath() const
{
    std::wstring result;
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

std::vector<std::wstring> VBox::IVirtualBox::machineGroups() const
{
    std::vector<std::wstring> result;
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

std::vector<std::wstring> VBox::IVirtualBox::internalNetworks() const
{
    std::vector<std::wstring> result;
    COM_GetStringArray(get_IFC(), InternalNetworks, result);
    return result;
}

std::vector<std::wstring> VBox::IVirtualBox::genericNetworkDrivers() const
{
    std::vector<std::wstring> result;
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

std::wstring VBox::IVirtualBox::composeMachineFilename(
        const std::wstring &name, const std::wstring &group,
        const std::wstring &createFlags, const std::wstring &baseFolder)
{
    COM_StringProxy result;
    COM_StringProxy pName(name);
    COM_StringProxy pGroup(group);
    COM_StringProxy pCreateFlags(createFlags);
    COM_StringProxy pBaseFolder(baseFolder);

    auto rc = get_IFC()->ComposeMachineFilename(pName.m_string, pGroup.m_string,
                                                pCreateFlags.m_string,
                                                pBaseFolder.m_string,
                                                &result.m_string);
    COM_ERROR_CHECK(rc);
    return result.toWString();
}

VBox::COMPtr<VBox::IMachine> VBox::IVirtualBox::createMachine(
        const std::wstring &settingsFile, const std::wstring &name,
        const std::vector<std::wstring> &groups, const std::wstring &osTypeId,
        const std::wstring &flags)
{
    ::IMachine *cResult = nullptr;
    COM_StringProxy pSettingsFile(settingsFile);
    COM_StringProxy pName(name);
    COM_StringArrayProxy pGroups(groups);
    COM_StringProxy pOsTypeId(osTypeId);
    COM_StringProxy pFlags(flags);

    auto rc = get_IFC()->CreateMachine(pSettingsFile.m_string, pName.m_string,
                                       COM_ArrayParameter(pGroups),
                                       pOsTypeId.m_string, pFlags.m_string,
                                       &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IMachine>::wrap(cResult);
}

VBox::COMPtr<VBox::IMachine> VBox::IVirtualBox::openMachine(
        const std::wstring &settingsFile)
{
    ::IMachine *cResult = nullptr;
    COM_StringProxy pSettingsFile(settingsFile);

    auto rc = get_IFC()->OpenMachine(pSettingsFile.m_string, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IMachine>::wrap(cResult);
}

void VBox::IVirtualBox::registerMachine(const COMPtr<IMachine> &machine)
{
    auto rc = get_IFC()->RegisterMachine(machine->get_IFC());
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IMachine> VBox::IVirtualBox::findMachine(
        const std::wstring &nameOrId)
{
    ::IMachine *cResult = nullptr;
    COM_StringProxy pNameOrId(nameOrId);

    auto rc = get_IFC()->FindMachine(pNameOrId.m_string, &cResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IMachine>::wrap(cResult);
}

std::vector<VBox::COMPtr<VBox::IMachine>> VBox::IVirtualBox::getMachinesByGroups(
        const std::vector<std::wstring> &groups)
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
    COM_ArrayProxy<COM_Type(PRUint32, ::MachineState)> pResult;
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
    ::IAppliance *pResult;
    auto rc = get_IFC()->CreateAppliance(&pResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IAppliance>::wrap(pResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox::COMPtr<VBox::IUnattended> VBox::IVirtualBox::createUnattendedInstaller()
{
    ::IUnattended *pResult;
    auto rc = get_IFC()->CreateUnattendedInstaller(&pResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IUnattended>::wrap(pResult);
}
#endif

VBox::COMPtr<VBox::IMedium> VBox::IVirtualBox::createMedium(
        const std::wstring &format, const std::wstring &location,
        AccessMode accessMode, DeviceType aADeviceTypeType)
{
    ::IMedium *pResult;
    COM_StringProxy pFormat(format);
    COM_StringProxy pLocation(location);
    auto cAccessMode = static_cast<COM_Type(PRUint32, ::AccessMode)>(accessMode);
    auto cDeviceType = static_cast<COM_Type(PRUint32, ::DeviceType)>(aADeviceTypeType);

    auto rc = get_IFC()->CreateMedium(pFormat.m_string, pLocation.m_string,
                                      cAccessMode, cDeviceType, &pResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(pResult);
}

VBox::COMPtr<VBox::IMedium> VBox::IVirtualBox::openMedium(
        const std::wstring &location, DeviceType deviceType,
        AccessMode accessMode, bool forceNewUuid)
{
    ::IMedium *pResult;
    COM_StringProxy pLocation(location);
    auto cDeviceType = static_cast<COM_Type(PRUint32, ::DeviceType)>(deviceType);
    auto cAccessMode = static_cast<COM_Type(PRUint32, ::AccessMode)>(accessMode);
    auto cForceNewUuid = static_cast<COM_Bool>(forceNewUuid);

    auto rc = get_IFC()->OpenMedium(pLocation.m_string, cDeviceType, cAccessMode,
                                    cForceNewUuid, &pResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(pResult);
}

VBox::COMPtr<VBox::IGuestOSType> VBox::IVirtualBox::getGuestOSType(
        const std::wstring &id)
{
    ::IGuestOSType *pResult;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->GetGuestOSType(pId.m_string, &pResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestOSType>::wrap(pResult);
}

void VBox::IVirtualBox::createSharedFolder(const std::wstring &name,
        const std::wstring &hostPath, bool writable, bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
      , const std::wstring &autoMountPoint
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

    auto rc = get_IFC()->CreateSharedFolder(pName.m_string, pHostPath.m_string,
                                            cWritable, cAutomount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
                                          , pAutoMountPoint.m_string
#endif
                                            );
    COM_ERROR_CHECK(rc);
}

void VBox::IVirtualBox::removeSharedFolder(const std::wstring &name)
{
    COM_StringProxy pName(name);
    auto rc = get_IFC()->RemoveSharedFolder(pName.m_string);
    COM_ERROR_CHECK(rc);
}

std::vector<std::wstring> VBox::IVirtualBox::getExtraDataKeys()
{
    COM_StringArrayProxy pResult;
    auto rc = get_IFC()->GetExtraDataKeys(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::wstring> result;
    pResult.toVector(result);
    return result;
}

std::wstring VBox::IVirtualBox::getExtraData(const std::wstring &key)
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetExtraData(pKey.m_string, &pResult.m_string);
    COM_ERROR_CHECK(rc);

    return pResult.toWString();
}

void VBox::IVirtualBox::setExtraData(const std::wstring &key,
        const std::wstring &value)
{
    COM_StringProxy pKey(key);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetExtraData(pKey.m_string, pValue.m_string);
    COM_ERROR_CHECK(rc);
}

void VBox::IVirtualBox::setSettingsSecret(const std::wstring &password)
{
    COM_StringProxy pPassword(password);
    auto rc = get_IFC()->SetSettingsSecret(pPassword.m_string);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IDHCPServer> VBox::IVirtualBox::createDHCPServer(
        const std::wstring &name)
{
    ::IDHCPServer *pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->CreateDHCPServer(pName.m_string, &pResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IDHCPServer>::wrap(pResult);
}

VBox::COMPtr<VBox::IDHCPServer> VBox::IVirtualBox::findDHCPServerByNetworkName(
        const std::wstring &name)
{
    ::IDHCPServer *pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindDHCPServerByNetworkName(pName.m_string, &pResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<IDHCPServer>::wrap(pResult);
}

void VBox::IVirtualBox::removeDHCPServer(const COMPtr<IDHCPServer> &server)
{
    auto rc = get_IFC()->RemoveDHCPServer(server->get_IFC());
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::INATNetwork> VBox::IVirtualBox::createNATNetwork(
        const std::wstring &networkName)
{
    ::INATNetwork *pResult;
    COM_StringProxy pNetworkName(networkName);

    auto rc = get_IFC()->CreateNATNetwork(pNetworkName.m_string, &pResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<INATNetwork>::wrap(pResult);
}

VBox::COMPtr<VBox::INATNetwork> VBox::IVirtualBox::findNATNetworkByName(
        const std::wstring &networkName)
{
    ::INATNetwork *pResult;
    COM_StringProxy pNetworkName(networkName);

    auto rc = get_IFC()->FindNATNetworkByName(pNetworkName.m_string, &pResult);
    COM_ERROR_CHECK(rc);
    return COMPtr<INATNetwork>::wrap(pResult);
}

void VBox::IVirtualBox::removeNATNetwork(const COMPtr<INATNetwork> &network)
{
    auto rc = get_IFC()->RemoveNATNetwork(network->get_IFC());
    COM_ERROR_CHECK(rc);
}

bool VBox::IVirtualBox::checkFirmwarePresent(FirmwareType firmwareType,
        const std::wstring &version, std::wstring &url, std::wstring &file)
{
    COM_Bool cResult;
    auto cFirmwareType = static_cast<COM_Type(PRUint32, ::FirmwareType)>(firmwareType);
    COM_StringProxy pVersion(version);
    COM_StringProxy pUrl;
    COM_StringProxy pFile;

    auto rc = get_IFC()->CheckFirmwarePresent(cFirmwareType, pVersion.m_string,
                                              &pUrl.m_string, &pFile.m_string,
                                              &cResult);
    COM_ERROR_CHECK(rc);

    url = pUrl.toWString();
    file = pFile.toWString();
    return static_cast<bool>(cResult);
}
