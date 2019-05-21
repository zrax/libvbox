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
COM_WRAP_IFC(ICloudProfile)

std::u16string VBox::ICloudProfile::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::ICloudProfile::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

std::u16string VBox::ICloudProfile::providerId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ProviderId, result);
    return result;
}

std::u16string VBox::ICloudProfile::getProperty(const std::u16string &name) const
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetProperty(pName.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::ICloudProfile::setProperty(const std::u16string &name,
        const std::u16string &value) const
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetProperty(pName.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

std::vector<std::u16string> VBox::ICloudProfile::getProperties(
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

void VBox::ICloudProfile::setProperties(const std::vector<std::u16string> &names,
        const std::vector<std::u16string> &values)
{
    COM_StringArrayProxy pNames(names);
    COM_StringArrayProxy pValues(values);

    auto rc = get_IFC()->SetProperties(COM_ArrayParameter(pNames),
                COM_ArrayParameter(pValues));
    COM_ERROR_CHECK(rc);
}

void VBox::ICloudProfile::remove()
{
    auto rc = get_IFC()->Remove();
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::ICloudClient> VBox::ICloudProfile::createCloudClient()
{
    ::ICloudClient *cResult = nullptr;

    auto rc = get_IFC()->CreateCloudClient(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ICloudClient>::wrap(cResult);
}
#endif
