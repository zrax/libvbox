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

void VBox::IVetoEvent::addVeto(const std::wstring &reason)
{
    auto reasonText = COM_FromWString(reason);
    auto rc = get_IFC()->AddVeto(reasonText);
    if (NS_FAILED(rc))
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
    std::vector<std::wstring> result;
#if defined(VBOX_XPCOM)
    PRUint32 vetoCount;
    PRUnichar **vetoTexts;
    auto rc = get_IFC()->GetVetos(&vetoCount, &vetoTexts);
    if (COM_FAILED(rc))
        throw COMError(rc);
    result.resize(vetoCount);
    for (PRUint32 i = 0; i < vetoCount; ++i) {
        result[i] = nsToWString<wchar_t>(vetoTexts[i]);
        COM_FreeString(vetoTexts[i]);
    }
    nsMemory::Free(reinterpret_cast<void *>(vetoTexts));
#elif defined(VBOX_MSCOM)
    SAFEARRAY *vetoTextsSA = nullptr;
    HRESULT rc = get_IFC()->GetVetos(&vetoTextsSA);
    if (COM_FAILED(rc))
        throw COMError(rc);
    BSTR *vetoTexts;
    rc = SafeArrayAccessData(vetoTextsSA, reinterpret_cast<void **>(&vetoTexts));
    if (COM_FAILED(rc)) {
        SafeArrayDestroy(vetoTextsSA);
        throw COMError(rc);
    }
    result.resize(vetoTextsSA->rgsabound[0].cElements);
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = std::wstring(vetoTexts[i], SysStringLen(vetoTexts[i]));
        COM_FreeString(vetoTexts[i]);
    }
    SafeArrayUnaccessData(vetoTextsSA);
    SafeArrayDestroy(vetoTextsSA);
#endif
    return result;
}

void VBox::IVetoEvent::addApproval(const std::wstring &reason)
{
    auto reasonText = COM_FromWString(reason);
    auto rc = get_IFC()->AddApproval(reasonText);
    if (NS_FAILED(rc))
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
    std::vector<std::wstring> result;
#if defined(VBOX_XPCOM)
    PRUint32 approvalCount;
    PRUnichar **approvalTexts;
    auto rc = get_IFC()->GetApprovals(&approvalCount, &approvalTexts);
    if (COM_FAILED(rc))
        throw COMError(rc);
    result.resize(approvalCount);
    for (PRUint32 i = 0; i < approvalCount; ++i) {
        result[i] = nsToWString<wchar_t>(approvalTexts[i]);
        COM_FreeString(approvalTexts[i]);
    }
    nsMemory::Free(reinterpret_cast<void *>(approvalTexts));
#elif defined(VBOX_MSCOM)
    SAFEARRAY *approvalTextsSA = nullptr;
    HRESULT rc = get_IFC()->GetApprovals(&approvalTextsSA);
    if (COM_FAILED(rc))
        throw COMError(rc);
    BSTR *approvalTexts;
    rc = SafeArrayAccessData(approvalTextsSA, reinterpret_cast<void **>(&approvalTexts));
    if (COM_FAILED(rc)) {
        SafeArrayDestroy(approvalTextsSA);
        throw COMError(rc);
    }
    result.resize(approvalTextsSA->rgsabound[0].cElements);
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = std::wstring(approvalTexts[i], SysStringLen(approvalTexts[i]));
        COM_FreeString(approvalTexts[i]);
    }
    SafeArrayUnaccessData(approvalTextsSA);
    SafeArrayDestroy(approvalTextsSA);
#endif
    return result;
}
