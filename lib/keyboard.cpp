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

COM_WRAP_IFC(IKeyboard)

std::vector<VBox::KeyboardLED> VBox::IKeyboard::keyboardLEDs() const
{
    std::vector<KeyboardLED> result;
    COM_GetArray(get_IFC(), KeyboardLEDs, COM_Enum(::KeyboardLED), result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IKeyboard::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

void VBox::IKeyboard::putScancode(int32_t scancode)
{
    auto rc = get_IFC()->PutScancode(scancode);
    COM_ERROR_CHECK(rc);
}

uint32_t VBox::IKeyboard::putScancodes(const std::vector<int32_t> &scancodes)
{
    COM_ULong cResult;
    COM_ArrayProxy<COM_Long> pScancodes(scancodes);

    auto rc = get_IFC()->PutScancodes(COM_ArrayParameter(pScancodes), &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

void VBox::IKeyboard::putCAD()
{
    auto rc = get_IFC()->PutCAD();
    COM_ERROR_CHECK(rc);
}

void VBox::IKeyboard::releaseKeys()
{
    auto rc = get_IFC()->ReleaseKeys();
    COM_ERROR_CHECK(rc);
}
