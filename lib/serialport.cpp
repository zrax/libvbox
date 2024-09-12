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

COM_WRAP_IFC(ISerialPort)

uint32_t VBox::ISerialPort::slot() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Slot, result);
    return static_cast<uint32_t>(result);
}

bool VBox::ISerialPort::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::ISerialPort::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
uint32_t VBox::ISerialPort::IOBase() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IOBase, result);
    return static_cast<uint32_t>(result);
}

void VBox::ISerialPort::set_IOBase(uint32_t value)
{
    COM_SetValue(get_IFC(), IOBase, value);
}
#else
uint32_t VBox::ISerialPort::IOAddress() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IOAddress, result);
    return static_cast<uint32_t>(result);
}

void VBox::ISerialPort::set_IOAddress(uint32_t value)
{
    COM_SetValue(get_IFC(), IOAddress, value);
}
#endif

uint32_t VBox::ISerialPort::IRQ() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), IRQ, result);
    return static_cast<uint32_t>(result);
}

void VBox::ISerialPort::set_IRQ(uint32_t value)
{
    COM_SetValue(get_IFC(), IRQ, value);
}

VBox::PortMode VBox::ISerialPort::hostMode() const
{
    COM_Enum(::PortMode) result;
    COM_GetValue(get_IFC(), HostMode, result);
    return static_cast<PortMode>(result);
}

void VBox::ISerialPort::set_hostMode(PortMode value)
{
    COM_SetValue(get_IFC(), HostMode, static_cast<COM_Enum(::PortMode)>(value));
}

bool VBox::ISerialPort::server() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Server, result);
    return static_cast<bool>(result);
}

void VBox::ISerialPort::set_server(bool value)
{
    COM_SetValue(get_IFC(), Server, value);
}

std::u16string VBox::ISerialPort::path() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Path, result);
    return result;
}

void VBox::ISerialPort::set_path(const std::u16string &value)
{
    COM_SetString(get_IFC(), Path, value);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::UartType VBox::ISerialPort::uartType() const
{
    COM_Enum(::UartType) result;
    COM_GetValue(get_IFC(), UartType, result);
    return static_cast<UartType>(result);
}

void VBox::ISerialPort::set_uartType(UartType value)
{
    COM_SetValue(get_IFC(), UartType, static_cast<COM_Enum(::UartType)>(value));
}
#endif
