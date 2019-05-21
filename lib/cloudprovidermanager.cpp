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
COM_WRAP_IFC(ICloudProviderManager)

std::vector<VBox::COMPtr<VBox::ICloudProvider>>
VBox::ICloudProviderManager::providers() const
{
    std::vector<COMPtr<ICloudProvider>> result;
    COM_GetArray_Wrap(get_IFC(), Providers, result);
    return result;
}

VBox::COMPtr<VBox::ICloudProvider> VBox::ICloudProviderManager::getProviderById(
        const std::u16string &providerId)
{
    ::ICloudProvider *cResult = nullptr;
    COM_StringProxy pProviderId(providerId);

    auto rc = get_IFC()->GetProviderById(pProviderId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ICloudProvider>::wrap(cResult);
}

VBox::COMPtr<VBox::ICloudProvider> VBox::ICloudProviderManager::getProviderByShortName(
        const std::u16string &providerName)
{
    ::ICloudProvider *cResult = nullptr;
    COM_StringProxy pProviderName(providerName);

    auto rc = get_IFC()->GetProviderByShortName(pProviderName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ICloudProvider>::wrap(cResult);
}

VBox::COMPtr<VBox::ICloudProvider> VBox::ICloudProviderManager::getProviderByName(
        const std::u16string &providerName)
{
    ::ICloudProvider *cResult = nullptr;
    COM_StringProxy pProviderName(providerName);

    auto rc = get_IFC()->GetProviderByName(pProviderName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ICloudProvider>::wrap(cResult);
}
#endif
