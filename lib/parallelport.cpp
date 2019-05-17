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

COM_WRAP_IFC(IParallelPort)

uint32_t VBox::IParallelPort::slot() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Slot, result);
    return static_cast<uint32_t>(result);
}

bool VBox::IParallelPort::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IParallelPort::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

uint32_t VBox::IParallelPort::IOBase() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IOBase, result);
    return static_cast<uint32_t>(result);
}

void VBox::IParallelPort::set_IOBase(uint32_t value)
{
    COM_SetValue(get_IFC(), IOBase, value);
}

uint32_t VBox::IParallelPort::IRQ() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IRQ, result);
    return static_cast<uint32_t>(result);
}

void VBox::IParallelPort::set_IRQ(uint32_t value)
{
    COM_SetValue(get_IFC(), IRQ, value);
}

std::u16string VBox::IParallelPort::path() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Path, result);
    return result;
}

void VBox::IParallelPort::set_path(const std::u16string &value)
{
    COM_SetString(get_IFC(), Path, value);
}
