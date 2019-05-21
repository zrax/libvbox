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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
COM_WRAP_IFC(ICloudProvider)

std::u16string VBox::ICloudProvider::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::ICloudProvider::shortName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ShortName, result);
    return result;
}

std::u16string VBox::ICloudProvider::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::ICloudProfile>>
VBox::ICloudProvider::profiles() const
{
    std::vector<COMPtr<ICloudProfile>> result;
    COM_GetArray_Wrap(get_IFC(), Profiles, result);
    return result;
}

std::vector<std::u16string> VBox::ICloudProvider::profileNames() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), ProfileNames, result);
    return result;
}

std::vector<std::u16string> VBox::ICloudProvider::supportedPropertyNames() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), SupportedPropertyNames, result);
    return result;
}

std::u16string VBox::ICloudProvider::getPropertyDescription(
        const std::u16string &name) const
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetPropertyDescription(pName.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::ICloudProvider::createProfile(const std::u16string &profileName,
        const std::vector<std::u16string> &names,
        const std::vector<std::u16string> &values)
{
    COM_StringProxy pProfileName(profileName);
    COM_StringArrayProxy pNames(names);
    COM_StringArrayProxy pValues(values);

    auto rc = get_IFC()->CreateProfile(pProfileName.m_text,
                COM_ArrayParameter(pNames), COM_ArrayParameter(pValues));
    COM_ERROR_CHECK(rc);
}

void VBox::ICloudProvider::importProfiles()
{
    auto rc = get_IFC()->ImportProfiles();
    COM_ERROR_CHECK(rc);
}

void VBox::ICloudProvider::restoreProfiles()
{
    auto rc = get_IFC()->RestoreProfiles();
    COM_ERROR_CHECK(rc);
}

void VBox::ICloudProvider::saveProfiles()
{
    auto rc = get_IFC()->SaveProfiles();
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::ICloudProfile> VBox::ICloudProvider::getProfileByName(
        const std::u16string &profileName)
{
    ::ICloudProfile *cResult = nullptr;
    COM_StringProxy pProfileName(profileName);

    auto rc = get_IFC()->GetProfileByName(pProfileName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ICloudProfile>::wrap(cResult);
}

void VBox::ICloudProvider::prepareUninstall()
{
    auto rc = get_IFC()->PrepareUninstall();
    COM_ERROR_CHECK(rc);
}
#endif
