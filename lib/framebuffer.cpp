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

COM_WRAP_IFC(IFramebuffer)

uint32_t VBox::IFramebuffer::width() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Width, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFramebuffer::height() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Height, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFramebuffer::bitsPerPixel() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), BitsPerPixel, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IFramebuffer::bytesPerLine() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), BytesPerLine, result);
    return static_cast<uint32_t>(result);
}

VBox::BitmapFormat VBox::IFramebuffer::pixelFormat() const
{
    COM_Enum(::BitmapFormat) result;
    COM_GetValue(get_IFC(), PixelFormat, result);
    return static_cast<BitmapFormat>(result);
}

uint32_t VBox::IFramebuffer::heightReduction() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), HeightReduction, result);
    return static_cast<uint32_t>(result);
}

VBox::COMPtr<VBox::IFramebufferOverlay> VBox::IFramebuffer::overlay() const
{
    COMPtr<IFramebufferOverlay> result;
    COM_GetValue_Wrap(get_IFC(), Overlay, result);
    return result;
}

int64_t VBox::IFramebuffer::winId() const
{
    COM_Long64 result;
    COM_GetValue(get_IFC(), WinId, result);
    return static_cast<int64_t>(result);
}

std::vector<VBox::FramebufferCapabilities> VBox::IFramebuffer::capabilities() const
{
    std::vector<FramebufferCapabilities> result;
    COM_GetArray(get_IFC(), Capabilities, COM_Enum(::FramebufferCapabilities),
                 result);
    return result;
}

void VBox::IFramebuffer::notifyUpdate(uint32_t x, uint32_t y, uint32_t width,
        uint32_t height)
{
    auto rc = get_IFC()->NotifyUpdate(x, y, width, height);
    COM_ERROR_CHECK(rc);
}

void VBox::IFramebuffer::notifyUpdateImage(uint32_t x, uint32_t y,
        uint32_t width, uint32_t height, const std::vector<uint8_t> &image)
{
    COM_ArrayProxy<COM_Byte> pImage(image);

    auto rc = get_IFC()->NotifyUpdateImage(x, y, width, height,
                COM_ArrayParameter(pImage));
    COM_ERROR_CHECK(rc);
}

void VBox::IFramebuffer::notifyChange(uint32_t screenId, uint32_t xOrigin,
        uint32_t yOrigin, uint32_t width, uint32_t height)
{
    auto rc = get_IFC()->NotifyChange(screenId, xOrigin, yOrigin, width, height);
    COM_ERROR_CHECK(rc);
}

bool VBox::IFramebuffer::videoModeSupported(uint32_t width, uint32_t height,
        uint32_t bpp)
{
    COM_Bool cResult;

    auto rc = get_IFC()->VideoModeSupported(width, height, bpp, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

uint32_t VBox::IFramebuffer::getVisibleRegion(uint8_t *rectangles,
        uint32_t count)
{
    COM_ULong cResult;

    auto rc = get_IFC()->GetVisibleRegion(reinterpret_cast<COM_Byte *>(rectangles),
                count, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<uint32_t>(cResult);
}

void VBox::IFramebuffer::setVisibleRegion(uint8_t *rectangles, uint32_t count)
{
    auto rc = get_IFC()->SetVisibleRegion(reinterpret_cast<COM_Byte *>(rectangles),
                count);
    COM_ERROR_CHECK(rc);
}

void VBox::IFramebuffer::processVHWACommand(uint8_t *command
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(5, 2, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 36) )
      , int32_t enmCmd, bool fromGuest
#endif
        )
{
    auto rc = get_IFC()->ProcessVHWACommand(reinterpret_cast<COM_Byte *>(command)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(5, 2, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 36) )
                                          , enmCmd, fromGuest
#endif
    );
    COM_ERROR_CHECK(rc);
}

void VBox::IFramebuffer::notify3DEvent(uint32_t type,
        const std::vector<uint8_t> &data)
{
    COM_ArrayProxy<COM_Byte> pData(data);

    auto rc = get_IFC()->Notify3DEvent(type, COM_ArrayParameter(pData));
    COM_ERROR_CHECK(rc);
}
