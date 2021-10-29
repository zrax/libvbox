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

COM_WRAP_IFC(IGuestOSType)

std::u16string VBox::IGuestOSType::familyId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FamilyId, result);
    return result;
}

std::u16string VBox::IGuestOSType::familyDescription() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FamilyDescription, result);
    return result;
}

std::u16string VBox::IGuestOSType::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::IGuestOSType::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

bool VBox::IGuestOSType::is64Bit() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Is64Bit, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommendedIOAPIC() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedIOAPIC, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommendedVirtEx() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedVirtEx, result);
    return static_cast<bool>(result);
}

uint32_t VBox::IGuestOSType::recommendedRAM() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), RecommendedRAM, result);
    return static_cast<uint32_t>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::GraphicsControllerType VBox::IGuestOSType::recommendedGraphicsController() const
{
    COM_Enum(::GraphicsControllerType) result;
    COM_GetValue(get_IFC(), RecommendedGraphicsController, result);
    return static_cast<GraphicsControllerType>(result);
}
#endif

uint32_t VBox::IGuestOSType::recommendedVRAM() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), RecommendedVRAM, result);
    return static_cast<uint32_t>(result);
}

bool VBox::IGuestOSType::recommended2DVideoAcceleration() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Recommended2DVideoAcceleration, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommended3DAcceleration() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Recommended3DAcceleration, result);
    return static_cast<bool>(result);
}

int64_t VBox::IGuestOSType::recommendedHDD() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), RecommendedHDD, result);
    return static_cast<int64_t>(result);
}

VBox::NetworkAdapterType VBox::IGuestOSType::adapterType() const
{
    COM_Enum(::NetworkAdapterType) result;
    COM_GetValue(get_IFC(), AdapterType, result);
    return static_cast<NetworkAdapterType>(result);
}

bool VBox::IGuestOSType::recommendedPAE() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedPAE, result);
    return static_cast<bool>(result);
}

VBox::StorageControllerType VBox::IGuestOSType::recommendedDVDStorageController() const
{
    COM_Enum(::StorageControllerType) result;
    COM_GetValue(get_IFC(), RecommendedDVDStorageController, result);
    return static_cast<StorageControllerType>(result);
}

VBox::StorageBus VBox::IGuestOSType::recommendedDVDStorageBus() const
{
    COM_Enum(::StorageBus) result;
    COM_GetValue(get_IFC(), RecommendedDVDStorageBus, result);
    return static_cast<StorageBus>(result);
}

VBox::StorageControllerType VBox::IGuestOSType::recommendedHDStorageController() const
{
    COM_Enum(::StorageControllerType) result;
    COM_GetValue(get_IFC(), RecommendedHDStorageController, result);
    return static_cast<StorageControllerType>(result);
}

VBox::StorageBus VBox::IGuestOSType::recommendedHDStorageBus() const
{
    COM_Enum(::StorageBus) result;
    COM_GetValue(get_IFC(), RecommendedHDStorageBus, result);
    return static_cast<StorageBus>(result);
}

VBox::FirmwareType VBox::IGuestOSType::recommendedFirmware() const
{
    COM_Enum(::FirmwareType) result;
    COM_GetValue(get_IFC(), RecommendedFirmware, result);
    return static_cast<FirmwareType>(result);
}

bool VBox::IGuestOSType::recommendedUSBHID() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedUSBHID, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommendedHPET() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedHPET, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommendedUSBTablet() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedUSBTablet, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommendedRTCUseUTC() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedRTCUseUTC, result);
    return static_cast<bool>(result);
}

VBox::ChipsetType VBox::IGuestOSType::recommendedChipset() const
{
    COM_Enum(::ChipsetType) result;
    COM_GetValue(get_IFC(), RecommendedChipset, result);
    return static_cast<ChipsetType>(result);
}

VBox::AudioControllerType VBox::IGuestOSType::recommendedAudioController() const
{
    COM_Enum(::AudioControllerType) result;
    COM_GetValue(get_IFC(), RecommendedAudioController, result);
    return static_cast<AudioControllerType>(result);
}

VBox::AudioCodecType VBox::IGuestOSType::recommendedAudioCodec() const
{
    COM_Enum(::AudioCodecType) result;
    COM_GetValue(get_IFC(), RecommendedAudioCodec, result);
    return static_cast<AudioCodecType>(result);
}

bool VBox::IGuestOSType::recommendedFloppy() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedFloppy, result);
    return static_cast<bool>(result);
}

bool VBox::IGuestOSType::recommendedUSB() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedUSB, result);
    return static_cast<bool>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
bool VBox::IGuestOSType::recommendedUSB3() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedUSB3, result);
    return static_cast<bool>(result);
}
#endif

bool VBox::IGuestOSType::recommendedTFReset() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedTFReset, result);
    return static_cast<bool>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
bool VBox::IGuestOSType::recommendedX2APIC() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecommendedX2APIC, result);
    return static_cast<bool>(result);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 28)
uint32_t VBox::IGuestOSType::recommendedCPUCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), RecommendedCPUCount, result);
    return static_cast<uint32_t>(result);
}
#endif
