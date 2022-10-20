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
COM_WRAP_IFC(IUefiVariableStore)

bool VBox::IUefiVariableStore::secureBootEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), SecureBootEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IUefiVariableStore::set_secureBootEnabled(bool value)
{
    COM_SetValue(get_IFC(), SecureBootEnabled, static_cast<COM_Bool>(value));
}

void VBox::IUefiVariableStore::addVariable(const std::u16string &name,
        const std::u16string &owner,
        const std::vector<UefiVariableAttributes> &attributes,
        const std::vector<uint8_t> &data)
{
    COM_StringProxy pName(name);
    COM_StringProxy pOwner(owner);
    COM_ArrayProxy<COM_Enum(::UefiVariableAttributes)> pAttributes(attributes);
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->AddVariable(pName.m_text, pOwner.m_text,
                COM_ArrayParameter(pAttributes), COM_ArrayParameter(pData));
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::deleteVariable(const std::u16string &name,
        const std::u16string &owner)
{
    COM_StringProxy pName(name);
    COM_StringProxy pOwner(owner);

    auto rc = get_IFC()->DeleteVariable(pName.m_text, pOwner.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::changeVariable(const std::u16string &name,
        const std::vector<uint8_t> &data)
{
    COM_StringProxy pName(name);
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->ChangeVariable(pName.m_text, COM_ArrayParameter(pData));
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::queryVariableByName(const std::u16string &name,
        std::u16string *owner, std::vector<UefiVariableAttributes> *attributes,
        std::vector<uint8_t> *data)
{
    COM_StringProxy pName(name);
    COM_StringProxy pOwner;
    COM_ArrayProxy<COM_Enum(::UefiVariableAttributes)> pAttributes;
    COM_ArrayProxy<COM_Byte> pData;

    auto rc = get_IFC()->QueryVariableByName(pName.m_text, &pOwner.m_text,
                COM_ArrayParameterRef(pAttributes), COM_ArrayParameterRef(pData));
    COM_ERROR_CHECK(rc);

    if (owner)
        *owner = pOwner.toString();
    if (attributes)
        pAttributes.toVector(*attributes);
    if (data)
        pData.toVector(*data);
}

void VBox::IUefiVariableStore::queryVariables(std::vector<std::u16string> *names,
        std::vector<std::u16string> *owners)
{
    COM_StringArrayProxy pNames;
    COM_StringArrayProxy pOwners;

    auto rc = get_IFC()->QueryVariables(COM_ArrayParameterRef(pNames),
                COM_ArrayParameterRef(pOwners));
    COM_ERROR_CHECK(rc);

    if (names)
        pNames.toVector(*names);
    if (owners)
        pOwners.toVector(*owners);
}

void VBox::IUefiVariableStore::enrollOraclePlatformKey()
{
    auto rc = get_IFC()->EnrollOraclePlatformKey();
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::enrollPlatformKey(
        const std::vector<uint8_t> &platformKey, const std::u16string &owner)
{
    COM_ArrayProxy<COM_Byte> pPlatformKey(platformKey);
    COM_StringProxy pOwner(owner);

    auto rc = get_IFC()->EnrollPlatformKey(COM_ArrayParameter(pPlatformKey),
                pOwner.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::addKek(const std::vector<uint8_t> &keyEncryptionKey,
        const std::u16string &owner, SignatureType signatureType)
{
    COM_ArrayProxy<COM_Byte> pKeyEncryptionKey(keyEncryptionKey);
    COM_StringProxy pOwner(owner);

    auto rc = get_IFC()->AddKek(COM_ArrayParameter(pKeyEncryptionKey), pOwner.m_text,
                static_cast<COM_Enum(::SignatureType)>(signatureType));
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::addSignatureToDb(
        const std::vector<uint8_t> &signature, const std::u16string &owner,
        SignatureType signatureType)
{
    COM_ArrayProxy<COM_Byte> pSignature(signature);
    COM_StringProxy pOwner(owner);

    auto rc = get_IFC()->AddSignatureToDb(COM_ArrayParameter(pSignature), pOwner.m_text,
                static_cast<COM_Enum(::SignatureType)>(signatureType));
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::addSignatureToDbx(
        const std::vector<uint8_t> &signature, const std::u16string &owner,
        SignatureType signatureType)
{
    COM_ArrayProxy<COM_Byte> pSignature(signature);
    COM_StringProxy pOwner(owner);

    auto rc = get_IFC()->AddSignatureToDbx(COM_ArrayParameter(pSignature), pOwner.m_text,
                static_cast<COM_Enum(::SignatureType)>(signatureType));
    COM_ERROR_CHECK(rc);
}

void VBox::IUefiVariableStore::enrollDefaultMsSignatures()
{
    auto rc = get_IFC()->EnrollDefaultMsSignatures();
    COM_ERROR_CHECK(rc);
}
#endif
