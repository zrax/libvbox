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

COM_WRAP_IFC(IVRDEServerInfo)

bool VBox::IVRDEServerInfo::active() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Active, result);
    return static_cast<bool>(result);
}

int32_t VBox::IVRDEServerInfo::port() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), Port, result);
    return static_cast<int32_t>(result);
}

uint32_t VBox::IVRDEServerInfo::numberOfClients() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), NumberOfClients, result);
    return static_cast<uint32_t>(result);
}

int64_t VBox::IVRDEServerInfo::beginTime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), BeginTime, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IVRDEServerInfo::endTime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), EndTime, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IVRDEServerInfo::bytesSent() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), BytesSent, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IVRDEServerInfo::bytesSentTotal() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), BytesSentTotal, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IVRDEServerInfo::bytesReceived() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), BytesReceived, result);
    return static_cast<int64_t>(result);
}

int64_t VBox::IVRDEServerInfo::bytesReceivedTotal() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), BytesReceivedTotal, result);
    return static_cast<int64_t>(result);
}

std::u16string VBox::IVRDEServerInfo::user() const
{
    std::u16string result;
    COM_GetString(get_IFC(), User, result);
    return result;
}

std::u16string VBox::IVRDEServerInfo::domain() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Domain, result);
    return result;
}

std::u16string VBox::IVRDEServerInfo::clientName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ClientName, result);
    return result;
}

std::u16string VBox::IVRDEServerInfo::clientIP() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ClientIP, result);
    return result;
}

uint32_t VBox::IVRDEServerInfo::clientVersion() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ClientVersion, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IVRDEServerInfo::encryptionStyle() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), EncryptionStyle, result);
    return static_cast<uint32_t>(result);
}
