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

COM_WRAP_IFC(IVirtualSystemDescription)

uint32_t VBox::IVirtualSystemDescription::count() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Count, result);
    return static_cast<uint32_t>(result);
}

void VBox::IVirtualSystemDescription::getDescription(
        std::vector<VirtualSystemDescriptionType> *types,
        std::vector<std::u16string> *refs,
        std::vector<std::u16string> *OVFValues,
        std::vector<std::u16string> *VBoxValues,
        std::vector<std::u16string> *extraConfigValues)
{
    COM_ArrayProxy<COM_Enum(::VirtualSystemDescriptionType)> pTypes;
    COM_StringArrayProxy pRefs;
    COM_StringArrayProxy pOVFValues;
    COM_StringArrayProxy pVBoxValues;
    COM_StringArrayProxy pExtraConfigValues;

    auto rc = get_IFC()->GetDescription(COM_ArrayParameterRef(pTypes),
                COM_ArrayParameterRef(pRefs), COM_ArrayParameterRef(pOVFValues),
                COM_ArrayParameterRef(pVBoxValues),
                COM_ArrayParameterRef(pExtraConfigValues));
    COM_ERROR_CHECK(rc);

    if (types)
        pTypes.toVector(*types);
    if (refs)
        pRefs.toVector(*refs);
    if (OVFValues)
        pOVFValues.toVector(*OVFValues);
    if (VBoxValues)
        pVBoxValues.toVector(*VBoxValues);
    if (extraConfigValues)
        pExtraConfigValues.toVector(*extraConfigValues);
}

void VBox::IVirtualSystemDescription::getDescriptionByType(
        VirtualSystemDescriptionType type,
        std::vector<VirtualSystemDescriptionType> *types,
        std::vector<std::u16string> *refs,
        std::vector<std::u16string> *OVFValues,
        std::vector<std::u16string> *VBoxValues,
        std::vector<std::u16string> *extraConfigValues)
{
    auto cType = static_cast<COM_Enum(::VirtualSystemDescriptionType)>(type);
    COM_ArrayProxy<COM_Enum(::VirtualSystemDescriptionType)> pTypes;
    COM_StringArrayProxy pRefs;
    COM_StringArrayProxy pOVFValues;
    COM_StringArrayProxy pVBoxValues;
    COM_StringArrayProxy pExtraConfigValues;

    auto rc = get_IFC()->GetDescriptionByType(cType, COM_ArrayParameterRef(pTypes),
                COM_ArrayParameterRef(pRefs), COM_ArrayParameterRef(pOVFValues),
                COM_ArrayParameterRef(pVBoxValues),
                COM_ArrayParameterRef(pExtraConfigValues));
    COM_ERROR_CHECK(rc);

    if (types)
        pTypes.toVector(*types);
    if (refs)
        pRefs.toVector(*refs);
    if (OVFValues)
        pOVFValues.toVector(*OVFValues);
    if (VBoxValues)
        pVBoxValues.toVector(*VBoxValues);
    if (extraConfigValues)
        pExtraConfigValues.toVector(*extraConfigValues);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::IVirtualSystemDescription::removeDescriptionByType(
        VirtualSystemDescriptionType type)
{
    auto cType = static_cast<COM_Enum(::VirtualSystemDescriptionType)>(type);

    auto rc = get_IFC()->RemoveDescriptionByType(cType);
    COM_ERROR_CHECK(rc);
}
#endif

std::vector<std::u16string> VBox::IVirtualSystemDescription::getValuesByType(
        VirtualSystemDescriptionType type, VirtualSystemDescriptionValueType which)
{
    COM_StringArrayProxy pResult;
    auto cType = static_cast<COM_Enum(::VirtualSystemDescriptionType)>(type);
    auto cWhich = static_cast<COM_Enum(::VirtualSystemDescriptionValueType)>(which);

    auto rc = get_IFC()->GetValuesByType(cType, cWhich, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

void VBox::IVirtualSystemDescription::setFinalValues(
        const std::vector<bool> &enabled,
        const std::vector<std::u16string> &VBoxValues,
        const std::vector<std::u16string> &extraConfigValues)
{
    COM_ArrayProxy<COM_Bool> pEnabled(enabled);
    COM_StringArrayProxy pVBoxValues(VBoxValues);
    COM_StringArrayProxy pExtraConfigValues(extraConfigValues);

    auto rc = get_IFC()->SetFinalValues(COM_ArrayParameter(pEnabled),
                COM_ArrayParameter(pVBoxValues), COM_ArrayParameter(pExtraConfigValues));
    COM_ERROR_CHECK(rc);
}

void VBox::IVirtualSystemDescription::addDescription(
        VirtualSystemDescriptionType type, const std::u16string &VBoxValue,
        const std::u16string &extraConfigValue)
{
    auto cType = static_cast<COM_Enum(::VirtualSystemDescriptionType)>(type);
    COM_StringProxy pVBoxValue(VBoxValue);
    COM_StringProxy pExtraConfigValue(extraConfigValue);

    auto rc = get_IFC()->AddDescription(cType, pVBoxValue.m_text,
                pExtraConfigValue.m_text);
    COM_ERROR_CHECK(rc);
}
