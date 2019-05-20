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

COM_WRAP_IFC(IUSBDevice)
COM_WRAP_IFC(IHostUSBDevice)

std::u16string VBox::IUSBDevice::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

uint16_t VBox::IUSBDevice::vendorId() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), VendorId, result);
    return static_cast<uint16_t>(result);
}

uint16_t VBox::IUSBDevice::productId() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), ProductId, result);
    return static_cast<uint16_t>(result);
}

uint16_t VBox::IUSBDevice::revision() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), Revision, result);
    return static_cast<uint16_t>(result);
}

std::u16string VBox::IUSBDevice::manufacturer() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Manufacturer, result);
    return result;
}

std::u16string VBox::IUSBDevice::product() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Product, result);
    return result;
}

std::u16string VBox::IUSBDevice::serialNumber() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SerialNumber, result);
    return result;
}

std::u16string VBox::IUSBDevice::address() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Address, result);
    return result;
}

uint16_t VBox::IUSBDevice::port() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), Port, result);
    return static_cast<uint16_t>(result);
}

uint16_t VBox::IUSBDevice::version() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), Version, result);
    return static_cast<uint16_t>(result);
}

uint16_t VBox::IUSBDevice::portVersion() const
{
    COM_UShort result;
    COM_GetValue(get_IFC(), PortVersion, result);
    return static_cast<uint16_t>(result);
}

VBox::USBConnectionSpeed VBox::IUSBDevice::speed() const
{
    COM_Enum(::USBConnectionSpeed) result;
    COM_GetValue(get_IFC(), Speed, result);
    return static_cast<USBConnectionSpeed>(result);
}

bool VBox::IUSBDevice::remote() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Remote, result);
    return static_cast<bool>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 0, 14)
std::vector<std::u16string> VBox::IUSBDevice::deviceInfo() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), DeviceInfo, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
std::u16string VBox::IUSBDevice::backend() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Backend, result);
    return result;
}
#endif

VBox::USBDeviceState VBox::IHostUSBDevice::state() const
{
    COM_Enum(::USBDeviceState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<USBDeviceState>(result);
}
