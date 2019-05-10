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

#ifndef _LIBVBOX_ERRORS_H
#define _LIBVBOX_ERRORS_H

#include <stdexcept>

#include "libvbox_vboxsdk_version.h"

#define VBox_WRAP_ERROR(classname, errcode)                             \
    class classname : public COMError                                   \
    {                                                                   \
    public:                                                             \
        classname() : COMError(errcode, #errcode) { }                   \
    };

namespace VBox
{
    enum
    {
        // Some standard error codes that VirtualBox may report.
        E_NOTIMPL = 0x80004001,
        E_POINTER = 0x80004003,
        E_ABORT = 0x80004004,
        E_FAIL = 0x80004005,
        E_ACCESSDENIED = 0x80070005,
        E_OUTOFMEMORY = 0x8007000E,
        E_INVALIDARG = 0x80070057,
        E_UNEXPECTED = 0x8000FFFF,

        // VirtualBox-specific error codes.
        E_OBJECT_NOT_FOUND = 0x80BB0001,
        E_INVALID_VM_STATE = 0x80BB0002,
        E_VM_ERROR = 0x80BB0003,
        E_FILE_ERROR = 0x80BB0004,
        E_IPRT_ERROR = 0x80BB0005,
        E_PDM_ERROR = 0x80BB0006,
        E_INVALID_OBJECT_STATE = 0x80BB0007,
        E_HOST_ERROR = 0x80BB0008,
        E_NOT_SUPPORTED = 0x80BB0009,
        E_XML_ERROR = 0x80BB000A,
        E_INVALID_SESSION_STATE = 0x80BB000B,
        E_OBJECT_IN_USE = 0x80BB000C,
        E_PASSWORD_INCORRECT = 0x80BB000D,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        E_MAXIMUM_REACHED = 0x80BB000E,
        E_GSTCTL_GUEST_ERROR = 0x80BB000F,
        E_TIMEOUT = 0x80BB0010,
#endif
    };

    class COMError : public std::runtime_error
    {
    public:
        COMError(uint32_t rc, const char *name = nullptr)
            : std::runtime_error(error_message(rc, name)), m_rc(rc) { }

        uint32_t error_code() const { return m_rc; }

        static LIBVBOX_API
        std::string error_message(uint32_t rc, const char *name = nullptr);

        static LIBVBOX_API void raise(uint32_t rc);

    private:
        uint32_t m_rc;
    };

    VBox_WRAP_ERROR(ENotImpl, E_NOTIMPL)
    VBox_WRAP_ERROR(EPointer, E_POINTER)
    VBox_WRAP_ERROR(EAbort, E_ABORT)
    VBox_WRAP_ERROR(EFail, E_FAIL)
    VBox_WRAP_ERROR(EAccessDenied, E_ACCESSDENIED)
    VBox_WRAP_ERROR(EOutOfMemory, E_OUTOFMEMORY)
    VBox_WRAP_ERROR(EInvalidArg, E_INVALIDARG)
    VBox_WRAP_ERROR(EUnexpected, E_UNEXPECTED)

    VBox_WRAP_ERROR(EObjectNotFound, E_OBJECT_NOT_FOUND)
    VBox_WRAP_ERROR(EInvalidVMState, E_INVALID_VM_STATE)
    VBox_WRAP_ERROR(EVMError, E_VM_ERROR)
    VBox_WRAP_ERROR(EFileError, E_FILE_ERROR)
    VBox_WRAP_ERROR(EIPRTError, E_IPRT_ERROR)
    VBox_WRAP_ERROR(EPDMError, E_PDM_ERROR)
    VBox_WRAP_ERROR(EInvalidObjectState, E_INVALID_OBJECT_STATE)
    VBox_WRAP_ERROR(EHostError, E_HOST_ERROR)
    VBox_WRAP_ERROR(ENotSupported, E_NOT_SUPPORTED)
    VBox_WRAP_ERROR(EXMLError, E_XML_ERROR)
    VBox_WRAP_ERROR(EInvalidSessionState, E_INVALID_SESSION_STATE)
    VBox_WRAP_ERROR(EObjectInUse, E_OBJECT_IN_USE)
    VBox_WRAP_ERROR(EPasswordIncorrect, E_PASSWORD_INCORRECT)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    VBox_WRAP_ERROR(EMaximumReached, E_MAXIMUM_REACHED)
    VBox_WRAP_ERROR(EGstctlGuestError, E_GSTCTL_GUEST_ERROR)
    VBox_WRAP_ERROR(ETimeout, E_TIMEOUT)
#endif
}

#endif // _LIBVBOX_ERRORS_H
