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

COM_WRAP_IFC(IVRDEServer)

bool VBox::IVRDEServer::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IVRDEServer::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

VBox::AuthType VBox::IVRDEServer::authType() const
{
    COM_Enum(::AuthType) result;
    COM_GetValue(get_IFC(), AuthType, result);
    return static_cast<AuthType>(result);
}

void VBox::IVRDEServer::set_authType(AuthType value)
{
    COM_SetValue(get_IFC(), AuthType, static_cast<COM_Enum(::AuthType)>(value));
}

uint32_t VBox::IVRDEServer::authTimeout() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AuthTimeout, result);
    return static_cast<uint32_t>(result);
}

void VBox::IVRDEServer::set_authTimeout(uint32_t value)
{
    COM_SetValue(get_IFC(), AuthTimeout, value);
}

bool VBox::IVRDEServer::allowMultiConnection() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AllowMultiConnection, result);
    return static_cast<bool>(result);
}

void VBox::IVRDEServer::set_allowMultiConnection(bool value)
{
    COM_SetValue(get_IFC(), AllowMultiConnection, value);
}

bool VBox::IVRDEServer::reuseSingleConnection() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ReuseSingleConnection, result);
    return static_cast<bool>(result);
}

void VBox::IVRDEServer::set_reuseSingleConnection(bool value)
{
    COM_SetValue(get_IFC(), ReuseSingleConnection, value);
}

std::u16string VBox::IVRDEServer::VRDEExtPack() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VRDEExtPack, result);
    return result;
}

void VBox::IVRDEServer::set_VRDEExtPack(const std::u16string &value)
{
    COM_SetString(get_IFC(), VRDEExtPack, value);
}

std::u16string VBox::IVRDEServer::authLibrary() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AuthLibrary, result);
    return result;
}

void VBox::IVRDEServer::set_authLibrary(const std::u16string &value)
{
    COM_SetString(get_IFC(), AuthLibrary, value);
}

std::vector<std::u16string> VBox::IVRDEServer::VRDEProperties() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), VRDEProperties, result);
    return result;
}

void VBox::IVRDEServer::setVRDEProperty(const std::u16string &key,
        const std::u16string &value)
{
    COM_StringProxy pKey(key);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetVRDEProperty(pKey.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IVRDEServer::getVRDEProperty(const std::u16string &key) const
{
    COM_StringProxy pResult;
    COM_StringProxy pKey(key);

    auto rc = get_IFC()->GetVRDEProperty(pKey.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}
