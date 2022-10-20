/* This file is part of libvbox
 * Copyright (C) 2022  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
COM_WRAP_IFC(IHostDrivePartition)

uint32_t VBox::IHostDrivePartition::number() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Number, result);
    return static_cast<uint32_t>(result);
}

int64_t VBox::IHostDrivePartition::size() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Size, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IHostDrivePartition::start() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Start, result);
    return static_cast<int64_t>(result);
}

VBox::PartitionType VBox::IHostDrivePartition::type() const
{
    COM_Enum(::PartitionType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<PartitionType>(result);
}

bool VBox::IHostDrivePartition::active() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Active, result);
    return static_cast<bool>(result);
}

uint32_t VBox::IHostDrivePartition::typeMBR() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), TypeMBR, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IHostDrivePartition::startCylinder() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), StartCylinder, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IHostDrivePartition::startHead() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), StartHead, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IHostDrivePartition::startSector() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), StartSector, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IHostDrivePartition::endCylinder() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), EndCylinder, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IHostDrivePartition::endHead() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), EndHead, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IHostDrivePartition::endSector() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), EndSector, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IHostDrivePartition::typeUuid() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TypeUuid, result);
    return result;
}

std::u16string VBox::IHostDrivePartition::uuid() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Uuid, result);
    return result;
}

std::u16string VBox::IHostDrivePartition::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}
#endif
