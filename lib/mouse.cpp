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

const void *VBox::IMouse::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IMouse);
}

bool VBox::IMouse::absoluteSupported() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AbsoluteSupported, result);
    return static_cast<bool>(result);
}

bool VBox::IMouse::relativeSupported() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RelativeSupported, result);
    return result;
}

bool VBox::IMouse::multiTouchSupported() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), MultiTouchSupported, result);
    return result;
}

bool VBox::IMouse::needsHostCursor() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), NeedsHostCursor, result);
    return result;
}

VBox::COMPtr<VBox::IMousePointerShape> VBox::IMouse::pointerShape() const
{
    COMPtr<IMousePointerShape> result;
    COM_GetValue_Wrap(get_IFC(), PointerShape, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IMouse::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

void VBox::IMouse::putMouseEvent(int32_t dx, int32_t dy, int32_t dz,
        int32_t dw, int32_t buttonState)
{
    auto rc = get_IFC()->PutMouseEvent(dx, dy, dz, dw, buttonState);
    COM_ERROR_CHECK(rc);
}

void VBox::IMouse::putMouseEventAbsolute(int32_t x, int32_t y, int32_t dz,
        int32_t dw, int32_t buttonState)
{
    auto rc = get_IFC()->PutMouseEventAbsolute(x, y, dz, dw, buttonState);
    COM_ERROR_CHECK(rc);
}

void VBox::IMouse::putEventMultiTouch(int32_t count,
        const std::vector<int64_t> &contacts, uint32_t scanTime)
{
    COM_ArrayProxy<COM_Long64> pContacts(contacts);

    auto rc = get_IFC()->PutEventMultiTouch(count, COM_ArrayParameter(pContacts),
                                            scanTime);
    COM_ERROR_CHECK(rc);
}

void VBox::IMouse::putEventMultiTouchString(int32_t count, const COMString &contacts,
        uint32_t scanTime)
{
    COM_StringProxy pContacts(contacts);

    auto rc = get_IFC()->PutEventMultiTouchString(count, pContacts.m_text, scanTime);
    COM_ERROR_CHECK(rc);
}
