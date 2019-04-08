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
