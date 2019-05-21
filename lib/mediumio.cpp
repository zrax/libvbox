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
COM_WRAP_IFC(IMediumIO)

VBox::COMPtr<VBox::IMedium> VBox::IMediumIO::medium() const
{
    COMPtr<IMedium> result;
    COM_GetValue_Wrap(get_IFC(), Medium, result);
    return result;
}

bool VBox::IMediumIO::writable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Writable, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IVFSExplorer> VBox::IMediumIO::explorer() const
{
    COMPtr<IVFSExplorer> result;
    COM_GetValue_Wrap(get_IFC(), Explorer, result);
    return result;
}

std::vector<uint8_t> VBox::IMediumIO::read(int64_t offset, uint32_t size)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->Read(offset, size, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

uint32_t VBox::IMediumIO::write(int64_t offset, const std::vector<uint8_t> &data)
{
    COM_ULong cResult;
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->Write(offset, COM_ArrayParameter(pData), &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

void VBox::IMediumIO::formatFAT(bool quick)
{
    auto rc = get_IFC()->FormatFAT(quick);
    COM_ERROR_CHECK(rc);
}

void VBox::IMediumIO::initializePartitionTable(PartitionTableType format,
        bool wholeDiskInOneEntry)
{
    auto cFormat = static_cast<COM_Enum(::PartitionTableType)>(format);

    auto rc = get_IFC()->InitializePartitionTable(cFormat, wholeDiskInOneEntry);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IMediumIO::convertToStream(
        const std::u16string &format, const std::vector<MediumVariant> &variant,
        uint32_t bufferSize, COMPtr<IDataStream> *stream)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pFormat(format);
    COM_ArrayProxy<COM_Enum(::MediumVariant)> pVariant(variant);
    ::IDataStream *cStream = nullptr;

    auto rc = get_IFC()->ConvertToStream(pFormat.m_text,
                COM_ArrayParameter(pVariant), bufferSize, &cStream, &cResult);
    COM_ERROR_CHECK(rc);

    if (stream)
        *stream = COMPtr<IDataStream>::wrap(cStream);
    else if (cStream)
        cStream->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IMediumIO::close()
{
    auto rc = get_IFC()->Close();
    COM_ERROR_CHECK(rc);
}
#endif
