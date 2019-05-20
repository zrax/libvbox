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

COM_WRAP_IFC(IExtPackManager)

std::vector<VBox::COMPtr<VBox::IExtPack>>
VBox::IExtPackManager::installedExtPacks() const
{
    std::vector<COMPtr<IExtPack>> result;
    COM_GetArray_Wrap(get_IFC(), InstalledExtPacks, result);
    return result;
}

VBox::COMPtr<VBox::IExtPack> VBox::IExtPackManager::find(const std::u16string &name)
{
    ::IExtPack *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->Find(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IExtPack>::wrap(cResult);
}

VBox::COMPtr<VBox::IExtPackFile> VBox::IExtPackManager::openExtPackFile(
        const std::u16string &path)
{
    ::IExtPackFile *cResult = nullptr;
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->OpenExtPackFile(pPath.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IExtPackFile>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IExtPackManager::uninstall(
        const std::u16string &name, bool forcedRemoval,
        const std::u16string &displayInfo)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pName(name);
    COM_StringProxy pDisplayInfo(displayInfo);

    auto rc = get_IFC()->Uninstall(pName.m_text, forcedRemoval,
                pDisplayInfo.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IExtPackManager::cleanup()
{
    auto rc = get_IFC()->Cleanup();
    COM_ERROR_CHECK(rc);
}

std::vector<std::u16string> VBox::IExtPackManager::queryAllPlugInsForFrontend(
        const std::u16string &frontendName)
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pFrontendName(frontendName);

    auto rc = get_IFC()->QueryAllPlugInsForFrontend(pFrontendName.m_text,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

bool VBox::IExtPackManager::isExtPackUsable(const std::u16string &name)
{
    COM_Bool cResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->IsExtPackUsable(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}
