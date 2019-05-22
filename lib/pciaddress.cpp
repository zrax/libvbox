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

COM_WRAP_IFC(IPCIAddress)

int16_t VBox::IPCIAddress::bus() const
{
    COM_Short result;
    COM_GetValue(get_IFC(), Bus, result);
    return static_cast<int16_t>(result);
}

void VBox::IPCIAddress::set_bus(int16_t value)
{
    COM_SetValue(get_IFC(), Bus, value);
}

int16_t VBox::IPCIAddress::device() const
{
    COM_Short result;
    COM_GetValue(get_IFC(), Device, result);
    return static_cast<int16_t>(result);
}

void VBox::IPCIAddress::set_device(int16_t value)
{
    COM_SetValue(get_IFC(), Device, value);
}

int16_t VBox::IPCIAddress::devFunction() const
{
    COM_Short result;
    COM_GetValue(get_IFC(), DevFunction, result);
    return static_cast<int16_t>(result);
}

void VBox::IPCIAddress::set_devFunction(int16_t value)
{
    COM_SetValue(get_IFC(), DevFunction, value);
}

int32_t VBox::IPCIAddress::asLong()
{
    COM_Long cResult;

    auto rc = get_IFC()->AsLong(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int32_t>(cResult);
}

void VBox::IPCIAddress::fromLong(int32_t number)
{
    auto rc = get_IFC()->FromLong(number);
    COM_ERROR_CHECK(rc);
}
