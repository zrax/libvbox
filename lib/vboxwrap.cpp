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
#   include <nsIExceptionService.h>
#endif

static bool isApiCompatible(int sdkVersion, int apiVersion)
{
    static const struct { int vLow, vHigh; } compatibility[] = {
        { VBox_MAKE_VERSION(5, 0, 0), VBox_MAKE_VERSION(5, 0, 8) },
        { VBox_MAKE_VERSION(5, 0, 10), VBox_MAKE_VERSION(5, 0, 40) },

        { VBox_MAKE_VERSION(5, 1, 0), VBox_MAKE_VERSION(5, 1, 34) },
        { VBox_MAKE_VERSION(5, 1, 36), VBox_MAKE_VERSION(5, 1, 38) },

        { VBox_MAKE_VERSION(5, 2, 0), VBox_MAKE_VERSION(5, 2, 8) },
        { VBox_MAKE_VERSION(5, 2, 10), VBox_MAKE_VERSION(5, 2, 42) },

        { VBox_MAKE_VERSION(6, 0, 0), VBox_MAKE_VERSION(6, 0, 22) },

        { VBox_MAKE_VERSION(6, 1, 0), VBox_MAKE_VERSION(6, 1, 10) },
    };

    if (sdkVersion > apiVersion)
        return false;

    for (const auto &r : compatibility) {
        if (sdkVersion >= r.vLow && sdkVersion <= r.vHigh) {
            return apiVersion >= r.vLow && apiVersion <= r.vHigh;
        }
    }

    // Handle cases not in the above list by requiring an exact match
    return sdkVersion == apiVersion;
}

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
            ::IVirtualBoxClient *vboxClient = nullptr;

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

            auto wrapClient = COMPtr<IVirtualBoxClient>::wrap(vboxClient);
            if (!wrapClient)
                throw std::runtime_error("Failed to create IVirtualBoxClient");

            // Check running VirtualBox version against our SDK version
            auto vbox = wrapClient->virtualBox();
            if (!vbox)
                throw std::runtime_error("Failed to get IVirtualBox object for version check");
            const int apiVersion = vbox->APIRevision() >> 40;
            if (!isApiCompatible(VirtualBoxSDK_VERSION, apiVersion)) {
                char msg[256];
                std::snprintf(msg, sizeof(msg),
                              "VirtualBox SDK %d.%d.%d is not compatible with running VirtualBox API %d.%d.%d",
                              (VirtualBoxSDK_VERSION >> 16) & 0xFF,
                              (VirtualBoxSDK_VERSION >> 8) & 0xFF,
                              VirtualBoxSDK_VERSION & 0xFF,
                              (apiVersion >> 16) & 0xFF,
                              (apiVersion >> 8) & 0xFF,
                              apiVersion & 0xFF);
                throw std::runtime_error(msg);
            }

            return wrapClient;
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

const void *VBox::COMUnknown::get_IID()
{
#if defined(VBOX_XPCOM)
    return reinterpret_cast<const void *>(&NS_GET_IID(nsISupports));
#elif defined(VBOX_MSCOM)
    return reinterpret_cast<const void *>(&IID_IUnknown);
#endif
}

uint32_t VBox::COMUnknown::AddRef()
{
    return get_IFC()->AddRef();
}

uint32_t VBox::COMUnknown::Release()
{
    return get_IFC()->Release();
}

void VBox::COMUnknown::_QueryInterface(const void *iid, void **pContainer)
{
#if defined(VBOX_XPCOM)
    REFNSIID riid = *reinterpret_cast<const nsIID *>(iid);
    auto rc = get_IFC()->QueryInterface(riid, pContainer);
#elif defined(VBOX_MSCOM)
    REFIID riid = *reinterpret_cast<const IID *>(iid);
    auto rc = get_IFC()->QueryInterface(riid, pContainer);
#endif

    if (rc == E_NOINTERFACE) {
        *pContainer = nullptr;
        return;
    }
    COM_ERROR_CHECK(rc);
}

const void *VBox::COMErrorInfo::get_IID()
{
#if defined(VBOX_XPCOM)
    return reinterpret_cast<const void *>(&NS_GET_IID(nsIException));
#elif defined(VBOX_MSCOM)
    return reinterpret_cast<const void *>(&IID_IErrorInfo);
#endif
}

std::u16string VBox::COMErrorInfo::message() const
{
    std::u16string result;

#if defined(VBOX_XPCOM)
    // The exception message is UTF-8 on XPCOM
    char *messageText = nullptr;
    auto rc = get_IFC()->GetMessage(&messageText);
    COM_ERROR_CHECK(rc);
    result = VBox::utf8ToUtf16(messageText);
    nsMemory::Free(reinterpret_cast<void *>(messageText));
#elif defined(VBOX_MSCOM)
    COM_StringProxy messageText;
    auto rc = get_IFC()->GetDescription(&messageText.m_text);
    COM_ERROR_CHECK(rc);
    result = messageText.toString();
#endif

    return result;
}

VBox::COMPtr<VBox::IVirtualBoxClient> VBox::virtualBoxClient()
{
    return get_API()->createVirtualBoxClient();
}

VBox::COMPtr<VBox::COMErrorInfo> VBox::currentError()
{
#if defined(VBOX_XPCOM)
    nsresult rc;
    nsCOMPtr<nsIExceptionService> esvc = do_GetService(NS_EXCEPTIONSERVICE_CONTRACTID, &rc);
    if (NS_FAILED(rc))
        return nullptr;

    nsCOMPtr<nsIExceptionManager> emgr;
    rc = esvc->GetCurrentExceptionManager(getter_AddRefs(emgr));
    if (NS_FAILED(rc))
        return nullptr;

    nsIException *ex = nullptr;
    rc = emgr->GetCurrentException(&ex);
    if (NS_FAILED(rc) || !ex)
        return nullptr;

    auto result = VBox::COMPtr<VBox::COMErrorInfo>::wrap(ex);
    emgr->SetCurrentException(nullptr);
    return result;
#elif defined(VBOX_MSCOM)
    IErrorInfo *err = nullptr;
    auto rc = GetErrorInfo(0, &err);
    if (FAILED(rc) || !err)
        return nullptr;

    return VBox::COMPtr<VBox::COMErrorInfo>::wrap(err);
#endif
}
