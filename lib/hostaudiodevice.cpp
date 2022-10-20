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
COM_WRAP_IFC(IHostAudioDevice)

std::u16string VBox::IHostAudioDevice::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::IHostAudioDevice::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IHostAudioDevice::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

VBox::AudioDeviceType VBox::IHostAudioDevice::type() const
{
    COM_Enum(::AudioDeviceType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<AudioDeviceType>(result);
}

void VBox::IHostAudioDevice::set_type(AudioDeviceType value)
{
    COM_SetValue(get_IFC(), Type, static_cast<COM_Enum(::AudioDeviceType)>(value));
}

VBox::AudioDirection VBox::IHostAudioDevice::usage() const
{
    COM_Enum(::AudioDirection) result;
    COM_GetValue(get_IFC(), Usage, result);
    return static_cast<AudioDirection>(result);
}

void VBox::IHostAudioDevice::set_usage(AudioDirection value)
{
    COM_SetValue(get_IFC(), Usage, static_cast<COM_Enum(::AudioDirection)>(value));
}

bool VBox::IHostAudioDevice::defaultIn() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), DefaultIn, result);
    return static_cast<bool>(result);
}

void VBox::IHostAudioDevice::set_defaultIn(bool value)
{
    COM_SetValue(get_IFC(), DefaultIn, static_cast<COM_Bool>(value));
}

bool VBox::IHostAudioDevice::defaultOut() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), DefaultOut, result);
    return static_cast<bool>(result);
}

void VBox::IHostAudioDevice::set_defaultOut(bool value)
{
    COM_SetValue(get_IFC(), DefaultOut, static_cast<COM_Bool>(value));
}

bool VBox::IHostAudioDevice::isHotPlug() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsHotPlug, result);
    return static_cast<bool>(result);
}

void VBox::IHostAudioDevice::set_isHotPlug(bool value)
{
    COM_SetValue(get_IFC(), IsHotPlug, static_cast<COM_Bool>(value));
}

VBox::AudioDeviceState VBox::IHostAudioDevice::state() const
{
    COM_Enum(::AudioDeviceState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<AudioDeviceState>(result);
}

void VBox::IHostAudioDevice::set_state(AudioDeviceState value)
{
    COM_SetValue(get_IFC(), State, static_cast<COM_Enum(::AudioDeviceState)>(value));
}

std::u16string VBox::IHostAudioDevice::getProperty(const std::u16string &key) const
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetProperty(pKey.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}
#endif
