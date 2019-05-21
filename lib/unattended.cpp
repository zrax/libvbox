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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
COM_WRAP_IFC(IUnattended)

std::u16string VBox::IUnattended::isoPath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IsoPath, result);
    return result;
}

void VBox::IUnattended::set_isoPath(const std::u16string &value)
{
    COM_SetString(get_IFC(), IsoPath, value);
}

VBox::COMPtr<VBox::IMachine> VBox::IUnattended::machine() const
{
    COMPtr<IMachine> result;
    COM_GetValue_Wrap(get_IFC(), Machine, result);
    return result;
}

void VBox::IUnattended::set_machine(const COMPtr<IMachine> &value)
{
    COM_SetValue_Wrap(get_IFC(), Machine, value);
}

std::u16string VBox::IUnattended::user() const
{
    std::u16string result;
    COM_GetString(get_IFC(), User, result);
    return result;
}

void VBox::IUnattended::set_user(const std::u16string &value)
{
    COM_SetString(get_IFC(), User, value);
}

std::u16string VBox::IUnattended::password() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Password, result);
    return result;
}

void VBox::IUnattended::set_password(const std::u16string &value)
{
    COM_SetString(get_IFC(), Password, value);
}

std::u16string VBox::IUnattended::fullUserName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FullUserName, result);
    return result;
}

void VBox::IUnattended::set_fullUserName(const std::u16string &value)
{
    COM_SetString(get_IFC(), FullUserName, value);
}

std::u16string VBox::IUnattended::productKey() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ProductKey, result);
    return result;
}

void VBox::IUnattended::set_productKey(const std::u16string &value)
{
    COM_SetString(get_IFC(), ProductKey, value);
}

std::u16string VBox::IUnattended::additionsIsoPath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AdditionsIsoPath, result);
    return result;
}

void VBox::IUnattended::set_additionsIsoPath(const std::u16string &value)
{
    COM_SetString(get_IFC(), AdditionsIsoPath, value);
}

bool VBox::IUnattended::installGuestAdditions() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), InstallGuestAdditions, result);
    return static_cast<bool>(result);
}

void VBox::IUnattended::set_installGuestAdditions(bool value)
{
    COM_SetValue(get_IFC(), InstallGuestAdditions, value);
}

std::u16string VBox::IUnattended::validationKitIsoPath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ValidationKitIsoPath, result);
    return result;
}

void VBox::IUnattended::set_validationKitIsoPath(const std::u16string &value)
{
    COM_SetString(get_IFC(), ValidationKitIsoPath, value);
}

bool VBox::IUnattended::installTestExecService() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), InstallTestExecService, result);
    return static_cast<bool>(result);
}

void VBox::IUnattended::set_installTestExecService(bool value)
{
    COM_SetValue(get_IFC(), InstallTestExecService, value);
}

std::u16string VBox::IUnattended::timeZone() const
{
    std::u16string result;
    COM_GetString(get_IFC(), TimeZone, result);
    return result;
}

void VBox::IUnattended::set_timeZone(const std::u16string &value)
{
    COM_SetString(get_IFC(), TimeZone, value);
}

std::u16string VBox::IUnattended::locale() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Locale, result);
    return result;
}

void VBox::IUnattended::set_locale(const std::u16string &value)
{
    COM_SetString(get_IFC(), Locale, value);
}

std::u16string VBox::IUnattended::language() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Language, result);
    return result;
}

void VBox::IUnattended::set_language(const std::u16string &value)
{
    COM_SetString(get_IFC(), Language, value);
}

std::u16string VBox::IUnattended::country() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Country, result);
    return result;
}

void VBox::IUnattended::set_country(const std::u16string &value)
{
    COM_SetString(get_IFC(), Country, value);
}

std::u16string VBox::IUnattended::proxy() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Proxy, result);
    return result;
}

void VBox::IUnattended::set_proxy(const std::u16string &value)
{
    COM_SetString(get_IFC(), Proxy, value);
}

std::u16string VBox::IUnattended::packageSelectionAdjustments() const
{
    std::u16string result;
    COM_GetString(get_IFC(), PackageSelectionAdjustments, result);
    return result;
}

void VBox::IUnattended::set_packageSelectionAdjustments(const std::u16string &value)
{
    COM_SetString(get_IFC(), PackageSelectionAdjustments, value);
}

std::u16string VBox::IUnattended::hostname() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Hostname, result);
    return result;
}

void VBox::IUnattended::set_hostname(const std::u16string &value)
{
    COM_SetString(get_IFC(), Hostname, value);
}

std::u16string VBox::IUnattended::auxiliaryBasePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AuxiliaryBasePath, result);
    return result;
}

void VBox::IUnattended::set_auxiliaryBasePath(const std::u16string &value)
{
    COM_SetString(get_IFC(), AuxiliaryBasePath, value);
}

uint32_t VBox::IUnattended::imageIndex() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ImageIndex, result);
    return static_cast<uint32_t>(result);
}

void VBox::IUnattended::set_imageIndex(uint32_t value)
{
    COM_SetValue(get_IFC(), ImageIndex, value);
}

std::u16string VBox::IUnattended::scriptTemplatePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ScriptTemplatePath, result);
    return result;
}

void VBox::IUnattended::set_scriptTemplatePath(const std::u16string &value)
{
    COM_SetString(get_IFC(), ScriptTemplatePath, value);
}

std::u16string VBox::IUnattended::postInstallScriptTemplatePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), PostInstallScriptTemplatePath, result);
    return result;
}

void VBox::IUnattended::set_postInstallScriptTemplatePath(const std::u16string &value)
{
    COM_SetString(get_IFC(), PostInstallScriptTemplatePath, value);
}

std::u16string VBox::IUnattended::postInstallCommand() const
{
    std::u16string result;
    COM_GetString(get_IFC(), PostInstallCommand, result);
    return result;
}

void VBox::IUnattended::set_postInstallCommand(const std::u16string &value)
{
    COM_SetString(get_IFC(), PostInstallCommand, value);
}

std::u16string VBox::IUnattended::extraInstallKernelParameters() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ExtraInstallKernelParameters, result);
    return result;
}

void VBox::IUnattended::set_extraInstallKernelParameters(const std::u16string &value)
{
    COM_SetString(get_IFC(), ExtraInstallKernelParameters, value);
}

std::u16string VBox::IUnattended::detectedOSTypeId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DetectedOSTypeId, result);
    return result;
}

std::u16string VBox::IUnattended::detectedOSVersion() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DetectedOSVersion, result);
    return result;
}

std::u16string VBox::IUnattended::detectedOSFlavor() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DetectedOSFlavor, result);
    return result;
}

std::u16string VBox::IUnattended::detectedOSLanguages() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DetectedOSLanguages, result);
    return result;
}

std::u16string VBox::IUnattended::detectedOSHints() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DetectedOSHints, result);
    return result;
}

void VBox::IUnattended::detectIsoOS()
{
    auto rc = get_IFC()->DetectIsoOS();
    COM_ERROR_CHECK(rc);
}

void VBox::IUnattended::prepare()
{
    auto rc = get_IFC()->Prepare();
    COM_ERROR_CHECK(rc);
}

void VBox::IUnattended::constructMedia()
{
    auto rc = get_IFC()->ConstructMedia();
    COM_ERROR_CHECK(rc);
}

void VBox::IUnattended::reconfigureVM()
{
    auto rc = get_IFC()->ReconfigureVM();
    COM_ERROR_CHECK(rc);
}

void VBox::IUnattended::done()
{
    auto rc = get_IFC()->Done();
    COM_ERROR_CHECK(rc);
}
#endif
