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

COM_WRAP_IFC(IInternalSessionControl)

uint32_t VBox::IInternalSessionControl::PID() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), PID, result);
    return static_cast<uint32_t>(result);
}

VBox::COMPtr<VBox::IConsole> VBox::IInternalSessionControl::remoteConsole() const
{
    COMPtr<IConsole> result;
    COM_GetValue_Wrap(get_IFC(), RemoteConsole, result);
    return result;
}

VBox::MachineState VBox::IInternalSessionControl::nominalState() const
{
    COM_Enum(::MachineState) result;
    COM_GetValue(get_IFC(), NominalState, result);
    return static_cast<MachineState>(result);
}

void VBox::IInternalSessionControl::assignRemoteMachine(
        const COMPtr<IMachine> &machine, const COMPtr<IConsole> &console)
{
    auto rc = get_IFC()->AssignRemoteMachine(machine->get_IFC(), console->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::updateMachineState(MachineState machineState)
{
    auto cMachineState = static_cast<COM_Enum(::MachineState)>(machineState);

    auto rc = get_IFC()->UpdateMachineState(cMachineState);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::uninitialize()
{
    auto rc = get_IFC()->Uninitialize();
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onNetworkAdapterChange(
        const COMPtr<INetworkAdapter> &networkAdapter, bool changeAdapter)
{
    auto rc = get_IFC()->OnNetworkAdapterChange(networkAdapter->get_IFC(),
                changeAdapter);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
void VBox::IInternalSessionControl::onAudioAdapterChange(
        const COMPtr<IAudioAdapter> &audioAdapter)
{
    auto rc = get_IFC()->OnAudioAdapterChange(audioAdapter->get_IFC());
    COM_ERROR_CHECK(rc);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
void VBox::IInternalSessionControl::onHostAudioDeviceChange(
        const COMPtr<IHostAudioDevice> &device, bool isNew,
        AudioDeviceState state, const COMPtr<IVirtualBoxErrorInfo> &errorInfo)
{
    auto rc = get_IFC()->OnHostAudioDeviceChange(device->get_IFC(), isNew,
                static_cast<COM_Enum(::AudioDeviceState)>(state), errorInfo->get_IFC());
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IInternalSessionControl::onSerialPortChange(
        const COMPtr<ISerialPort> &serialPort)
{
    auto rc = get_IFC()->OnSerialPortChange(serialPort->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onParallelPortChange(
        const COMPtr<IParallelPort> &parallelPort)
{
    auto rc = get_IFC()->OnParallelPortChange(parallelPort->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onStorageControllerChange(
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        const std::u16string &machineId, const std::u16string &controllerName
#endif
        )
{
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    COM_StringProxy pMachineId(machineId);
    COM_StringProxy pControllerName(controllerName);
#endif

    auto rc = get_IFC()->OnStorageControllerChange(
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
                pMachineId.m_text, pControllerName.m_text
#endif
                );
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onMediumChange(
        const COMPtr<IMediumAttachment> &mediumAttachment, bool force)
{
    auto rc = get_IFC()->OnMediumChange(mediumAttachment->get_IFC(), force);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onStorageDeviceChange(
        const COMPtr<IMediumAttachment> &mediumAttachment, bool remove,
        bool silent)
{
    auto rc = get_IFC()->OnStorageDeviceChange(mediumAttachment->get_IFC(),
                remove, silent);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
void VBox::IInternalSessionControl::onVMProcessPriorityChange(VMProcPriority priority)
{
    auto cPriority = static_cast<COM_Enum(::VMProcPriority)>(priority);

    auto rc = get_IFC()->OnVMProcessPriorityChange(cPriority);
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IInternalSessionControl::onClipboardModeChange(
        ClipboardMode clipboardMode)
{
    auto cClipboardMode = static_cast<COM_Enum(::ClipboardMode)>(clipboardMode);

    auto rc = get_IFC()->OnClipboardModeChange(cClipboardMode);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
void VBox::IInternalSessionControl::onClipboardFileTransferModeChange(bool enabled)
{
    auto rc = get_IFC()->OnClipboardFileTransferModeChange(enabled);
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IInternalSessionControl::onDnDModeChange(DnDMode dndMode)
{
    auto cDndMode = static_cast<COM_Enum(::DnDMode)>(dndMode);

    auto rc = get_IFC()->OnDnDModeChange(cDndMode);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onCPUChange(uint32_t cpu, bool add)
{
    auto rc = get_IFC()->OnCPUChange(cpu, add);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onCPUExecutionCapChange(uint32_t executionCap)
{
    auto rc = get_IFC()->OnCPUExecutionCapChange(executionCap);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onVRDEServerChange(bool restart)
{
    auto rc = get_IFC()->OnVRDEServerChange(restart);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
void VBox::IInternalSessionControl::onRecordingChange(bool enable)
{
    auto rc = get_IFC()->OnRecordingChange(enable);
    COM_ERROR_CHECK(rc);
}
#else
void VBox::IInternalSessionControl::onVideoCaptureChange()
{
    auto rc = get_IFC()->OnVideoCaptureChange();
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IInternalSessionControl::onUSBControllerChange()
{
    auto rc = get_IFC()->OnUSBControllerChange();
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onSharedFolderChange(bool global)
{
    auto rc = get_IFC()->OnSharedFolderChange(global);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
void VBox::IInternalSessionControl::onGuestDebugControlChange(
        const COMPtr<IGuestDebugControl> &guestDebugControl)
{
    auto rc = get_IFC()->OnGuestDebugControlChange(guestDebugControl->get_IFC());
    COM_ERROR_CHECK(rc);
}
#endif

void VBox::IInternalSessionControl::onUSBDeviceAttach(
        const COMPtr<IUSBDevice> &device,
        const COMPtr<IVirtualBoxErrorInfo> &error, uint32_t maskedInterfaces,
        const std::u16string &captureFilename)
{
    COM_StringProxy pCaptureFilename(captureFilename);

    auto rc = get_IFC()->OnUSBDeviceAttach(device->get_IFC(), error->get_IFC(),
                maskedInterfaces, pCaptureFilename.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onUSBDeviceDetach(const std::u16string &id,
        const COMPtr<IVirtualBoxErrorInfo> &error)
{
    COM_StringProxy pId(id);

    auto rc = get_IFC()->OnUSBDeviceDetach(pId.m_text, error->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::onShowWindow(bool check, bool *canShow,
        int64_t *winId)
{
    COM_Bool cCanShow;
    COM_Long64 cWinId;

    auto rc = get_IFC()->OnShowWindow(check, &cCanShow, &cWinId);
    COM_ERROR_CHECK(rc);

    if (canShow)
        *canShow = static_cast<bool>(cCanShow);
    if (winId)
        *winId = static_cast<int64_t>(cWinId);
}

void VBox::IInternalSessionControl::onBandwidthGroupChange(
        const COMPtr<IBandwidthGroup> &bandwidthGroup)
{
    auto rc = get_IFC()->OnBandwidthGroupChange(bandwidthGroup->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::accessGuestProperty(
        const std::u16string &name, const std::u16string &value,
        const std::u16string &flags, uint32_t accessMode,
        std::u16string *retValue, int64_t *retTimestamp,
        std::u16string *retFlags)
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue(value);
    COM_StringProxy pFlags(flags);
    COM_StringProxy pRetValue;
    COM_Long64 cRetTimestamp;
    COM_StringProxy pRetFlags;

    auto rc = get_IFC()->AccessGuestProperty(pName.m_text, pValue.m_text,
                pFlags.m_text, accessMode, &pRetValue.m_text, &cRetTimestamp,
                &pRetFlags.m_text);
    COM_ERROR_CHECK(rc);

    if (retValue)
        *retValue = pRetValue.toString();
    if (retTimestamp)
        *retTimestamp = static_cast<int64_t>(cRetTimestamp);
    if (retFlags)
        *retFlags = pRetFlags.toString();
}

void VBox::IInternalSessionControl::enumerateGuestProperties(
        const std::u16string &patterns, std::vector<std::u16string> *keys,
        std::vector<std::u16string> *values, std::vector<int64_t> *timestamps,
        std::vector<std::u16string> *flags) const
{
    COM_StringProxy pPatterns(patterns);
    COM_StringArrayProxy pKeys;
    COM_StringArrayProxy pValues;
    COM_ArrayProxy<COM_Long64> pTimestamps;
    COM_StringArrayProxy pFlags;

    auto rc = get_IFC()->EnumerateGuestProperties(pPatterns.m_text,
                COM_ArrayParameterRef(pKeys), COM_ArrayParameterRef(pValues),
                COM_ArrayParameterRef(pTimestamps), COM_ArrayParameterRef(pFlags));
    COM_ERROR_CHECK(rc);

    if (keys)
        pKeys.toVector(*keys);
    if (values)
        pValues.toVector(*values);
    if (timestamps)
        pTimestamps.toVector(*timestamps);
    if (flags)
        pFlags.toVector(*flags);
}

void VBox::IInternalSessionControl::onlineMergeMedium(
        const COMPtr<IMediumAttachment> &mediumAttachment, uint32_t sourceIdx,
        uint32_t targetIdx, const COMPtr<IProgress> &progress)
{
    auto rc = get_IFC()->OnlineMergeMedium(mediumAttachment->get_IFC(), sourceIdx,
                targetIdx, progress->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::reconfigureMediumAttachments(
        const std::vector<COMPtr<IMediumAttachment>> &attachments)
{
    COM_ArrayProxy<::IMediumAttachment *> pAttachments(attachments);

    auto rc = get_IFC()->ReconfigureMediumAttachments(COM_ArrayParameter(pAttachments));
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::enableVMMStatistics(bool enable)
{
    auto rc = get_IFC()->EnableVMMStatistics(enable);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::pauseWithReason(Reason reason)
{
    auto cReason = static_cast<COM_Enum(::Reason)>(reason);

    auto rc = get_IFC()->PauseWithReason(cReason);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalSessionControl::resumeWithReason(Reason reason)
{
    auto cReason = static_cast<COM_Enum(::Reason)>(reason);

    auto rc = get_IFC()->ResumeWithReason(cReason);
    COM_ERROR_CHECK(rc);
}

bool VBox::IInternalSessionControl::saveStateWithReason(Reason reason,
        const COMPtr<IProgress> &progress,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        const COMPtr<ISnapshot> &snapshot,
#endif
        const std::u16string &stateFilePath, bool pauseVM)
{
    COM_Bool cResult;
    auto cReason = static_cast<COM_Enum(::Reason)>(reason);
    COM_StringProxy pStateFilePath(stateFilePath);

    auto rc = get_IFC()->SaveStateWithReason(cReason, progress->get_IFC(),
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                snapshot->get_IFC(),
#endif
                pStateFilePath.m_text, pauseVM, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IInternalSessionControl::cancelSaveStateWithReason()
{
    auto rc = get_IFC()->CancelSaveStateWithReason();
    COM_ERROR_CHECK(rc);
}
