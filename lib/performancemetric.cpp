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

COM_WRAP_IFC(IPerformanceMetric)

std::u16string VBox::IPerformanceMetric::metricName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), MetricName, result);
    return result;
}

VBox::COMPtr<VBox::COMUnknown> VBox::IPerformanceMetric::object() const
{
    COMPtr<COMUnknown> result;
    COM_GetValue_Wrap(get_IFC(), Object, result);
    return result;
}

std::u16string VBox::IPerformanceMetric::description() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Description, result);
    return result;
}

uint32_t VBox::IPerformanceMetric::period() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Period, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IPerformanceMetric::count() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Count, result);
    return static_cast<uint32_t>(result);
}

std::u16string VBox::IPerformanceMetric::unit() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Unit, result);
    return result;
}

int32_t VBox::IPerformanceMetric::minimumValue() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), MinimumValue, result);
    return static_cast<int32_t>(result);
}

int32_t VBox::IPerformanceMetric::maximumValue() const
{
    COM_Long result;
    COM_GetValue(get_IFC(), MaximumValue, result);
    return static_cast<int32_t>(result);
}
