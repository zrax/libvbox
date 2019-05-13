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

const void *VBox::IProcess::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IProcess);
}

const void *VBox::IGuestProcess::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IGuestProcess);
}

std::vector<VBox::COMString> VBox::IProcess::arguments() const
{
    std::vector<COMString> result;
    COM_GetStringArray(get_IFC(), Arguments, result);
    return result;
}

std::vector<VBox::COMString> VBox::IProcess::environment() const
{
    std::vector<COMString> result;
    COM_GetStringArray(get_IFC(), Environment, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IProcess::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

VBox::COMString VBox::IProcess::executablePath() const
{
    COMString result;
    COM_GetString(get_IFC(), ExecutablePath, result);
    return result;
}

int32_t VBox::IProcess::exitCode() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), ExitCode, result);
    return static_cast<int32_t>(result);
}

VBox::COMString VBox::IProcess::name() const
{
    COMString result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

uint32_t VBox::IProcess::PID() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), PID, result);
    return result;
}

VBox::ProcessStatus VBox::IProcess::status() const
{
    COM_Enum(::ProcessStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<ProcessStatus>(result);
}

VBox::ProcessWaitResult VBox::IProcess::waitFor(uint32_t waitFor, uint32_t timeoutMS)
{
    COM_Enum(::ProcessWaitResult) cResult;

    auto rc = get_IFC()->WaitFor(waitFor, timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<ProcessWaitResult>(cResult);
}

VBox::ProcessWaitResult VBox::IProcess::waitForArray(
        const std::vector<ProcessWaitForFlag> &waitFor, uint32_t timeoutMS)
{
    COM_Enum(::ProcessWaitResult) cResult;
    COM_ArrayProxy<COM_Enum(::ProcessWaitForFlag)> pWaitFor(waitFor);

    auto rc = get_IFC()->WaitForArray(COM_ArrayParameter(pWaitFor), timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<ProcessWaitResult>(cResult);
}

std::vector<uint8_t> VBox::IProcess::read(uint32_t handle, uint32_t toRead,
        uint32_t timeoutMS)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->Read(handle, toRead, timeoutMS, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

uint32_t VBox::IProcess::write(uint32_t handle, uint32_t flags,
        const std::vector<uint8_t> &data, uint32_t timeoutMS)
{
    COM_ULong cResult;
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->Write(handle, flags, COM_ArrayParameter(pData),
                timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

uint32_t VBox::IProcess::writeArray(uint32_t handle,
        const std::vector<ProcessInputFlag> &flags,
        const std::vector<uint8_t> &data, uint32_t timeoutMS)
{
    COM_ULong cResult;
    COM_ArrayProxy<COM_Enum(::ProcessInputFlag)> pFlags(flags);
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->WriteArray(handle, COM_ArrayParameter(pFlags),
                COM_ArrayParameter(pData), timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

void VBox::IProcess::terminate()
{
    auto rc = get_IFC()->Terminate();
    COM_ERROR_CHECK(rc);
}
