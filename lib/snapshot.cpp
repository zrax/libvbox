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

COM_WRAP_IFC(ISnapshot)

std::u16string VBox::ISnapshot::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::ISnapshot::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::ISnapshot::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

std::u16string VBox::ISnapshot::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

void VBox::ISnapshot::set_description(const std::u16string &value)
{
    COM_SetString(get_IFC(), Description, value);
}

int64_t VBox::ISnapshot::timeStamp() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), TimeStamp, result);
    return static_cast<int64_t>(result);
}

bool VBox::ISnapshot::online() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Online, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IMachine> VBox::ISnapshot::machine() const
{
    COMPtr<IMachine> result;
    COM_GetValue_Wrap(get_IFC(), Machine, result);
    return result;
}

VBox::COMPtr<VBox::ISnapshot> VBox::ISnapshot::parent() const
{
    COMPtr<ISnapshot> result;
    COM_GetValue_Wrap(get_IFC(), Parent, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::ISnapshot>> VBox::ISnapshot::children() const
{
    std::vector<COMPtr<ISnapshot>> result;
    COM_GetArray_Wrap(get_IFC(), Children, result);
    return result;
}

uint32_t VBox::ISnapshot::childrenCount() const
{
    COM_ULong result;

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_GetValue(get_IFC(), ChildrenCount, result);
#else
    auto rc = get_IFC()->GetChildrenCount(&result);
    COM_ERROR_CHECK(rc);
#endif

    return static_cast<uint32_t>(result);
}

uint32_t VBox::ISnapshot::getChildrenCount() const
{
    return childrenCount();
}
