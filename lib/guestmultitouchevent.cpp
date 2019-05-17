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

COM_WRAP_IFC(IGuestMultiTouchEvent)

int32_t VBox::IGuestMultiTouchEvent::contactCount() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), ContactCount, result);
    return static_cast<int32_t>(result);
}

std::vector<int16_t> VBox::IGuestMultiTouchEvent::xPositions() const
{
    std::vector<int16_t> result;
    COM_GetArray(get_IFC(), XPositions, COM_Short, result);
    return result;
}

std::vector<int16_t> VBox::IGuestMultiTouchEvent::yPositions() const
{
    std::vector<int16_t> result;
    COM_GetArray(get_IFC(), YPositions, COM_Short, result);
    return result;
}

std::vector<uint16_t> VBox::IGuestMultiTouchEvent::contactIds() const
{
    std::vector<uint16_t> result;
    COM_GetArray(get_IFC(), ContactIds, COM_UShort, result);
    return result;
}

std::vector<uint16_t> VBox::IGuestMultiTouchEvent::contactFlags() const
{
    std::vector<uint16_t> result;
    COM_GetArray(get_IFC(), ContactFlags, COM_UShort, result);
    return result;
}

uint32_t VBox::IGuestMultiTouchEvent::scanTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ScanTime, result);
    return static_cast<uint32_t>(result);
}
