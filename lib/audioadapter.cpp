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

COM_WRAP_IFC(IAudioAdapter)

bool VBox::IAudioAdapter::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IAudioAdapter::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

bool VBox::IAudioAdapter::enabledIn() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), EnabledIn, result);
    return static_cast<bool>(result);
}

void VBox::IAudioAdapter::set_enabledIn(bool value)
{
    COM_SetValue(get_IFC(), EnabledIn, value);
}

bool VBox::IAudioAdapter::enabledOut() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), EnabledOut, result);
    return static_cast<bool>(result);
}

void VBox::IAudioAdapter::set_enabledOut(bool value)
{
    COM_SetValue(get_IFC(), EnabledOut, value);
}

VBox::AudioControllerType VBox::IAudioAdapter::audioController() const
{
    COM_Enum(::AudioControllerType) result;
    COM_GetValue(get_IFC(), AudioController, result);
    return static_cast<AudioControllerType>(result);
}

void VBox::IAudioAdapter::set_audioController(AudioControllerType value)
{
    COM_SetValue(get_IFC(), AudioController,
                 static_cast<COM_Enum(::AudioControllerType)>(value));
}

VBox::AudioCodecType VBox::IAudioAdapter::audioCodec() const
{
    COM_Enum(::AudioCodecType) result;
    COM_GetValue(get_IFC(), AudioCodec, result);
    return static_cast<AudioCodecType>(result);
}

void VBox::IAudioAdapter::set_audioCodec(AudioCodecType value)
{
    COM_SetValue(get_IFC(), AudioCodec,
                 static_cast<COM_Enum(::AudioCodecType)>(value));
}

VBox::AudioDriverType VBox::IAudioAdapter::audioDriver() const
{
    COM_Enum(::AudioDriverType) result;
    COM_GetValue(get_IFC(), AudioDriver, result);
    return static_cast<AudioDriverType>(result);
}

void VBox::IAudioAdapter::set_audioDriver(AudioDriverType value)
{
    COM_SetValue(get_IFC(), AudioDriver,
                 static_cast<COM_Enum(::AudioDriverType)>(value));
}

std::vector<std::u16string> VBox::IAudioAdapter::propertiesList() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), PropertiesList, result);
    return result;
}

void VBox::IAudioAdapter::setProperty(const std::u16string &key,
        const std::u16string &value)
{
    COM_StringProxy pKey(key);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetProperty(pKey.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IAudioAdapter::getProperty(const std::u16string &key) const
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetProperty(pKey.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}
