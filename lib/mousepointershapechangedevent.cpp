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

COM_WRAP_IFC(IMousePointerShapeChangedEvent)

bool VBox::IMousePointerShapeChangedEvent::visible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Visible, result);
    return result;
}

bool VBox::IMousePointerShapeChangedEvent::alpha() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Alpha, result);
    return result;
}

uint32_t VBox::IMousePointerShapeChangedEvent::xhot() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Xhot, result);
    return result;
}

uint32_t VBox::IMousePointerShapeChangedEvent::yhot() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Yhot, result);
    return result;
}

uint32_t VBox::IMousePointerShapeChangedEvent::width() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Width, result);
    return result;
}

uint32_t VBox::IMousePointerShapeChangedEvent::height() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Height, result);
    return result;
}

std::vector<uint8_t> VBox::IMousePointerShapeChangedEvent::shape() const
{
    std::vector<uint8_t> result;
    COM_GetArray(get_IFC(), Shape, COM_Byte, result);
    return result;
}
