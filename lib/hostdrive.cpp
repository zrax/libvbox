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
COM_WRAP_IFC(IHostDrive)

std::u16string VBox::IHostDrive::drivePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DrivePath, result);
    return result;
}

VBox::PartitioningType VBox::IHostDrive::partitioningType() const
{
    COM_Enum(::PartitioningType) result;
    COM_GetValue(get_IFC(), PartitioningType, result);
    return static_cast<PartitioningType>(result);
}

std::u16string VBox::IHostDrive::uuid() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Uuid, result);
    return result;
}

uint32_t VBox::IHostDrive::sectorSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SectorSize, result);
    return static_cast<uint32_t>(result);
}

int64_t VBox::IHostDrive::size() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Size, result);
    return static_cast<int64_t>(result);
}

std::u16string VBox::IHostDrive::model() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Model, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IHostDrivePartition>> VBox::IHostDrive::partitions() const
{
    std::vector<COMPtr<IHostDrivePartition>> result;
    COM_GetArray_Wrap(get_IFC(), Partitions, result);
    return result;
}
#endif
