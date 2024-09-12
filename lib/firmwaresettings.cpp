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
COM_WRAP_IFC(IFirmwareSettings)

VBox::FirmwareType VBox::IFirmwareSettings::firmwareType() const
{
    COM_Enum(::FirmwareType) result;
    COM_GetValue(get_IFC(), FirmwareType, result);
    return static_cast<FirmwareType>(result);
}

void VBox::IFirmwareSettings::set_firmwareType(FirmwareType value)
{
    COM_SetValue(get_IFC(), FirmwareType,
                 static_cast<COM_Enum(::FirmwareType)>(value));
}

bool VBox::IFirmwareSettings::logoFadeIn() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), LogoFadeIn, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_logoFadeIn(bool value)
{
    COM_SetValue(get_IFC(), LogoFadeIn, value);
}

bool VBox::IFirmwareSettings::logoFadeOut() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), LogoFadeOut, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_logoFadeOut(bool value)
{
    COM_SetValue(get_IFC(), LogoFadeOut, value);
}

uint32_t VBox::IFirmwareSettings::logoDisplayTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), LogoDisplayTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IFirmwareSettings::set_logoDisplayTime(uint32_t value)
{
    COM_SetValue(get_IFC(), LogoDisplayTime, value);
}

std::u16string VBox::IFirmwareSettings::logoImagePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogoImagePath, result);
    return result;
}

void VBox::IFirmwareSettings::set_logoImagePath(const std::u16string &value)
{
    COM_SetString(get_IFC(), LogoImagePath, value);
}

VBox::FirmwareBootMenuMode VBox::IFirmwareSettings::bootMenuMode() const
{
    COM_Enum(::FirmwareBootMenuMode) result;
    COM_GetValue(get_IFC(), BootMenuMode, result);
    return static_cast<FirmwareBootMenuMode>(result);
}

void VBox::IFirmwareSettings::set_bootMenuMode(FirmwareBootMenuMode value)
{
    COM_SetValue(get_IFC(), BootMenuMode,
                 static_cast<COM_Enum(::FirmwareBootMenuMode)>(value));
}

bool VBox::IFirmwareSettings::ACPIEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ACPIEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_ACPIEnabled(bool value)
{
    COM_SetValue(get_IFC(), ACPIEnabled, value);
}

bool VBox::IFirmwareSettings::IOAPICEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IOAPICEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_IOAPICEnabled(bool value)
{
    COM_SetValue(get_IFC(), IOAPICEnabled, value);
}

VBox::APICMode VBox::IFirmwareSettings::APICMode() const
{
    COM_Enum(::APICMode) result;
    COM_GetValue(get_IFC(), APICMode, result);
    return static_cast<VBox::APICMode>(result);
}

void VBox::IFirmwareSettings::set_APICMode(VBox::APICMode value)
{
    COM_SetValue(get_IFC(), APICMode, static_cast<COM_Enum(::APICMode)>(value));
}

int64_t VBox::IFirmwareSettings::timeOffset() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), TimeOffset, result);
    return static_cast<int64_t>(result);
}

void VBox::IFirmwareSettings::set_timeOffset(int64_t value)
{
    COM_SetValue(get_IFC(), TimeOffset, value);
}

bool VBox::IFirmwareSettings::PXEDebugEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), PXEDebugEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_PXEDebugEnabled(bool value)
{
    COM_SetValue(get_IFC(), PXEDebugEnabled, value);
}

bool VBox::IFirmwareSettings::SMBIOSUuidLittleEndian() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), SMBIOSUuidLittleEndian, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_SMBIOSUuidLittleEndian(bool value)
{
    COM_SetValue(get_IFC(), SMBIOSUuidLittleEndian, value);
}

bool VBox::IFirmwareSettings::AutoSerialNumGen() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AutoSerialNumGen, result);
    return static_cast<bool>(result);
}

void VBox::IFirmwareSettings::set_AutoSerialNumGen(bool value)
{
    COM_SetValue(get_IFC(), AutoSerialNumGen, value);
}
#endif
