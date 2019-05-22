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

COM_WRAP_IFC(ISystemProperties)

uint32_t VBox::ISystemProperties::minGuestRAM() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MinGuestRAM, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::maxGuestRAM() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxGuestRAM, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::minGuestVRAM() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MinGuestVRAM, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::maxGuestVRAM() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxGuestVRAM, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::minGuestCPUCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MinGuestCPUCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::maxGuestCPUCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxGuestCPUCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::maxGuestMonitors() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxGuestMonitors, result);
    return static_cast<uint32_t>(result);
}

int64_t VBox::ISystemProperties::infoVDSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), InfoVDSize, result);
    return static_cast<int64_t>(result);
}

uint32_t VBox::ISystemProperties::serialPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SerialPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::parallelPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ParallelPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISystemProperties::maxBootPosition() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxBootPosition, result);
    return static_cast<uint32_t>(result);
}

bool VBox::ISystemProperties::rawModeSupported() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RawModeSupported, result);
    return static_cast<bool>(result);
}

bool VBox::ISystemProperties::exclusiveHwVirt() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ExclusiveHwVirt, result);
    return static_cast<bool>(result);
}

void VBox::ISystemProperties::set_exclusiveHwVirt(bool value)
{
    COM_SetValue(get_IFC(), ExclusiveHwVirt, value);
}

std::u16string VBox::ISystemProperties::defaultMachineFolder() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultMachineFolder, result);
    return result;
}

void VBox::ISystemProperties::set_defaultMachineFolder(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultMachineFolder, value);
}

std::u16string VBox::ISystemProperties::loggingLevel() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LoggingLevel, result);
    return result;
}

void VBox::ISystemProperties::set_loggingLevel(const std::u16string &value)
{
    COM_SetString(get_IFC(), LoggingLevel, value);
}

std::vector<VBox::COMPtr<VBox::IMediumFormat>>
VBox::ISystemProperties::mediumFormats() const
{
    std::vector<COMPtr<IMediumFormat>> result;
    COM_GetArray_Wrap(get_IFC(), MediumFormats, result);
    return result;
}

std::u16string VBox::ISystemProperties::defaultHardDiskFormat() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultHardDiskFormat, result);
    return result;
}

void VBox::ISystemProperties::set_defaultHardDiskFormat(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultHardDiskFormat, value);
}

int64_t VBox::ISystemProperties::freeDiskSpaceWarning() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), FreeDiskSpaceWarning, result);
    return static_cast<int64_t>(result);
}

void VBox::ISystemProperties::set_freeDiskSpaceWarning(int64_t value)
{
    COM_SetValue(get_IFC(), FreeDiskSpaceWarning, value);
}

uint32_t VBox::ISystemProperties::freeDiskSpacePercentWarning() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), FreeDiskSpacePercentWarning, result);
    return static_cast<uint32_t>(result);
}

void VBox::ISystemProperties::set_freeDiskSpacePercentWarning(uint32_t value)
{
    COM_SetValue(get_IFC(), FreeDiskSpacePercentWarning, value);
}

int64_t VBox::ISystemProperties::freeDiskSpaceError() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), FreeDiskSpaceError, result);
    return static_cast<int64_t>(result);
}

void VBox::ISystemProperties::set_freeDiskSpaceError(int64_t value)
{
    COM_SetValue(get_IFC(), FreeDiskSpaceError, value);
}

uint32_t VBox::ISystemProperties::freeDiskSpacePercentError() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), FreeDiskSpacePercentError, result);
    return static_cast<uint32_t>(result);
}

void VBox::ISystemProperties::set_freeDiskSpacePercentError(uint32_t value)
{
    COM_SetValue(get_IFC(), FreeDiskSpacePercentError, value);
}

std::u16string VBox::ISystemProperties::VRDEAuthLibrary() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VRDEAuthLibrary, result);
    return result;
}

void VBox::ISystemProperties::set_VRDEAuthLibrary(const std::u16string &value)
{
    COM_SetString(get_IFC(), VRDEAuthLibrary, value);
}

std::u16string VBox::ISystemProperties::webServiceAuthLibrary() const
{
    std::u16string result;
    COM_GetString(get_IFC(), WebServiceAuthLibrary, result);
    return result;
}

void VBox::ISystemProperties::set_webServiceAuthLibrary(const std::u16string &value)
{
    COM_SetString(get_IFC(), WebServiceAuthLibrary, value);
}

std::u16string VBox::ISystemProperties::defaultVRDEExtPack() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultVRDEExtPack, result);
    return result;
}

void VBox::ISystemProperties::set_defaultVRDEExtPack(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultVRDEExtPack, value);
}

uint32_t VBox::ISystemProperties::logHistoryCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), LogHistoryCount, result);
    return static_cast<uint32_t>(result);
}

void VBox::ISystemProperties::set_logHistoryCount(uint32_t value)
{
    COM_SetValue(get_IFC(), LogHistoryCount, value);
}

VBox::AudioDriverType VBox::ISystemProperties::defaultAudioDriver() const
{
    COM_Enum(::AudioDriverType) result;
    COM_GetValue(get_IFC(), DefaultAudioDriver, result);
    return static_cast<AudioDriverType>(result);
}

std::u16string VBox::ISystemProperties::autostartDatabasePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AutostartDatabasePath, result);
    return result;
}

void VBox::ISystemProperties::set_autostartDatabasePath(const std::u16string &value)
{
    COM_SetString(get_IFC(), AutostartDatabasePath, value);
}

std::u16string VBox::ISystemProperties::defaultAdditionsISO() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultAdditionsISO, result);
    return result;
}

void VBox::ISystemProperties::set_defaultAdditionsISO(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultAdditionsISO, value);
}

std::u16string VBox::ISystemProperties::defaultFrontend() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultFrontend, result);
    return result;
}

void VBox::ISystemProperties::set_defaultFrontend(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultFrontend, value);
}

std::vector<VBox::BitmapFormat> VBox::ISystemProperties::screenShotFormats() const
{
    std::vector<BitmapFormat> result;
    COM_GetArray(get_IFC(), ScreenShotFormats, COM_Enum(::BitmapFormat), result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::ProxyMode VBox::ISystemProperties::proxyMode() const
{
    COM_Enum(::ProxyMode) result;
    COM_GetValue(get_IFC(), ProxyMode, result);
    return static_cast<ProxyMode>(result);
}

void VBox::ISystemProperties::set_proxyMode(ProxyMode value)
{
    COM_SetValue(get_IFC(), ProxyMode, static_cast<COM_Enum(::ProxyMode)>(value));
}

std::u16string VBox::ISystemProperties::proxyURL() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ProxyURL, result);
    return result;
}

void VBox::ISystemProperties::set_proxyURL(const std::u16string &value)
{
    COM_SetString(get_IFC(), ProxyURL, value);
}
#endif

uint32_t VBox::ISystemProperties::getMaxNetworkAdapters(ChipsetType chipset)
{
    COM_ULong cResult;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);

    auto rc = get_IFC()->GetMaxNetworkAdapters(cChipset, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::ISystemProperties::getMaxNetworkAdaptersOfType(
        ChipsetType chipset, NetworkAttachmentType type)
{
    COM_ULong cResult;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);
    auto cType = static_cast<COM_Enum(::NetworkAttachmentType)>(type);

    auto rc = get_IFC()->GetMaxNetworkAdaptersOfType(cChipset, cType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::ISystemProperties::getMaxDevicesPerPortForStorageBus(StorageBus bus)
{
    COM_ULong cResult;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMaxDevicesPerPortForStorageBus(cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::ISystemProperties::getMinPortCountForStorageBus(StorageBus bus)
{
    COM_ULong cResult;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMinPortCountForStorageBus(cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::ISystemProperties::getMaxPortCountForStorageBus(StorageBus bus)
{
    COM_ULong cResult;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMaxPortCountForStorageBus(cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::ISystemProperties::getMaxInstancesOfStorageBus(
        ChipsetType chipset, StorageBus bus)
{
    COM_ULong cResult;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMaxInstancesOfStorageBus(cChipset, cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

std::vector<VBox::DeviceType> VBox::ISystemProperties::getDeviceTypesForStorageBus(
        StorageBus bus)
{
    COM_ArrayProxy<COM_Enum(::DeviceType)> pResult;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetDeviceTypesForStorageBus(cBus,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<DeviceType> result;
    pResult.toVector(result);
    return result;
}

bool VBox::ISystemProperties::getDefaultIoCacheSettingForStorageController(
        StorageControllerType controllerType)
{
    COM_Bool cResult;
    auto cControllerType = static_cast<COM_Enum(::StorageControllerType)>(controllerType);

    auto rc = get_IFC()->GetDefaultIoCacheSettingForStorageController(
                cControllerType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

bool VBox::ISystemProperties::getStorageControllerHotplugCapable(
        StorageControllerType controllerType)
{
    COM_Bool cResult;
    auto cControllerType = static_cast<COM_Enum(::StorageControllerType)>(controllerType);

    auto rc = get_IFC()->GetStorageControllerHotplugCapable(cControllerType,
                &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

uint32_t VBox::ISystemProperties::getMaxInstancesOfUSBControllerType(
        ChipsetType chipset, USBControllerType type)
{
    COM_ULong cResult;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);
    auto cType = static_cast<COM_Enum(::USBControllerType)>(type);

    auto rc = get_IFC()->GetMaxInstancesOfUSBControllerType(cChipset, cType,
                &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}
