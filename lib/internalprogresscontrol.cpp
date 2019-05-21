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
COM_WRAP_IFC(IInternalProgressControl)

void VBox::IInternalProgressControl::setCurrentOperationProgress(uint32_t percent)
{
    auto rc = get_IFC()->SetCurrentOperationProgress(percent);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalProgressControl::waitForOtherProgressCompletion(
        const COMPtr<IProgress> &progressOther, uint32_t timeoutMS)
{
    auto rc = get_IFC()->WaitForOtherProgressCompletion(progressOther->get_IFC(),
                timeoutMS);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalProgressControl::setNextOperation(
        const std::u16string &nextOperationDescription,
        uint32_t nextOperationsWeight)
{
    COM_StringProxy pNextOperationDescription(nextOperationDescription);

    auto rc = get_IFC()->SetNextOperation(pNextOperationDescription.m_text,
                nextOperationsWeight);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalProgressControl::notifyPointOfNoReturn()
{
    auto rc = get_IFC()->NotifyPointOfNoReturn();
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalProgressControl::notifyComplete(int32_t resultCode,
        const COMPtr<IVirtualBoxErrorInfo> &errorInfo)
{
    auto rc = get_IFC()->NotifyComplete(resultCode, errorInfo->get_IFC());
    COM_ERROR_CHECK(rc);
}
#endif
