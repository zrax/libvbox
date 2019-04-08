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

const void *VBox::IVetoEvent::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IVetoEvent);
}

void VBox::IVetoEvent::addVeto(const std::wstring &reason)
{
    auto reasonText = COM_FromWString(reason);
    auto rc = get_IFC()->AddVeto(reasonText);
    if (COM_FAILED(rc))
        throw COMError(rc);
    COM_FreeString(reasonText);
}

bool VBox::IVetoEvent::isVetoed()
{
    COM_Bool result;
    auto rc = get_IFC()->IsVetoed(&result);
    if (COM_FAILED(rc))
        throw COMError(rc);
    return result;
}

std::vector<std::wstring> VBox::IVetoEvent::getVetos()
{
    COM_DeclareArray(PRUnichar *, vetoTexts);
    auto rc = get_IFC()->GetVetos(COM_ArrayParameterIn(vetoTexts));
    if (COM_FAILED(rc))
        throw COMError(rc);

    COM_StringArrayProxy proxy(COM_ArrayParameterOut(vetoTexts));
    std::vector<std::wstring> result;
    proxy.toVector(result);
    return result;
}

void VBox::IVetoEvent::addApproval(const std::wstring &reason)
{
    auto reasonText = COM_FromWString(reason);
    auto rc = get_IFC()->AddApproval(reasonText);
    if (COM_FAILED(rc))
        throw COMError(rc);
    COM_FreeString(reasonText);
}

bool VBox::IVetoEvent::isApproved()
{
    COM_Bool result;
    auto rc = get_IFC()->IsApproved(&result);
    if (COM_FAILED(rc))
        throw COMError(rc);
    return result;
}

std::vector<std::wstring> VBox::IVetoEvent::getApprovals()
{
    COM_DeclareArray(PRUnichar *, approvalTexts);
    auto rc = get_IFC()->GetApprovals(COM_ArrayParameterIn(approvalTexts));
    if (COM_FAILED(rc))
        throw COMError(rc);

    COM_StringArrayProxy proxy(COM_ArrayParameterOut(approvalTexts));
    std::vector<std::wstring> result;
    proxy.toVector(result);
    return result;
}
