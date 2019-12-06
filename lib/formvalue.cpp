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
COM_WRAP_IFC(IFormValue)
COM_WRAP_IFC(IBooleanFormValue)
COM_WRAP_IFC(IRangedIntegerFormValue)
COM_WRAP_IFC(IStringFormValue)
COM_WRAP_IFC(IChoiceFormValue)

VBox::FormValueType VBox::IFormValue::type() const
{
    COM_Enum(::FormValueType) result;
    COM_GetValue(get_IFC(), Type, result);
    return static_cast<FormValueType>(result);
}

int32_t VBox::IFormValue::generation() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), Generation, result);
    return static_cast<int32_t>(result);
}

bool VBox::IFormValue::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

bool VBox::IFormValue::visible() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Visible, result);
    return static_cast<bool>(result);
}

std::u16string VBox::IFormValue::label() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Label, result);
    return result;
}

std::u16string VBox::IFormValue::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

std::u16string VBox::IFormValue::help() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Help, result);
    return result;
}

bool VBox::IBooleanFormValue::getSelected()
{
    COM_Bool cResult;

    auto rc = get_IFC()->GetSelected(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IBooleanFormValue::setSelected(bool selected)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->SetSelected(selected, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

std::u16string VBox::IRangedIntegerFormValue::suffix() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Suffix, result);
    return result;
}

int32_t VBox::IRangedIntegerFormValue::minimum() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), Minimum, result);
    return static_cast<int32_t>(result);
}

int32_t VBox::IRangedIntegerFormValue::maximum() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), Maximum, result);
    return static_cast<int32_t>(result);
}

int32_t VBox::IRangedIntegerFormValue::getInteger()
{
    COM_Long cResult;

    auto rc = get_IFC()->GetInteger(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int32_t>(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IRangedIntegerFormValue::setInteger(int32_t value)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->SetInteger(value, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

bool VBox::IStringFormValue::multiline() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Multiline, result);
    return result;
}

std::u16string VBox::IStringFormValue::getString()
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->GetString(&pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

VBox::COMPtr<VBox::IProgress> VBox::IStringFormValue::setString(
        const std::u16string &text)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pText(text);

    auto rc = get_IFC()->SetString(pText.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

std::vector<std::u16string> VBox::IChoiceFormValue::values() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), Values, result);
    return result;
}

// Methods
int32_t VBox::IChoiceFormValue::getSelectedIndex()
{
    COM_Long cResult;

    auto rc = get_IFC()->GetSelectedIndex(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int32_t>(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IChoiceFormValue::setSelectedIndex(int32_t index)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->SetSelectedIndex(index, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif
