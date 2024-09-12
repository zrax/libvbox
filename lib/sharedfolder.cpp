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

COM_WRAP_IFC(ISharedFolder)

std::u16string VBox::ISharedFolder::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::ISharedFolder::hostPath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), HostPath, result);
    return result;
}

bool VBox::ISharedFolder::accessible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accessible, result);
    return static_cast<bool>(result);
}

bool VBox::ISharedFolder::writable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Writable, result);
    return static_cast<bool>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::ISharedFolder::set_writable(bool value)
{
    COM_SetValue(get_IFC(), Writable, value);
}
#endif

bool VBox::ISharedFolder::autoMount() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AutoMount, result);
    return static_cast<bool>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::ISharedFolder::set_autoMount(bool value)
{
    COM_SetValue(get_IFC(), AutoMount, value);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
std::u16string VBox::ISharedFolder::autoMountPoint() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AutoMountPoint, result);
    return result;
}

void VBox::ISharedFolder::set_autoMountPoint(const std::u16string &value)
{
    COM_SetString(get_IFC(), AutoMountPoint, value);
}
#endif

std::u16string VBox::ISharedFolder::lastAccessError() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LastAccessError, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox::SymlinkPolicy VBox::ISharedFolder::symlinkPolicy() const
{
    COM_Enum(::SymlinkPolicy) result;
    COM_GetValue(get_IFC(), SymlinkPolicy, result);
    return static_cast<SymlinkPolicy>(result);
}
#endif
