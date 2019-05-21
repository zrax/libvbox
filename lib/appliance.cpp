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

COM_WRAP_IFC(IAppliance)

std::u16string VBox::IAppliance::path() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Path, result);
    return result;
}

std::vector<std::u16string> VBox::IAppliance::disks() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Disks, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IVirtualSystemDescription>>
VBox::IAppliance::virtualSystemDescriptions() const
{
    std::vector<COMPtr<IVirtualSystemDescription>> result;
    COM_GetArray_Wrap(get_IFC(), VirtualSystemDescriptions, result);
    return result;
}

std::vector<std::u16string> VBox::IAppliance::machines() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Machines, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
VBox::COMPtr<VBox::ICertificate> VBox::IAppliance::certificate() const
{
    COMPtr<ICertificate> result;
    COM_GetValue_Wrap(get_IFC(), Certificate, result);
    return result;
}
#endif

// Methods
VBox::COMPtr<VBox::IProgress> VBox::IAppliance::read(const std::u16string &file)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pFile(file);

    auto rc = get_IFC()->Read(pFile.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IAppliance::interpret()
{
    auto rc = get_IFC()->Interpret();
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IAppliance::importMachines(
        const std::vector<ImportOptions> &options)
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::ImportOptions)> pOptions(options);

    auto rc = get_IFC()->ImportMachines(COM_ArrayParameter(pOptions), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IVFSExplorer> VBox::IAppliance::createVFSExplorer(
        const std::u16string &URI)
{
    ::IVFSExplorer *cResult = nullptr;
    COM_StringProxy pURI(URI);

    auto rc = get_IFC()->CreateVFSExplorer(pURI.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IVFSExplorer>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IAppliance::write(
        const std::u16string &format, const std::vector<ExportOptions> &options,
        const std::u16string &path)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pFormat(format);
    COM_ArrayProxy<COM_Enum(::ExportOptions)> pOptions(options);
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->Write(pFormat.m_text, COM_ArrayParameter(pOptions),
                pPath.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

std::vector<std::u16string> VBox::IAppliance::getWarnings()
{
    COM_StringArrayProxy pResult;

    auto rc = get_IFC()->GetWarnings(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

std::vector<std::u16string> VBox::IAppliance::getPasswordIds()
{
    COM_StringArrayProxy pResult;

    auto rc = get_IFC()->GetPasswordIds(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

std::vector<std::u16string> VBox::IAppliance::getMediumIdsForPasswordId(
        const std::u16string &passwordId)
{
    COM_StringArrayProxy pResult;
    COM_StringProxy pPasswordId(passwordId);

    auto rc = get_IFC()->GetMediumIdsForPasswordId(pPasswordId.m_text,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

void VBox::IAppliance::addPasswords(const std::vector<std::u16string> &identifiers,
        const std::vector<std::u16string> &passwords)
{
    COM_StringArrayProxy pIdentifiers(identifiers);
    COM_StringArrayProxy pPasswords(passwords);

    auto rc = get_IFC()->AddPasswords(COM_ArrayParameter(pIdentifiers),
                COM_ArrayParameter(pPasswords));
    COM_ERROR_CHECK(rc);
}
