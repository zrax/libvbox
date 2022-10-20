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

COM_WRAP_IFC(IMachine)

VBox::COMPtr<VBox::IVirtualBox> VBox::IMachine::parent() const
{
    COMPtr<IVirtualBox> result;
    COM_GetValue_Wrap(get_IFC(), Parent, result);
    return result;
}

std::vector<uint8_t> VBox::IMachine::icon() const
{
    std::vector<uint8_t> result;
    COM_GetArray(get_IFC(), Icon, COM_Byte, result);
    return result;
}

void VBox::IMachine::set_icon(const std::vector<uint8_t> &value)
{
    COM_SetArray(get_IFC(), Icon, COM_Byte, value);
}

bool VBox::IMachine::accessible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accessible, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo> VBox::IMachine::accessError() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), AccessError, result);
    return result;
}

std::u16string VBox::IMachine::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IMachine::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

std::u16string VBox::IMachine::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

void VBox::IMachine::set_description(const std::u16string &value)
{
    COM_SetString(get_IFC(), Description, value);
}

std::u16string VBox::IMachine::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::vector<std::u16string> VBox::IMachine::groups() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Groups, result);
    return result;
}

void VBox::IMachine::set_groups(const std::vector<std::u16string> &value)
{
    COM_SetStringArray(get_IFC(), Groups, value);
}

std::u16string VBox::IMachine::OSTypeId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OSTypeId, result);
    return result;
}

void VBox::IMachine::set_OSTypeId(const std::u16string &value)
{
    COM_SetString(get_IFC(), OSTypeId, value);
}

std::u16string VBox::IMachine::hardwareVersion() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HardwareVersion, result);
    return result;
}

void VBox::IMachine::set_hardwareVersion(const std::u16string &value)
{
    COM_SetString(get_IFC(), HardwareVersion, value);
}

std::u16string VBox::IMachine::hardwareUUID() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HardwareUUID, result);
    return result;
}

void VBox::IMachine::set_hardwareUUID(const std::u16string &value)
{
    COM_SetString(get_IFC(), HardwareUUID, value);
}

uint32_t VBox::IMachine::CPUCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), CPUCount, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_CPUCount(uint32_t value)
{
    COM_SetValue(get_IFC(), CPUCount, value);
}

bool VBox::IMachine::CPUHotPlugEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), CPUHotPlugEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_CPUHotPlugEnabled(bool value)
{
    COM_SetValue(get_IFC(), CPUHotPlugEnabled, value);
}

uint32_t VBox::IMachine::CPUExecutionCap() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), CPUExecutionCap, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_CPUExecutionCap(uint32_t value)
{
    COM_SetValue(get_IFC(), CPUExecutionCap, value);
}

uint32_t VBox::IMachine::CPUIDPortabilityLevel() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), CPUIDPortabilityLevel, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_CPUIDPortabilityLevel(uint32_t value)
{
    COM_SetValue(get_IFC(), CPUIDPortabilityLevel, value);
}

uint32_t VBox::IMachine::memorySize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MemorySize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_memorySize(uint32_t value)
{
    COM_SetValue(get_IFC(), MemorySize, value);
}

uint32_t VBox::IMachine::memoryBalloonSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MemoryBalloonSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_memoryBalloonSize(uint32_t value)
{
    COM_SetValue(get_IFC(), MemoryBalloonSize, value);
}

bool VBox::IMachine::pageFusionEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), PageFusionEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_pageFusionEnabled(bool value)
{
    COM_SetValue(get_IFC(), PageFusionEnabled, value);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
VBox::GraphicsControllerType VBox::IMachine::graphicsControllerType() const
{
    COM_Enum(::GraphicsControllerType) result;
    COM_GetValue(get_IFC(), GraphicsControllerType, result);
    return static_cast<GraphicsControllerType>(result);
}

void VBox::IMachine::set_graphicsControllerType(GraphicsControllerType value)
{
    auto cValue = static_cast<COM_Enum(::GraphicsControllerType)>(value);
    COM_SetValue(get_IFC(), GraphicsControllerType, cValue);
}

uint32_t VBox::IMachine::VRAMSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VRAMSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_VRAMSize(uint32_t value)
{
    COM_SetValue(get_IFC(), VRAMSize, value);
}

bool VBox::IMachine::accelerate3DEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accelerate3DEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_accelerate3DEnabled(bool value)
{
    COM_SetValue(get_IFC(), Accelerate3DEnabled, value);
}

bool VBox::IMachine::accelerate2DVideoEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accelerate2DVideoEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_accelerate2DVideoEnabled(bool value)
{
    COM_SetValue(get_IFC(), Accelerate2DVideoEnabled, value);
}

uint32_t VBox::IMachine::monitorCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MonitorCount, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_monitorCount(uint32_t value)
{
    COM_SetValue(get_IFC(), MonitorCount, value);
}
#else
VBox::COMPtr<VBox::IGraphicsAdapter> VBox::IMachine::graphicsAdapter() const
{
    COMPtr<IGraphicsAdapter> result;
    COM_GetValue_Wrap(get_IFC(), GraphicsAdapter, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
bool VBox::IMachine::videoCaptureEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), VideoCaptureEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_videoCaptureEnabled(bool value)
{
    COM_SetValue(get_IFC(), VideoCaptureEnabled, value);
}

std::vector<bool> VBox::IMachine::videoCaptureScreens() const
{
    std::vector<bool> result;
    COM_GetArray(get_IFC(), VideoCaptureScreens, COM_Bool, result);
    return result;
}

void VBox::IMachine::set_videoCaptureScreens(const std::vector<bool> &value)
{
    COM_SetArray(get_IFC(), VideoCaptureScreens, COM_Bool, value);
}

std::u16string VBox::IMachine::videoCaptureFile() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VideoCaptureFile, result);
    return result;
}

void VBox::IMachine::set_videoCaptureFile(const std::u16string &value)
{
    COM_SetString(get_IFC(), VideoCaptureFile, value);
}

uint32_t VBox::IMachine::videoCaptureWidth() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoCaptureWidth, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_videoCaptureWidth(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoCaptureWidth, value);
}

uint32_t VBox::IMachine::videoCaptureHeight() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoCaptureHeight, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_videoCaptureHeight(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoCaptureHeight, value);
}

uint32_t VBox::IMachine::videoCaptureRate() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoCaptureRate, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_videoCaptureRate(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoCaptureRate, value);
}

uint32_t VBox::IMachine::videoCaptureFPS() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoCaptureFPS, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_videoCaptureFPS(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoCaptureFPS, value);
}

uint32_t VBox::IMachine::videoCaptureMaxTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoCaptureMaxTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_videoCaptureMaxTime(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoCaptureMaxTime, value);
}

uint32_t VBox::IMachine::videoCaptureMaxFileSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoCaptureMaxFileSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_videoCaptureMaxFileSize(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoCaptureMaxFileSize, value);
}

std::u16string VBox::IMachine::videoCaptureOptions() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VideoCaptureOptions, result);
    return result;
}

void VBox::IMachine::set_videoCaptureOptions(const std::u16string &value)
{
    COM_SetString(get_IFC(), VideoCaptureOptions, value);
}
#endif

VBox::COMPtr<VBox::IBIOSSettings> VBox::IMachine::BIOSSettings() const
{
    COMPtr<IBIOSSettings> result;
    COM_GetValue_Wrap(get_IFC(), BIOSSettings, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::ITrustedPlatformModule> VBox::IMachine::trustedPlatformModule() const
{
    COMPtr<ITrustedPlatformModule> result;
    COM_GetValue_Wrap(get_IFC(), TrustedPlatformModule, result);
    return result;
}

VBox::COMPtr<VBox::INvramStore> VBox::IMachine::nonVolatileStore() const
{
    COMPtr<INvramStore> result;
    COM_GetValue_Wrap(get_IFC(), NonVolatileStore, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IRecordingSettings> VBox::IMachine::recordingSettings() const
{
    COMPtr<IRecordingSettings> result;
    COM_GetValue_Wrap(get_IFC(), RecordingSettings, result);
    return result;
}
#endif

VBox::FirmwareType VBox::IMachine::firmwareType() const
{
    COM_Enum(::FirmwareType) result;
    COM_GetValue(get_IFC(), FirmwareType, result);
    return static_cast<FirmwareType>(result);
}

void VBox::IMachine::set_firmwareType(FirmwareType value)
{
    auto cValue = static_cast<COM_Enum(::FirmwareType)>(value);
    COM_SetValue(get_IFC(), FirmwareType, cValue);
}

VBox::PointingHIDType VBox::IMachine::pointingHIDType() const
{
    COM_Enum(::PointingHIDType) result;
    COM_GetValue(get_IFC(), PointingHIDType, result);
    return static_cast<PointingHIDType>(result);
}

void VBox::IMachine::set_pointingHIDType(PointingHIDType value)
{
    auto cValue = static_cast<COM_Enum(::PointingHIDType)>(value);
    COM_SetValue(get_IFC(), PointingHIDType, cValue);
}

VBox::KeyboardHIDType VBox::IMachine::keyboardHIDType() const
{
    COM_Enum(::KeyboardHIDType) result;
    COM_GetValue(get_IFC(), KeyboardHIDType, result);
    return static_cast<KeyboardHIDType>(result);
}

void VBox::IMachine::set_keyboardHIDType(KeyboardHIDType value)
{
    auto cValue = static_cast<COM_Enum(::KeyboardHIDType)>(value);
    COM_SetValue(get_IFC(), KeyboardHIDType, cValue);
}

bool VBox::IMachine::HPETEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HPETEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_HPETEnabled(bool value)
{
    COM_SetValue(get_IFC(), HPETEnabled, value);
}

VBox::ChipsetType VBox::IMachine::chipsetType() const
{
    COM_Enum(::ChipsetType) result;
    COM_GetValue(get_IFC(), ChipsetType, result);
    return static_cast<ChipsetType>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::IommuType VBox::IMachine::iommuType() const
{
    COM_Enum(::IommuType) result;
    COM_GetValue(get_IFC(), IommuType, result);
    return static_cast<IommuType>(result);
}

void VBox::IMachine::set_iommuType(IommuType value)
{
    COM_SetValue(get_IFC(), IommuType, static_cast<COM_Enum(::IommuType)>(value));
}
#endif

void VBox::IMachine::set_chipsetType(ChipsetType value)
{
    auto cValue = static_cast<COM_Enum(::ChipsetType)>(value);
    COM_SetValue(get_IFC(), ChipsetType, cValue);
}

std::u16string VBox::IMachine::snapshotFolder() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SnapshotFolder, result);
    return result;
}

void VBox::IMachine::set_snapshotFolder(const std::u16string &value)
{
    COM_SetString(get_IFC(), SnapshotFolder, value);
}

VBox::COMPtr<VBox::IVRDEServer> VBox::IMachine::VRDEServer() const
{
    COMPtr<IVRDEServer> result;
    COM_GetValue_Wrap(get_IFC(), VRDEServer, result);
    return result;
}

bool VBox::IMachine::emulatedUSBCardReaderEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), EmulatedUSBCardReaderEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_emulatedUSBCardReaderEnabled(bool value)
{
    COM_SetValue(get_IFC(), EmulatedUSBCardReaderEnabled, value);
}

std::vector<VBox::COMPtr<VBox::IMediumAttachment>> VBox::IMachine::mediumAttachments() const
{
    std::vector<COMPtr<IMediumAttachment>> result;
    COM_GetArray_Wrap(get_IFC(), MediumAttachments, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IUSBController>> VBox::IMachine::USBControllers() const
{
    std::vector<COMPtr<IUSBController>> result;
    COM_GetArray_Wrap(get_IFC(), USBControllers, result);
    return result;
}

VBox::COMPtr<VBox::IUSBDeviceFilters> VBox::IMachine::USBDeviceFilters() const
{
    COMPtr<IUSBDeviceFilters> result;
    COM_GetValue_Wrap(get_IFC(), USBDeviceFilters, result);
    return result;
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::IAudioAdapter> VBox::IMachine::audioAdapter() const
{
    COMPtr<IAudioAdapter> result;
    COM_GetValue_Wrap(get_IFC(), AudioAdapter, result);
    return result;
}
#else
VBox::COMPtr<VBox::IAudioSettings> VBox::IMachine::audioSettings() const
{
    COMPtr<IAudioSettings> result;
    COM_GetValue_Wrap(get_IFC(), AudioSettings, result);
    return result;
}
#endif

std::vector<VBox::COMPtr<VBox::IStorageController>> VBox::IMachine::storageControllers() const
{
    std::vector<COMPtr<IStorageController>> result;
    COM_GetArray_Wrap(get_IFC(), StorageControllers, result);
    return result;
}

std::u16string VBox::IMachine::settingsFilePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SettingsFilePath, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
std::u16string VBox::IMachine::settingsAuxFilePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SettingsAuxFilePath, result);
    return result;
}
#endif

bool VBox::IMachine::settingsModified() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), SettingsModified, result);
    return static_cast<bool>(result);
}

VBox::SessionState VBox::IMachine::sessionState() const
{
    COM_Enum(::SessionState) result;
    COM_GetValue(get_IFC(), SessionState, result);
    return static_cast<SessionState>(result);
}

std::u16string VBox::IMachine::sessionName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SessionName, result);
    return result;
}

uint32_t VBox::IMachine::sessionPID() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SessionPID, result);
    return static_cast<uint32_t>(result);
}

VBox::MachineState VBox::IMachine::state() const
{
    COM_Enum(::MachineState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<MachineState>(result);
}

int64_t VBox::IMachine::lastStateChange() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), LastStateChange, result);
    return static_cast<int64_t>(result);
}

std::u16string VBox::IMachine::stateFilePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), StateFilePath, result);
    return result;
}

std::u16string VBox::IMachine::logFolder() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogFolder, result);
    return result;
}

VBox::COMPtr<VBox::ISnapshot> VBox::IMachine::currentSnapshot() const
{
    COMPtr<ISnapshot> result;
    COM_GetValue_Wrap(get_IFC(), CurrentSnapshot, result);
    return result;
}

uint32_t VBox::IMachine::snapshotCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SnapshotCount, result);
    return static_cast<uint32_t>(result);
}

bool VBox::IMachine::currentStateModified() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), CurrentStateModified, result);
    return static_cast<bool>(result);
}

std::vector<VBox::COMPtr<VBox::ISharedFolder>> VBox::IMachine::sharedFolders() const
{
    std::vector<COMPtr<ISharedFolder>> result;
    COM_GetArray_Wrap(get_IFC(), SharedFolders, result);
    return result;
}

VBox::ClipboardMode VBox::IMachine::clipboardMode() const
{
    COM_Enum(::ClipboardMode) result;
    COM_GetValue(get_IFC(), ClipboardMode, result);
    return static_cast<ClipboardMode>(result);
}

void VBox::IMachine::set_clipboardMode(ClipboardMode value)
{
    auto cValue = static_cast<COM_Enum(::ClipboardMode)>(value);
    COM_SetValue(get_IFC(), ClipboardMode, cValue);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
bool VBox::IMachine::clipboardFileTransfersEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ClipboardFileTransfersEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_clipboardFileTransfersEnabled(bool value)
{
    COM_SetValue(get_IFC(), ClipboardFileTransfersEnabled, value);
}
#endif

VBox::DnDMode VBox::IMachine::dnDMode() const
{
    COM_Enum(::DnDMode) result;
    COM_GetValue(get_IFC(), DnDMode, result);
    return static_cast<DnDMode>(result);
}

void VBox::IMachine::set_dnDMode(DnDMode value)
{
    auto cValue = static_cast<COM_Enum(::DnDMode)>(value);
    COM_SetValue(get_IFC(), DnDMode, cValue);
}

bool VBox::IMachine::teleporterEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), TeleporterEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_teleporterEnabled(bool value)
{
    COM_SetValue(get_IFC(), TeleporterEnabled, value);
}

uint32_t VBox::IMachine::teleporterPort() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), TeleporterPort, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_teleporterPort(uint32_t value)
{
    COM_SetValue(get_IFC(), TeleporterPort, value);
}

std::u16string VBox::IMachine::teleporterAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TeleporterAddress, result);
    return result;
}

void VBox::IMachine::set_teleporterAddress(const std::u16string &value)
{
    COM_SetString(get_IFC(), TeleporterAddress, value);
}

std::u16string VBox::IMachine::teleporterPassword() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TeleporterPassword, result);
    return result;
}

void VBox::IMachine::set_teleporterPassword(const std::u16string &value)
{
    COM_SetString(get_IFC(), TeleporterPassword, value);
}

VBox::ParavirtProvider VBox::IMachine::paravirtProvider() const
{
    COM_Enum(::ParavirtProvider) result;
    COM_GetValue(get_IFC(), ParavirtProvider, result);
    return static_cast<ParavirtProvider>(result);
}

void VBox::IMachine::set_paravirtProvider(ParavirtProvider value)
{
    auto cValue = static_cast<COM_Enum(::ParavirtProvider)>(value);
    COM_SetValue(get_IFC(), ParavirtProvider, cValue);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
VBox::FaultToleranceState VBox::IMachine::faultToleranceState() const
{
    COM_Enum(::FaultToleranceState) result;
    COM_GetValue(get_IFC(), FaultToleranceState, result);
    return static_cast<FaultToleranceState>(result);
}

void VBox::IMachine::set_faultToleranceState(FaultToleranceState value)
{
    auto cValue = static_cast<COM_Enum(::FaultToleranceState)>(value);
    COM_SetValue(get_IFC(), FaultToleranceState, cValue);
}

uint32_t VBox::IMachine::faultTolerancePort() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), FaultTolerancePort, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_faultTolerancePort(uint32_t value)
{
    COM_SetValue(get_IFC(), FaultTolerancePort, value);
}

std::u16string VBox::IMachine::faultToleranceAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FaultToleranceAddress, result);
    return result;
}

void VBox::IMachine::set_faultToleranceAddress(const std::u16string &value)
{
    COM_SetString(get_IFC(), FaultToleranceAddress, value);
}

std::u16string VBox::IMachine::faultTolerancePassword() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FaultTolerancePassword, result);
    return result;
}

void VBox::IMachine::set_faultTolerancePassword(const std::u16string &value)
{
    COM_SetString(get_IFC(), FaultTolerancePassword, value);
}

uint32_t VBox::IMachine::faultToleranceSyncInterval() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), FaultToleranceSyncInterval, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_faultToleranceSyncInterval(uint32_t value)
{
    COM_SetValue(get_IFC(), FaultToleranceSyncInterval, value);
}
#endif

bool VBox::IMachine::RTCUseUTC() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RTCUseUTC, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_RTCUseUTC(bool value)
{
    COM_SetValue(get_IFC(), RTCUseUTC, value);
}

bool VBox::IMachine::IOCacheEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IOCacheEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_IOCacheEnabled(bool value)
{
    COM_SetValue(get_IFC(), IOCacheEnabled, value);
}

uint32_t VBox::IMachine::IOCacheSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IOCacheSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_IOCacheSize(uint32_t value)
{
    COM_SetValue(get_IFC(), IOCacheSize, value);
}

std::vector<VBox::COMPtr<VBox::IPCIDeviceAttachment>> VBox::IMachine::PCIDeviceAssignments() const
{
    std::vector<COMPtr<IPCIDeviceAttachment>> result;
    COM_GetArray_Wrap(get_IFC(), PCIDeviceAssignments, result);
    return result;
}

VBox::COMPtr<VBox::IBandwidthControl> VBox::IMachine::bandwidthControl() const
{
    COMPtr<IBandwidthControl> result;
    COM_GetValue_Wrap(get_IFC(), BandwidthControl, result);
    return result;
}

bool VBox::IMachine::tracingEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), TracingEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_tracingEnabled(bool value)
{
    COM_SetValue(get_IFC(), TracingEnabled, value);
}

std::u16string VBox::IMachine::tracingConfig() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TracingConfig, result);
    return result;
}

void VBox::IMachine::set_tracingConfig(const std::u16string &value)
{
    COM_SetString(get_IFC(), TracingConfig, value);
}

bool VBox::IMachine::allowTracingToAccessVM() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AllowTracingToAccessVM, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_allowTracingToAccessVM(bool value)
{
    COM_SetValue(get_IFC(), AllowTracingToAccessVM, value);
}

bool VBox::IMachine::autostartEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AutostartEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachine::set_autostartEnabled(bool value)
{
    COM_SetValue(get_IFC(), AutostartEnabled, value);
}

uint32_t VBox::IMachine::autostartDelay() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AutostartDelay, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachine::set_autostartDelay(uint32_t value)
{
    COM_SetValue(get_IFC(), AutostartDelay, value);
}

VBox::AutostopType VBox::IMachine::autostopType() const
{
    COM_Enum(::AutostopType) result;
    COM_GetValue(get_IFC(), AutostopType, result);
    return static_cast<AutostopType>(result);
}

void VBox::IMachine::set_autostopType(AutostopType value)
{
    auto cValue = static_cast<COM_Enum(::AutostopType)>(value);
    COM_SetValue(get_IFC(), AutostopType, cValue);
}

std::u16string VBox::IMachine::defaultFrontend() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DefaultFrontend, result);
    return result;
}

void VBox::IMachine::set_defaultFrontend(const std::u16string &value)
{
    COM_SetString(get_IFC(), DefaultFrontend, value);
}

bool VBox::IMachine::USBProxyAvailable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), USBProxyAvailable, result);
    return static_cast<bool>(result);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
std::u16string VBox::IMachine::VMProcessPriority() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VMProcessPriority, result);
    return result;
}

void VBox::IMachine::set_VMProcessPriority(const std::u16string &value)
{
    COM_SetString(get_IFC(), VMProcessPriority, value);
}
#else
VBox::VMProcPriority VBox::IMachine::VMProcessPriority() const
{
    COM_Enum(::VMProcPriority) result;
    COM_GetValue(get_IFC(), VMProcessPriority, result);
    return static_cast<VMProcPriority>(result);
}

void VBox::IMachine::set_VMProcessPriority(VMProcPriority value)
{
    COM_SetValue(get_IFC(), VMProcessPriority,
                 static_cast<COM_Enum(::VMProcPriority)>(value));
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
std::u16string VBox::IMachine::paravirtDebug() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ParavirtDebug, result);
    return result;
}

void VBox::IMachine::set_paravirtDebug(const std::u16string &value)
{
    COM_SetString(get_IFC(), ParavirtDebug, value);
}

std::u16string VBox::IMachine::CPUProfile() const
{
    std::u16string result;
    COM_GetString(get_IFC(), CPUProfile, result);
    return result;
}

void VBox::IMachine::set_CPUProfile(const std::u16string &value)
{
    COM_SetString(get_IFC(), CPUProfile, value);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
std::u16string VBox::IMachine::stateKeyId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), StateKeyId, result);
    return result;
}

std::u16string VBox::IMachine::stateKeyStore() const
{
    std::u16string result;
    COM_GetString(get_IFC(), StateKeyStore, result);
    return result;
}

std::u16string VBox::IMachine::logKeyId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogKeyId, result);
    return result;
}

std::u16string VBox::IMachine::logKeyStore() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogKeyStore, result);
    return result;
}

VBox::COMPtr<VBox::IGuestDebugControl> VBox::IMachine::guestDebugControl() const
{
    COMPtr<IGuestDebugControl> result;
    COM_GetValue_Wrap(get_IFC(), GuestDebugControl, result);
    return result;
}
#endif

void VBox::IMachine::lockMachine(const COMPtr<ISession> &session, LockType lockType)
{
    auto cLockType = static_cast<COM_Enum(::LockType)>(lockType);

    auto rc = get_IFC()->LockMachine(session->get_IFC(), cLockType);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::launchVMProcess(
        const COMPtr<ISession> &session, const std::u16string &name,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        const std::u16string &environment
#else
        const std::vector<std::u16string> &environmentChanges
#endif
        )
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pName(name);
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
    COM_StringProxy pEnvironment(environment);
#else
    COM_StringArrayProxy pEnvironmentChanges(environmentChanges);
#endif

    auto rc = get_IFC()->LaunchVMProcess(session->get_IFC(), pName.m_text,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
                                         pEnvironment.m_text,
#else
                                         COM_ArrayParameter(pEnvironmentChanges),
#endif
                                         &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IMachine::setBootOrder(uint32_t position, DeviceType device)
{
    auto cDevice = static_cast<COM_Enum(::DeviceType)>(device);

    auto rc = get_IFC()->SetBootOrder(position, cDevice);
    COM_ERROR_CHECK(rc);
}

VBox::DeviceType VBox::IMachine::getBootOrder(uint32_t position) const
{
    COM_Enum(::DeviceType) cResult;

    auto rc = get_IFC()->GetBootOrder(position, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<DeviceType>(cResult);
}

void VBox::IMachine::attachDevice(const std::u16string &name, int32_t controllerPort,
    int32_t device, DeviceType type, const COMPtr<IMedium> &medium)
{
    COM_StringProxy pName(name);
    auto cType = static_cast<COM_Enum(::DeviceType)>(type);

    auto rc = get_IFC()->AttachDevice(pName.m_text, controllerPort, device,
                                      cType, medium->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::attachDeviceWithoutMedium(const std::u16string &name,
        int32_t controllerPort, int32_t device, DeviceType type)
{
    COM_StringProxy pName(name);
    auto cType = static_cast<COM_Enum(::DeviceType)>(type);

    auto rc = get_IFC()->AttachDeviceWithoutMedium(pName.m_text, controllerPort,
                                                   device, cType);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::detachDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->DetachDevice(pName.m_text, controllerPort, device);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::passthroughDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device, bool passthrough)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->PassthroughDevice(pName.m_text, controllerPort,
                                           device, passthrough);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::temporaryEjectDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device, bool temporaryEject)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->TemporaryEjectDevice(pName.m_text, controllerPort,
                                              device, temporaryEject);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::nonRotationalDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device, bool nonRotational)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->NonRotationalDevice(pName.m_text, controllerPort,
                                             device, nonRotational);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::setAutoDiscardForDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device, bool discard)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->SetAutoDiscardForDevice(pName.m_text, controllerPort,
                                                 device, discard);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::setHotPluggableForDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device, bool hotPluggable)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->SetHotPluggableForDevice(pName.m_text, controllerPort,
                                                  device, hotPluggable);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::setBandwidthGroupForDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device,
        const COMPtr<IBandwidthGroup> &bandwidthGroup)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->SetBandwidthGroupForDevice(pName.m_text,
                controllerPort, device, bandwidthGroup->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::setNoBandwidthGroupForDevice(const std::u16string &name,
        int32_t controllerPort, int32_t device)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->SetNoBandwidthGroupForDevice(pName.m_text,
                controllerPort, device);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::unmountMedium(const std::u16string &name,
        int32_t controllerPort, int32_t device, bool force)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->UnmountMedium(pName.m_text, controllerPort, device,
                                       force);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::mountMedium(const std::u16string &name, int32_t controllerPort,
        int32_t device, const COMPtr<IMedium> &medium, bool force)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->MountMedium(pName.m_text, controllerPort, device,
                                     medium->get_IFC(), force);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IMedium> VBox::IMachine::getMedium(const std::u16string &name,
        int32_t controllerPort, int32_t device) const
{
    ::IMedium *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetMedium(pName.m_text, controllerPort, device,
                                   &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMedium>::wrap(cResult);
}

std::vector<VBox::COMPtr<VBox::IMediumAttachment>>
VBox::IMachine::getMediumAttachmentsOfController(const std::u16string &name) const
{
    COM_ArrayProxy<::IMediumAttachment *> pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetMediumAttachmentsOfController(pName.m_text,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IMediumAttachment>> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IMediumAttachment> VBox::IMachine::getMediumAttachment(
        const std::u16string &name, int32_t controllerPort, int32_t device) const
{
    ::IMediumAttachment *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetMediumAttachment(pName.m_text, controllerPort,
                                             device, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMediumAttachment>::wrap(cResult);
}

void VBox::IMachine::attachHostPCIDevice(int32_t hostAddress,
        int32_t desiredGuestAddress, bool tryToUnbind)
{
    auto rc = get_IFC()->AttachHostPCIDevice(hostAddress, desiredGuestAddress,
                                             tryToUnbind);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::detachHostPCIDevice(int32_t hostAddress)
{
    auto rc = get_IFC()->DetachHostPCIDevice(hostAddress);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::INetworkAdapter> VBox::IMachine::getNetworkAdapter(
        uint32_t slot) const
{
    ::INetworkAdapter *cResult = nullptr;

    auto rc = get_IFC()->GetNetworkAdapter(slot, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<INetworkAdapter>::wrap(cResult);
}

VBox::COMPtr<VBox::IStorageController> VBox::IMachine::addStorageController(
        const std::u16string &name, StorageBus connectionType)
{
    ::IStorageController *cResult = nullptr;
    COM_StringProxy pName(name);
    auto cConnectionType = static_cast<COM_Enum(::StorageBus)>(connectionType);

    auto rc = get_IFC()->AddStorageController(pName.m_text, cConnectionType,
                                              &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IStorageController>::wrap(cResult);
}

VBox::COMPtr<VBox::IStorageController> VBox::IMachine::getStorageControllerByName(
        const std::u16string &name) const
{
    ::IStorageController *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetStorageControllerByName(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IStorageController>::wrap(cResult);
}

VBox::COMPtr<VBox::IStorageController> VBox::IMachine::getStorageControllerByInstance(
        StorageBus connectionType, uint32_t instance) const
{
    ::IStorageController *cResult = nullptr;
    auto cConnectionType = static_cast<COM_Enum(::StorageBus)>(connectionType);

    auto rc = get_IFC()->GetStorageControllerByInstance(cConnectionType, instance,
                                                        &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IStorageController>::wrap(cResult);
}

void VBox::IMachine::removeStorageController(const std::u16string &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->RemoveStorageController(pName.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::setStorageControllerBootable(const std::u16string &name,
        bool bootable)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->SetStorageControllerBootable(pName.m_text, bootable);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IUSBController> VBox::IMachine::addUSBController(
        const std::u16string &name, USBControllerType type)
{
    ::IUSBController *cResult = nullptr;
    COM_StringProxy pName(name);
    auto cType = static_cast<COM_Enum(::USBControllerType)>(type);

    auto rc = get_IFC()->AddUSBController(pName.m_text, cType, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBController>::wrap(cResult);
}

void VBox::IMachine::removeUSBController(const std::u16string &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->RemoveUSBController(pName.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IUSBController> VBox::IMachine::getUSBControllerByName(
        const std::u16string &name) const
{
    ::IUSBController *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetUSBControllerByName(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBController>::wrap(cResult);
}

uint32_t VBox::IMachine::getUSBControllerCountByType(USBControllerType type) const
{
    COM_ULong cResult;
    auto cType = static_cast<COM_Enum(::USBControllerType)>(type);

    auto rc = get_IFC()->GetUSBControllerCountByType(cType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

VBox::COMPtr<VBox::ISerialPort> VBox::IMachine::getSerialPort(uint32_t slot) const
{
    ::ISerialPort *cResult = nullptr;

    auto rc = get_IFC()->GetSerialPort(slot, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ISerialPort>::wrap(cResult);
}

VBox::COMPtr<VBox::IParallelPort> VBox::IMachine::getParallelPort(
        uint32_t slot) const
{
    ::IParallelPort *cResult = nullptr;

    auto rc = get_IFC()->GetParallelPort(slot, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IParallelPort>::wrap(cResult);
}

std::vector<std::u16string> VBox::IMachine::getExtraDataKeys()
{
    COM_StringArrayProxy pResult;

    auto rc = get_IFC()->GetExtraDataKeys(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

std::u16string VBox::IMachine::getExtraData(const std::u16string &key)
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetExtraData(pKey.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IMachine::setExtraData(const std::u16string &key, const std::u16string &value)
{
    COM_StringProxy pKey(key);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetExtraData(pKey.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

bool VBox::IMachine::getCPUProperty(CPUPropertyType property) const
{
    COM_Bool cResult;
    auto cProperty = static_cast<COM_Enum(::CPUPropertyType)>(property);

    auto rc = get_IFC()->GetCPUProperty(cProperty, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IMachine::setCPUProperty(CPUPropertyType property, bool value)
{
    auto cProperty = static_cast<COM_Enum(::CPUPropertyType)>(property);

    auto rc = get_IFC()->SetCPUProperty(cProperty, value);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
void VBox::IMachine::getCPUIDLeafByOrdinal(uint32_t ordinal, uint32_t *idx,
        uint32_t *idxSub, uint32_t *valEax, uint32_t *valEbx, uint32_t *valEcx,
        uint32_t *valEdx) const
{
    COM_ULong cIdx;
    COM_ULong cIdxSub;
    COM_ULong cValEax;
    COM_ULong cValEbx;
    COM_ULong cValEcx;
    COM_ULong cValEdx;

    auto rc = get_IFC()->GetCPUIDLeafByOrdinal(ordinal, &cIdx, &cIdxSub,
                &cValEax, &cValEbx, &cValEcx, &cValEdx);
    COM_ERROR_CHECK(rc);

    if (idx)
        *idx = static_cast<uint32_t>(cIdx);
    if (idxSub)
        *idxSub = static_cast<uint32_t>(cIdxSub);
    if (valEax)
        *valEax = static_cast<uint32_t>(cValEax);
    if (valEbx)
        *valEbx = static_cast<uint32_t>(cValEbx);
    if (valEcx)
        *valEcx = static_cast<uint32_t>(cValEcx);
    if (valEdx)
        *valEdx = static_cast<uint32_t>(cValEdx);
}
#endif

void VBox::IMachine::getCPUIDLeaf(uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        uint32_t idxSub,
#endif
        uint32_t *valEax, uint32_t *valEbx, uint32_t *valEcx, uint32_t *valEdx) const
{
    COM_ULong cValEax;
    COM_ULong cValEbx;
    COM_ULong cValEcx;
    COM_ULong cValEdx;

    auto rc = get_IFC()->GetCPUIDLeaf(idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                idxSub,
#endif
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

void VBox::IMachine::setCPUIDLeaf(uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        uint32_t idxSub,
#endif
        uint32_t valEax, uint32_t valEbx, uint32_t valEcx, uint32_t valEdx)
{
    auto rc = get_IFC()->SetCPUIDLeaf(idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                idxSub,
#endif
                valEax, valEbx, valEcx, valEdx);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::removeCPUIDLeaf(uint32_t idx
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
      , uint32_t idxSub
#endif
        )
{
    auto rc = get_IFC()->RemoveCPUIDLeaf(idx
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
              , idxSub
#endif
                );
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::removeAllCPUIDLeaves()
{
    auto rc = get_IFC()->RemoveAllCPUIDLeaves();
    COM_ERROR_CHECK(rc);
}

bool VBox::IMachine::getHWVirtExProperty(HWVirtExPropertyType property) const
{
    COM_Bool cResult;
    auto cProperty = static_cast<COM_Enum(::HWVirtExPropertyType)>(property);

    auto rc = get_IFC()->GetHWVirtExProperty(cProperty, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IMachine::setHWVirtExProperty(HWVirtExPropertyType property, bool value)
{
    auto cProperty = static_cast<COM_Enum(::HWVirtExPropertyType)>(property);

    auto rc = get_IFC()->SetHWVirtExProperty(cProperty, value);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::setSettingsFilePath(
        const std::u16string &settingsFilePath)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSettingsFilePath(settingsFilePath);

    auto rc = get_IFC()->SetSettingsFilePath(pSettingsFilePath.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IMachine::saveSettings()
{
    auto rc = get_IFC()->SaveSettings();
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::discardSettings()
{
    auto rc = get_IFC()->DiscardSettings();
    COM_ERROR_CHECK(rc);
}

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IMachine::unregister(
        CleanupMode cleanupMode)
{
    COM_ArrayProxy<::IMedium *> pResult;
    auto cCleanupMode = static_cast<COM_Enum(::CleanupMode)>(cleanupMode);

    auto rc = get_IFC()->Unregister(cCleanupMode, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IMedium>> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::deleteConfig(
        const std::vector<COMPtr<IMedium>> &media)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<::IMedium *> pMedia(media);

    auto rc = get_IFC()->DeleteConfig(COM_ArrayParameter(pMedia), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IVirtualSystemDescription> VBox::IMachine::exportTo(
        const COMPtr<IAppliance> &appliance, const std::u16string &location)
{
    ::IVirtualSystemDescription *cResult = nullptr;
    COM_StringProxy pLocation(location);

    auto rc = get_IFC()->ExportTo(appliance->get_IFC(), pLocation.m_text,
                                  &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IVirtualSystemDescription>::wrap(cResult);
}

VBox::COMPtr<VBox::ISnapshot> VBox::IMachine::findSnapshot(
        const std::u16string &nameOrId)
{
    ::ISnapshot *cResult = nullptr;
    COM_StringProxy pNameOrId(nameOrId);

    auto rc = get_IFC()->FindSnapshot(pNameOrId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ISnapshot>::wrap(cResult);
}

void VBox::IMachine::createSharedFolder(const std::u16string &name,
        const std::u16string &hostPath, bool writable, bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
      , const std::u16string &autoMountPoint
#endif
        )
{
    COM_StringProxy pName(name);
    COM_StringProxy pHostPath(hostPath);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_StringProxy pAutoMountPoint(autoMountPoint);
#endif

    auto rc = get_IFC()->CreateSharedFolder(pName.m_text, pHostPath.m_text,
                                            writable, automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
                                          , pAutoMountPoint.m_text
#endif
                                            );
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::removeSharedFolder(const std::u16string &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->RemoveSharedFolder(pName.m_text);
    COM_ERROR_CHECK(rc);
}

bool VBox::IMachine::canShowConsoleWindow()
{
    COM_Bool cResult;

    auto rc = get_IFC()->CanShowConsoleWindow(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

int64_t VBox::IMachine::showConsoleWindow()
{
    COM_Long64 cResult;

    auto rc = get_IFC()->ShowConsoleWindow(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int64_t>(cResult);
}

void VBox::IMachine::getGuestProperty(const std::u16string &name,
        std::u16string *value, int64_t *timestamp, std::u16string *flags) const
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue;
    COM_Long64 cTimestamp;
    COM_StringProxy pFlags;

    auto rc = get_IFC()->GetGuestProperty(pName.m_text, &pValue.m_text,
                                          &cTimestamp, &pFlags.m_text);
    COM_ERROR_CHECK(rc);

    if (value)
        *value = pValue.toString();
    if (timestamp)
        *timestamp = static_cast<int64_t>(cTimestamp);
    if (flags)
        *flags = pFlags.toString();
}

std::u16string VBox::IMachine::getGuestPropertyValue(const std::u16string &property) const
{
    COM_StringProxy pResult;
    COM_StringProxy pProperty(property);

    auto rc = get_IFC()->GetGuestPropertyValue(pProperty.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

int64_t VBox::IMachine::getGuestPropertyTimestamp(const std::u16string &property) const
{
    COM_Long64 cResult;
    COM_StringProxy pProperty(property);

    auto rc = get_IFC()->GetGuestPropertyTimestamp(pProperty.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int64_t>(cResult);
}

void VBox::IMachine::setGuestProperty(const std::u16string &property,
        const std::u16string &value, const std::u16string &flags)
{
    COM_StringProxy pProperty(property);
    COM_StringProxy pValue(value);
    COM_StringProxy pFlags(flags);

    auto rc = get_IFC()->SetGuestProperty(pProperty.m_text, pValue.m_text,
                                          pFlags.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::setGuestPropertyValue(const std::u16string &property,
        const std::u16string &value)
{
    COM_StringProxy pProperty(property);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetGuestPropertyValue(pProperty.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::deleteGuestProperty(const std::u16string &name) const
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->DeleteGuestProperty(pName.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::enumerateGuestProperties(const std::u16string &patterns,
        std::vector<std::u16string> *names, std::vector<std::u16string> *values,
        std::vector<int64_t> *timestamps, std::vector<std::u16string> *flags) const
{
    COM_StringProxy pPatterns(patterns);
    COM_StringArrayProxy pNames;
    COM_StringArrayProxy pValues;
    COM_ArrayProxy<int64_t> pTimestamps;
    COM_StringArrayProxy pFlags;

    auto rc = get_IFC()->EnumerateGuestProperties(pPatterns.m_text,
                COM_ArrayParameterRef(pNames), COM_ArrayParameterRef(pValues),
                COM_ArrayParameterRef(pTimestamps), COM_ArrayParameterRef(pFlags));
    COM_ERROR_CHECK(rc);

    if (names)
        pNames.toVector(*names);
    if (values)
        pValues.toVector(*values);
    if (timestamps)
        pTimestamps.toVector(*timestamps);
    if (flags)
        pFlags.toVector(*flags);
}

void VBox::IMachine::querySavedGuestScreenInfo(uint32_t screenId,
        uint32_t *originX, uint32_t *originY, uint32_t *width,
        uint32_t *height, bool *enabled) const
{
    COM_ULong cOriginX;
    COM_ULong cOriginY;
    COM_ULong cWidth;
    COM_ULong cHeight;
    COM_Bool cEnabled;

    auto rc = get_IFC()->QuerySavedGuestScreenInfo(screenId, &cOriginX,
                &cOriginY, &cWidth, &cHeight, &cEnabled);
    COM_ERROR_CHECK(rc);

    if (originX)
        *originX = static_cast<uint32_t>(cOriginX);
    if (originY)
        *originY = static_cast<uint32_t>(cOriginY);
    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    if (enabled)
        *enabled = static_cast<bool>(cEnabled);
}

std::vector<uint8_t> VBox::IMachine::readSavedThumbnailToArray(uint32_t screenId,
        BitmapFormat bitmapFormat, uint32_t *width, uint32_t *height)
{
    COM_ArrayProxy<COM_Byte> pResult;
    auto cBitmapFormat = static_cast<COM_Enum(::BitmapFormat)>(bitmapFormat);
    COM_ULong cWidth;
    COM_ULong cHeight;

    auto rc = get_IFC()->ReadSavedThumbnailToArray(screenId, cBitmapFormat,
                &cWidth, &cHeight, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

std::vector<VBox::BitmapFormat> VBox::IMachine::querySavedScreenshotInfo(
        uint32_t screenId, uint32_t *width, uint32_t *height)
{
    COM_ArrayProxy<COM_Enum(::BitmapFormat)> pResult;
    COM_ULong cWidth;
    COM_ULong cHeight;

    auto rc = get_IFC()->QuerySavedScreenshotInfo(screenId, &cWidth, &cHeight,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    std::vector<BitmapFormat> result;
    pResult.toVector(result);
    return result;
}

std::vector<uint8_t> VBox::IMachine::readSavedScreenshotToArray(
        uint32_t screenId, BitmapFormat bitmapFormat,
        uint32_t *width, uint32_t *height)
{
    COM_ArrayProxy<COM_Byte> pResult;
    auto cBitmapFormat = static_cast<COM_Enum(::BitmapFormat)>(bitmapFormat);
    COM_ULong cWidth;
    COM_ULong cHeight;

    auto rc = get_IFC()->ReadSavedScreenshotToArray(screenId, cBitmapFormat,
                &cWidth, &cHeight, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

void VBox::IMachine::hotPlugCPU(uint32_t cpu)
{
    auto rc = get_IFC()->HotPlugCPU(cpu);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::hotUnplugCPU(uint32_t cpu)
{
    auto rc = get_IFC()->HotUnplugCPU(cpu);
    COM_ERROR_CHECK(rc);
}

bool VBox::IMachine::getCPUStatus(uint32_t cpu)
{
    COM_Bool cResult;

    auto rc = get_IFC()->GetCPUStatus(cpu, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::ParavirtProvider VBox::IMachine::getEffectiveParavirtProvider() const
{
    COM_Enum(::ParavirtProvider) cResult;

    auto rc = get_IFC()->GetEffectiveParavirtProvider(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<ParavirtProvider>(cResult);
}

std::u16string VBox::IMachine::queryLogFilename(uint32_t idx)
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->QueryLogFilename(idx, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

std::vector<uint8_t> VBox::IMachine::readLog(uint32_t idx, int64_t offset,
        int64_t size)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->ReadLog(idx, offset, size, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::cloneTo(
        const COMPtr<IMachine> &target, CloneMode mode,
        const std::vector<CloneOptions> &options)
{
    ::IProgress *cResult = nullptr;
    auto cMode = static_cast<COM_Enum(::CloneMode)>(mode);
    COM_ArrayProxy<COM_Enum(::CloneOptions)> pOptions(options);

    auto rc = get_IFC()->CloneTo(target->get_IFC(), cMode,
                COM_ArrayParameter(pOptions), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::IMachine::moveTo(const std::u16string &folder,
        const std::u16string &type)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pFolder(folder);
    COM_StringProxy pType(type);

    auto rc = get_IFC()->MoveTo(pFolder.m_text, pType.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IProgress> VBox::IMachine::saveState()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->SaveState(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IMachine::adoptSavedState(const std::u16string &savedStateFile)
{
    COM_StringProxy pSavedStateFile(savedStateFile);

    auto rc = get_IFC()->AdoptSavedState(pSavedStateFile.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::discardSavedState(bool fRemoveFile)
{
    auto rc = get_IFC()->DiscardSavedState(fRemoveFile);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::takeSnapshot(
        const std::u16string &name, const std::u16string &description,
        bool pause, std::u16string *id)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pName(name);
    COM_StringProxy pDescription(description);
    COM_StringProxy pId;

    auto rc = get_IFC()->TakeSnapshot(pName.m_text, pDescription.m_text,
                                      pause, &pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    if (id)
        *id = pId.toString();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::deleteSnapshot(
        const std::u16string &id)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->DeleteSnapshot(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::deleteSnapshotAndAllChildren(
        const std::u16string &id)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->DeleteSnapshotAndAllChildren(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::deleteSnapshotRange(
        const std::u16string &startId,
        const std::u16string &endId)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pStartId(startId);
    COM_StringProxy pEndId(endId);

    auto rc = get_IFC()->DeleteSnapshotRange(pStartId.m_text, pEndId.m_text,
                                             &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMachine::restoreSnapshot(
        const COMPtr<ISnapshot> &snapshot)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->RestoreSnapshot(snapshot->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IMachine::applyDefaults(const std::u16string &flags)
{
    COM_StringProxy pFlags(flags);

    auto rc = get_IFC()->ApplyDefaults(pFlags.m_text);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::IMachine::changeEncryption(
        const std::u16string &currentPassword, const std::u16string &cipher,
        const std::u16string &newPassword, const std::u16string &newPasswordId,
        bool force)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pCurrentPassword(currentPassword);
    COM_StringProxy pCipher(cipher);
    COM_StringProxy pNewPassword(newPassword);
    COM_StringProxy pNewPasswordId(newPasswordId);

    auto rc = get_IFC()->ChangeEncryption(pCurrentPassword.m_text, pCipher.m_text,
                                          pNewPassword.m_text, pNewPasswordId.m_text,
                                          static_cast<COM_Bool>(force), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IMachine::getEncryptionSettings(
        std::u16string *cipher, std::u16string *passwordId) const
{
    COM_StringProxy pCipher;
    COM_StringProxy pPasswordId;

    auto rc = get_IFC()->GetEncryptionSettings(&pCipher.m_text, &pPasswordId.m_text);
    COM_ERROR_CHECK(rc);

    if (cipher)
        *cipher = pCipher.toString();
    if (passwordId)
        *passwordId = pPasswordId.toString();
}

void VBox::IMachine::checkEncryptionPassword(const std::u16string &password) const
{
    COM_StringProxy pPassword(password);

    auto rc = get_IFC()->CheckEncryptionPassword(pPassword.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::addEncryptionPassword(const std::u16string &id,
        const std::u16string &password)
{
    COM_StringProxy pId(id);
    COM_StringProxy pPassword(password);

    auto rc = get_IFC()->AddEncryptionPassword(pId.m_text, pPassword.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::addEncryptionPasswords(
        const std::vector<std::u16string> &ids,
        const std::vector<std::u16string> &passwords)
{
    COM_StringArrayProxy pIds(ids);
    COM_StringArrayProxy pPasswords(passwords);

    auto rc = get_IFC()->AddEncryptionPasswords(COM_ArrayParameter(pIds),
                                                COM_ArrayParameter(pPasswords));
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::removeEncryptionPassword(const std::u16string &id)
{
    COM_StringProxy pId(id);

    auto rc = get_IFC()->RemoveEncryptionPassword(pId.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachine::clearAllEncryptionPasswords()
{
    auto rc = get_IFC()->ClearAllEncryptionPasswords();
    COM_ERROR_CHECK(rc);
}
#endif
