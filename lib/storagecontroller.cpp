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

COM_WRAP_IFC(IStorageController)

std::u16string VBox::IStorageController::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IStorageController::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

uint32_t VBox::IStorageController::maxDevicesPerPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxDevicesPerPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IStorageController::minPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MinPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IStorageController::maxPortCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxPortCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IStorageController::instance() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Instance, result);
    return static_cast<uint32_t>(result);
}

void VBox::IStorageController::set_instance(uint32_t value)
{
    COM_SetValue(get_IFC(), Instance, value);
}

uint32_t VBox::IStorageController::portCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), PortCount, result);
    return static_cast<uint32_t>(result);
}

void VBox::IStorageController::set_portCount(uint32_t value)
{
    COM_SetValue(get_IFC(), PortCount, value);
}

VBox::StorageBus VBox::IStorageController::bus() const
{
    COM_Enum(::StorageBus) result;
    COM_GetValue(get_IFC(), Bus, result);
    return static_cast<StorageBus>(result);
}

VBox::StorageControllerType VBox::IStorageController::controllerType() const
{
    COM_Enum(::StorageControllerType) result;
    COM_GetValue(get_IFC(), ControllerType, result);
    return static_cast<StorageControllerType>(result);
}

void VBox::IStorageController::set_controllerType(StorageControllerType value)
{
    COM_SetValue(get_IFC(), ControllerType,
                 static_cast<COM_Enum(::StorageControllerType)>(value));
}

bool VBox::IStorageController::useHostIOCache() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), UseHostIOCache, result);
    return static_cast<bool>(result);
}

void VBox::IStorageController::set_useHostIOCache(bool value)
{
    COM_SetValue(get_IFC(), UseHostIOCache, value);
}

bool VBox::IStorageController::bootable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Bootable, result);
    return static_cast<bool>(result);
}
