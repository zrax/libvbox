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

std::wstring VBox::IVirtualBox::version() const
{
    std::wstring result;
    COM_GetString(get_IFC(), Version, result);
    return result;
}

std::wstring VBox::IVirtualBox::versionNormalized() const
{
    std::wstring result;
    COM_GetString(get_IFC(), VersionNormalized, result);
    return result;
}

uint32_t VBox::IVirtualBox::revision() const
{
    uint32_t result;
    COM_GetValue(get_IFC(), Revision, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMachine>> VBox::IVirtualBox::machines() const
{
    std::vector<COMPtr<IMachine>> result;
    COM_GetArray_Wrap(get_IFC(), Machines, result);
    return result;
}
