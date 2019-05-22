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

COM_WRAP_IFC(IBIOSSettings)

bool VBox::IBIOSSettings::logoFadeIn() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), LogoFadeIn, result);
    return static_cast<bool>(result);
}

void VBox::IBIOSSettings::set_logoFadeIn(bool value)
{
    COM_SetValue(get_IFC(), LogoFadeIn, value);
}

bool VBox::IBIOSSettings::logoFadeOut() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), LogoFadeOut, result);
    return static_cast<bool>(result);
}

void VBox::IBIOSSettings::set_logoFadeOut(bool value)
{
    COM_SetValue(get_IFC(), LogoFadeOut, value);
}

uint32_t VBox::IBIOSSettings::logoDisplayTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), LogoDisplayTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IBIOSSettings::set_logoDisplayTime(uint32_t value)
{
    COM_SetValue(get_IFC(), LogoDisplayTime, value);
}

std::u16string VBox::IBIOSSettings::logoImagePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogoImagePath, result);
    return result;
}

void VBox::IBIOSSettings::set_logoImagePath(const std::u16string &value)
{
    COM_SetString(get_IFC(), LogoImagePath, value);
}

VBox::BIOSBootMenuMode VBox::IBIOSSettings::bootMenuMode() const
{
    COM_Enum(::BIOSBootMenuMode) result;
    COM_GetValue(get_IFC(), BootMenuMode, result);
    return static_cast<BIOSBootMenuMode>(result);
}

void VBox::IBIOSSettings::set_bootMenuMode(BIOSBootMenuMode value)
{
    COM_SetValue(get_IFC(), BootMenuMode,
                 static_cast<COM_Enum(::BIOSBootMenuMode)>(value));
}

bool VBox::IBIOSSettings::ACPIEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ACPIEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IBIOSSettings::set_ACPIEnabled(bool value)
{
    COM_SetValue(get_IFC(), ACPIEnabled, value);
}

bool VBox::IBIOSSettings::IOAPICEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IOAPICEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IBIOSSettings::set_IOAPICEnabled(bool value)
{
    COM_SetValue(get_IFC(), IOAPICEnabled, value);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
VBox::APICMode VBox::IBIOSSettings::APICMode() const
{
    COM_Enum(::APICMode) result;
    COM_GetValue(get_IFC(), APICMode, result);
    return static_cast<VBox::APICMode>(result);
}

void VBox::IBIOSSettings::set_APICMode(VBox::APICMode value)
{
    COM_SetValue(get_IFC(), APICMode, static_cast<COM_Enum(::APICMode)>(value));
}
#endif

int64_t VBox::IBIOSSettings::timeOffset() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), TimeOffset, result);
    return static_cast<int64_t>(result);
}

void VBox::IBIOSSettings::set_timeOffset(int64_t value)
{
    COM_SetValue(get_IFC(), TimeOffset, value);
}

bool VBox::IBIOSSettings::PXEDebugEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), PXEDebugEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IBIOSSettings::set_PXEDebugEnabled(bool value)
{
    COM_SetValue(get_IFC(), PXEDebugEnabled, value);
}

std::u16string VBox::IBIOSSettings::nonVolatileStorageFile() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NonVolatileStorageFile, result);
    return result;
}
