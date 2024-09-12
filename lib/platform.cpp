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
COM_WRAP_IFC(IPlatform)
COM_WRAP_IFC(IPlatformARM)

VBox::PlatformArchitecture VBox::IPlatform::architecture() const
{
    COM_Enum(::PlatformArchitecture) result;
    COM_GetValue(get_IFC(), Architecture, result);
    return static_cast<PlatformArchitecture>(result);
}

void VBox::IPlatform::set_architecture(PlatformArchitecture value)
{
    COM_SetValue(get_IFC(), Architecture,
                 static_cast<COM_Enum(::PlatformArchitecture)>(value));
}

VBox::COMPtr<VBox::IPlatformProperties> VBox::IPlatform::properties() const
{
    COMPtr<IPlatformProperties> result;
    COM_GetValue_Wrap(get_IFC(), Properties, result);
    return result;
}

VBox::COMPtr<VBox::IPlatformX86> VBox::IPlatform::x86() const
{
    COMPtr<IPlatformX86> result;
    COM_GetValue_Wrap(get_IFC(), X86, result);
    return result;
}

VBox::COMPtr<VBox::IPlatformARM> VBox::IPlatform::ARM() const
{
    COMPtr<IPlatformARM> result;
    COM_GetValue_Wrap(get_IFC(), ARM, result);
    return result;
}

VBox::ChipsetType VBox::IPlatform::chipsetType() const
{
    COM_Enum(::ChipsetType) result;
    COM_GetValue(get_IFC(), ChipsetType, result);
    return static_cast<ChipsetType>(result);
}

void VBox::IPlatform::set_chipsetType(ChipsetType value)
{
    COM_SetValue(get_IFC(), ChipsetType, static_cast<COM_Enum(::ChipsetType)>(value));
}

VBox::IommuType VBox::IPlatform::iommuType() const
{
    COM_Enum(::IommuType) result;
    COM_GetValue(get_IFC(), IommuType, result);
    return static_cast<IommuType>(result);
}

void VBox::IPlatform::set_iommuType(IommuType value)
{
    COM_SetValue(get_IFC(), IommuType, static_cast<COM_Enum(::IommuType)>(value));
}

bool VBox::IPlatform::RTCUseUTC() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RTCUseUTC, result);
    return static_cast<bool>(result);
}

void VBox::IPlatform::set_RTCUseUTC(bool value)
{
    COM_SetValue(get_IFC(), RTCUseUTC, static_cast<COM_Bool>(value));
}
#endif
