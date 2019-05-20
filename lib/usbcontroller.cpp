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

COM_WRAP_IFC(IUSBController)

std::u16string VBox::IUSBController::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IUSBController::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

VBox::USBControllerType VBox::IUSBController::type() const
{
    COM_Enum(::USBControllerType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<USBControllerType>(result);
}

void VBox::IUSBController::set_type(USBControllerType value)
{
    COM_SetValue(get_IFC(), Type, static_cast<COM_Enum(::USBControllerType)>(value));
}

uint16_t VBox::IUSBController::USBStandard() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), USBStandard, result);
    return static_cast<uint16_t>(result);
}
