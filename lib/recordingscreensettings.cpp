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
COM_WRAP_IFC(IRecordingScreenSettings)

// Attributes
uint32_t VBox::IRecordingScreenSettings::id() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Id, result);
    return static_cast<uint32_t>(result);
}

bool VBox::IRecordingScreenSettings::enabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Enabled, result);
    return static_cast<bool>(result);
}

void VBox::IRecordingScreenSettings::set_enabled(bool value)
{
    COM_SetValue(get_IFC(), Enabled, value);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
uint32_t VBox::IRecordingScreenSettings::features() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Features, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_features(uint32_t value)
{
    COM_SetValue(get_IFC(), Features, value);
}
#else
std::vector<VBox::RecordingFeature> VBox::IRecordingScreenSettings::features() const
{
    std::vector<RecordingFeature> result;
    COM_GetArray(get_IFC(), Features, COM_Enum(::RecordingFeature), result);
    return result;
}

void VBox::IRecordingScreenSettings::set_features(const std::vector<RecordingFeature> &value)
{
    COM_SetArray(get_IFC(), Features, COM_Enum(::RecordingFeature), value);
}
#endif

VBox::RecordingDestination VBox::IRecordingScreenSettings::destination() const
{
    COM_Enum(::RecordingDestination) result;
    COM_GetValue(get_IFC(), Destination, result);
    return static_cast<RecordingDestination>(result);
}

void VBox::IRecordingScreenSettings::set_destination(RecordingDestination value)
{
    COM_SetValue(get_IFC(), Destination,
                 static_cast<COM_Enum(::RecordingDestination)>(value));
}

std::u16string VBox::IRecordingScreenSettings::filename() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Filename, result);
    return result;
}

void VBox::IRecordingScreenSettings::set_filename(const std::u16string &value)
{
    COM_SetString(get_IFC(), Filename, value);
}

uint32_t VBox::IRecordingScreenSettings::maxTime() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxTime, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_maxTime(uint32_t value)
{
    COM_SetValue(get_IFC(), MaxTime, value);
}

uint32_t VBox::IRecordingScreenSettings::maxFileSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MaxFileSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_maxFileSize(uint32_t value)
{
    COM_SetValue(get_IFC(), MaxFileSize, value);
}

std::u16string VBox::IRecordingScreenSettings::options() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Options, result);
    return result;
}

void VBox::IRecordingScreenSettings::set_options(const std::u16string &value)
{
    COM_SetString(get_IFC(), Options, value);
}

VBox::RecordingAudioCodec VBox::IRecordingScreenSettings::audioCodec() const
{
    COM_Enum(::RecordingAudioCodec) result;
    COM_GetValue(get_IFC(), AudioCodec, result);
    return static_cast<RecordingAudioCodec>(result);
}

void VBox::IRecordingScreenSettings::set_audioCodec(RecordingAudioCodec value)
{
    COM_SetValue(get_IFC(), AudioCodec,
                 static_cast<COM_Enum(::RecordingAudioCodec)>(value));
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::RecordingRateControlMode VBox::IRecordingScreenSettings::audioRateControlMode() const
{
    COM_Enum(::RecordingRateControlMode) result;
    COM_GetValue(get_IFC(), AudioRateControlMode, result);
    return static_cast<RecordingRateControlMode>(result);
}

void VBox::IRecordingScreenSettings::set_audioRateControlMode(RecordingRateControlMode value)
{
    COM_SetValue(get_IFC(), AudioRateControlMode,
                 static_cast<COM_Enum(::RecordingRateControlMode)>(value));
}

VBox::RecordingCodecDeadline VBox::IRecordingScreenSettings::audioDeadline() const
{
    COM_Enum(::RecordingCodecDeadline) result;
    COM_GetValue(get_IFC(), AudioDeadline, result);
    return static_cast<RecordingCodecDeadline>(result);
}

void VBox::IRecordingScreenSettings::set_audioDeadline(RecordingCodecDeadline value)
{
    COM_SetValue(get_IFC(), AudioDeadline,
                 static_cast<COM_Enum(::RecordingCodecDeadline)>(value));
}
#endif

uint32_t VBox::IRecordingScreenSettings::audioHz() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AudioHz, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_audioHz(uint32_t value)
{
    COM_SetValue(get_IFC(), AudioHz, value);
}

uint32_t VBox::IRecordingScreenSettings::audioBits() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AudioBits, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_audioBits(uint32_t value)
{
    COM_SetValue(get_IFC(), AudioBits, value);
}

uint32_t VBox::IRecordingScreenSettings::audioChannels() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), AudioChannels, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_audioChannels(uint32_t value)
{
    COM_SetValue(get_IFC(), AudioChannels, value);
}

VBox::RecordingVideoCodec VBox::IRecordingScreenSettings::videoCodec() const
{
    COM_Enum(::RecordingVideoCodec) result;
    COM_GetValue(get_IFC(), VideoCodec, result);
    return static_cast<RecordingVideoCodec>(result);
}

void VBox::IRecordingScreenSettings::set_videoCodec(RecordingVideoCodec value)
{
    COM_SetValue(get_IFC(), VideoCodec,
                 static_cast<COM_Enum(::RecordingVideoCodec)>(value));
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::RecordingCodecDeadline VBox::IRecordingScreenSettings::videoDeadline() const
{
    COM_Enum(::RecordingCodecDeadline) result;
    COM_GetValue(get_IFC(), VideoDeadline, result);
    return static_cast<RecordingCodecDeadline>(result);
}

void VBox::IRecordingScreenSettings::set_videoDeadline(RecordingCodecDeadline value)
{
    COM_SetValue(get_IFC(), VideoDeadline,
                 static_cast<COM_Enum(::RecordingCodecDeadline)>(value));
}
#endif

uint32_t VBox::IRecordingScreenSettings::videoWidth() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoWidth, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_videoWidth(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoWidth, value);
}

uint32_t VBox::IRecordingScreenSettings::videoHeight() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoHeight, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_videoHeight(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoHeight, value);
}

uint32_t VBox::IRecordingScreenSettings::videoRate() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoRate, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_videoRate(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoRate, value);
}

VBox::RecordingRateControlMode
VBox::IRecordingScreenSettings::videoRateControlMode() const
{
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
    COM_Enum(::RecordingVideoRateControlMode) result;
#else
    COM_Enum(::RecordingRateControlMode) result;
#endif
    COM_GetValue(get_IFC(), VideoRateControlMode, result);
    return static_cast<RecordingRateControlMode>(result);
}

void VBox::IRecordingScreenSettings::set_videoRateControlMode(
        RecordingRateControlMode value)
{
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
    COM_SetValue(get_IFC(), VideoRateControlMode,
                 static_cast<COM_Enum(::RecordingVideoRateControlMode)>(value));
#else
    COM_SetValue(get_IFC(), VideoRateControlMode,
                 static_cast<COM_Enum(::RecordingRateControlMode)>(value));
#endif
}

uint32_t VBox::IRecordingScreenSettings::videoFPS() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VideoFPS, result);
    return static_cast<uint32_t>(result);
}

void VBox::IRecordingScreenSettings::set_videoFPS(uint32_t value)
{
    COM_SetValue(get_IFC(), VideoFPS, value);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
VBox::RecordingVideoScalingMethod
VBox::IRecordingScreenSettings::videoScalingMethod() const
{
    COM_Enum(::RecordingVideoScalingMethod) result;
    COM_GetValue(get_IFC(), VideoScalingMethod, result);
    return static_cast<RecordingVideoScalingMethod>(result);
}

void VBox::IRecordingScreenSettings::set_videoScalingMethod(
        RecordingVideoScalingMethod value)
{
    COM_SetValue(get_IFC(), VideoScalingMethod,
                 static_cast<COM_Enum(::RecordingVideoScalingMethod)>(value));
}
#else
VBox::RecordingVideoScalingMode
VBox::IRecordingScreenSettings::videoScalingMode() const
{
    COM_Enum(::RecordingVideoScalingMode) result;
    COM_GetValue(get_IFC(), VideoScalingMode, result);
    return static_cast<RecordingVideoScalingMode>(result);
}

void VBox::IRecordingScreenSettings::set_videoScalingMode(
        RecordingVideoScalingMode value)
{
    COM_SetValue(get_IFC(), VideoScalingMode,
                 static_cast<COM_Enum(::RecordingVideoScalingMode)>(value));
}
#endif

bool VBox::IRecordingScreenSettings::isFeatureEnabled(RecordingFeature feature)
{
    COM_Bool cResult;
    auto cFeature = static_cast<COM_Enum(::RecordingFeature)>(feature);

    auto rc = get_IFC()->IsFeatureEnabled(cFeature, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}
#endif
