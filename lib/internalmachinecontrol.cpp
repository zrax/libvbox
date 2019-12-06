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

COM_WRAP_IFC(IInternalMachineControl)

void VBox::IInternalMachineControl::updateState(MachineState state)
{
    auto cState = static_cast<COM_Enum(::MachineState)>(state);

    auto rc = get_IFC()->UpdateState(cState);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::beginPowerUp(const COMPtr<IProgress> &progress)
{
    auto rc = get_IFC()->BeginPowerUp(progress->get_IFC());
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::endPowerUp(int32_t result)
{
    auto rc = get_IFC()->EndPowerUp(result);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::beginPoweringDown(COMPtr<IProgress> *progress)
{
    ::IProgress *cProgress = nullptr;

    auto rc = get_IFC()->BeginPoweringDown(&cProgress);
    COM_ERROR_CHECK(rc);

    if (progress)
        *progress = COMPtr<IProgress>::wrap(cProgress);
    else if (cProgress)
        cProgress->Release();
}

void VBox::IInternalMachineControl::endPoweringDown(int32_t result,
        const std::u16string &errMsg)
{
    COM_StringProxy pErrMsg(errMsg);

    auto rc = get_IFC()->EndPoweringDown(result, pErrMsg.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::runUSBDeviceFilters(
        const COMPtr<IUSBDevice> &device, bool *matched,
        uint32_t *maskedInterfaces)
{
    COM_Bool cMatched;
    COM_ULong cMaskedInterfaces;

    auto rc = get_IFC()->RunUSBDeviceFilters(device->get_IFC(), &cMatched,
                &cMaskedInterfaces);
    COM_ERROR_CHECK(rc);

    if (matched)
        *matched = static_cast<bool>(cMatched);
    if (maskedInterfaces)
        *maskedInterfaces = static_cast<uint32_t>(cMaskedInterfaces);
}

void VBox::IInternalMachineControl::captureUSBDevice(const std::u16string &id,
        const std::u16string &captureFilename)
{
    COM_StringProxy pId(id);
    COM_StringProxy pCaptureFilename(captureFilename);

    auto rc = get_IFC()->CaptureUSBDevice(pId.m_text, pCaptureFilename.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::detachUSBDevice(const std::u16string &id,
        bool done)
{
    COM_StringProxy pId(id);

    auto rc = get_IFC()->DetachUSBDevice(pId.m_text, done);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::autoCaptureUSBDevices()
{
    auto rc = get_IFC()->AutoCaptureUSBDevices();
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::detachAllUSBDevices(bool done)
{
    auto rc = get_IFC()->DetachAllUSBDevices(done);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IInternalMachineControl::onSessionEnd(
        const COMPtr<ISession> &session)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->OnSessionEnd(session->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IInternalMachineControl::finishOnlineMergeMedium()
{
    auto rc = get_IFC()->FinishOnlineMergeMedium();
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::pullGuestProperties(
        std::vector<std::u16string> *names, std::vector<std::u16string> *values,
        std::vector<int64_t> *timestamps, std::vector<std::u16string> *flags)
{
    COM_StringArrayProxy pNames;
    COM_StringArrayProxy pValues;
    COM_ArrayProxy<COM_Long64> pTimestamps;
    COM_StringArrayProxy pFlags;

    auto rc = get_IFC()->PullGuestProperties(COM_ArrayParameterRef(pNames),
                COM_ArrayParameterRef(pValues), COM_ArrayParameterRef(pTimestamps),
                COM_ArrayParameterRef(pFlags));
    COM_ERROR_CHECK(rc);

    if (names)
        pNames.toVector(*names);
    if (values)
        pValues.toVector(*values);
    if (timestamps)
        pTimestamps.toVector(*timestamps);
    if (flags)
        pFlags.toVector(*flags);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
void VBox::IInternalMachineControl::clipboardAreaRegister(
        const std::vector<std::u16string> &parms, uint32_t *id)
{
    COM_StringArrayProxy pParms(parms);
    COM_ULong cId;

    auto rc = get_IFC()->ClipboardAreaRegister(COM_ArrayParameter(pParms), &cId);
    COM_ERROR_CHECK(rc);

    if (id)
        *id = static_cast<uint32_t>(cId);
}

void VBox::IInternalMachineControl::clipboardAreaUnregister(uint32_t id)
{
    auto rc = get_IFC()->ClipboardAreaUnregister(id);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::clipboardAreaAttach(uint32_t id)
{
    auto rc = get_IFC()->ClipboardAreaAttach(id);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::clipboardAreaDetach(uint32_t id)
{
    auto rc = get_IFC()->ClipboardAreaDetach(id);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::clipboardAreaGetMostRecent(uint32_t *id)
{
    COM_ULong cId;

    auto rc = get_IFC()->ClipboardAreaGetMostRecent(&cId);
    COM_ERROR_CHECK(rc);

    if (id)
        *id = static_cast<uint32_t>(cId);
}

void VBox::IInternalMachineControl::clipboardAreaGetRefCount(uint32_t id,
        uint32_t *refcount)
{
    COM_ULong cRefcount;

    auto rc = get_IFC()->ClipboardAreaGetRefCount(id, &cRefcount);
    COM_ERROR_CHECK(rc);

    if (refcount)
        *refcount = static_cast<uint32_t>(cRefcount);
}
#endif

void VBox::IInternalMachineControl::pushGuestProperty(const std::u16string &name,
        const std::u16string &value, int64_t timestamp, const std::u16string &flags)
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue(value);
    COM_StringProxy pFlags(flags);

    auto rc = get_IFC()->PushGuestProperty(pName.m_text, pValue.m_text,
                timestamp, pFlags.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::lockMedia()
{
    auto rc = get_IFC()->LockMedia();
    COM_ERROR_CHECK(rc);
}

void VBox::IInternalMachineControl::unlockMedia()
{
    auto rc = get_IFC()->UnlockMedia();
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IMediumAttachment> VBox::IInternalMachineControl::ejectMedium(
        const COMPtr<IMediumAttachment> &attachment)
{
    ::IMediumAttachment *cResult = nullptr;

    auto rc = get_IFC()->EjectMedium(attachment->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IMediumAttachment>::wrap(cResult);
}

void VBox::IInternalMachineControl::reportVmStatistics(uint32_t validStats,
        uint32_t cpuUser, uint32_t cpuKernel, uint32_t cpuIdle, uint32_t memTotal,
        uint32_t memFree, uint32_t memBalloon, uint32_t memShared,
        uint32_t memCache, uint32_t pagedTotal, uint32_t memAllocTotal,
        uint32_t memFreeTotal, uint32_t memBalloonTotal, uint32_t memSharedTotal,
        uint32_t vmNetRx, uint32_t vmNetTx)
{
    auto rc = get_IFC()->ReportVmStatistics(validStats, cpuUser, cpuKernel,
                cpuIdle, memTotal, memFree, memBalloon, memShared,
                memCache, pagedTotal, memAllocTotal, memFreeTotal,
                memBalloonTotal, memSharedTotal, vmNetRx, vmNetTx);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 0, 10)
void VBox::IInternalMachineControl::authenticateExternal(
        const std::vector<std::u16string> &authParams, std::u16string *result)
{
    COM_StringArrayProxy pAuthParams(authParams);
    COM_StringProxy pResult;

    auto rc = get_IFC()->AuthenticateExternal(COM_ArrayParameter(pAuthParams),
                &pResult.m_text);
    COM_ERROR_CHECK(rc);

    if (result)
        *result = pResult.toString();
}
#endif
