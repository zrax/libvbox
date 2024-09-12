/* This file is part of libvbox
 * Copyright (C) 2024  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
COM_WRAP_IFC(IRecordingStateChangedEvent)
COM_WRAP_IFC(IRecordingScreenStateChangedEvent)
#elif VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
COM_WRAP_IFC(IRecordingChangedEvent)
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
bool VBox::IRecordingStateChangedEvent::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo> VBox::IRecordingStateChangedEvent::error() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), Error, result);
    return result;
}

uint32_t VBox::IRecordingScreenStateChangedEvent::screen() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Screen, result);
    return static_cast<uint32_t>(result);
}
#endif
