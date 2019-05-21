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

COM_WRAP_IFC(IAdditionsFacility)

VBox::AdditionsFacilityClass VBox::IAdditionsFacility::classType() const
{
    COM_Enum(::AdditionsFacilityClass) result;
    COM_GetValue(get_IFC(), ClassType, result);
    return static_cast<AdditionsFacilityClass>(result);
}

int64_t VBox::IAdditionsFacility::lastUpdated() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), LastUpdated, result);
    return static_cast<int64_t>(result);
}

std::u16string VBox::IAdditionsFacility::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

VBox::AdditionsFacilityStatus VBox::IAdditionsFacility::status() const
{
    COM_Enum(::AdditionsFacilityStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<AdditionsFacilityStatus>(result);
}

VBox::AdditionsFacilityType VBox::IAdditionsFacility::type() const
{
    COM_Enum(::AdditionsFacilityType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<AdditionsFacilityType>(result);
}
