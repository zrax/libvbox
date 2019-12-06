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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 32) )
COM_WRAP_IFC(IGuestAdditionsStatusChangedEvent)

VBox::AdditionsFacilityType VBox::IGuestAdditionsStatusChangedEvent::facility() const
{
    COM_Enum(::AdditionsFacilityType) result;
    COM_GetValue(get_IFC(), Facility, result);
    return static_cast<AdditionsFacilityType>(result);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
void VBox::IGuestAdditionsStatusChangedEvent::set_facility(AdditionsFacilityType value)
{
    COM_SetValue(get_IFC(), Facility,
                 static_cast<COM_Enum(::AdditionsFacilityType)>(value));
}
#endif

VBox::AdditionsFacilityStatus VBox::IGuestAdditionsStatusChangedEvent::status() const
{
    COM_Enum(::AdditionsFacilityStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<AdditionsFacilityStatus>(result);
}

VBox::AdditionsRunLevelType VBox::IGuestAdditionsStatusChangedEvent::runLevel() const
{
    COM_Enum(::AdditionsRunLevelType) result;
    COM_GetValue(get_IFC(), RunLevel, result);
    return static_cast<AdditionsRunLevelType>(result);
}

int64_t VBox::ICursorPositionChangedEvent::timestamp() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Timestamp, result);
    return static_cast<int64_t>(result);
}
#endif
