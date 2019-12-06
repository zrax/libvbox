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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
COM_WRAP_IFC(IDHCPConfig)
COM_WRAP_IFC(IDHCPGlobalConfig)
COM_WRAP_IFC(IDHCPGroupConfig)
COM_WRAP_IFC(IDHCPIndividualConfig)

VBox::DHCPConfigScope VBox::IDHCPConfig::scope() const
{
    COM_Enum(::DHCPConfigScope) result;
    COM_GetValue(get_IFC(), Scope, result);
    return static_cast<DHCPConfigScope>(result);
}

uint32_t VBox::IDHCPConfig::minLeaseTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MinLeaseTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IDHCPConfig::set_minLeaseTime(uint32_t value)
{
    COM_SetValue(get_IFC(), MinLeaseTime, value);
}

uint32_t VBox::IDHCPConfig::defaultLeaseTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), DefaultLeaseTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IDHCPConfig::set_defaultLeaseTime(uint32_t value)
{
    COM_SetValue(get_IFC(), DefaultLeaseTime, value);
}

uint32_t VBox::IDHCPConfig::maxLeaseTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxLeaseTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IDHCPConfig::set_maxLeaseTime(uint32_t value)
{
    COM_SetValue(get_IFC(), MaxLeaseTime, value);
}

std::vector<VBox::DHCPOption> VBox::IDHCPConfig::forcedOptions() const
{
    std::vector<DHCPOption> result;
    COM_GetArray(get_IFC(), ForcedOptions, COM_Enum(::DHCPOption), result);
    return result;
}

void VBox::IDHCPConfig::set_forcedOptions(const std::vector<DHCPOption> &value)
{
    COM_SetArray(get_IFC(), ForcedOptions, COM_Enum(::DHCPOption), value);
}

std::vector<VBox::DHCPOption> VBox::IDHCPConfig::suppressedOptions() const
{
    std::vector<DHCPOption> result;
    COM_GetArray(get_IFC(), SuppressedOptions, COM_Enum(::DHCPOption), result);
    return result;
}

void VBox::IDHCPConfig::set_suppressedOptions(const std::vector<DHCPOption> &value)
{
    COM_SetArray(get_IFC(), SuppressedOptions, COM_Enum(::DHCPOption), value);
}

void VBox::IDHCPConfig::setOption(DHCPOption option, DHCPOptionEncoding encoding,
        const std::u16string &value)
{
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->SetOption(static_cast<COM_Enum(::DHCPOption)>(option),
                static_cast<COM_Enum(::DHCPOptionEncoding)>(encoding),
                pValue.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IDHCPConfig::removeOption(DHCPOption option)
{
    auto rc = get_IFC()->RemoveOption(static_cast<COM_Enum(::DHCPOption)>(option));
    COM_ERROR_CHECK(rc);
}

void VBox::IDHCPConfig::removeAllOptions()
{
    auto rc = get_IFC()->RemoveAllOptions();
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IDHCPConfig::getOption(DHCPOption option,
        DHCPOptionEncoding *encoding)
{
    COM_StringProxy pResult;
    COM_Enum(::DHCPOptionEncoding) cEncoding;

    auto rc = get_IFC()->GetOption(static_cast<COM_Enum(::DHCPOption)>(option),
                &cEncoding, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    if (encoding)
        *encoding = static_cast<DHCPOptionEncoding>(cEncoding);
    return pResult.toString();
}

std::vector<std::u16string> VBox::IDHCPConfig::getAllOptions(
        std::vector<DHCPOption> *options,
        std::vector<DHCPOptionEncoding> *encodings)
{
    COM_StringArrayProxy pResult;
    COM_ArrayProxy<COM_Enum(::DHCPOption)> pOptions;
    COM_ArrayProxy<COM_Enum(::DHCPOptionEncoding)> pEncodings;

    auto rc = get_IFC()->GetAllOptions(COM_ArrayParameterRef(pOptions),
                COM_ArrayParameterRef(pEncodings), COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (options)
        pOptions.toVector(*options);
    if (encodings)
        pEncodings.toVector(*encodings);

    std::vector<std::u16string> result;
    pResult.toVector(result);
    return result;
}

void VBox::IDHCPConfig::remove()
{
    auto rc = get_IFC()->Remove();
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IDHCPGroupConfig::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

void VBox::IDHCPGroupConfig::set_name(const std::u16string &value)
{
    COM_SetString(get_IFC(), Name, value);
}

std::vector<VBox::COMPtr<VBox::IDHCPGroupCondition>>
VBox::IDHCPGroupConfig::conditions() const
{
    std::vector<COMPtr<IDHCPGroupCondition>> result;
    COM_GetArray_Wrap(get_IFC(), Conditions, result);
    return result;
}

VBox::COMPtr<VBox::IDHCPGroupCondition> VBox::IDHCPGroupConfig::addCondition(
        bool inclusive, DHCPGroupConditionType type,
        const std::u16string &value)
{
    ::IDHCPGroupCondition *cResult = nullptr;
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->AddCondition(inclusive,
                static_cast<COM_Enum(::DHCPGroupConditionType)>(type),
                pValue.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IDHCPGroupCondition>::wrap(cResult);
}

void VBox::IDHCPGroupConfig::removeAllConditions()
{
    auto rc = get_IFC()->RemoveAllConditions();
    COM_ERROR_CHECK(rc);
}

std::u16string VBox::IDHCPIndividualConfig::MACAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MACAddress, result);
    return result;
}

std::u16string VBox::IDHCPIndividualConfig::machineId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MachineId, result);
    return result;
}

uint32_t VBox::IDHCPIndividualConfig::slot() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Slot, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IDHCPIndividualConfig::fixedAddress() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FixedAddress, result);
    return result;
}

void VBox::IDHCPIndividualConfig::set_fixedAddress(const std::u16string &value)
{
    COM_SetString(get_IFC(), FixedAddress, value);
}
#endif
