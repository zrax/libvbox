/* This file is part of libvbox
 * Copyright (C) 2022  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
COM_WRAP_IFC(INvramStore)

std::u16string VBox::INvramStore::nonVolatileStorageFile() const
{
    std::u16string result;
    COM_GetString(get_IFC(), NonVolatileStorageFile, result);
    return result;
}

VBox::COMPtr<VBox::IUefiVariableStore> VBox::INvramStore::uefiVariableStore() const
{
    COMPtr<IUefiVariableStore> result;
    COM_GetValue_Wrap(get_IFC(), UefiVariableStore, result);
    return result;
}

std::u16string VBox::INvramStore::keyId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), KeyId, result);
    return result;
}

std::u16string VBox::INvramStore::keyStore() const
{
    std::u16string result;
    COM_GetString(get_IFC(), KeyStore, result);
    return result;
}

void VBox::INvramStore::initUefiVariableStore(uint32_t size)
{
    auto rc = get_IFC()->InitUefiVariableStore(static_cast<COM_ULong>(size));
    COM_ERROR_CHECK(rc);
}
#endif
