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

#ifndef _LIBVBOX_H
#define _LIBVBOX_H

#include "libvbox_vboxsdk_types.h"

#include <string>
#include <vector>
#include <stdexcept>

#define VBox_PROPERTY_RO(type, name)            \
    type name() const;

#define VBox_PROPERTY_RW_V(type, name)          \
    type name() const;                          \
    void set_##name(type value);

#define VBox_PROPERTY_RW_R(type, name)          \
    type name() const;                          \
    void set_##name(const type &value);

namespace VBox
{
    class COMError : public std::runtime_error
    {
    public:
        COMError(uint32_t rc)
            : std::runtime_error(error_message(rc)), m_rc(rc) { }

        uint32_t error_code() const { return m_rc; }

        static std::string error_message(uint32_t rc);

    private:
        uint32_t m_rc;
    };

    class COMWrapBase
    {
    public:
        template <class Ifc>
        Ifc *_get_IFC() const { return reinterpret_cast<Ifc *>(m_ifc); }

        template <class Ifc>
        void _set_IFC(Ifc *ifc) { m_ifc = reinterpret_cast<void *>(ifc); }

        bool _have_IFC() const { return m_ifc != nullptr; }
        void _reset() { m_ifc = nullptr; }

        uint32_t AddRef();
        uint32_t Release();

    private:
        void *m_ifc;
    };

    #define COM_WRAPPED(COMType) \
                typedef COMType COM_Ifc; \
                COMType *get_IFC() const { return _get_IFC<COMType>(); } \
                void set_IFC(COMType *ifc) { _set_IFC(ifc); }

    template <class Wrapped>
    class COMPtr
    {
    public:
        typedef Wrapped element_type;

        COMPtr() { }
        COMPtr(std::nullptr_t) { }

        COMPtr(const COMPtr<Wrapped> &other) : m_wrap(other.m_wrap)
        {
            if (m_wrap._have_IFC())
                m_wrap.AddRef();
        }

        COMPtr(COMPtr<Wrapped> &&other) : m_wrap(other.m_wrap)
        {
            other.m_wrap._reset();
        }

        COMPtr<Wrapped> &operator=(std::nullptr_t)
        {
            if (m_wrap._have_IFC())
                m_wrap.Release();
            m_wrap._reset();
            return *this;
        }

        COMPtr<Wrapped> &operator=(const COMPtr<Wrapped> &other)
        {
            if (other.m_wrap._have_IFC())
                other.m_wrap.AddRef();
            if (m_wrap._have_IFC())
                m_wrap.Release();
            m_wrap = other.m_wrap;
            return *this;
        }

        COMPtr<Wrapped> &operator=(COMPtr<Wrapped> &&other)
        {
            m_wrap = other.m_wrap;
            other.m_wrap._reset();
            return *this;
        }

        ~COMPtr()
        {
            if (m_wrap._have_IFC())
                m_wrap.Release();
        }

        template <class COM_Ifc>
        static COMPtr<Wrapped> wrap(COM_Ifc *ifc)
        {
            COMPtr<Wrapped> wrapPtr;
            wrapPtr.m_wrap.set_IFC(ifc);
            return wrapPtr;
        }

        Wrapped *operator->() { return &m_wrap; }
        Wrapped &operator*() { return m_wrap; }

        const Wrapped *operator->() const { return &m_wrap; }
        const Wrapped &operator*() const { return m_wrap; }

        operator bool() const { return m_wrap.get_IFC() != nullptr; }

    private:
        Wrapped m_wrap;
    };

    class IEvent : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IEvent)

        // Attributes
        VBox_PROPERTY_RO(VBoxEventType, type)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, source)
        VBox_PROPERTY_RO(bool, waitable)

        // Methods
        void setProcessed();
        bool waitProcessed(/* in */ int32_t timeout);
    };

    class IVetoEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVetoEvent)

        // Methods
        void addVeto(/* in */ const std::wstring &reason);
        bool isVetoed();
        std::vector<std::wstring> getVetos();
        void addApproval(/* in */ const std::wstring &reason);
        bool isApproved();
        std::vector<std::wstring> getApprovals();
    };

    class IMachine : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMachine)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IVirtualBox>, parent)
        VBox_PROPERTY_RW_R(std::vector<uint8_t>, icon)
        VBox_PROPERTY_RO(bool, accessible)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, accessError)
        VBox_PROPERTY_RW_R(std::wstring, name)
        VBox_PROPERTY_RW_R(std::wstring, description)
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RW_R(std::vector<std::wstring>, groups)
        VBox_PROPERTY_RW_R(std::wstring, OSTypeId)
        VBox_PROPERTY_RW_R(std::wstring, hardwareVersion)
        VBox_PROPERTY_RW_R(std::wstring, hardwareUUID)
        VBox_PROPERTY_RW_V(uint32_t, CPUCount)
        VBox_PROPERTY_RW_V(bool, CPUHotPlugEnabled)
        VBox_PROPERTY_RW_V(uint32_t, CPUExecutionCap)
        VBox_PROPERTY_RW_V(uint32_t, CPUIDPortabilityLevel)
        VBox_PROPERTY_RW_V(uint32_t, memorySize)
        VBox_PROPERTY_RW_V(uint32_t, memoryBalloonSize)
        VBox_PROPERTY_RW_V(bool, pageFusionEnabled)
        VBox_PROPERTY_RW_V(GraphicsControllerType, graphicsControllerType)
        VBox_PROPERTY_RW_V(uint32_t, VRAMSize)
        VBox_PROPERTY_RW_V(bool, accelerate3DEnabled)
        VBox_PROPERTY_RW_V(bool, accelerate2DVideoEnabled)
        VBox_PROPERTY_RW_V(uint32_t, monitorCount)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(bool, videoCaptureEnabled)
        VBox_PROPERTY_RW_R(std::vector<bool>, videoCaptureScreens)
        VBox_PROPERTY_RW_R(std::wstring, videoCaptureFile)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureWidth)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureHeight)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureRate)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureFPS)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureMaxTime)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureMaxFileSize)
        VBox_PROPERTY_RW_R(std::wstring, videoCaptureOptions)
#endif
        VBox_PROPERTY_RW_R(COMPtr<IBIOSSettings>, BIOSSettings)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_R(COMPtr<IRecordingSettings>, recordingSettings)
#endif
        VBox_PROPERTY_RW_V(FirmwareType, firmwareType)
        VBox_PROPERTY_RW_V(PointingHIDType, pointingHIDType)
        VBox_PROPERTY_RW_V(KeyboardHIDType, keyboardHIDType)
        VBox_PROPERTY_RW_V(bool, HPETEnabled)
        VBox_PROPERTY_RW_V(ChipsetType, chipsetType)
        VBox_PROPERTY_RW_R(std::wstring, snapshotFolder)
        VBox_PROPERTY_RO(COMPtr<IVRDEServer>, VRDEServer)
        VBox_PROPERTY_RW_V(bool, emulatedUSBCardReaderEnabled)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMediumAttachment>>, mediumAttachments)
        VBox_PROPERTY_RO(std::vector<COMPtr<IUSBController>>, USBControllers)
        VBox_PROPERTY_RO(COMPtr<IUSBDeviceFilters>, USBDeviceFilters)
        VBox_PROPERTY_RO(COMPtr<IAudioAdapter>, audioAdapter)
        VBox_PROPERTY_RO(std::vector<COMPtr<IStorageController>>, storageControllers)
        VBox_PROPERTY_RO(std::wstring, settingsFilePath)
        VBox_PROPERTY_RO(std::wstring, settingsAuxFilePath)
        VBox_PROPERTY_RO(bool, settingsModified)
        VBox_PROPERTY_RO(SessionState, sessionState)
        VBox_PROPERTY_RO(std::wstring, sessionName)
        VBox_PROPERTY_RO(uint32_t, sessionPID)
        VBox_PROPERTY_RO(MachineState, state)
        VBox_PROPERTY_RO(int64_t, lastStateChange)
        VBox_PROPERTY_RO(std::wstring, stateFilePath)
        VBox_PROPERTY_RO(std::wstring, logFolder)
        VBox_PROPERTY_RO(COMPtr<ISnapshot>, currentSnapshot)
        VBox_PROPERTY_RO(uint32_t, snapshotCount)
        VBox_PROPERTY_RO(bool, currentStateModified)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISharedFolder>>, sharedFolders)
        VBox_PROPERTY_RW_V(ClipboardMode, clipboardMode)
        VBox_PROPERTY_RW_V(DnDMode, dnDMode)
        VBox_PROPERTY_RW_V(bool, teleporterEnabled)
        VBox_PROPERTY_RW_V(uint32_t, teleporterPort)
        VBox_PROPERTY_RW_R(std::wstring, teleporterAddress)
        VBox_PROPERTY_RW_R(std::wstring, teleporterPassword)
        VBox_PROPERTY_RW_V(ParavirtProvider, paravirtProvider)
        VBox_PROPERTY_RW_V(FaultToleranceState, faultToleranceState)
        VBox_PROPERTY_RW_V(uint32_t, faultTolerancePort)
        VBox_PROPERTY_RW_R(std::wstring, faultToleranceAddress)
        VBox_PROPERTY_RW_R(std::wstring, faultTolerancePassword)
        VBox_PROPERTY_RW_V(uint32_t, faultToleranceSyncInterval)
        VBox_PROPERTY_RW_V(bool, RTCUseUTC)
        VBox_PROPERTY_RW_V(bool, IOCacheEnabled)
        VBox_PROPERTY_RW_V(uint32_t, IOCacheSize)
        VBox_PROPERTY_RO(std::vector<COMPtr<IPCIDeviceAttachment>>, PCIDeviceAssignments)
        VBox_PROPERTY_RO(COMPtr<IBandwidthControl>, bandwidthControl)
        VBox_PROPERTY_RW_V(bool, tracingEnabled)
        VBox_PROPERTY_RW_R(std::wstring, tracingConfig)
        VBox_PROPERTY_RW_V(bool, allowTracingAccessToVM)
        VBox_PROPERTY_RW_V(bool, autostartEnabled)
        VBox_PROPERTY_RW_V(uint32_t, autostartDelay)
        VBox_PROPERTY_RW_V(AutostopType, autostopType)
        VBox_PROPERTY_RW_R(std::wstring, defaultFrontend)
        VBox_PROPERTY_RO(bool, USBProxyAvailable)
        VBox_PROPERTY_RW_R(std::wstring, VMProcessPriority)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RW_R(std::wstring, paravirtDebug)
        VBox_PROPERTY_RW_R(std::wstring, CPUProfile)
#endif

        // TODO: Methods
    };

    class IVirtualBox : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVirtualBox)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, version)
        VBox_PROPERTY_RO(std::wstring, versionNormalized)
        VBox_PROPERTY_RO(uint32_t, revision)
        VBox_PROPERTY_RO(std::wstring, packageType)
        VBox_PROPERTY_RO(std::wstring, APIVersion)
        VBox_PROPERTY_RO(int64_t, APIRevision)
        VBox_PROPERTY_RO(std::wstring, homeFolder)
        VBox_PROPERTY_RO(std::wstring, settingsFilePath)
        VBox_PROPERTY_RO(COMPtr<IHost>, host)
        VBox_PROPERTY_RO(COMPtr<ISystemProperties>, systemProperties)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMachine>>, machines)
        VBox_PROPERTY_RO(std::vector<std::wstring>, machineGroups)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, hardDisks)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, DVDImages)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, floppyImages)
        VBox_PROPERTY_RO(std::vector<COMPtr<IProgress>>, progressOperations)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestOSType>>, guestOSTypes)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISharedFolder>>, sharedFolders)
        VBox_PROPERTY_RO(COMPtr<IPerformanceCollector>, performanceCollector)
        VBox_PROPERTY_RO(std::vector<COMPtr<IDHCPServer>>, DHCPServers)
        VBox_PROPERTY_RO(std::vector<COMPtr<INATNetwork>>, NATNetworks)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(COMPtr<IExtPackManager>, extensionPackManager)
        VBox_PROPERTY_RO(std::vector<std::wstring>, internalNetworks)
        VBox_PROPERTY_RO(std::vector<std::wstring>, genericNetworkDrivers)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(COMPtr<ICloudProviderManager>, cloudProviderManager)
#endif

        // Methods
        std::wstring composeMachineFilename(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &group,
                /* in */ const std::wstring &createFlags,
                /* in */ const std::wstring &baseFolder);
        COMPtr<IMachine> createMachine(
                /* in */ const std::wstring &settingsFile,
                /* in */ const std::wstring &name,
                /* in */ const std::vector<std::wstring> &groups,
                /* in */ const std::wstring &osTypeId,
                /* in */ const std::wstring &flags);
        COMPtr<IMachine> openMachine(
                /* in */ const std::wstring &settingsFile);
        void registerMachine(
                /* in */ const COMPtr<IMachine> &machine);
        COMPtr<IMachine> findMachine(
                /* in */ const std::wstring &nameOrId);
        std::vector<COMPtr<IMachine>> getMachinesByGroups(
                /* in */ const std::vector<std::wstring> &groups);
        std::vector<MachineState> getMachineStates(
                /* in */ const std::vector<COMPtr<IMachine>> &machines);
        COMPtr<IAppliance> createAppliance();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        COMPtr<IUnattended> createUnattendedInstaller();
#endif
        COMPtr<IMedium> createMedium(
                /* in */ const std::wstring &format,
                /* in */ const std::wstring &location,
                /* in */ AccessMode accessMode,
                /* in */ DeviceType aDeviceTypeType);
        COMPtr<IMedium> openMedium(
                /* in */ const std::wstring &location,
                /* in */ DeviceType deviceType,
                /* in */ AccessMode accessMode,
                /* in */ bool forceNewUuid);
        COMPtr<IGuestOSType> getGuestOSType(
                /* in */ const std::wstring &id);
        void createSharedFolder(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &hostPath,
                /* in */ bool writable,
                /* in */ bool automount,
                /* in */ const std::wstring &autoMountPoint);
        void removeSharedFolder(
                /* in */ const std::wstring &name);
        std::vector<std::wstring> getExtraDataKeys();
        std::wstring getExtraData(
                /* in */ const std::wstring &key);
        void setExtraData(
                /* in */ const std::wstring &key,
                /* in */ const std::wstring &value);
        void setSettingsSecret(
                /* in */ const std::wstring &password);
        COMPtr<IDHCPServer> createDHCPServer(
                /* in */ const std::wstring &name);
        COMPtr<IDHCPServer> findDHCPServerByNetworkName(
                /* in */ const std::wstring &name);
        void removeDHCPServer(
                /* in */ const COMPtr<IDHCPServer> &server);
        COMPtr<INATNetwork> createNATNetwork(
                /* in */ const std::wstring &networkName);
        COMPtr<INATNetwork> findNATNetworkByName(
                /* in */ const std::wstring &networkName);
        void removeNATNetwork(
                /* in */ const COMPtr<INATNetwork> &network);
        bool checkFirmwarePresent(
                /* in */  FirmwareType firmwareType,
                /* in */  const std::wstring &version,
                /* out */ std::wstring &url,
                /* out */ std::wstring &file);
    };

    class ISession : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISession)

        // Attributes
        VBox_PROPERTY_RO(SessionState, state)
        VBox_PROPERTY_RO(SessionType, type)
        VBox_PROPERTY_RW_R(std::wstring, name)
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RO(COMPtr<IConsole>, console)

        // Methods
        void unlockMachine();
    };

    class IEventSource : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IEventSource)

        // Methods
        COMPtr<IEventListener> createListener();
        COMPtr<IEventSource> createAggregator(
                /* in */ const std::vector<COMPtr<IEventSource>> &subordinates);
        void registerListener(
                /* in */ const COMPtr<IEventListener> &listener,
                /* in */ const std::vector<VBoxEventType> &interesting,
                /* in */ bool active);
        void unregisterListener(
                /* in */ const COMPtr<IEventListener> &listener);
        bool fireEvent(
                /* in */ const COMPtr<IEvent> &event,
                /* in */ int32_t timeout);
        COMPtr<IEvent> getEvent(
                /* in */ const COMPtr<IEventListener> &listener,
                /* in */ int32_t timeout);
        void eventProcessed(
                /* in */ const COMPtr<IEventListener> &listener,
                /* in */ const COMPtr<IEvent> &event);
    };

    class IVirtualBoxClient : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVirtualBoxClient)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IVirtualBox>, virtualBox)
        VBox_PROPERTY_RO(COMPtr<ISession>, session)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)

        // Methods
        void checkMachineError(/* in */ const COMPtr<IMachine> &machine);
    };

    namespace API
    {
        COMPtr<IVirtualBoxClient> virtualBoxClient();
    }
}

#endif /* _LIBVBOX_H */
