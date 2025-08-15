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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
COM_WRAP_IFC(IRecordingSettings)

bool VBox::IRecordingSettings::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IRecordingSettings::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

std::vector<VBox::COMPtr<VBox::IRecordingScreenSettings>>
VBox::IRecordingSettings::screens() const
{
    std::vector<COMPtr<IRecordingScreenSettings>> result;
    COM_GetArray_Wrap(get_IFC(), Screens, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox::COMPtr<VBox::IProgress> VBox::IRecordingSettings::progress() const
{
    COMPtr<IProgress> result;
    COM_GetValue_Wrap(get_IFC(), Progress, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
bool VBox::IRecordingSettings::paused() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Paused, result);
    return static_cast<bool>(result);
}

void VBox::IRecordingSettings::set_paused(bool value)
{
    COM_SetValue(get_IFC(), Paused, value);
}
#endif

VBox::COMPtr<VBox::IRecordingScreenSettings>
VBox::IRecordingSettings::getScreenSettings(uint32_t screenId)
{
    ::IRecordingScreenSettings *cResult = nullptr;

    auto rc = get_IFC()->GetScreenSettings(screenId, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IRecordingScreenSettings>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox::COMPtr<VBox::IProgress> VBox::IRecordingSettings::start()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->Start(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
void VBox::IRecordingSettings::resume()
{
    auto rc = get_IFC()->Resume();
    COM_ERROR_CHECK(rc);
}

#endif

#endif
