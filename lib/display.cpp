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

COM_WRAP_IFC(IDisplay)

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
std::vector<VBox::COMPtr<VBox::IGuestScreenInfo>> VBox::IDisplay::guestScreenLayout() const
{
    std::vector<COMPtr<IGuestScreenInfo>> result;
    COM_GetArray_Wrap(get_IFC(), GuestScreenLayout, result);
    return result;
}
#endif

void VBox::IDisplay::getScreenResolution(uint32_t screenId, uint32_t *width,
        uint32_t *height, uint32_t *bitsPerPixel, int32_t *xOrigin,
        int32_t *yOrigin, GuestMonitorStatus *guestMonitorStatus)
{
    COM_ULong cWidth;
    COM_ULong cHeight;
    COM_ULong cBitsPerPixel;
    COM_Long cXOrigin;
    COM_Long cYOrigin;
    COM_Enum(::GuestMonitorStatus) cGuestMonitorStatus;

    auto rc = get_IFC()->GetScreenResolution(screenId, &cWidth, &cHeight,
                    &cBitsPerPixel, &cXOrigin, &cYOrigin, &cGuestMonitorStatus);
    COM_ERROR_CHECK(rc);

    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    if (bitsPerPixel)
        *bitsPerPixel = static_cast<uint32_t>(cBitsPerPixel);
    if (xOrigin)
        *xOrigin = static_cast<int32_t>(cXOrigin);
    if (yOrigin)
        *yOrigin = static_cast<int32_t>(cYOrigin);
    if (guestMonitorStatus)
        *guestMonitorStatus = static_cast<GuestMonitorStatus>(cGuestMonitorStatus);
}

std::u16string VBox::IDisplay::attachFramebuffer(uint32_t screenId,
        const COMPtr<IFramebuffer> &framebuffer)
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->AttachFramebuffer(screenId, framebuffer->get_IFC(),
                                           &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::IDisplay::detachFramebuffer(uint32_t screenId, const std::u16string &id)
{
    COM_StringProxy pId(id);

    auto rc = get_IFC()->DetachFramebuffer(screenId, pId.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IFramebuffer> VBox::IDisplay::queryFramebuffer(uint32_t screenId)
{
    ::IFramebuffer *cResult = nullptr;

    auto rc = get_IFC()->QueryFramebuffer(screenId, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IFramebuffer>::wrap(cResult);
}

void VBox::IDisplay::setVideoModeHint(uint32_t display, bool enabled,
        bool changeOrigin, int32_t originX, int32_t originY, uint32_t width,
        uint32_t height, uint32_t bitsPerPixel
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
      , bool notify
#endif
        )
{
    auto rc = get_IFC()->SetVideoModeHint(display, enabled, changeOrigin,
                    originX, originY, width, height, bitsPerPixel
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
                  , notify
#endif
                    );
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
void VBox::IDisplay::getVideoModeHint(uint32_t display, bool *enabled,
        bool *changeOrigin, int32_t *originX, int32_t *originY, uint32_t *width,
        uint32_t *height, uint32_t *bitsPerPixel)
{
    COM_Bool cEnabled;
    COM_Bool cChangeOrigin;
    COM_Long cOriginX;
    COM_Long cOriginY;
    COM_ULong cWidth;
    COM_ULong cHeight;
    COM_ULong cBitsPerPixel;

    auto rc = get_IFC()->GetVideoModeHint(display, &cEnabled, &cChangeOrigin,
                &cOriginX, &cOriginY, &cWidth, &cHeight, &cBitsPerPixel);
    COM_ERROR_CHECK(rc);

    if (enabled)
        *enabled = static_cast<bool>(cEnabled);
    if (changeOrigin)
        *changeOrigin = static_cast<bool>(cChangeOrigin);
    if (originX)
        *originX = static_cast<int32_t>(cOriginX);
    if (originY)
        *originY = static_cast<int32_t>(cOriginY);
    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    if (bitsPerPixel)
        *bitsPerPixel = static_cast<uint32_t>(cBitsPerPixel);
}
#endif

void VBox::IDisplay::setSeamlessMode(bool enabled)
{
    auto rc = get_IFC()->SetSeamlessMode(enabled);
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::takeScreenShot(uint32_t screenId, uint8_t *address,
        uint32_t width, uint32_t height, BitmapFormat bitmapFormat)
{
    auto cBitmapFormat = static_cast<COM_Enum(::BitmapFormat)>(bitmapFormat);

    auto rc = get_IFC()->TakeScreenShot(screenId, address, width, height,
                                        cBitmapFormat);
    COM_ERROR_CHECK(rc);
}

std::vector<uint8_t> VBox::IDisplay::takeScreenShotToArray(uint32_t screenId,
        uint32_t width, uint32_t height, BitmapFormat bitmapFormat)
{
    COM_ArrayProxy<COM_Byte> cResult;
    auto cBitmapFormat = static_cast<COM_Enum(::BitmapFormat)>(bitmapFormat);

    auto rc = get_IFC()->TakeScreenShotToArray(screenId, width, height,
                    cBitmapFormat, COM_ArrayParameterRef(cResult));
    COM_ERROR_CHECK(rc);

    std::vector<uint8_t> result;
    cResult.toVector(result);
    return result;
}

void VBox::IDisplay::drawToScreen(uint32_t screenId, uint8_t *address,
        uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    auto rc = get_IFC()->DrawToScreen(screenId, address, x, y, width, height);
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::invalidateAndUpdate()
{
    auto rc = get_IFC()->InvalidateAndUpdate();
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::invalidateAndUpdateScreen(uint32_t screenId)
{
    auto rc = get_IFC()->InvalidateAndUpdateScreen(screenId);
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::completeVHWACommand(uint8_t *command)
{
    auto rc = get_IFC()->CompleteVHWACommand(command);
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::viewportChanged(uint32_t screenId, uint32_t x, uint32_t y,
        uint32_t width, uint32_t height)
{
    auto rc = get_IFC()->ViewportChanged(screenId, x, y, width, height);
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::querySourceBitmap(uint32_t screenId,
        COMPtr<IDisplaySourceBitmap> *displaySourceBitmap)
{
    ::IDisplaySourceBitmap *cDisplaySourceBitmap = nullptr;

    auto rc = get_IFC()->QuerySourceBitmap(screenId, &cDisplaySourceBitmap);
    COM_ERROR_CHECK(rc);

    if (displaySourceBitmap)
        *displaySourceBitmap = COMPtr<IDisplaySourceBitmap>::wrap(cDisplaySourceBitmap);
    else if (cDisplaySourceBitmap)
        cDisplaySourceBitmap->Release();
}

void VBox::IDisplay::notifyScaleFactorChange(uint32_t screenId,
        uint32_t u32ScaleFactorWMultiplied, uint32_t u32ScaleFactorHMultiplied)
{
    auto rc = get_IFC()->NotifyScaleFactorChange(screenId, u32ScaleFactorWMultiplied,
                                                 u32ScaleFactorHMultiplied);
    COM_ERROR_CHECK(rc);
}

void VBox::IDisplay::notifyHiDPIOutputPolicyChange(bool fUnscaledHiDPI)
{
    auto rc = get_IFC()->NotifyHiDPIOutputPolicyChange(fUnscaledHiDPI);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
void VBox::IDisplay::setScreenLayout(ScreenLayoutMode screenLayoutMode,
        const std::vector<COMPtr<IGuestScreenInfo>> &guestScreenInfo)
{
    auto cScreenLayoutMode = static_cast<COM_Enum(::ScreenLayoutMode)>(screenLayoutMode);
    COM_ArrayProxy<::IGuestScreenInfo *> pGuestScreenInfo(guestScreenInfo);

    auto rc = get_IFC()->SetScreenLayout(cScreenLayoutMode,
                                        COM_ArrayParameter(pGuestScreenInfo));
    COM_ERROR_CHECK(rc);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
void VBox::IDisplay::detachScreens(const std::vector<int32_t> &screenIds)
{
    COM_ArrayProxy<COM_Long> pScreenIds(screenIds);

    auto rc = get_IFC()->DetachScreens(COM_ArrayParameter(pScreenIds));
    COM_ERROR_CHECK(rc);
}
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IGuestScreenInfo> VBox::IDisplay::createGuestScreenInfo(
        uint32_t display, GuestMonitorStatus status, bool primary,
        bool changeOrigin, int32_t originX, int32_t originY,
        uint32_t width, uint32_t height, uint32_t bitsPerPixel)
{
    ::IGuestScreenInfo *cResult = nullptr;
    auto cStatus = static_cast<COM_Enum(::GuestMonitorStatus)>(status);

    auto rc = get_IFC()->CreateGuestScreenInfo(display, cStatus, primary,
                    changeOrigin, originX, originY, width, height,
                    bitsPerPixel, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestScreenInfo>::wrap(cResult);
}
#endif
