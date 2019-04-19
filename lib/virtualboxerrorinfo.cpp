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

#include <cwchar>

const void *VBox::IVirtualBoxErrorInfo::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IVirtualBoxErrorInfo);
}

int32_t VBox::IVirtualBoxErrorInfo::resultCode() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), ResultCode, result);
    return result;
}

int32_t VBox::IVirtualBoxErrorInfo::resultDetail() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), ResultDetail, result);
    return result;
}

VBox::COMString VBox::IVirtualBoxErrorInfo::interfaceID() const
{
    COMString result;
    COM_GetString(get_IFC(), InterfaceID, result);
    return result;
}

VBox::COMString VBox::IVirtualBoxErrorInfo::component() const
{
    COMString result;
    COM_GetString(get_IFC(), Component, result);
    return result;
}

VBox::COMString VBox::IVirtualBoxErrorInfo::text() const
{
    COMString result;
    COM_GetString(get_IFC(), Text, result);
    return result;
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo> VBox::IVirtualBoxErrorInfo::next() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), Next, result);
    return result;
}
