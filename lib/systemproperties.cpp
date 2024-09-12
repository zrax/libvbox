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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox::COMPtr<VBox::IPlatformProperties> VBox::ISystemProperties::platform() const
{
    COMPtr<IPlatformProperties> result;
    COM_GetValue_Wrap(get_IFC(), Platform, result);
    return result;
}
#endif

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

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
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
#endif

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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
std::u16string VBox::ISystemProperties::defaultCryptoExtPack() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultCryptoExtPack, result);
    return result;
}

void VBox::ISystemProperties::set_defaultCryptoExtPack(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultCryptoExtPack, value);
}
#endif

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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::ParavirtProvider> VBox::ISystemProperties::supportedParavirtProviders() const
{
    std::vector<ParavirtProvider> result;
    COM_GetArray(get_IFC(), SupportedParavirtProviders, COM_Enum(::ParavirtProvider), result);
    return result;
}
#else
std::vector<VBox::PlatformArchitecture>
VBox::ISystemProperties::supportedPlatformArchitectures() const
{
    std::vector<PlatformArchitecture> result;
    COM_GetArray(get_IFC(), SupportedPlatformArchitectures,
                 COM_Enum(::PlatformArchitecture), result);
    return result;
}
#endif

std::vector<VBox::ClipboardMode> VBox::ISystemProperties::supportedClipboardModes() const
{
    std::vector<ClipboardMode> result;
    COM_GetArray(get_IFC(), SupportedClipboardModes, COM_Enum(::ClipboardMode), result);
    return result;
}

std::vector<VBox::DnDMode> VBox::ISystemProperties::supportedDnDModes() const
{
    std::vector<DnDMode> result;
    COM_GetArray(get_IFC(), SupportedDnDModes, COM_Enum(::DnDMode), result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::FirmwareType> VBox::ISystemProperties::supportedFirmwareTypes() const
{
    std::vector<FirmwareType> result;
    COM_GetArray(get_IFC(), SupportedFirmwareTypes, COM_Enum(::FirmwareType), result);
    return result;
}
#endif

std::vector<VBox::PointingHIDType> VBox::ISystemProperties::supportedPointingHIDTypes() const
{
    std::vector<PointingHIDType> result;
    COM_GetArray(get_IFC(), SupportedPointingHIDTypes, COM_Enum(::PointingHIDType), result);
    return result;
}

std::vector<VBox::KeyboardHIDType> VBox::ISystemProperties::supportedKeyboardHIDTypes() const
{
    std::vector<KeyboardHIDType> result;
    COM_GetArray(get_IFC(), SupportedKeyboardHIDTypes, COM_Enum(::KeyboardHIDType), result);
    return result;
}

std::vector<VBox::VFSType> VBox::ISystemProperties::supportedVFSTypes() const
{
    std::vector<VFSType> result;
    COM_GetArray(get_IFC(), SupportedVFSTypes, COM_Enum(::VFSType), result);
    return result;
}

std::vector<VBox::ImportOptions> VBox::ISystemProperties::supportedImportOptions() const
{
    std::vector<ImportOptions> result;
    COM_GetArray(get_IFC(), SupportedImportOptions, COM_Enum(::ImportOptions), result);
    return result;
}

std::vector<VBox::ExportOptions> VBox::ISystemProperties::supportedExportOptions() const
{
    std::vector<ExportOptions> result;
    COM_GetArray(get_IFC(), SupportedExportOptions, COM_Enum(::ExportOptions), result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::GraphicsFeature>
VBox::ISystemProperties::supportedGraphicsFeatures() const
{
    std::vector<GraphicsFeature> result;
    COM_GetArray(get_IFC(), SupportedGraphicsFeatures,
                 COM_Enum(::GraphicsFeature), result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
std::vector<VBox::RecordingFeature>
VBox::ISystemProperties::supportedRecordingFeatures() const
{
    std::vector<RecordingFeature> result;
    COM_GetArray(get_IFC(), SupportedRecordingFeatures,
                 COM_Enum(::RecordingFeature), result);
    return result;
}
#endif

std::vector<VBox::RecordingAudioCodec>
VBox::ISystemProperties::supportedRecordingAudioCodecs() const
{
    std::vector<RecordingAudioCodec> result;
    COM_GetArray(get_IFC(), SupportedRecordingAudioCodecs,
                 COM_Enum(::RecordingAudioCodec), result);
    return result;
}

std::vector<VBox::RecordingVideoCodec>
VBox::ISystemProperties::supportedRecordingVideoCodecs() const
{
    std::vector<RecordingVideoCodec> result;
    COM_GetArray(get_IFC(), SupportedRecordingVideoCodecs,
                 COM_Enum(::RecordingVideoCodec), result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
std::vector<VBox::RecordingVideoScalingMethod>
VBox::ISystemProperties::supportedRecordingVSMethods() const
{
    std::vector<RecordingVideoScalingMethod> result;
    COM_GetArray(get_IFC(), SupportedRecordingVSMethods,
                 COM_Enum(::RecordingVideoScalingMethod), result);
    return result;
}

std::vector<VBox::RecordingVideoRateControlMode>
VBox::ISystemProperties::supportedRecordingVRCModes() const
{
    std::vector<RecordingVideoRateControlMode> result;
    COM_GetArray(get_IFC(), SupportedRecordingVRCModes,
                 COM_Enum(::RecordingVideoRateControlMode), result);
    return result;
}
#else
std::vector<VBox::RecordingVideoScalingMode>
VBox::ISystemProperties::supportedRecordingVSModes() const
{
    std::vector<RecordingVideoScalingMode> result;
    COM_GetArray(get_IFC(), SupportedRecordingVSModes,
                 COM_Enum(::RecordingVideoScalingMode), result);
    return result;
}

std::vector<VBox::RecordingRateControlMode>
VBox::ISystemProperties::supportedRecordingARCModes() const
{
    std::vector<RecordingRateControlMode> result;
    COM_GetArray(get_IFC(), SupportedRecordingARCModes,
                 COM_Enum(::RecordingRateControlMode), result);
    return result;
}

std::vector<VBox::RecordingRateControlMode>
VBox::ISystemProperties::supportedRecordingVRCModes() const
{
    std::vector<RecordingRateControlMode> result;
    COM_GetArray(get_IFC(), SupportedRecordingVRCModes,
                 COM_Enum(::RecordingRateControlMode), result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::GraphicsControllerType>
VBox::ISystemProperties::supportedGraphicsControllerTypes() const
{
    std::vector<GraphicsControllerType> result;
    COM_GetArray(get_IFC(), SupportedGraphicsControllerTypes,
                 COM_Enum(::GraphicsControllerType), result);
    return result;
}
#endif

std::vector<VBox::CloneOptions> VBox::ISystemProperties::supportedCloneOptions() const
{
    std::vector<CloneOptions> result;
    COM_GetArray(get_IFC(), SupportedCloneOptions, COM_Enum(::CloneOptions), result);
    return result;
}

std::vector<VBox::AutostopType> VBox::ISystemProperties::supportedAutostopTypes() const
{
    std::vector<AutostopType> result;
    COM_GetArray(get_IFC(), SupportedAutostopTypes, COM_Enum(::AutostopType), result);
    return result;
}

std::vector<VBox::VMProcPriority> VBox::ISystemProperties::supportedVMProcPriorities() const
{
    std::vector<VMProcPriority> result;
    COM_GetArray(get_IFC(), SupportedVMProcPriorities, COM_Enum(::VMProcPriority), result);
    return result;
}

std::vector<VBox::NetworkAttachmentType>
VBox::ISystemProperties::supportedNetworkAttachmentTypes() const
{
    std::vector<NetworkAttachmentType> result;
    COM_GetArray(get_IFC(), SupportedNetworkAttachmentTypes,
                 COM_Enum(::NetworkAttachmentType), result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::NetworkAdapterType>
VBox::ISystemProperties::supportedNetworkAdapterTypes() const
{
    std::vector<NetworkAdapterType> result;
    COM_GetArray(get_IFC(), SupportedNetworkAdapterTypes,
                 COM_Enum(::NetworkAdapterType), result);
    return result;
}
#endif

std::vector<VBox::PortMode> VBox::ISystemProperties::supportedPortModes() const
{
    std::vector<PortMode> result;
    COM_GetArray(get_IFC(), SupportedPortModes, COM_Enum(::PortMode), result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::UartType> VBox::ISystemProperties::supportedUartTypes() const
{
    std::vector<UartType> result;
    COM_GetArray(get_IFC(), SupportedUartTypes, COM_Enum(::UartType), result);
    return result;
}

std::vector<VBox::USBControllerType> VBox::ISystemProperties::supportedUSBControllerTypes() const
{
    std::vector<USBControllerType> result;
    COM_GetArray(get_IFC(), SupportedUSBControllerTypes, COM_Enum(::USBControllerType), result);
    return result;
}
#endif

std::vector<VBox::AudioDriverType> VBox::ISystemProperties::supportedAudioDriverTypes() const
{
    std::vector<AudioDriverType> result;
    COM_GetArray(get_IFC(), SupportedAudioDriverTypes, COM_Enum(::AudioDriverType), result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::AudioControllerType> VBox::ISystemProperties::supportedAudioControllerTypes() const
{
    std::vector<AudioControllerType> result;
    COM_GetArray(get_IFC(), SupportedAudioControllerTypes, COM_Enum(::AudioControllerType), result);
    return result;
}

std::vector<VBox::StorageBus> VBox::ISystemProperties::supportedStorageBuses() const
{
    std::vector<StorageBus> result;
    COM_GetArray(get_IFC(), SupportedStorageBuses, COM_Enum(::StorageBus), result);
    return result;
}

std::vector<VBox::StorageControllerType> VBox::ISystemProperties::supportedStorageControllerTypes() const
{
    std::vector<StorageControllerType> result;
    COM_GetArray(get_IFC(), SupportedStorageControllerTypes, COM_Enum(::StorageControllerType), result);
    return result;
}

std::vector<VBox::ChipsetType> VBox::ISystemProperties::supportedChipsetTypes() const
{
    std::vector<ChipsetType> result;
    COM_GetArray(get_IFC(), SupportedChipsetTypes, COM_Enum(::ChipsetType), result);
    return result;
}
#endif
#endif

#if (VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)) \
    && (VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0))
std::vector<VBox::IommuType> VBox::ISystemProperties::supportedIommuTypes() const
{
    std::vector<IommuType> result;
    COM_GetArray(get_IFC(), SupportedIommuTypes, COM_Enum(::IommuType), result);
    return result;
}

std::vector<VBox::TpmType> VBox::ISystemProperties::supportedTpmTypes() const
{
    std::vector<TpmType> result;
    COM_GetArray(get_IFC(), SupportedTpmTypes, COM_Enum(::TpmType), result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
std::u16string VBox::ISystemProperties::languageId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LanguageId, result);
    return result;
}

void VBox::ISystemProperties::set_languageId(const std::u16string &value)
{
    COM_SetString(get_IFC(), LanguageId, value);
}
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox::StorageBus VBox::ISystemProperties::getStorageBusForStorageControllerType(
        StorageControllerType storageControllerType)
{
    COM_Enum(::StorageBus) cResult;
    auto cStorageControllerType = static_cast<COM_Enum(::StorageControllerType)>(storageControllerType);

    auto rc = get_IFC()->GetStorageBusForStorageControllerType(cStorageControllerType,
                &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<StorageBus>(cResult);
}

std::vector<VBox::StorageControllerType>
VBox::ISystemProperties::getStorageControllerTypesForStorageBus(StorageBus storageBus)
{
    COM_ArrayProxy<COM_Enum(::StorageControllerType)> pResult;
    auto cStorageBus = static_cast<COM_Enum(::StorageBus)>(storageBus);

    auto rc = get_IFC()->GetStorageControllerTypesForStorageBus(cStorageBus,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<StorageControllerType> result;
    pResult.toVector(result);
    return result;
}
#endif
#endif

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

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
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
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
std::vector<VBox::COMPtr<VBox::ICPUProfile>> VBox::ISystemProperties::getCPUProfiles(
        CPUArchitecture architecture, const std::u16string &namePattern)
{
    COM_ArrayProxy<::ICPUProfile *> pResult;
    COM_StringProxy pNamePattern(namePattern);

    auto rc = get_IFC()->GetCPUProfiles(static_cast<COM_Enum(::CPUArchitecture)>(architecture),
                pNamePattern.m_text, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<ICPUProfile>> result;
    pResult.toVector(result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::VMExecutionEngine>
VBox::ISystemProperties::getExecutionEnginesForVmCpuArchitecture(CPUArchitecture cpuArchitecture)
{
    COM_ArrayProxy<COM_Enum(::VMExecutionEngine)> pResult;
    auto cCpuArchitecture = static_cast<COM_Enum(::CPUArchitecture)>(cpuArchitecture);

    auto rc = get_IFC()->GetExecutionEnginesForVmCpuArchitecture(cCpuArchitecture,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<VMExecutionEngine> result;
    pResult.toVector(result);
    return result;
}
#endif
