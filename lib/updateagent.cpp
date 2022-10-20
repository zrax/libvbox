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
COM_WRAP_IFC(IUpdateAgent)
COM_WRAP_IFC(IHostUpdateAgent)

std::u16string VBox::IUpdateAgent::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IUpdateAgent::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

uint32_t VBox::IUpdateAgent::order() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Order, result);
    return static_cast<uint32_t>(result);
}

std::vector<std::u16string> VBox::IUpdateAgent::dependsOn() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), DependsOn, result);
    return result;
}

std::u16string VBox::IUpdateAgent::version() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Version, result);
    return result;
}

std::u16string VBox::IUpdateAgent::downloadUrl() const
{
    std::u16string result;
    COM_GetString(get_IFC(), DownloadUrl, result);
    return result;
}

std::u16string VBox::IUpdateAgent::webUrl() const
{
    std::u16string result;
    COM_GetString(get_IFC(), WebUrl, result);
    return result;
}

std::u16string VBox::IUpdateAgent::releaseNotes() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ReleaseNotes, result);
    return result;
}

bool VBox::IUpdateAgent::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IUpdateAgent::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, static_cast<COM_Bool>(value));
}

bool VBox::IUpdateAgent::hidden() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Hidden, result);
    return static_cast<bool>(result);
}

VBox::UpdateState VBox::IUpdateAgent::state() const
{
    COM_Enum(::UpdateState) result;
    COM_GetValue(get_IFC(), State, result);
    return static_cast<UpdateState>(result);
}

uint32_t VBox::IUpdateAgent::checkFrequency() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), CheckFrequency, result);
    return result;
}

void VBox::IUpdateAgent::set_checkFrequency(uint32_t value)
{
    COM_SetValue(get_IFC(), CheckFrequency, value);
}

VBox::UpdateChannel VBox::IUpdateAgent::channel() const
{
    COM_Enum(::UpdateChannel) result;
    COM_GetValue(get_IFC(), Channel, result);
    return static_cast<UpdateChannel>(result);
}

void VBox::IUpdateAgent::set_channel(UpdateChannel value)
{
    COM_SetValue(get_IFC(), Channel,
                 static_cast<COM_Enum(::UpdateChannel)>(value));
}

std::u16string VBox::IUpdateAgent::repositoryURL() const
{
    std::u16string result;
    COM_GetString(get_IFC(), RepositoryURL, result);
    return result;
}

void VBox::IUpdateAgent::set_repositoryURL(const std::u16string &value)
{
    COM_SetString(get_IFC(), RepositoryURL, value);
}

std::u16string VBox::IUpdateAgent::lastCheckDate() const
{
    std::u16string result;
    COM_GetString(get_IFC(), LastCheckDate, result);
    return result;
}

uint32_t VBox::IUpdateAgent::checkCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), CheckCount, result);
    return result;
}

bool VBox::IUpdateAgent::isCheckNeeded() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), IsCheckNeeded, result);
    return static_cast<bool>(result);
}

std::vector<VBox::UpdateChannel> VBox::IUpdateAgent::supportedChannels() const
{
    std::vector<UpdateChannel> result;
    COM_GetArray(get_IFC(), SupportedChannels, COM_Enum(::UpdateChannel), result);
    return result;
}

VBox::COMPtr<VBox::IProgress> VBox::IUpdateAgent::checkFor()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->CheckFor(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IUpdateAgent::download()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Download(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IUpdateAgent::install()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Install(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IUpdateAgent::rollback()
{
    auto rc = get_IFC()->Rollback();
    COM_ERROR_CHECK(rc);
}
#endif
