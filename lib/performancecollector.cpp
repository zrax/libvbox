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

COM_WRAP_IFC(IPerformanceCollector)

std::vector<std::u16string> VBox::IPerformanceCollector::metricNames() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), MetricNames, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IPerformanceMetric>>
VBox::IPerformanceCollector::getMetrics(
        const std::vector<std::u16string> &metricNames,
        const std::vector<COMPtr<COMUnknown>> &objects)
{
    COM_ArrayProxy<::IPerformanceMetric *> pResult;
    COM_StringArrayProxy pMetricNames(metricNames);
    COM_ArrayProxy<COMUnknown::COM_Ifc *> pObjects(objects);

    auto rc = get_IFC()->GetMetrics(COM_ArrayParameter(pMetricNames),
                COM_ArrayParameter(pObjects), COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IPerformanceMetric>> result;
    pResult.toVector(result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IPerformanceMetric>>
VBox::IPerformanceCollector::setupMetrics(
        const std::vector<std::u16string> &metricNames,
        const std::vector<COMPtr<COMUnknown>> &objects,
        uint32_t period, uint32_t count)
{
    COM_ArrayProxy<::IPerformanceMetric *> pResult;
    COM_StringArrayProxy pMetricNames(metricNames);
    COM_ArrayProxy<COMUnknown::COM_Ifc *> pObjects(objects);

    auto rc = get_IFC()->SetupMetrics(COM_ArrayParameter(pMetricNames),
                COM_ArrayParameter(pObjects), period, count,
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IPerformanceMetric>> result;
    pResult.toVector(result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IPerformanceMetric>>
VBox::IPerformanceCollector::enableMetrics(
        const std::vector<std::u16string> &metricNames,
        const std::vector<COMPtr<COMUnknown>> &objects)
{
    COM_ArrayProxy<::IPerformanceMetric *> pResult;
    COM_StringArrayProxy pMetricNames(metricNames);
    COM_ArrayProxy<COMUnknown::COM_Ifc *> pObjects(objects);

    auto rc = get_IFC()->EnableMetrics(COM_ArrayParameter(pMetricNames),
                COM_ArrayParameter(pObjects), COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IPerformanceMetric>> result;
    pResult.toVector(result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IPerformanceMetric>>
VBox::IPerformanceCollector::disableMetrics(
        const std::vector<std::u16string> &metricNames,
        const std::vector<COMPtr<COMUnknown>> &objects)
{
    COM_ArrayProxy<::IPerformanceMetric *> pResult;
    COM_StringArrayProxy pMetricNames(metricNames);
    COM_ArrayProxy<COMUnknown::COM_Ifc *> pObjects(objects);

    auto rc = get_IFC()->DisableMetrics(COM_ArrayParameter(pMetricNames),
                COM_ArrayParameter(pObjects), COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IPerformanceMetric>> result;
    pResult.toVector(result);
    return result;
}

std::vector<int32_t> VBox::IPerformanceCollector::queryMetricsData(
        const std::vector<std::u16string> &metricNames,
        const std::vector<COMPtr<COMUnknown>> &objects,
        std::vector<std::u16string> *returnMetricNames,
        std::vector<COMPtr<COMUnknown>> *returnObjects,
        std::vector<std::u16string> *returnUnits,
        std::vector<uint32_t> *returnScales,
        std::vector<uint32_t> *returnSequenceNumbers,
        std::vector<uint32_t> *returnDataIndices,
        std::vector<uint32_t> *returnDataLengths)
{
    COM_ArrayProxy<COM_Long> pResult;
    COM_StringArrayProxy pMetricNames(metricNames);
    COM_ArrayProxy<COMUnknown::COM_Ifc *> pObjects(objects);
    COM_StringArrayProxy pReturnMetricNames;
    COM_ArrayProxy<COMUnknown::COM_Ifc *> pReturnObjects;
    COM_StringArrayProxy pReturnUnits;
    COM_ArrayProxy<COM_ULong> pReturnScales;
    COM_ArrayProxy<COM_ULong> pReturnSequenceNumbers;
    COM_ArrayProxy<COM_ULong> pReturnDataIndices;
    COM_ArrayProxy<COM_ULong> pReturnDataLengths;

    auto rc = get_IFC()->QueryMetricsData(COM_ArrayParameter(pMetricNames),
                COM_ArrayParameter(pObjects),
                COM_ArrayParameterRef(pReturnMetricNames),
                COM_ArrayParameterRef(pReturnObjects),
                COM_ArrayParameterRef(pReturnUnits),
                COM_ArrayParameterRef(pReturnScales),
                COM_ArrayParameterRef(pReturnSequenceNumbers),
                COM_ArrayParameterRef(pReturnDataIndices),
                COM_ArrayParameterRef(pReturnDataLengths),
                COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    if (returnMetricNames)
        pReturnMetricNames.toVector(*returnMetricNames);
    if (returnObjects)
        pReturnObjects.toVector(*returnObjects);
    if (returnUnits)
        pReturnUnits.toVector(*returnUnits);
    if (returnScales)
        pReturnScales.toVector(*returnScales);
    if (returnSequenceNumbers)
        pReturnSequenceNumbers.toVector(*returnSequenceNumbers);
    if (returnDataIndices)
        pReturnDataIndices.toVector(*returnDataIndices);
    if (returnDataLengths)
        pReturnDataLengths.toVector(*returnDataLengths);
    std::vector<int32_t> result;
    pResult.toVector(result);
    return result;
}
