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
COM_WRAP_IFC(IFsInfo)
COM_WRAP_IFC(IGuestFsInfo)

int64_t VBox::IFsInfo::freeSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), FreeSize, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFsInfo::totalSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), TotalSize, result);
    return static_cast<int64_t>(result);
}

uint32_t VBox::IFsInfo::blockSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), BlockSize, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFsInfo::sectorSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SectorSize, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFsInfo::serialNumber() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), SerialNumber, result);
    return static_cast<uint32_t>(result);
}

bool VBox::IFsInfo::isRemote() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsRemote, result);
    return static_cast<bool>(result);
}

bool VBox::IFsInfo::isCaseSensitive() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsCaseSensitive, result);
    return static_cast<bool>(result);
}

bool VBox::IFsInfo::isReadOnly() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsReadOnly, result);
    return static_cast<bool>(result);
}

bool VBox::IFsInfo::isCompressed() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsCompressed, result);
    return static_cast<bool>(result);
}

bool VBox::IFsInfo::supportsFileCompression() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), SupportsFileCompression, result);
    return static_cast<bool>(result);
}

uint32_t VBox::IFsInfo::maxComponent() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxComponent, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IFsInfo::type() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Type, result);
    return result;
}

std::u16string VBox::IFsInfo::label() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Label, result);
    return result;
}

std::u16string VBox::IFsInfo::mountPoint() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MountPoint, result);
    return result;
}
#endif
