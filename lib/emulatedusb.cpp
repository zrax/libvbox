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

COM_WRAP_IFC(IEmulatedUSB)

std::vector<std::u16string> VBox::IEmulatedUSB::webcams() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Webcams, result);
    return result;
}

void VBox::IEmulatedUSB::webcamAttach(const std::u16string &path,
        const std::u16string &settings)
{
    COM_StringProxy pPath(path);
    COM_StringProxy pSettings(settings);

    auto rc = get_IFC()->WebcamAttach(pPath.m_text, pSettings.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IEmulatedUSB::webcamDetach(const std::u16string &path)
{
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->WebcamDetach(pPath.m_text);
    COM_ERROR_CHECK(rc);
}
