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

COM_WRAP_IFC(IDisplaySourceBitmap)

uint32_t VBox::IDisplaySourceBitmap::screenId() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ScreenId, result);
    return static_cast<uint32_t>(result);
}

void VBox::IDisplaySourceBitmap::queryBitmapInfo(uint8_t **address,
        uint32_t *width, uint32_t *height, uint32_t *bitsPerPixel,
        uint32_t *bytesPerLine, BitmapFormat *bitmapFormat)
{
    COM_Byte *cAddress = nullptr;
    COM_ULong cWidth, cHeight, cBitsPerPixel, cBytesPerLine;
    COM_Enum(::BitmapFormat) cBitmapFormat;

    auto rc = get_IFC()->QueryBitmapInfo(&cAddress, &cWidth, &cHeight,
                &cBitsPerPixel, &cBytesPerLine, &cBitmapFormat);
    COM_ERROR_CHECK(rc);

    if (address)
        *address = reinterpret_cast<uint8_t *>(cAddress);
    if (width)
        *width = static_cast<uint32_t>(cWidth);
    if (height)
        *height = static_cast<uint32_t>(cHeight);
    if (bitsPerPixel)
        *bitsPerPixel = static_cast<uint32_t>(cBitsPerPixel);
    if (bytesPerLine)
        *bytesPerLine = static_cast<uint32_t>(cBytesPerLine);
    if (bitmapFormat)
        *bitmapFormat = static_cast<BitmapFormat>(cBitmapFormat);
}
