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

#if defined(VBOX_XPCOM)
#   include <nsIServiceManager.h>
#   include <nsEventQueueUtils.h>
#endif

namespace VBox
{
    class API_Private
    {
    public:
        API_Private()
        {
#if defined(VBOX_XPCOM)
            nsresult rc = NS_InitXPCOM2(getter_AddRefs(m_serviceManager), nullptr, nullptr);
            COM_ERROR_CHECK(rc);

            rc = NS_GetMainEventQ(getter_AddRefs(m_eventQueue));
            COM_ERROR_CHECK(rc);

            rc = NS_GetComponentManager(getter_AddRefs(m_componentManager));
            COM_ERROR_CHECK(rc);
#elif defined(VBOX_MSCOM)
            CoInitialize(nullptr);
#endif
        }

        ~API_Private()
        {
#if defined(VBOX_XPCOM)
            m_eventQueue->ProcessPendingEvents();

            // Reset the smart pointers to remove remaining references
            m_componentManager = nullptr;
            m_eventQueue = nullptr;
            m_serviceManager = nullptr;
            NS_ShutdownXPCOM(nullptr);
#elif defined(VBOX_MSCOM)
            CoUninitialize();
#endif
        }

        COMPtr<IVirtualBoxClient> createVirtualBoxClient()
        {
            ::IVirtualBoxClient *vboxClient;

#if defined(VBOX_XPCOM)
            nsresult rc = m_componentManager->CreateInstanceByContractID(
                            NS_VIRTUALBOXCLIENT_CONTRACTID,
                            nullptr, IID_IVirtualBoxClient,
                            reinterpret_cast<void **>(&vboxClient));
            COM_ERROR_CHECK(rc);
#elif defined(VBOX_MSCOM)
            HRESULT rc = CoCreateInstance(CLSID_VirtualBoxClient, nullptr,
                            CLSCTX_INPROC_SERVER, IID_IVirtualBoxClient,
                            reinterpret_cast<void **>(&vboxClient));
            COM_ERROR_CHECK(rc);
#endif

            return COMPtr<IVirtualBoxClient>::wrap(vboxClient);
        }

    private:
#if defined(VBOX_XPCOM)
        nsCOMPtr<nsIServiceManager> m_serviceManager;
        nsCOMPtr<nsIEventQueue> m_eventQueue;
        nsCOMPtr<nsIComponentManager> m_componentManager;
#endif
    };

    static API_Private *get_API()
    {
        static API_Private s_priv;
        return &s_priv;
    }
}

std::string VBox::COMError::error_message(uint32_t rc)
{
    // TODO: Get a string representation of the error itself.
    // I can't find how to do that with XPCOM currently...
    char buffer[40];
    snprintf(buffer, sizeof(buffer), "COM Error %#x", rc);
    return buffer;
}

uint32_t VBox::COMWrapBase::AddRef()
{
#if defined(VBOX_XPCOM)
    return _get_IFC<nsISupports>()->AddRef();
#elif defined(VBOX_MSCOM)
    return _get_IFC<::IUnknown>()->AddRef();
#endif
}

uint32_t VBox::COMWrapBase::Release()
{
#if defined(VBOX_XPCOM)
    return _get_IFC<nsISupports>()->Release();
#elif defined(VBOX_MSCOM)
    return _get_IFC<::IUnknown>()->Release();
#endif
}

void VBox::COMWrapBase::_QueryInterface(const void *iid, void **pContainer)
{
#if defined(VBOX_XPCOM)
    REFNSIID riid = *reinterpret_cast<const nsIID *>(iid);
    auto rc = _get_IFC<nsISupports>()->QueryInterface(riid, pContainer);
#elif defined(VBOX_MSCOM)
    REFIID riid = *reinterpret_cast<const IID *>(iid);
    auto rc = _get_IFC<::IUnknown>()->QueryInterface(riid, pContainer);
#endif

    if (rc == E_NOINTERFACE) {
        *pContainer = nullptr;
        return;
    }
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IVirtualBoxClient> VBox::API::virtualBoxClient()
{
    return get_API()->createVirtualBoxClient();
}
