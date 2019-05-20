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

COM_WRAP_IFC(IUSBDeviceFilters)

std::vector<VBox::COMPtr<VBox::IUSBDeviceFilter>>
VBox::IUSBDeviceFilters::deviceFilters() const
{
    std::vector<COMPtr<IUSBDeviceFilter>> result;
    COM_GetArray_Wrap(get_IFC(), DeviceFilters, result);
    return result;
}

VBox::COMPtr<VBox::IUSBDeviceFilter> VBox::IUSBDeviceFilters::createDeviceFilter(
        const std::u16string &name)
{
    ::IUSBDeviceFilter *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->CreateDeviceFilter(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBDeviceFilter>::wrap(cResult);
}

void VBox::IUSBDeviceFilters::insertDeviceFilter(uint32_t position,
        const COMPtr<IUSBDeviceFilter> &filter)
{
    auto rc = get_IFC()->InsertDeviceFilter(position, filter->get_IFC());
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IUSBDeviceFilter> VBox::IUSBDeviceFilters::removeDeviceFilter(
        uint32_t position)
{
    ::IUSBDeviceFilter *cResult = nullptr;

    auto rc = get_IFC()->RemoveDeviceFilter(position, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBDeviceFilter>::wrap(cResult);
}
