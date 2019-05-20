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

COM_WRAP_IFC(IBandwidthControl)

uint32_t VBox::IBandwidthControl::numGroups() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), NumGroups, result);
    return static_cast<uint32_t>(result);
}

void VBox::IBandwidthControl::createBandwidthGroup(const std::u16string &name,
        BandwidthGroupType type, int64_t maxBytesPerSec)
{
    COM_StringProxy pName(name);
    auto cType = static_cast<COM_Enum(::BandwidthGroupType)>(type);

    auto rc = get_IFC()->CreateBandwidthGroup(pName.m_text, cType, maxBytesPerSec);
    COM_ERROR_CHECK(rc);
}

void VBox::IBandwidthControl::deleteBandwidthGroup(const std::u16string &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->DeleteBandwidthGroup(pName.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IBandwidthGroup> VBox::IBandwidthControl::getBandwidthGroup(
        const std::u16string &name) const
{
    ::IBandwidthGroup *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetBandwidthGroup(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IBandwidthGroup>::wrap(cResult);
}

std::vector<VBox::COMPtr<VBox::IBandwidthGroup>>
VBox::IBandwidthControl::getAllBandwidthGroups() const
{
    COM_ArrayProxy<::IBandwidthGroup *> pResult;

    auto rc = get_IFC()->GetAllBandwidthGroups(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IBandwidthGroup>> result;
    pResult.toVector(result);
    return result;
}
