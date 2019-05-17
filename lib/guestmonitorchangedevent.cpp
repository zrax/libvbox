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

COM_WRAP_IFC(IGuestMonitorChangedEvent)

VBox::GuestMonitorChangedEventType VBox::IGuestMonitorChangedEvent::changeType() const
{
    COM_Enum(::GuestMonitorChangedEventType) result;
    COM_GetValue(get_IFC(), ChangeType, result);
    return static_cast<GuestMonitorChangedEventType>(result);
}

uint32_t VBox::IGuestMonitorChangedEvent::screenId() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ScreenId, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestMonitorChangedEvent::originX() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), OriginX, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestMonitorChangedEvent::originY() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), OriginY, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestMonitorChangedEvent::width() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Width, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestMonitorChangedEvent::height() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Height, result);
    return static_cast<uint32_t>(result);
}
