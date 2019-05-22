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

COM_WRAP_IFC(IVFSExplorer)

std::u16string VBox::IVFSExplorer::path() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Path, result);
    return result;
}

VBox::VFSType VBox::IVFSExplorer::type() const
{
    COM_Enum(::VFSType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<VFSType>(result);
}

VBox::COMPtr<VBox::IProgress> VBox::IVFSExplorer::update()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Update(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IVFSExplorer::cd(const std::u16string &dir)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pDir(dir);

    auto rc = get_IFC()->Cd(pDir.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IVFSExplorer::cdUp()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->CdUp(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IVFSExplorer::entryList(std::vector<std::u16string> *names,
        std::vector<uint32_t> *types, std::vector<int64_t> *sizes,
        std::vector<uint32_t> *modes)
{
    COM_StringArrayProxy pNames;
    COM_ArrayProxy<COM_ULong> pTypes;
    COM_ArrayProxy<COM_Long64> pSizes;
    COM_ArrayProxy<COM_ULong> pModes;

    auto rc = get_IFC()->EntryList(COM_ArrayParameterRef(pNames),
                COM_ArrayParameterRef(pTypes), COM_ArrayParameterRef(pSizes),
                COM_ArrayParameterRef(pModes));
    COM_ERROR_CHECK(rc);

    if (names)
        pNames.toVector(*names);
    if (types)
        pTypes.toVector(*types);
    if (sizes)
        pSizes.toVector(*sizes);
    if (modes)
        pModes.toVector(*modes);
}

std::vector<std::u16string> VBox::IVFSExplorer::exists(
        const std::vector<std::u16string> &names)
{
    COM_StringArrayProxy pResult;
    COM_StringArrayProxy pNames(names);

    auto rc = get_IFC()->Exists(COM_ArrayParameter(pNames),
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IVFSExplorer::remove(
        const std::vector<std::u16string> &names)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pNames(names);

    auto rc = get_IFC()->Remove(COM_ArrayParameter(pNames), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
