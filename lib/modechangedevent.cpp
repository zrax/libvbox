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

COM_WRAP_IFC(IClipboardModeChangedEvent)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
COM_WRAP_IFC(IClipboardFileTransferModeChangedEvent)
#endif
COM_WRAP_IFC(IDnDModeChangedEvent)

VBox::ClipboardMode VBox::IClipboardModeChangedEvent::clipboardMode() const
{
    COM_Enum(::ClipboardMode) result;
    COM_GetValue(get_IFC(), ClipboardMode, result);
    return static_cast<ClipboardMode>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
bool VBox::IClipboardFileTransferModeChangedEvent::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}
#endif

VBox::DnDMode VBox::IDnDModeChangedEvent::dndMode() const
{
    COM_Enum(::DnDMode) result;
    COM_GetValue(get_IFC(), DndMode, result);
    return static_cast<DnDMode>(result);
}
