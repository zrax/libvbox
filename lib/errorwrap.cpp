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

#include "libvbox_errors.h"

std::string VBox::COMError::error_message(uint32_t rc, const char *name)
{
    char buffer[64];
    if (name)
        snprintf(buffer, sizeof(buffer), "COM Error %#x: %s", rc, name);
    else
        snprintf(buffer, sizeof(buffer), "COM Error %#x", rc);
    return buffer;
}

void VBox::COMError::raise(uint32_t rc)
{
    switch (rc) {
    case E_NOTIMPL:
        throw ENotImpl();
    case E_POINTER:
        throw EPointer();
    case E_ABORT:
        throw EAbort();
    case E_FAIL:
        throw EFail();
    case E_ACCESSDENIED:
        throw EAccessDenied();
    case E_OUTOFMEMORY:
        throw EOutOfMemory();
    case E_INVALIDARG:
        throw EInvalidArg();
    case E_UNEXPECTED:
        throw EUnexpected();
    case E_OBJECT_NOT_FOUND:
        throw EObjectNotFound();
    case E_INVALID_VM_STATE:
        throw EInvalidVMState();
    case E_VM_ERROR:
        throw EVMError();
    case E_FILE_ERROR:
        throw EFileError();
    case E_IPRT_ERROR:
        throw EIPRTError();
    case E_PDM_ERROR:
        throw EPDMError();
    case E_INVALID_OBJECT_STATE:
        throw EInvalidObjectState();
    case E_HOST_ERROR:
        throw EHostError();
    case E_NOT_SUPPORTED:
        throw ENotSupported();
    case E_XML_ERROR:
        throw EXMLError();
    case E_INVALID_SESSION_STATE:
        throw EInvalidSessionState();
    case E_OBJECT_IN_USE:
        throw EObjectInUse();
    case E_PASSWORD_INCORRECT:
        throw EPasswordIncorrect();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    case E_MAXIMUM_REACHED:
        throw EMaximumReached();
    case E_GSTCTL_GUEST_ERROR:
        throw EGstctlGuestError();
    case E_TIMEOUT:
        throw ETimeout();
#endif
    default:
        throw COMError(rc);
    }
}
