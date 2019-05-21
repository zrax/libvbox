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

COM_WRAP_IFC(IFsObjInfo)
COM_WRAP_IFC(IGuestFsObjInfo)

std::u16string VBox::IFsObjInfo::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

VBox::FsObjType VBox::IFsObjInfo::type() const
{
    COM_Enum(::FsObjType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<FsObjType>(result);
}

std::u16string VBox::IFsObjInfo::fileAttributes() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FileAttributes, result);
    return result;
}

int64_t VBox::IFsObjInfo::objectSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), ObjectSize, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFsObjInfo::allocatedSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), AllocatedSize, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFsObjInfo::accessTime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), AccessTime, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFsObjInfo::birthTime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), BirthTime, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFsObjInfo::changeTime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), ChangeTime, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFsObjInfo::modificationTime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), ModificationTime, result);
    return static_cast<int64_t>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
int32_t VBox::IFsObjInfo::UID() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), UID, result);
    return static_cast<int32_t>(result);
}
#else
uint32_t VBox::IFsObjInfo::UID() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), UID, result);
    return static_cast<uint32_t>(result);
}
#endif

std::u16string VBox::IFsObjInfo::userName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), UserName, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
int32_t VBox::IFsObjInfo::GID() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), GID, result);
    return static_cast<int32_t>(result);
}
#else
uint32_t VBox::IFsObjInfo::GID() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), GID, result);
    return static_cast<uint32_t>(result);
}
#endif

std::u16string VBox::IFsObjInfo::groupName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), GroupName, result);
    return result;
}

int64_t VBox::IFsObjInfo::nodeId() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), NodeId, result);
    return static_cast<int64_t>(result);
}

uint32_t VBox::IFsObjInfo::nodeIdDevice() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), NodeIdDevice, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFsObjInfo::hardLinks() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), HardLinks, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFsObjInfo::deviceNumber() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), DeviceNumber, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFsObjInfo::generationId() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), GenerationId, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFsObjInfo::userFlags() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), UserFlags, result);
    return static_cast<uint32_t>(result);
}
