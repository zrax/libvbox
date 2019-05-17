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

COM_WRAP_IFC(IDnDTarget)
COM_WRAP_IFC(IGuestDnDTarget)

VBox::DnDAction VBox::IDnDTarget::enter(uint32_t screenId, uint32_t y, uint32_t x,
        DnDAction defaultAction, const std::vector<DnDAction> &allowedActions,
        const std::vector<std::u16string> &formats)
{
    COM_Enum(::DnDAction) cResult;
    auto cDefaultAction = static_cast<COM_Enum(::DnDAction)>(defaultAction);
    COM_ArrayProxy<COM_Enum(::DnDAction)> pAllowedActions(allowedActions);
    COM_StringArrayProxy pFormats(formats);

    auto rc = get_IFC()->Enter(screenId, y, x, cDefaultAction,
                    COM_ArrayParameter(pAllowedActions),
                    COM_ArrayParameter(pFormats), &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<DnDAction>(cResult);
}

VBox::DnDAction VBox::IDnDTarget::move(uint32_t screenId, uint32_t x, uint32_t y,
        DnDAction defaultAction, const std::vector<DnDAction> &allowedActions,
        const std::vector<std::u16string> &formats)
{
    COM_Enum(::DnDAction) cResult;
    auto cDefaultAction = static_cast<COM_Enum(::DnDAction)>(defaultAction);
    COM_ArrayProxy<COM_Enum(::DnDAction)> pAllowedActions(allowedActions);
    COM_StringArrayProxy pFormats(formats);

    auto rc = get_IFC()->Move(screenId, x, y, cDefaultAction,
                    COM_ArrayParameter(pAllowedActions),
                    COM_ArrayParameter(pFormats), &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<DnDAction>(cResult);
}

void VBox::IDnDTarget::leave(uint32_t screenId)
{
    auto rc = get_IFC()->Leave(screenId);
    COM_ERROR_CHECK(rc);
}

VBox::DnDAction VBox::IDnDTarget::drop(uint32_t screenId, uint32_t x, uint32_t y,
        DnDAction defaultAction, const std::vector<DnDAction> &allowedActions,
        const std::vector<std::u16string> &formats, std::u16string *format)
{
    COM_Enum(::DnDAction) cResult;
    auto cDefaultAction = static_cast<COM_Enum(::DnDAction)>(defaultAction);
    COM_ArrayProxy<COM_Enum(::DnDAction)> pAllowedActions(allowedActions);
    COM_StringArrayProxy pFormats(formats);
    COM_StringProxy pFormat;

    auto rc = get_IFC()->Drop(screenId, x, y, cDefaultAction,
                    COM_ArrayParameter(pAllowedActions),
                    COM_ArrayParameter(pFormats), &pFormat.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    if (format)
        *format = pFormat.toString();
    return static_cast<DnDAction>(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IDnDTarget::sendData(uint32_t screenId,
        const std::u16string& format, const std::vector<uint8_t> &data)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pFormat(format);
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->SendData(screenId, pFormat.m_text, COM_ArrayParameter(pData),
                    &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

bool VBox::IDnDTarget::cancel()
{
    COM_Bool cResult;

    auto rc = get_IFC()->Cancel(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}
