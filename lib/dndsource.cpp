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

COM_WRAP_IFC(IDnDSource)
COM_WRAP_IFC(IGuestDnDSource)

VBox::DnDAction VBox::IDnDSource::dragIsPending(uint32_t screenId,
        /* out */ std::vector<std::u16string> *formats,
        /* out */ std::vector<DnDAction> *allowedActions)
{
    COM_Enum(::DnDAction) cResult;
    COM_StringArrayProxy pFormats;
    COM_ArrayProxy<COM_Enum(::DnDAction)> pAllowedActions;

    auto rc = get_IFC()->DragIsPending(screenId, COM_ArrayParameterRef(pFormats),
                    COM_ArrayParameterRef(pAllowedActions), &cResult);
    COM_ERROR_CHECK(rc);

    if (formats)
        pFormats.toVector(*formats);
    if (allowedActions)
        pAllowedActions.toVector(*allowedActions);
    return static_cast<DnDAction>(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IDnDSource::drop(const std::u16string &format,
        DnDAction action)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pFormat(format);
    auto cAction = static_cast<COM_Enum(::DnDAction)>(action);

    auto rc = get_IFC()->Drop(pFormat.m_text, cAction, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

std::vector<uint8_t> VBox::IDnDSource::receiveData()
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->ReceiveData(COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}
