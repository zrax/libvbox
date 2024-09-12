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

COM_WRAP_IFC(IDirectory)
COM_WRAP_IFC(IGuestDirectory)

std::u16string VBox::IDirectory::directoryName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DirectoryName, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox::COMPtr<VBox::IEventSource> VBox::IDirectory::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}
#endif

std::u16string VBox::IDirectory::filter() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Filter, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
uint32_t VBox::IDirectory::id() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Id, result);
    return static_cast<uint32_t>(result);
}

VBox::DirectoryStatus VBox::IDirectory::status() const
{
    COM_Enum(::DirectoryStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<DirectoryStatus>(result);
}
#endif

void VBox::IDirectory::close()
{
    auto rc = get_IFC()->Close();
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
std::vector<VBox::COMPtr<VBox::IFsObjInfo>> VBox::IDirectory::list(uint32_t maxEntries)
{
    COM_ArrayProxy<::IFsObjInfo *> pResult;
    auto cMaxEntries = static_cast<COM_ULong>(maxEntries);

    auto rc = get_IFC()->List(cMaxEntries, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IFsObjInfo>> result;
    pResult.toVector(result);
    return result;
}
#endif

VBox::COMPtr<VBox::IFsObjInfo> VBox::IDirectory::read()
{
    ::IFsObjInfo *cResult = nullptr;

    auto rc = get_IFC()->Read(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IFsObjInfo>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
void VBox::IDirectory::rewind()
{
    auto rc = get_IFC()->Rewind();
    COM_ERROR_CHECK(rc);
}
#endif
