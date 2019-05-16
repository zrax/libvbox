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

COM_WRAP_IFC(IGuest)

std::u16string VBox::IGuest::OSTypeId() const
{
    std::u16string result;
    COM_GetString(get_IFC(), OSTypeId, result);
    return result;
}

VBox::AdditionsRunLevelType VBox::IGuest::additionsRunLevel() const
{
    COM_Enum(::AdditionsRunLevelType) result;
    COM_GetValue(get_IFC(), AdditionsRunLevel, result);
    return static_cast<AdditionsRunLevelType>(result);
}

std::u16string VBox::IGuest::additionsVersion() const
{
    std::u16string result;
    COM_GetString(get_IFC(), AdditionsVersion, result);
    return result;
}

uint32_t VBox::IGuest::additionsRevision() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AdditionsRevision, result);
    return static_cast<uint32_t>(result);
}

VBox::COMPtr<VBox::IGuestDnDSource> VBox::IGuest::dnDSource() const
{
    COMPtr<IGuestDnDSource> result;
    COM_GetValue_Wrap(get_IFC(), DnDSource, result);
    return result;
}

VBox::COMPtr<VBox::IGuestDnDTarget> VBox::IGuest::dnDTarget() const
{
    COMPtr<IGuestDnDTarget> result;
    COM_GetValue_Wrap(get_IFC(), DnDTarget, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IGuest::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IAdditionsFacility>> VBox::IGuest::facilities() const
{
    std::vector<COMPtr<IAdditionsFacility>> result;
    COM_GetArray_Wrap(get_IFC(), Facilities, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IGuestSession>> VBox::IGuest::sessions() const
{
    std::vector<COMPtr<IGuestSession>> result;
    COM_GetArray_Wrap(get_IFC(), Sessions, result);
    return result;
}

uint32_t VBox::IGuest::memoryBalloonSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MemoryBalloonSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IGuest::set_memoryBalloonSize(uint32_t value)
{
    COM_SetValue(get_IFC(), MemoryBalloonSize, value);
}

uint32_t VBox::IGuest::statisticsUpdateInterval() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), StatisticsUpdateInterval, result);
    return static_cast<uint32_t>(result);
}

void VBox::IGuest::set_statisticsUpdateInterval(uint32_t value)
{
    COM_SetValue(get_IFC(), StatisticsUpdateInterval, value);
}

void VBox::IGuest::internalGetStatistics(uint32_t *cpuUser, uint32_t *cpuKernel,
        uint32_t *cpuIdle, uint32_t *memTotal, uint32_t *memFree,
        uint32_t *memBalloon, uint32_t *memShared, uint32_t *memCache,
        uint32_t *pagedTotal, uint32_t *memAllocTotal, uint32_t *memFreeTotal,
        uint32_t *memBalloonTotal, uint32_t *memSharedTotal)
{
    COM_ULong cCpuUser, cCpuKernel, cCpuIdle;
    COM_ULong cMemTotal, cMemFree, cMemBalloon, cMemShared, cMemCache;
    COM_ULong cPagedTotal, cMemAllocTotal, cMemFreeTotal;
    COM_ULong cMemBalloonTotal, cMemSharedTotal;

    auto rc = get_IFC()->InternalGetStatistics(&cCpuUser, &cCpuKernel,
                &cCpuIdle, &cMemTotal, &cMemFree, &cMemBalloon, &cMemShared,
                &cMemCache, &cPagedTotal, &cMemAllocTotal, &cMemFreeTotal,
                &cMemBalloonTotal, &cMemSharedTotal);
    COM_ERROR_CHECK(rc);

    if (cpuUser)
        *cpuUser = static_cast<uint32_t>(cCpuUser);
    if (cpuKernel)
        *cpuKernel = static_cast<uint32_t>(cCpuKernel);
    if (cpuIdle)
        *cpuIdle = static_cast<uint32_t>(cCpuIdle);
    if (memTotal)
        *memTotal = static_cast<uint32_t>(cMemTotal);
    if (memFree)
        *memFree = static_cast<uint32_t>(cMemFree);
    if (memBalloon)
        *memBalloon = static_cast<uint32_t>(cMemBalloon);
    if (memShared)
        *memShared = static_cast<uint32_t>(cMemShared);
    if (memCache)
        *memCache = static_cast<uint32_t>(cMemCache);
    if (pagedTotal)
        *pagedTotal = static_cast<uint32_t>(cPagedTotal);
    if (memAllocTotal)
        *memAllocTotal = static_cast<uint32_t>(cMemAllocTotal);
    if (memFreeTotal)
        *memFreeTotal = static_cast<uint32_t>(cMemFreeTotal);
    if (memBalloonTotal)
        *memBalloonTotal = static_cast<uint32_t>(cMemBalloonTotal);
    if (memSharedTotal)
        *memSharedTotal = static_cast<uint32_t>(cMemSharedTotal);
}

VBox::AdditionsFacilityStatus VBox::IGuest::getFacilityStatus(
        AdditionsFacilityType facility, int64_t *timestamp)
{
    COM_Enum(::AdditionsFacilityStatus) cResult;
    auto cFacility = static_cast<COM_Enum(::AdditionsFacilityType)>(facility);
    COM_Long64 cTimestamp;

    auto rc = get_IFC()->GetFacilityStatus(cFacility, &cTimestamp, &cResult);
    COM_ERROR_CHECK(rc);

    if (timestamp)
        *timestamp = static_cast<int64_t>(cTimestamp);
    return static_cast<AdditionsFacilityStatus>(cResult);
}

bool VBox::IGuest::getAdditionsStatus(AdditionsRunLevelType level)
{
    COM_Bool cResult;
    auto cLevel = static_cast<COM_Enum(::AdditionsRunLevelType)>(level);

    auto rc = get_IFC()->GetAdditionsStatus(cLevel, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

void VBox::IGuest::setCredentials(const std::u16string &userName,
        const std::u16string &password, const std::u16string &domain,
        bool allowInteractiveLogon)
{
    COM_StringProxy pUserName(userName);
    COM_StringProxy pPassword(password);
    COM_StringProxy pDomain(domain);

    auto rc = get_IFC()->SetCredentials(pUserName.m_text, pPassword.m_text,
                pDomain.m_text, allowInteractiveLogon);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IGuestSession> VBox::IGuest::createSession(
        const std::u16string &user, const std::u16string &password,
        const std::u16string &domain, const std::u16string &sessionName)
{
    ::IGuestSession *cResult = nullptr;
    COM_StringProxy pUser(user);
    COM_StringProxy pPassword(password);
    COM_StringProxy pDomain(domain);
    COM_StringProxy pSessionName(sessionName);

    auto rc = get_IFC()->CreateSession(pUser.m_text, pPassword.m_text,
                pDomain.m_text, pSessionName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestSession>::wrap(cResult);
}

std::vector<VBox::COMPtr<VBox::IGuestSession>> VBox::IGuest::findSession(
        const std::u16string &sessionName)
{
    COM_ArrayProxy<::IGuestSession *> pResult;
    COM_StringProxy pSessionName(sessionName);

    auto rc = get_IFC()->FindSession(pSessionName.m_text, COM_ArrayParameterRef(pResult));
    COM_ERROR_CHECK(rc);

    std::vector<COMPtr<IGuestSession>> result;
    pResult.toVector(result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IGuest::updateGuestAdditions(
        const std::u16string &source, const std::vector<std::u16string> &arguments,
        const std::vector<AdditionsUpdateFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringArrayProxy pArguments(arguments);
    COM_ArrayProxy<COM_Enum(::AdditionsUpdateFlag)> pFlags(flags);

    auto rc = get_IFC()->UpdateGuestAdditions(pSource.m_text, COM_ArrayParameter(pArguments),
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
