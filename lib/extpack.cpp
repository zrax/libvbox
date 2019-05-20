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

COM_WRAP_IFC(IExtPackBase)
COM_WRAP_IFC(IExtPack)
COM_WRAP_IFC(IExtPackFile)

std::u16string VBox::IExtPackBase::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::IExtPackBase::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

std::u16string VBox::IExtPackBase::version() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Version, result);
    return result;
}

uint32_t VBox::IExtPackBase::revision() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Revision, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IExtPackBase::edition() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Edition, result);
    return result;
}

std::u16string VBox::IExtPackBase::VRDEModule() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VRDEModule, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IExtPackPlugIn>> VBox::IExtPackBase::plugIns() const
{
    std::vector<COMPtr<IExtPackPlugIn>> result;
    COM_GetArray_Wrap(get_IFC(), PlugIns, result);
    return result;
}

bool VBox::IExtPackBase::usable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Usable, result);
    return static_cast<bool>(result);
}

std::u16string VBox::IExtPackBase::whyUnusable() const
{
    std::u16string result;
    COM_GetString(get_IFC(), WhyUnusable, result);
    return result;
}

bool VBox::IExtPackBase::showLicense() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ShowLicense, result);
    return static_cast<bool>(result);
}

std::u16string VBox::IExtPackBase::license() const
{
    std::u16string result;
    COM_GetString(get_IFC(), License, result);
    return result;
}

std::u16string VBox::IExtPackBase::queryLicense(
        const std::u16string &preferredLocale,
        const std::u16string &preferredLanguage, const std::u16string &format)
{
    COM_StringProxy pResult;
    COM_StringProxy pPreferredLocale(preferredLocale);
    COM_StringProxy pPreferredLanguage(preferredLanguage);
    COM_StringProxy pFormat(format);

    auto rc = get_IFC()->QueryLicense(pPreferredLocale.m_text,
                pPreferredLanguage.m_text, pFormat.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

VBox::COMPtr<VBox::COMUnknown> VBox::IExtPack::queryObject(
        const std::u16string &objUuid)
{
    COMUnknown::COM_Ifc *cResult = nullptr;
    COM_StringProxy pObjUuid(objUuid);

    auto rc = get_IFC()->QueryObject(pObjUuid.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<COMUnknown>::wrap(cResult);
}

std::u16string VBox::IExtPackFile::filePath() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FilePath, result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IExtPackFile::install(bool replace,
        const std::u16string &displayInfo)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pDisplayInfo(displayInfo);

    auto rc = get_IFC()->Install(replace, pDisplayInfo.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
