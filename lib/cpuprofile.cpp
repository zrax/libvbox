/* This file is part of libvbox
 * Copyright (C) 2022  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
COM_WRAP_IFC(ICPUProfile)

std::u16string VBox::ICPUProfile::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::ICPUProfile::fullName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FullName, result);
    return result;
}

VBox::CPUArchitecture VBox::ICPUProfile::architecture() const
{
    COM_Enum(::CPUArchitecture) result;
    COM_GetValue(get_IFC(), Architecture, result);
    return static_cast<CPUArchitecture>(result);
}
#endif
