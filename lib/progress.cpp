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

const void *VBox::IProgress::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IProgress);
}

std::u16string VBox::IProgress::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::IProgress::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

VBox::COMPtr<VBox::COMUnknown> VBox::IProgress::initiator() const
{
    COMPtr<COMUnknown> result;
    COM_GetValue_Wrap(get_IFC(), Initiator, result);
    return result;
}

bool VBox::IProgress::cancelable() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Cancelable, result);
    return static_cast<bool>(result);
}

uint32_t VBox::IProgress::percent() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Percent, result);
    return static_cast<uint32_t>(result);
}

int32_t VBox::IProgress::timeRemaining() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), TimeRemaining, result);
    return static_cast<int32_t>(result);
}

bool VBox::IProgress::completed() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Completed, result);
    return static_cast<bool>(result);
}

bool VBox::IProgress::canceled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Canceled, result);
    return static_cast<bool>(result);
}

int32_t VBox::IProgress::resultCode() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), ResultCode, result);
    return static_cast<int32_t>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo> VBox::IProgress::errorInfo() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), ErrorInfo, result);
    return result;
}

uint32_t VBox::IProgress::operationCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), OperationCount, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IProgress::operation() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Operation, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IProgress::operationDescription() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OperationDescription, result);
    return result;
}

uint32_t VBox::IProgress::operationPercent() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), OperationPercent, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IProgress::operationWeight() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), OperationWeight, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IProgress::timeout() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Timeout, result);
    return static_cast<uint32_t>(result);
}

void VBox::IProgress::set_timeout(uint32_t value)
{
    COM_SetValue(get_IFC(), Timeout, value);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox::COMPtr<VBox::IEventSource> VBox::IProgress::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
void VBox::IProgress::setCurrentOperationProgress(uint32_t percent)
{
    auto rc = get_IFC()->SetCurrentOperationProgress(percent);
    COM_ERROR_CHECK(rc);
}

void VBox::IProgress::setNextOperation(const std::u16string &nextOperationDescription,
        uint32_t nextOperationsWeight)
{
    COM_StringProxy pNextOperationDescription(nextOperationDescription);

    auto rc = get_IFC()->SetNextOperation(pNextOperationDescription.m_text,
                                          nextOperationsWeight);
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IProgress::waitForCompletion(int32_t timeout)
{
    auto rc = get_IFC()->WaitForCompletion(timeout);
    COM_ERROR_CHECK(rc);
}

void VBox::IProgress::waitForOperationCompletion(uint32_t operation,
        int32_t timeout)
{
    auto rc = get_IFC()->WaitForOperationCompletion(operation, timeout);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
void VBox::IProgress::waitForAsyncProgressCompletion(
        const COMPtr<IProgress> &pProgressAsync)
{
    auto rc = get_IFC()->WaitForAsyncProgressCompletion(pProgressAsync->get_IFC());
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IProgress::cancel()
{
    auto rc = get_IFC()->Cancel();
    COM_ERROR_CHECK(rc);
}
