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
COM_WRAP_IFC(IPlatformX86)

bool VBox::IPlatformX86::HPETEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HPETEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IPlatformX86::set_HPETEnabled(bool value)
{
    COM_SetValue(get_IFC(), HPETEnabled, value);
}

bool VBox::IPlatformX86::getCPUProperty(CPUPropertyTypeX86 property) const
{
    COM_Bool cResult;
    auto cProperty = static_cast<COM_Enum(::CPUPropertyTypeX86)>(property);

    auto rc = get_IFC()->GetCPUProperty(cProperty, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IPlatformX86::setCPUProperty(CPUPropertyTypeX86 property, bool value)
{
    auto cProperty = static_cast<COM_Enum(::CPUPropertyTypeX86)>(property);

    auto rc = get_IFC()->SetCPUProperty(cProperty, value);
    COM_ERROR_CHECK(rc);
}

void VBox::IPlatformX86::getCPUIDLeafByOrdinal(uint32_t ordinal, uint32_t *idx,
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

void VBox::IPlatformX86::getCPUIDLeaf(uint32_t idx, uint32_t idxSub,
        uint32_t *valEax, uint32_t *valEbx, uint32_t *valEcx, uint32_t *valEdx) const
{
    COM_ULong cValEax;
    COM_ULong cValEbx;
    COM_ULong cValEcx;
    COM_ULong cValEdx;

    auto rc = get_IFC()->GetCPUIDLeaf(idx, idxSub, &cValEax, &cValEbx,
                                      &cValEcx, &cValEdx);
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

void VBox::IPlatformX86::setCPUIDLeaf(uint32_t idx, uint32_t idxSub,
        uint32_t valEax, uint32_t valEbx, uint32_t valEcx, uint32_t valEdx)
{
    auto rc = get_IFC()->SetCPUIDLeaf(idx, idxSub, valEax, valEbx, valEcx, valEdx);
    COM_ERROR_CHECK(rc);
}

void VBox::IPlatformX86::removeCPUIDLeaf(uint32_t idx, uint32_t idxSub)
{
    auto rc = get_IFC()->RemoveCPUIDLeaf(idx, idxSub);
    COM_ERROR_CHECK(rc);
}

void VBox::IPlatformX86::removeAllCPUIDLeaves()
{
    auto rc = get_IFC()->RemoveAllCPUIDLeaves();
    COM_ERROR_CHECK(rc);
}

bool VBox::IPlatformX86::getHWVirtExProperty(HWVirtExPropertyType property) const
{
    COM_Bool cResult;
    auto cProperty = static_cast<COM_Enum(::HWVirtExPropertyType)>(property);

    auto rc = get_IFC()->GetHWVirtExProperty(cProperty, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IPlatformX86::setHWVirtExProperty(HWVirtExPropertyType property, bool value)
{
    auto cProperty = static_cast<COM_Enum(::HWVirtExPropertyType)>(property);

    auto rc = get_IFC()->SetHWVirtExProperty(cProperty, value);
    COM_ERROR_CHECK(rc);
}
#endif
