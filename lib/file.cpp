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

COM_WRAP_IFC(IFile)
COM_WRAP_IFC(IGuestFile)

VBox::COMPtr<VBox::IEventSource> VBox::IFile::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

uint32_t VBox::IFile::id() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Id, result);
    return static_cast<uint32_t>(result);
}

int64_t VBox::IFile::initialSize() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), InitialSize, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IFile::offset() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Offset, result);
    return static_cast<int64_t>(result);
}

VBox::FileStatus VBox::IFile::status() const
{
    COM_Enum(::FileStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<FileStatus>(result);
}

std::u16string VBox::IFile::filename() const
{
    std::u16string result;
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_GetString(get_IFC(), Filename, result);
#else
    COM_GetString(get_IFC(), FileName, result);
#endif
    return result;
}

std::u16string VBox::IFile::fileName() const
{
    return filename();
}

uint32_t VBox::IFile::creationMode() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), CreationMode, result);
    return static_cast<uint32_t>(result);
}

VBox::FileOpenAction VBox::IFile::openAction() const
{
    COM_Enum(::FileOpenAction) result;
    COM_GetValue(get_IFC(), OpenAction, result);
    return static_cast<FileOpenAction>(result);
}

VBox::FileAccessMode VBox::IFile::accessMode() const
{
    COM_Enum(::FileAccessMode) result;
    COM_GetValue(get_IFC(), AccessMode, result);
    return static_cast<FileAccessMode>(result);
}

void VBox::IFile::close()
{
    auto rc = get_IFC()->Close();
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IFsObjInfo> VBox::IFile::queryInfo()
{
    ::IFsObjInfo *cResult = nullptr;

    auto rc = get_IFC()->QueryInfo(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IFsObjInfo>::wrap(cResult);
}

int64_t VBox::IFile::querySize()
{
    COM_Long64 cResult;

    auto rc = get_IFC()->QuerySize(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int64_t>(cResult);
}

std::vector<uint8_t> VBox::IFile::read(uint32_t toRead, uint32_t timeoutMS)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->Read(toRead, timeoutMS, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

std::vector<uint8_t> VBox::IFile::readAt(int64_t offset, uint32_t toRead,
        uint32_t timeoutMS)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->ReadAt(offset, toRead, timeoutMS,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

int64_t VBox::IFile::seek(int64_t offset, FileSeekOrigin whence)
{
    COM_Long64 cResult;
    auto cWhence = static_cast<COM_Enum(::FileSeekOrigin)>(whence);

    auto rc = get_IFC()->Seek(offset, cWhence, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int64_t>(cResult);
}

void VBox::IFile::setACL(const std::u16string &acl, uint32_t mode)
{
    COM_StringProxy pAcl(acl);

    auto rc = get_IFC()->SetACL(pAcl.m_text, mode);
    COM_ERROR_CHECK(rc);
}

void VBox::IFile::setSize(int64_t size)
{
    auto rc = get_IFC()->SetSize(size);
    COM_ERROR_CHECK(rc);
}

uint32_t VBox::IFile::write(const std::vector<uint8_t> &data, uint32_t timeoutMS)
{
    COM_ULong cResult;
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->Write(COM_ArrayParameter(pData), timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IFile::writeAt(int64_t offset, const std::vector<uint8_t> &data,
        uint32_t timeoutMS)
{
    COM_ULong cResult;
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->WriteAt(offset, COM_ArrayParameter(pData), timeoutMS,
                &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}
