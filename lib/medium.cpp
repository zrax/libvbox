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

COM_WRAP_IFC(IMedium)

std::u16string VBox::IMedium::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::IMedium::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

void VBox::IMedium::set_description(const std::u16string &value)
{
    COM_SetString(get_IFC(), Description, value);
}

VBox::MediumState VBox::IMedium::state() const
{
    COM_Enum(::MediumState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<MediumState>(result);
}

std::vector<VBox::MediumVariant> VBox::IMedium::variant() const
{
    std::vector<MediumVariant> result;
    COM_GetArray(get_IFC(), Variant, COM_Enum(::MediumVariant), result);
    return result;
}

std::u16string VBox::IMedium::location() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Location, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::IMedium::set_location(const std::u16string &value)
{
    COM_SetString(get_IFC(), Location, value);
}
#endif

std::u16string VBox::IMedium::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

VBox::DeviceType VBox::IMedium::deviceType() const
{
    COM_Enum(::DeviceType) result;
    COM_GetValue(get_IFC(), DeviceType, result);
    return static_cast<DeviceType>(result);
}

bool VBox::IMedium::hostDrive() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HostDrive, result);
    return static_cast<bool>(result);
}

int64_t VBox::IMedium::size() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Size, result);
    return static_cast<int64_t>(result);
}

std::u16string VBox::IMedium::format() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Format, result);
    return result;
}

VBox::COMPtr<VBox::IMediumFormat> VBox::IMedium::mediumFormat() const
{
    COMPtr<IMediumFormat> result;
    COM_GetValue_Wrap(get_IFC(), MediumFormat, result);
    return result;
}

VBox::MediumType VBox::IMedium::type() const
{
    COM_Enum(::MediumType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<MediumType>(result);
}

void VBox::IMedium::set_type(MediumType value)
{
    COM_SetValue(get_IFC(), Type, static_cast<COM_Enum(::MediumType)>(value));
}

std::vector<VBox::MediumType> VBox::IMedium::allowedTypes() const
{
    std::vector<MediumType> result;
    COM_GetArray(get_IFC(), AllowedTypes, COM_Enum(::MediumType), result);
    return result;
}

VBox::COMPtr<VBox::IMedium> VBox::IMedium::parent() const
{
    COMPtr<IMedium> result;
    COM_GetValue_Wrap(get_IFC(), Parent, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IMedium>> VBox::IMedium::children() const
{
    std::vector<COMPtr<IMedium>> result;
    COM_GetArray_Wrap(get_IFC(), Children, result);
    return result;
}

VBox::COMPtr<VBox::IMedium> VBox::IMedium::base() const
{
    COMPtr<IMedium> result;
    COM_GetValue_Wrap(get_IFC(), Base, result);
    return result;
}

bool VBox::IMedium::readOnly() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ReadOnly, result);
    return static_cast<bool>(result);
}

int64_t VBox::IMedium::logicalSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), LogicalSize, result);
    return static_cast<int64_t>(result);
}

bool VBox::IMedium::autoReset() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), AutoReset, result);
    return static_cast<bool>(result);
}

void VBox::IMedium::set_autoReset(bool value)
{
    COM_SetValue(get_IFC(), AutoReset, value);
}

std::u16string VBox::IMedium::lastAccessError() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LastAccessError, result);
    return result;
}

std::vector<std::u16string> VBox::IMedium::machineIds() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), MachineIds, result);
    return result;
}

void VBox::IMedium::setIds(bool setImageId, const std::u16string &imageId,
        bool setParentId, const std::u16string &parentId)
{
    COM_StringProxy pImageId(imageId);
    COM_StringProxy pParentId(parentId);

    auto rc = get_IFC()->SetIds(setImageId, pImageId.m_text, setParentId,
                pParentId.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::MediumState VBox::IMedium::refreshState()
{
    COM_Enum(::MediumState) cResult;

    auto rc = get_IFC()->RefreshState(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<MediumState>(cResult);
}

std::vector<std::u16string> VBox::IMedium::getSnapshotIds(
        const std::u16string &machineId)
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pMachineId(machineId);

    auto rc = get_IFC()->GetSnapshotIds(pMachineId.m_text,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IToken> VBox::IMedium::lockRead()
{
    ::IToken *cResult = nullptr;

    auto rc = get_IFC()->LockRead(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IToken>::wrap(cResult);
}

VBox::COMPtr<VBox::IToken> VBox::IMedium::lockWrite()
{
    ::IToken *cResult = nullptr;

    auto rc = get_IFC()->LockWrite(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IToken>::wrap(cResult);
}

void VBox::IMedium::close()
{
    auto rc = get_IFC()->Close();
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IMedium::getProperty(const std::u16string &name) const
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetProperty(pName.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IMedium::setProperty(const std::u16string &name,
        const std::u16string &value)
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetProperty(pName.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

std::vector<std::u16string> VBox::IMedium::getProperties(
        const std::u16string &names, std::vector<std::u16string> *returnNames) const
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pNames(names);
    COM_StringArrayProxy pReturnNames;

    auto rc = get_IFC()->GetProperties(pNames.m_text,
                COM_ArrayParameterRef(pReturnNames), COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (returnNames)
        pReturnNames.toVector(*returnNames);
    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

void VBox::IMedium::setProperties(const std::vector<std::u16string> &names,
        const std::vector<std::u16string> &values)
{
    COM_StringArrayProxy pNames(names);
    COM_StringArrayProxy pValues(values);

    auto rc = get_IFC()->SetProperties(COM_ArrayParameter(pNames),
                COM_ArrayParameter(pValues));
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::createBaseStorage(int64_t logicalSize,
        const std::vector<MediumVariant> &variant)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::MediumVariant)> pVariant(variant);

    auto rc = get_IFC()->CreateBaseStorage(logicalSize, COM_ArrayParameter(pVariant),
                    &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::deleteStorage()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->DeleteStorage(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::createDiffStorage(
        const COMPtr<IMedium> &target, const std::vector<MediumVariant> &variant)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::MediumVariant)> pVariant(variant);

    auto rc = get_IFC()->CreateDiffStorage(target->get_IFC(),
                COM_ArrayParameter(pVariant), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::mergeTo(const COMPtr<IMedium> &target)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->MergeTo(target->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::cloneTo(const COMPtr<IMedium> &target,
        const std::vector<MediumVariant> &variant, const COMPtr<IMedium> &parent)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::MediumVariant)> pVariant(variant);

    auto rc = get_IFC()->CloneTo(target->get_IFC(), COM_ArrayParameter(pVariant),
                parent->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::cloneToBase(
        const COMPtr<IMedium> &target, const std::vector<MediumVariant> &variant)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::MediumVariant)> pVariant(variant);

    auto rc = get_IFC()->CloneToBase(target->get_IFC(),
                COM_ArrayParameter(pVariant), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::setLocation(
        const std::u16string &location)
{
    return moveTo(location);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::moveTo(const std::u16string &location)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pLocation(location);

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    auto rc = get_IFC()->MoveTo(pLocation.m_text, &cResult);
#else
    auto rc = get_IFC()->SetLocation(pLocation.m_text, &cResult);
#endif
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::compact()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Compact(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::resize(int64_t logicalSize)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Resize(logicalSize, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::reset()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Reset(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IMedium::changeEncryption(
        const std::u16string &currentPassword, const std::u16string &cipher,
        const std::u16string &newPassword, const std::u16string &newPasswordId)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pCurrentPassword(currentPassword);
    COM_StringProxy pCipher(cipher);
    COM_StringProxy pNewPassword(newPassword);
    COM_StringProxy pNewPasswordId(newPasswordId);

    auto rc = get_IFC()->ChangeEncryption(pCurrentPassword.m_text, pCipher.m_text,
                pNewPassword.m_text, pNewPasswordId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

std::u16string VBox::IMedium::getEncryptionSettings(std::u16string *cipher) const
{
    COM_StringProxy pResult;
    COM_StringProxy pCipher;

    auto rc = get_IFC()->GetEncryptionSettings(&pCipher.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    if (cipher)
        *cipher = pCipher.toString();
    return pResult.toString();
}

void VBox::IMedium::checkEncryptionPassword(const std::u16string &password) const
{
    COM_StringProxy pPassword(password);

    auto rc = get_IFC()->CheckEncryptionPassword(pPassword.m_text);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IMediumIO> VBox::IMedium::openForIO(bool writable,
        const std::u16string &password)
{
    ::IMediumIO *cResult = nullptr;
    COM_StringProxy pPassword(password);

    auto rc = get_IFC()->OpenForIO(writable, pPassword.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMediumIO>::wrap(cResult);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 6)
VBox::COMPtr<VBox::IProgress> VBox::IMedium::resizeAndCloneTo(
        const COMPtr<IMedium> &target, int64_t logicalSize,
        const std::vector<MediumVariant> &variant, const COMPtr<IMedium> &parent)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::MediumVariant)> pVariant(variant);

    auto rc = get_IFC()->ResizeAndCloneTo(target->get_IFC(), logicalSize,
                COM_ArrayParameter(pVariant), parent->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif
