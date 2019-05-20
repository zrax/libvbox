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

COM_WRAP_IFC(IUSBDeviceFilter)
COM_WRAP_IFC(IHostUSBDeviceFilter)

std::u16string VBox::IUSBDeviceFilter::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

bool VBox::IUSBDeviceFilter::active() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Active, result);
    return static_cast<bool>(result);
}

void VBox::IUSBDeviceFilter::set_active(bool value)
{
    COM_SetValue(get_IFC(), Active, value);
}

std::u16string VBox::IUSBDeviceFilter::vendorId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VendorId, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_vendorId(const std::u16string &value)
{
    COM_SetString(get_IFC(), VendorId, value);
}

std::u16string VBox::IUSBDeviceFilter::productId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ProductId, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_productId(const std::u16string &value)
{
    COM_SetString(get_IFC(), ProductId, value);
}

std::u16string VBox::IUSBDeviceFilter::revision() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Revision, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_revision(const std::u16string &value)
{
    COM_SetString(get_IFC(), Revision, value);
}

std::u16string VBox::IUSBDeviceFilter::manufacturer() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Manufacturer, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_manufacturer(const std::u16string &value)
{
    COM_SetString(get_IFC(), Manufacturer, value);
}

std::u16string VBox::IUSBDeviceFilter::product() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Product, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_product(const std::u16string &value)
{
    COM_SetString(get_IFC(), Product, value);
}

std::u16string VBox::IUSBDeviceFilter::serialNumber() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SerialNumber, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_serialNumber(const std::u16string &value)
{
    COM_SetString(get_IFC(), SerialNumber, value);
}

std::u16string VBox::IUSBDeviceFilter::port() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Port, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_port(const std::u16string &value)
{
    COM_SetString(get_IFC(), Port, value);
}

std::u16string VBox::IUSBDeviceFilter::remote() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Remote, result);
    return result;
}

void VBox::IUSBDeviceFilter::set_remote(const std::u16string &value)
{
    COM_SetString(get_IFC(), Remote, value);
}

uint32_t VBox::IUSBDeviceFilter::maskedInterfaces() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaskedInterfaces, result);
    return static_cast<uint32_t>(result);
}

void VBox::IUSBDeviceFilter::set_maskedInterfaces(uint32_t value)
{
    COM_SetValue(get_IFC(), MaskedInterfaces, value);
}

VBox::USBDeviceFilterAction VBox::IHostUSBDeviceFilter::action() const
{
    COM_Enum(::USBDeviceFilterAction) result;
    COM_GetValue(get_IFC(), Action, result);
    return static_cast<USBDeviceFilterAction>(result);
}

void VBox::IHostUSBDeviceFilter::set_action(USBDeviceFilterAction value)
{
    COM_SetValue(get_IFC(), Action, static_cast<COM_Enum(::USBDeviceFilterAction)>(value));
}
