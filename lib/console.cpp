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

const void *VBox::IConsole::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IConsole);
}

VBox::COMPtr<VBox::IMachine> VBox::IConsole::machine() const
{
    COMPtr<IMachine> result;
    COM_GetValue_Wrap(get_IFC(), Machine, result);
    return result;
}

VBox::MachineState VBox::IConsole::state() const
{
    COM_Enum(::MachineState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<MachineState>(result);
}

VBox::COMPtr<VBox::IGuest> VBox::IConsole::guest() const
{
    COMPtr<IGuest> result;
    COM_GetValue_Wrap(get_IFC(), Guest, result);
    return result;
}

VBox::COMPtr<VBox::IKeyboard> VBox::IConsole::keyboard() const
{
    COMPtr<IKeyboard> result;
    COM_GetValue_Wrap(get_IFC(), Keyboard, result);
    return result;
}

VBox::COMPtr<VBox::IMouse> VBox::IConsole::mouse() const
{
    COMPtr<IMouse> result;
    COM_GetValue_Wrap(get_IFC(), Mouse, result);
    return result;
}

VBox::COMPtr<VBox::IDisplay> VBox::IConsole::display() const
{
    COMPtr<IDisplay> result;
    COM_GetValue_Wrap(get_IFC(), Display, result);
    return result;
}

VBox::COMPtr<VBox::IMachineDebugger> VBox::IConsole::debugger() const
{
    COMPtr<IMachineDebugger> result;
    COM_GetValue_Wrap(get_IFC(), Debugger, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IUSBDevice>> VBox::IConsole::USBDevices() const
{
    std::vector<COMPtr<IUSBDevice>> result;
    COM_GetArray_Wrap(get_IFC(), USBDevices, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IHostUSBDevice>> VBox::IConsole::remoteUSBDevices() const
{
    std::vector<COMPtr<IHostUSBDevice>> result;
    COM_GetArray_Wrap(get_IFC(), RemoteUSBDevices, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::ISharedFolder>> VBox::IConsole::sharedFolders() const
{
    std::vector<COMPtr<ISharedFolder>> result;
    COM_GetArray_Wrap(get_IFC(), SharedFolders, result);
    return result;
}

VBox::COMPtr<VBox::IVRDEServerInfo> VBox::IConsole::VRDEServerInfo() const
{
    COMPtr<IVRDEServerInfo> result;
    COM_GetValue_Wrap(get_IFC(), VRDEServerInfo, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IConsole::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IPCIDeviceAttachment>> VBox::IConsole::attachedPCIDevices() const
{
    std::vector<COMPtr<IPCIDeviceAttachment>> result;
    COM_GetArray_Wrap(get_IFC(), AttachedPCIDevices, result);
    return result;
}

bool VBox::IConsole::useHostClipboard() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), UseHostClipboard, result);
    return static_cast<bool>(result);
}

void VBox::IConsole::set_useHostClipboard(bool value)
{
    COM_SetValue(get_IFC(), UseHostClipboard, value);
}

VBox::COMPtr<VBox::IEmulatedUSB> VBox::IConsole::emulatedUSB() const
{
    COMPtr<IEmulatedUSB> result;
    COM_GetValue_Wrap(get_IFC(), EmulatedUSB, result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IConsole::powerUp()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->PowerUp(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IConsole::powerUpPaused()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->PowerUpPaused(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IConsole::powerDown()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->PowerDown(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IConsole::reset()
{
    auto rc = get_IFC()->Reset();
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::pause()
{
    auto rc = get_IFC()->Pause();
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::resume()
{
    auto rc = get_IFC()->Resume();
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::powerButton()
{
    auto rc = get_IFC()->PowerButton();
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::sleepButton()
{
    auto rc = get_IFC()->SleepButton();
    COM_ERROR_CHECK(rc);
}

bool VBox::IConsole::getPowerButtonHandled()
{
    COM_Bool cResult;

    auto rc = get_IFC()->GetPowerButtonHandled(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

bool VBox::IConsole::getGuestEnteredACPIMode()
{
    COM_Bool cResult;

    auto rc = get_IFC()->GetGuestEnteredACPIMode(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

std::vector<VBox::DeviceActivity> VBox::IConsole::getDeviceActivity(
        const std::vector<DeviceType> &type)
{
    COM_ArrayProxy<COM_Enum(::DeviceType)> pType(type);
    COM_ArrayProxy<COM_Enum(::DeviceActivity)> pResult;

    auto rc = get_IFC()->GetDeviceActivity(COM_ArrayParameter(pType),
                                           COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<DeviceActivity> result;
    pResult.toVector(result);
    return result;
}

void VBox::IConsole::attachUSBDevice(const COMString &id,
        const COMString &captureFilename)
{
    COM_StringProxy pId(id);
    COM_StringProxy pCaptureFilename(captureFilename);

    auto rc = get_IFC()->AttachUSBDevice(pId.m_text, pCaptureFilename.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IUSBDevice> VBox::IConsole::detachUSBDevice(
        const COMString &id)
{
    ::IUSBDevice *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->DetachUSBDevice(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBDevice>::wrap(cResult);
}

VBox::COMPtr<VBox::IUSBDevice> VBox::IConsole::findUSBDeviceByAddress(
        const COMString &name)
{
    ::IUSBDevice *cResult = nullptr;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->FindUSBDeviceByAddress(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBDevice>::wrap(cResult);
}

VBox::COMPtr<VBox::IUSBDevice> VBox::IConsole::findUSBDeviceById(
        const COMString &id)
{
    ::IUSBDevice *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->FindUSBDeviceById(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IUSBDevice>::wrap(cResult);
}

void VBox::IConsole::createSharedFolder(const COMString &name,
        const COMString &hostPath, bool writable, bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
      , const COMString &autoMountPoint
#endif
        )
{
    COM_StringProxy pName(name);
    COM_StringProxy pHostPath(hostPath);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_StringProxy pAutoMountPoint(autoMountPoint);
#endif

    auto rc = get_IFC()->CreateSharedFolder(pName.m_text, pHostPath.m_text,
                                            writable, automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
                                          , pAutoMountPoint.m_text
#endif
                                            );
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::removeSharedFolder(const COMString &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->RemoveSharedFolder(pName.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IConsole::teleport(
        const COMString &hostname, uint32_t tcpport,
        const COMString &password, uint32_t maxDowntime)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pHostname(hostname);
    COM_StringProxy pPassword(password);

    auto rc = get_IFC()->Teleport(pHostname.m_text, tcpport, pPassword.m_text,
                                  maxDowntime, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IConsole::addDiskEncryptionPassword(const COMString &id,
        const COMString &password, bool clearOnSuspend)
{
    COM_StringProxy pId(id);
    COM_StringProxy pPassword(password);

    auto rc = get_IFC()->AddDiskEncryptionPassword(pId.m_text, pPassword.m_text,
                                                   clearOnSuspend);
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::addDiskEncryptionPasswords(
        const std::vector<COMString> &ids,
        const std::vector<COMString> &passwords, bool clearOnSuspend)
{
    COM_StringArrayProxy pIds(ids);
    COM_StringArrayProxy pPasswords(passwords);

    auto rc = get_IFC()->AddDiskEncryptionPasswords(COM_ArrayParameter(pIds),
                    COM_ArrayParameter(pPasswords), clearOnSuspend);
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::removeDiskEncryptionPassword(const COMString &id)
{
    COM_StringProxy pId(id);

    auto rc = get_IFC()->RemoveDiskEncryptionPassword(pId.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IConsole::clearAllDiskEncryptionPasswords()
{
    auto rc = get_IFC()->ClearAllDiskEncryptionPasswords();
    COM_ERROR_CHECK(rc);
}
