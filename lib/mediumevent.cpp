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

COM_WRAP_IFC(IMediumRegisteredEvent)
COM_WRAP_IFC(IMediumConfigChangedEvent)

std::u16string VBox::IMediumRegisteredEvent::mediumId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MediumId, result);
    return result;
}

VBox::DeviceType VBox::IMediumRegisteredEvent::mediumType() const
{
    COM_Enum(::DeviceType) result;
    COM_GetValue(get_IFC(), MediumType, result);
    return static_cast<DeviceType>(result);
}

bool VBox::IMediumRegisteredEvent::registered() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Registered, result);
    return result;
}

VBox::COMPtr<VBox::IMedium> VBox::IMediumConfigChangedEvent::medium() const
{
    COMPtr<IMedium> result;
    COM_GetValue_Wrap(get_IFC(), Medium, result);
    return result;
}
