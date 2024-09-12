/* This file is part of libvbox
 * Copyright (C) 2022  Michael Hansen
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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
COM_WRAP_IFC(ICloudMachine)

std::u16string VBox::ICloudMachine::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
std::u16string VBox::ICloudMachine::cloudId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), CloudId, result);
    return result;
}
#endif

bool VBox::ICloudMachine::accessible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accessible, result);
    return static_cast<bool>(result);
}

VBox::COMPtr<VBox::IVirtualBoxErrorInfo> VBox::ICloudMachine::accessError() const
{
    COMPtr<IVirtualBoxErrorInfo> result;
    COM_GetValue_Wrap(get_IFC(), AccessError, result);
    return result;
}

std::u16string VBox::ICloudMachine::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::u16string VBox::ICloudMachine::OSTypeId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OSTypeId, result);
    return result;
}

VBox::CloudMachineState VBox::ICloudMachine::state() const
{
    COM_Enum(::CloudMachineState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<CloudMachineState>(result);
}

std::u16string VBox::ICloudMachine::consoleConnectionFingerprint() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ConsoleConnectionFingerprint, result);
    return result;
}

std::u16string VBox::ICloudMachine::serialConsoleCommand() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SerialConsoleCommand, result);
    return result;
}

std::u16string VBox::ICloudMachine::serialConsoleCommandWindows() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SerialConsoleCommandWindows, result);
    return result;
}

std::u16string VBox::ICloudMachine::VNCConsoleCommand() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VNCConsoleCommand, result);
    return result;
}

std::u16string VBox::ICloudMachine::VNCConsoleCommandWindows() const
{
    std::u16string result;
    COM_GetString(get_IFC(), VNCConsoleCommandWindows, result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::refresh()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Refresh(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IForm> VBox::ICloudMachine::getDetailsForm() const
{
    ::IForm *cResult = nullptr;

    auto rc = get_IFC()->GetDetailsForm(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IForm>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::getSettingsForm(COMPtr<IForm> *form)
{
    ::IProgress *cResult = nullptr;
    ::IForm *cForm = nullptr;

    auto rc = get_IFC()->GetSettingsForm(&cForm, &cResult);
    COM_ERROR_CHECK(rc);

    if (form)
        *form = COMPtr<IForm>::wrap(cForm);
    else if (cForm)
        cForm->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::powerUp()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->PowerUp(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::reboot()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Reboot(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 10)
VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::reset()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Reset(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::shutdown()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Shutdown(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::powerDown()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->PowerDown(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::terminate()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Terminate(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::unregister()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Unregister(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::remove()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Remove(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::getConsoleHistory(
        COMPtr<VBox::IDataStream> *stream)
{
    ::IProgress *cResult = nullptr;
    ::IDataStream *cStream = nullptr;

    auto rc = get_IFC()->GetConsoleHistory(&cStream, &cResult);
    COM_ERROR_CHECK(rc);

    if (stream)
        *stream = COMPtr<IDataStream>::wrap(cStream);
    else if (cStream)
        cStream->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::createConsoleConnection(
        const std::u16string &sshPublicKey)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSshPublicKey(sshPublicKey);

    auto rc = get_IFC()->CreateConsoleConnection(pSshPublicKey.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::deleteConsoleConnection()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->DeleteConsoleConnection(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::listMetricNames(
        COMPtr<IStringArray> *metricNames)
{
    ::IProgress *cResult = nullptr;
    ::IStringArray *cMetricNames = nullptr;

    auto rc = get_IFC()->ListMetricNames(&cMetricNames, &cResult);
    COM_ERROR_CHECK(rc);

    if (metricNames)
        *metricNames = COMPtr<IStringArray>::wrap(cMetricNames);
    else if (cMetricNames)
        cMetricNames->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudMachine::enumerateMetricData(
        MetricType metricType, uint32_t pointsNumber, COMPtr<IStringArray> *values,
        COMPtr<IStringArray> *timestamps, COMPtr<IStringArray> *unit)
{
    ::IProgress *cResult = nullptr;
    auto cMetricType = static_cast<COM_Enum(::MetricType)>(metricType);
    auto cPointsNumber = static_cast<COM_ULong>(pointsNumber);
    ::IStringArray *cValues = nullptr;
    ::IStringArray *cTimestamps = nullptr;
    ::IStringArray *cUnit = nullptr;

    auto rc = get_IFC()->EnumerateMetricData(cMetricType, cPointsNumber, &cValues,
                                             &cTimestamps, &cUnit, &cResult);
    COM_ERROR_CHECK(rc);

    if (values)
        *values = COMPtr<IStringArray>::wrap(cValues);
    else if (cValues)
        cValues->Release();
    if (timestamps)
        *timestamps = COMPtr<IStringArray>::wrap(cTimestamps);
    else if (cTimestamps)
        cTimestamps->Release();
    if (unit)
        *unit = COMPtr<IStringArray>::wrap(cUnit);
    else if (cUnit)
        cUnit->Release();
    return COMPtr<IProgress>::wrap(cResult);
}
#endif

#endif
