/* This file is part of libvbox
 * Copyright (C) 2024  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
COM_WRAP_IFC(IPlatformProperties)

bool VBox::IPlatformProperties::rawModeSupported() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RawModeSupported, result);
    return static_cast<bool>(result);
}

bool VBox::IPlatformProperties::exclusiveHwVirt() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ExclusiveHwVirt, result);
    return static_cast<bool>(result);
}

void VBox::IPlatformProperties::set_exclusiveHwVirt(bool value)
{
    COM_SetValue(get_IFC(), ExclusiveHwVirt, value);
}

uint32_t VBox::IPlatformProperties::serialPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SerialPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IPlatformProperties::parallelPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ParallelPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IPlatformProperties::maxBootPosition() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxBootPosition, result);
    return static_cast<uint32_t>(result);
}

std::vector<VBox::ParavirtProvider>
VBox::IPlatformProperties::supportedParavirtProviders() const
{
    std::vector<ParavirtProvider> result;
    COM_GetArray(get_IFC(), SupportedParavirtProviders,
                 COM_Enum(::ParavirtProvider), result);
    return result;
}

std::vector<VBox::FirmwareType>
VBox::IPlatformProperties::supportedFirmwareTypes() const
{
    std::vector<FirmwareType> result;
    COM_GetArray(get_IFC(), SupportedFirmwareTypes, COM_Enum(::FirmwareType), result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IGuestOSType>>
VBox::IPlatformProperties::supportedGuestOSTypes() const
{
    std::vector<COMPtr<IGuestOSType>> result;
    COM_GetArray_Wrap(get_IFC(), SupportedGuestOSTypes, result);
    return result;
}

std::vector<VBox::GraphicsControllerType>
VBox::IPlatformProperties::supportedGfxControllerTypes() const
{
    std::vector<GraphicsControllerType> result;
    COM_GetArray(get_IFC(), SupportedGfxControllerTypes,
                 COM_Enum(::GraphicsControllerType), result);
    return result;
}

std::vector<VBox::NetworkAdapterPromiscModePolicy>
VBox::IPlatformProperties::supportedNetAdpPromiscModePols() const
{
    std::vector<NetworkAdapterPromiscModePolicy> result;
    COM_GetArray(get_IFC(), SupportedNetAdpPromiscModePols,
                 COM_Enum(::NetworkAdapterPromiscModePolicy), result);
    return result;
}

std::vector<VBox::NetworkAdapterType>
VBox::IPlatformProperties::supportedNetworkAdapterTypes() const
{
    std::vector<NetworkAdapterType> result;
    COM_GetArray(get_IFC(), SupportedNetworkAdapterTypes,
                 COM_Enum(::NetworkAdapterType), result);
    return result;
}

std::vector<VBox::UartType> VBox::IPlatformProperties::supportedUartTypes() const
{
    std::vector<UartType> result;
    COM_GetArray(get_IFC(), SupportedUartTypes, COM_Enum(::UartType), result);
    return result;
}

std::vector<VBox::USBControllerType>
VBox::IPlatformProperties::supportedUSBControllerTypes() const
{
    std::vector<USBControllerType> result;
    COM_GetArray(get_IFC(), SupportedUSBControllerTypes,
                 COM_Enum(::USBControllerType), result);
    return result;
}

std::vector<VBox::AudioControllerType>
VBox::IPlatformProperties::supportedAudioControllerTypes() const
{
    std::vector<AudioControllerType> result;
    COM_GetArray(get_IFC(), SupportedAudioControllerTypes,
                 COM_Enum(::AudioControllerType), result);
    return result;
}

std::vector<VBox::DeviceType> VBox::IPlatformProperties::supportedBootDevices() const
{
    std::vector<DeviceType> result;
    COM_GetArray(get_IFC(), SupportedBootDevices, COM_Enum(::DeviceType), result);
    return result;
}

std::vector<VBox::StorageBus> VBox::IPlatformProperties::supportedStorageBuses() const
{
    std::vector<StorageBus> result;
    COM_GetArray(get_IFC(), SupportedStorageBuses, COM_Enum(::StorageBus), result);
    return result;
}

std::vector<VBox::StorageControllerType>
VBox::IPlatformProperties::supportedStorageControllerTypes() const
{
    std::vector<StorageControllerType> result;
    COM_GetArray(get_IFC(), SupportedStorageControllerTypes,
                 COM_Enum(::StorageControllerType), result);
    return result;
}

std::vector<VBox::ChipsetType> VBox::IPlatformProperties::supportedChipsetTypes() const
{
    std::vector<ChipsetType> result;
    COM_GetArray(get_IFC(), SupportedChipsetTypes, COM_Enum(::ChipsetType), result);
    return result;
}

std::vector<VBox::IommuType> VBox::IPlatformProperties::supportedIommuTypes() const
{
    std::vector<IommuType> result;
    COM_GetArray(get_IFC(), SupportedIommuTypes, COM_Enum(::IommuType), result);
    return result;
}

std::vector<VBox::TpmType> VBox::IPlatformProperties::supportedTpmTypes() const
{
    std::vector<TpmType> result;
    COM_GetArray(get_IFC(), SupportedTpmTypes, COM_Enum(::TpmType), result);
    return result;
}

uint32_t VBox::IPlatformProperties::getMaxNetworkAdapters(ChipsetType chipset)
{
    COM_ULong cResult = 0;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);

    auto rc = get_IFC()->GetMaxNetworkAdapters(cChipset, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IPlatformProperties::getMaxNetworkAdaptersOfType(
        ChipsetType chipset, NetworkAttachmentType type)
{
    COM_ULong cResult = 0;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);
    auto cType = static_cast<COM_Enum(::NetworkAttachmentType)>(type);

    auto rc = get_IFC()->GetMaxNetworkAdaptersOfType(cChipset, cType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IPlatformProperties::getMaxDevicesPerPortForStorageBus(StorageBus bus)
{
    COM_ULong cResult = 0;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMaxDevicesPerPortForStorageBus(cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IPlatformProperties::getMinPortCountForStorageBus(StorageBus bus)
{
    COM_ULong cResult = 0;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMinPortCountForStorageBus(cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IPlatformProperties::getMaxPortCountForStorageBus(StorageBus bus)
{
    COM_ULong cResult = 0;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMaxPortCountForStorageBus(cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IPlatformProperties::getMaxInstancesOfStorageBus(
        ChipsetType chipset, StorageBus bus)
{
    COM_ULong cResult = 0;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetMaxInstancesOfStorageBus(cChipset, cBus, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IPlatformProperties::getSupportedVRAMRange(
        GraphicsControllerType graphicsControllerType, bool accelerate3DEnabled,
        uint32_t *minMB, uint32_t *maxMB)
{
    COM_ULong cResult = 0;
    auto cGraphicsControllerType = static_cast<COM_Enum(::GraphicsControllerType)>(graphicsControllerType);
    auto cAccelerate3DEnabled = static_cast<COM_Bool>(accelerate3DEnabled);
    COM_ULong cMinMB;
    COM_ULong cMaxMB;

    auto rc = get_IFC()->GetSupportedVRAMRange(cGraphicsControllerType, cAccelerate3DEnabled,
                                               &cMinMB, &cMaxMB, &cResult);
    COM_ERROR_CHECK(rc);

    if (minMB)
        *minMB = static_cast<uint32_t>(cMinMB);
    if (maxMB)
        *maxMB = static_cast<uint32_t>(cMaxMB);

    return static_cast<uint32_t>(cResult);
}

std::vector<VBox::GraphicsFeature>
VBox::IPlatformProperties::getSupportedGfxFeaturesForType(
        GraphicsControllerType graphicsControllerType)
{
    COM_ArrayProxy<COM_Enum(::GraphicsFeature)> pResult;
    auto cGraphicsControllerType =
            static_cast<COM_Enum(::GraphicsControllerType)>(graphicsControllerType);

    auto rc = get_IFC()->GetSupportedGfxFeaturesForType(
                cGraphicsControllerType, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<GraphicsFeature> result;
    pResult.toVector(result);
    return result;
}

std::vector<VBox::DeviceType>
VBox::IPlatformProperties::getDeviceTypesForStorageBus(StorageBus bus)
{
    COM_ArrayProxy<COM_Enum(::DeviceType)> pResult;
    auto cBus = static_cast<COM_Enum(::StorageBus)>(bus);

    auto rc = get_IFC()->GetDeviceTypesForStorageBus(cBus, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<DeviceType> result;
    pResult.toVector(result);
    return result;
}

VBox::StorageBus VBox::IPlatformProperties::getStorageBusForControllerType(
        StorageControllerType storageControllerType)
{
    COM_Enum(::StorageBus) cResult;
    auto cStorageControllerType = static_cast<COM_Enum(::StorageControllerType)>(storageControllerType);

    auto rc = get_IFC()->GetStorageBusForControllerType(cStorageControllerType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<StorageBus>(cResult);
}

std::vector<VBox::StorageControllerType>
VBox::IPlatformProperties::getStorageControllerTypesForBus(StorageBus storageBus)
{
    COM_ArrayProxy<COM_Enum(::StorageControllerType)> pResult;
    auto cStorageBus = static_cast<COM_Enum(::StorageBus)>(storageBus);

    auto rc = get_IFC()->GetStorageControllerTypesForBus(cStorageBus,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<StorageControllerType> result;
    pResult.toVector(result);
    return result;
}

bool VBox::IPlatformProperties::getStorageControllerHotplugCapable(
        StorageControllerType controllerType)
{
    COM_Bool cResult = false;
    auto cControllerType = static_cast<COM_Enum(::StorageControllerType)>(controllerType);

    auto rc = get_IFC()->GetStorageControllerHotplugCapable(cControllerType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

uint32_t VBox::IPlatformProperties::getMaxInstancesOfUSBControllerType(
        ChipsetType chipset, USBControllerType type)
{
    COM_ULong cResult = 0;
    auto cChipset = static_cast<COM_Enum(::ChipsetType)>(chipset);
    auto cType = static_cast<COM_Enum(::USBControllerType)>(type);

    auto rc = get_IFC()->GetMaxInstancesOfUSBControllerType(cChipset, cType, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}
#endif
