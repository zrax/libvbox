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
COM_WRAP_IFC(ICloudClient)

std::u16string VBox::ICloudClient::getExportLaunchParameters() const
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->GetExportLaunchParameters(&pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::ICloudClient::exportLaunchVM(
        const COMPtr<IVirtualSystemDescription> &description,
        const COMPtr<IProgress> &progress, const COMPtr<IVirtualBox> &virtualBox)
{
    auto rc = get_IFC()->ExportLaunchVM(description->get_IFC(), progress->get_IFC(),
                virtualBox->get_IFC());
    COM_ERROR_CHECK(rc);
}
#endif
