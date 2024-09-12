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
COM_WRAP_IFC(IGraphicsAdapter)

VBox::GraphicsControllerType VBox::IGraphicsAdapter::graphicsControllerType() const
{
    COM_Enum(::GraphicsControllerType) result;
    COM_GetValue(get_IFC(), GraphicsControllerType, result);
    return static_cast<GraphicsControllerType>(result);
}

void VBox::IGraphicsAdapter::set_graphicsControllerType(GraphicsControllerType value)
{
    COM_SetValue(get_IFC(), GraphicsControllerType,
                 static_cast<COM_Enum(::GraphicsControllerType)>(value));
}

uint32_t VBox::IGraphicsAdapter::VRAMSize() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), VRAMSize, result);
    return static_cast<uint32_t>(result);
}

void VBox::IGraphicsAdapter::set_VRAMSize(uint32_t value)
{
    COM_SetValue(get_IFC(), VRAMSize, value);
}

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
bool VBox::IGraphicsAdapter::accelerate3DEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accelerate3DEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IGraphicsAdapter::set_accelerate3DEnabled(bool value)
{
    COM_SetValue(get_IFC(), Accelerate3DEnabled, value);
}

bool VBox::IGraphicsAdapter::accelerate2DVideoEnabled() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Accelerate2DVideoEnabled, result);
    return static_cast<bool>(result);
}

void VBox::IGraphicsAdapter::set_accelerate2DVideoEnabled(bool value)
{
    COM_SetValue(get_IFC(), Accelerate2DVideoEnabled, value);
}
#endif

uint32_t VBox::IGraphicsAdapter::monitorCount() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), MonitorCount, result);
    return static_cast<uint32_t>(result);
}

void VBox::IGraphicsAdapter::set_monitorCount(uint32_t value)
{
    COM_SetValue(get_IFC(), MonitorCount, value);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
void VBox::IGraphicsAdapter::setFeature(GraphicsFeature feature, bool enabled)
{
    auto cFeature = static_cast<COM_Enum(::GraphicsFeature)>(feature);
    auto cEnabled = static_cast<COM_Bool>(enabled);

    auto rc = get_IFC()->SetFeature(cFeature, cEnabled);
    COM_ERROR_CHECK(rc);
}

bool VBox::IGraphicsAdapter::isFeatureEnabled(GraphicsFeature feature) const
{
    COM_Bool cResult = false;
    auto cFeature = static_cast<COM_Enum(::GraphicsFeature)>(feature);

    auto rc = get_IFC()->IsFeatureEnabled(cFeature, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}
#endif

#endif
