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

COM_WRAP_IFC(IMediumFormat)

std::u16string VBox::IMediumFormat::id() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Id, result);
    return result;
}

std::u16string VBox::IMediumFormat::name() const
{
    std::u16string result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

std::vector<VBox::MediumFormatCapabilities> VBox::IMediumFormat::capabilities() const
{
    std::vector<MediumFormatCapabilities> result;
    COM_GetArray(get_IFC(), Capabilities, COM_Enum(::MediumFormatCapabilities), result);
    return result;
}

void VBox::IMediumFormat::describeFileExtensions(
        std::vector<std::u16string> *extensions, std::vector<DeviceType> *types
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
        )
#else
        ) const
#endif
{
    COM_StringArrayProxy pExtensions;
    COM_ArrayProxy<COM_Enum(::DeviceType)> pTypes;

    auto rc = get_IFC()->DescribeFileExtensions(COM_ArrayParameterRef(pExtensions),
                COM_ArrayParameterRef(pTypes));
    COM_ERROR_CHECK(rc);

    if (extensions)
        pExtensions.toVector(*extensions);
    if (types)
        pTypes.toVector(*types);
}

void VBox::IMediumFormat::describeProperties(std::vector<std::u16string> *names,
        std::vector<std::u16string> *descriptions, std::vector<DataType> *types,
        std::vector<uint32_t> *flags, std::vector<std::u16string> *defaults) const
{
    COM_StringArrayProxy pNames;
    COM_StringArrayProxy pDescriptions;
    COM_ArrayProxy<COM_Enum(::DataType)> pTypes;
    COM_ArrayProxy<COM_ULong> pFlags;
    COM_StringArrayProxy pDefaults;

    auto rc = get_IFC()->DescribeProperties(COM_ArrayParameterRef(pNames),
                COM_ArrayParameterRef(pDescriptions), COM_ArrayParameterRef(pTypes),
                COM_ArrayParameterRef(pFlags), COM_ArrayParameterRef(pDefaults));
    COM_ERROR_CHECK(rc);

    if (names)
        pNames.toVector(*names);
    if (descriptions)
        pDescriptions.toVector(*descriptions);
    if (types)
        pTypes.toVector(*types);
    if (flags)
        pFlags.toVector(*flags);
    if (defaults)
        pDefaults.toVector(*defaults);
}
