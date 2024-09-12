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
COM_WRAP_IFC(IGuestDirectoryEvent)
COM_WRAP_IFC(IGuestDirectoryRegisteredEvent)
COM_WRAP_IFC(IGuestDirectoryStateChangedEvent)
COM_WRAP_IFC(IGuestDirectoryReadEvent)

VBox::COMPtr<VBox::IGuestDirectory> VBox::IGuestDirectoryEvent::directory() const
{
    COMPtr<IGuestDirectory> result;
    COM_GetValue_Wrap(get_IFC(), Directory, result);
    return result;
}

bool VBox::IGuestDirectoryRegisteredEvent::registered() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Registered, result);
    return static_cast<bool>(result);
}

VBox::DirectoryStatus VBox::IGuestDirectoryStateChangedEvent::status() const
{
    COM_Enum(::DirectoryStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<DirectoryStatus>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo>
VBox::IGuestDirectoryStateChangedEvent::error() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), Error, result);
    return result;
}

std::u16string VBox::IGuestDirectoryReadEvent::path() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Path, result);
    return result;
}

VBox::COMPtr<VBox::IFsObjInfo> VBox::IGuestDirectoryReadEvent::objInfo() const
{
    COMPtr<IFsObjInfo> result;
    COM_GetValue_Wrap(get_IFC(), ObjInfo, result);
    return result;
}

std::u16string VBox::IGuestDirectoryReadEvent::owner() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Owner, result);
    return result;
}

std::u16string VBox::IGuestDirectoryReadEvent::groups() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Groups, result);
    return result;
}
#endif
