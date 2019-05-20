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

COM_WRAP_IFC(IMachineDebugger)

bool VBox::IMachineDebugger::singleStep() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), SingleStep, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_singleStep(bool value)
{
    COM_SetValue(get_IFC(), SingleStep, value);
}

bool VBox::IMachineDebugger::recompileUser() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecompileUser, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_recompileUser(bool value)
{
    COM_SetValue(get_IFC(), RecompileUser, value);
}

bool VBox::IMachineDebugger::recompileSupervisor() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), RecompileSupervisor, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_recompileSupervisor(bool value)
{
    COM_SetValue(get_IFC(), RecompileSupervisor, value);
}

bool VBox::IMachineDebugger::executeAllInIEM() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), ExecuteAllInIEM, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_executeAllInIEM(bool value)
{
    COM_SetValue(get_IFC(), ExecuteAllInIEM, value);
}

bool VBox::IMachineDebugger::PATMEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), PATMEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_PATMEnabled(bool value)
{
    COM_SetValue(get_IFC(), PATMEnabled, value);
}

bool VBox::IMachineDebugger::CSAMEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), CSAMEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_CSAMEnabled(bool value)
{
    COM_SetValue(get_IFC(), CSAMEnabled, value);
}

bool VBox::IMachineDebugger::logEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), LogEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IMachineDebugger::set_logEnabled(bool value)
{
    COM_SetValue(get_IFC(), LogEnabled, value);
}

std::u16string VBox::IMachineDebugger::logDbgFlags() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogDbgFlags, result);
    return result;
}

std::u16string VBox::IMachineDebugger::logDbgGroups() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogDbgGroups, result);
    return result;
}

std::u16string VBox::IMachineDebugger::logDbgDestinations() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogDbgDestinations, result);
    return result;
}

std::u16string VBox::IMachineDebugger::logRelFlags() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogRelFlags, result);
    return result;
}

std::u16string VBox::IMachineDebugger::logRelGroups() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogRelGroups, result);
    return result;
}

std::u16string VBox::IMachineDebugger::logRelDestinations() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LogRelDestinations, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::VMExecutionEngine VBox::IMachineDebugger::executionEngine() const
{
    COM_Enum(::VMExecutionEngine) result;
    COM_GetValue(get_IFC(), ExecutionEngine, result);
    return static_cast<VMExecutionEngine>(result);
}
#endif

bool VBox::IMachineDebugger::HWVirtExEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HWVirtExEnabled, result);
    return static_cast<bool>(result);
}

bool VBox::IMachineDebugger::HWVirtExNestedPagingEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HWVirtExNestedPagingEnabled, result);
    return static_cast<bool>(result);
}

bool VBox::IMachineDebugger::HWVirtExVPIDEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HWVirtExVPIDEnabled, result);
    return static_cast<bool>(result);
}

bool VBox::IMachineDebugger::HWVirtExUXEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), HWVirtExUXEnabled, result);
    return static_cast<bool>(result);
}

std::u16string VBox::IMachineDebugger::OSName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OSName, result);
    return result;
}

std::u16string VBox::IMachineDebugger::OSVersion() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OSVersion, result);
    return result;
}

bool VBox::IMachineDebugger::PAEEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), PAEEnabled, result);
    return static_cast<bool>(result);
}

uint32_t VBox::IMachineDebugger::virtualTimeRate() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VirtualTimeRate, result);
    return static_cast<uint32_t>(result);
}

void VBox::IMachineDebugger::set_virtualTimeRate(uint32_t value)
{
    COM_SetValue(get_IFC(), VirtualTimeRate, value);
}

int64_t VBox::IMachineDebugger::VM() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), VM, result);
    return static_cast<int64_t>(result);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 4)
int64_t VBox::IMachineDebugger::uptime() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), Uptime, result);
    return static_cast<int64_t>(result);
}
#endif

// Methods
void VBox::IMachineDebugger::dumpGuestCore(const std::u16string &filename,
        const std::u16string &compression)
{
    COM_StringProxy pFilename(filename);
    COM_StringProxy pCompression(compression);

    auto rc = get_IFC()->DumpGuestCore(pFilename.m_text, pCompression.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachineDebugger::dumpHostProcessCore(const std::u16string &filename,
        const std::u16string &compression)
{
    COM_StringProxy pFilename(filename);
    COM_StringProxy pCompression(compression);

    auto rc = get_IFC()->DumpHostProcessCore(pFilename.m_text, pCompression.m_text);
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IMachineDebugger::info(const std::u16string &name,
        const std::u16string &args)
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);
    COM_StringProxy pArgs(args);

    auto rc = get_IFC()->Info(pName.m_text, pArgs.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IMachineDebugger::injectNMI()
{
    auto rc = get_IFC()->InjectNMI();
    COM_ERROR_CHECK(rc);
}

void VBox::IMachineDebugger::modifyLogGroups(const std::u16string &settings)
{
    COM_StringProxy pSettings(settings);

    auto rc = get_IFC()->ModifyLogGroups(pSettings.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachineDebugger::modifyLogFlags(const std::u16string &settings)
{
    COM_StringProxy pSettings(settings);

    auto rc = get_IFC()->ModifyLogFlags(pSettings.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachineDebugger::modifyLogDestinations(const std::u16string &settings)
{
    COM_StringProxy pSettings(settings);

    auto rc = get_IFC()->ModifyLogDestinations(pSettings.m_text);
    COM_ERROR_CHECK(rc);
}

std::vector<uint8_t> VBox::IMachineDebugger::readPhysicalMemory(int64_t address,
        uint32_t size)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->ReadPhysicalMemory(address, size, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

void VBox::IMachineDebugger::writePhysicalMemory(int64_t address, uint32_t size,
        const std::vector<uint8_t> &bytes)
{
    COM_ArrayProxy<COM_Byte> pBytes(bytes);

    auto rc = get_IFC()->WritePhysicalMemory(address, size, COM_ArrayParameter(pBytes));
    COM_ERROR_CHECK(rc);
}

std::vector<uint8_t> VBox::IMachineDebugger::readVirtualMemory(uint32_t cpuId,
        int64_t address, uint32_t size)
{
    COM_ArrayProxy<COM_Byte> pResult;

    auto rc = get_IFC()->ReadVirtualMemory(cpuId, address, size,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    pResult.toVector(result);
    return result;
}

void VBox::IMachineDebugger::writeVirtualMemory(uint32_t cpuId, int64_t address,
        uint32_t size, const std::vector<uint8_t> &bytes)
{
    COM_ArrayProxy<COM_Byte> pBytes(bytes);

    auto rc = get_IFC()->WriteVirtualMemory(cpuId, address, size,
                COM_ArrayParameter(pBytes));
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IMachineDebugger::loadPlugIn(const std::u16string &name)
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->LoadPlugIn(pName.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IMachineDebugger::unloadPlugIn(const std::u16string &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->UnloadPlugIn(pName.m_text);
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IMachineDebugger::detectOS()
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->DetectOS(&pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

std::u16string VBox::IMachineDebugger::queryOSKernelLog(uint32_t maxMessages)
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->QueryOSKernelLog(maxMessages, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

std::u16string VBox::IMachineDebugger::getRegister(uint32_t cpuId,
        const std::u16string &name)
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->GetRegister(cpuId, pName.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IMachineDebugger::getRegisters(uint32_t cpuId,
        std::vector<std::u16string> *names, std::vector<std::u16string> *values)
{
    COM_StringArrayProxy pNames;
    COM_StringArrayProxy pValues;

    auto rc = get_IFC()->GetRegisters(cpuId, COM_ArrayParameterRef(pNames),
                COM_ArrayParameterRef(pValues));
    COM_ERROR_CHECK(rc);

    if (names)
        pNames.toVector(*names);
    if (values)
        pValues.toVector(*values);
}

void VBox::IMachineDebugger::setRegister(uint32_t cpuId,
        const std::u16string &name, const std::u16string &value)
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetRegister(cpuId, pName.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachineDebugger::setRegisters(uint32_t cpuId,
        const std::vector<std::u16string> &names,
        const std::vector<std::u16string> &values)
{
    COM_StringArrayProxy pNames(names);
    COM_StringArrayProxy pValues(values);

    auto rc = get_IFC()->SetRegisters(cpuId, COM_ArrayParameter(pNames),
                COM_ArrayParameter(pValues));
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IMachineDebugger::dumpGuestStack(uint32_t cpuId)
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->DumpGuestStack(cpuId, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IMachineDebugger::resetStats(const std::u16string &pattern)
{
    COM_StringProxy pPattern(pattern);

    auto rc = get_IFC()->ResetStats(pPattern.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IMachineDebugger::dumpStats(const std::u16string &pattern)
{
    COM_StringProxy pPattern(pattern);

    auto rc = get_IFC()->DumpStats(pPattern.m_text);
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IMachineDebugger::getStats(const std::u16string &pattern,
        bool withDescriptions)
{
    COM_StringProxy pResult;
    COM_StringProxy pPattern(pattern);

    auto rc = get_IFC()->GetStats(pPattern.m_text, withDescriptions, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}
