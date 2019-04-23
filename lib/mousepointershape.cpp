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

const void *VBox::IMousePointerShape::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IMousePointerShape);
}

bool VBox::IMousePointerShape::visible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Visible, result);
    return static_cast<bool>(result);
}

bool VBox::IMousePointerShape::alpha() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Alpha, result);
    return static_cast<bool>(result);
}

uint32_t VBox::IMousePointerShape::hotX() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), HotX, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IMousePointerShape::hotY() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), HotY, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IMousePointerShape::width() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Width, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IMousePointerShape::height() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Height, result);
    return static_cast<uint32_t>(result);
}

std::vector<uint8_t> VBox::IMousePointerShape::shape() const
{
    std::vector<uint8_t> result;
    COM_GetArray(get_IFC(), Shape, COM_Byte, result);
    return result;
}
