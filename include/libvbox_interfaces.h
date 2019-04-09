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

#ifndef _LIBVBOX_INTERFACES_H
#define _LIBVBOX_INTERFACES_H

#include "libvbox_vboxsdk_types.h"
#include "libvbox_wrap.h"

namespace VBox
{
    class LIBVBOX_API IVirtualBoxErrorInfo : public WrapErrorInfo
    {
    public:
        COM_WRAPPED(::IVirtualBoxErrorInfo)

        // Attributes
        VBox_PROPERTY_RO(int32_t, resultCode);
        VBox_PROPERTY_RO(int32_t, resultDetail);
        VBox_PROPERTY_RO(std::wstring, interfaceID);
        VBox_PROPERTY_RO(std::wstring, component);
        VBox_PROPERTY_RO(std::wstring, text);
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, next);
    };

    class LIBVBOX_API INATNetwork : public COMWrapBase
    {
    public:
        COM_WRAPPED(::INATNetwork)

        // TODO
    };

    class LIBVBOX_API IDHCPServer : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDHCPServer)

        // TODO
    };

    class LIBVBOX_API IVirtualBox : public COMWrapBase
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
                /* in */ DeviceType aADeviceTypeType);
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

    class LIBVBOX_API IVFSExplorer : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVFSExplorer)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API ICertificate : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ICertificate)

        // TODO
    };
#endif

    class LIBVBOX_API IAppliance : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IAppliance)

        // TODO
    };

    class LIBVBOX_API IVirtualSystemDescription : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVirtualSystemDescription)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IUnattended : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUnattended)

        // TODO
    };
#endif

    class LIBVBOX_API IInternalMachineControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IInternalMachineControl)

        // TODO
    };

    class LIBVBOX_API IBIOSSettings : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IBIOSSettings)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingScreenSettings : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IRecordingScreenSettings)

        // TODO
    };

    class LIBVBOX_API IRecordingSettings : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IRecordingSettings)

        // TODO
    };
#endif

    class LIBVBOX_API IPCIAddress : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IPCIAddress)

        // TODO
    };

    class LIBVBOX_API IPCIDeviceAttachment : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IPCIDeviceAttachment)

        // TODO
    };

    class LIBVBOX_API IMachine : public COMWrapBase
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

    class LIBVBOX_API IEmulatedUSB : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IEmulatedUSB)

        // TODO
    };

    class LIBVBOX_API IVRDEServerInfo : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVRDEServerInfo)

        // TODO
    };

    class LIBVBOX_API IConsole : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IConsole)

        // TODO
    };

    class LIBVBOX_API IHostNetworkInterface : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IHostNetworkInterface)

        // TODO
    };

    class LIBVBOX_API IHostVideoInputDevice : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IHostVideoInputDevice)

        // TODO
    };

    class LIBVBOX_API IHost : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IHost)

        // TODO
    };

    class LIBVBOX_API ISystemProperties : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISystemProperties)

        // TODO
    };

    class LIBVBOX_API IGuestOSType : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuestOSType)

        // TODO
    };

    class LIBVBOX_API IAdditionsFacility : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IAdditionsFacility)

        // TODO
    };

    class LIBVBOX_API IDnDBase : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDnDBase)

        // TODO
    };

    class LIBVBOX_API IDnDSource : public IDnDBase
    {
    public:
        COM_WRAPPED(::IDnDSource)

        // TODO
    };

    class LIBVBOX_API IGuestDnDSource : public IDnDSource
    {
    public:
        COM_WRAPPED(::IGuestDnDSource)

        // TODO
    };

    class LIBVBOX_API IDnDTarget : public IDnDBase
    {
    public:
        COM_WRAPPED(::IDnDTarget)

        // TODO
    };

    class LIBVBOX_API IGuestDnDTarget : public IDnDTarget
    {
    public:
        COM_WRAPPED(::IGuestDnDTarget)

        // TODO
    };

    class LIBVBOX_API IGuestSession : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuestSession)

        // TODO
    };

    class LIBVBOX_API IProcess : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IProcess)

        // TODO
    };

    class LIBVBOX_API IGuestProcess : public IProcess
    {
    public:
        COM_WRAPPED(::IGuestProcess)

        // TODO
    };

    class LIBVBOX_API IDirectory : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDirectory)

        // TODO
    };

    class LIBVBOX_API IGuestDirectory : public IDirectory
    {
    public:
        COM_WRAPPED(::IGuestDirectory)

        // TODO
    };

    class LIBVBOX_API IFile : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IFile)

        // TODO
    };

    class LIBVBOX_API IGuestFile : public IFile
    {
    public:
        COM_WRAPPED(::IGuestFile)

        // TODO
    };

    class LIBVBOX_API IFsObjInfo : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IFsObjInfo)

        // TODO
    };

    class LIBVBOX_API IGuestFsObjInfo : public IFsObjInfo
    {
    public:
        COM_WRAPPED(::IGuestFsObjInfo)

        // TODO
    };

    class LIBVBOX_API IGuest : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuest)

        // TODO
    };

    class LIBVBOX_API IProgress : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IProgress)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IInternalProgressControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IInternalProgressControl)

        // TODO
    };
#endif

    class LIBVBOX_API ISnapshot : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISnapshot)

        // TODO
    };

    class LIBVBOX_API IMediumAttachment : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMediumAttachment)

        // TODO
    };

    class LIBVBOX_API IMedium : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMedium)

        // TODO
    };

    class LIBVBOX_API IMediumFormat : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMediumFormat)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IDataStream : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDataStream)

        // TODO
    };

    class LIBVBOX_API IMediumIO : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMediumIO)

        // TODO
    };
#endif

    class LIBVBOX_API IToken : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IToken)

        // TODO
    };

    class LIBVBOX_API IKeyboard : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IKeyboard)

        // TODO
    };

    class LIBVBOX_API IMousePointerShape : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMousePointerShape)

        // TODO
    };

    class LIBVBOX_API IMouse : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMouse)

        // TODO
    };

    class LIBVBOX_API IDisplaySourceBitmap : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDisplaySourceBitmap)

        // TODO
    };

    class LIBVBOX_API IFramebuffer : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IFramebuffer)

        // TODO
    };

    class LIBVBOX_API IFramebufferOverlay : public IFramebuffer
    {
    public:
        COM_WRAPPED(::IFramebufferOverlay)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API IGuestScreenInfo : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuestScreenInfo)

        // TODO
    };
#endif

    class LIBVBOX_API IDisplay : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDisplay)

        // TODO
    };

    class LIBVBOX_API INetworkAdapter : public COMWrapBase
    {
    public:
        COM_WRAPPED(::INetworkAdapter)

        // TODO
    };

    class LIBVBOX_API ISerialPort : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISerialPort)

        // TODO
    };

    class LIBVBOX_API IParallelPort : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IParallelPort)

        // TODO
    };

    class LIBVBOX_API IMachineDebugger : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMachineDebugger)

        // TODO
    };

    class LIBVBOX_API IUSBDeviceFilters : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUSBDeviceFilters)

        // TODO
    };

    class LIBVBOX_API IUSBController : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUSBController)

        // TODO
    };

    class LIBVBOX_API IUSBDevice : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUSBDevice)

        // TODO
    };

    class LIBVBOX_API IUSBDeviceFilter : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUSBDeviceFilter)

        // TODO
    };

    class LIBVBOX_API IHostUSBDevice : public IUSBDevice
    {
    public:
        COM_WRAPPED(::IHostUSBDevice)

        // TODO
    };

    class LIBVBOX_API IHostUSBDeviceFilter : public IUSBDeviceFilter
    {
    public:
        COM_WRAPPED(::IHostUSBDeviceFilter)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API IUSBProxyBackend : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUSBProxyBackend)

        // TODO
    };
#endif

    class LIBVBOX_API IAudioAdapter : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IAudioAdapter)

        // TODO
    };

    class LIBVBOX_API IVRDEServer : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVRDEServer)

        // TODO
    };

    class LIBVBOX_API ISharedFolder : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISharedFolder)

        // TODO
    };

    class LIBVBOX_API IInternalSessionControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IInternalSessionControl)

        // TODO
    };

    class LIBVBOX_API ISession : public COMWrapBase
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

    class LIBVBOX_API IStorageController : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IStorageController)

        // TODO
    };

    class LIBVBOX_API IPerformanceMetric : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IPerformanceMetric)

        // TODO
    };

    class LIBVBOX_API IPerformanceCollector : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IPerformanceCollector)

        // TODO
    };

    class LIBVBOX_API INATEngine : public COMWrapBase
    {
    public:
        COM_WRAPPED(::INATEngine)

        // TODO
    };

    class LIBVBOX_API IExtPackPlugIn : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IExtPackPlugIn)

        // TODO
    };

    class LIBVBOX_API IExtPackBase : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IExtPackBase)

        // TODO
    };

    class LIBVBOX_API IExtPack : public IExtPackBase
    {
    public:
        COM_WRAPPED(::IExtPack)

        // TODO
    };

    class LIBVBOX_API IExtPackFile : public IExtPackBase
    {
    public:
        COM_WRAPPED(::IExtPackFile)

        // TODO
    };

    class LIBVBOX_API IExtPackManager : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IExtPackManager)

        // TODO
    };

    class LIBVBOX_API IBandwidthGroup : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IBandwidthGroup)

        // TODO
    };

    class LIBVBOX_API IBandwidthControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IBandwidthControl)

        // TODO
    };

    class LIBVBOX_API IVirtualBoxClient : public COMWrapBase
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

    class LIBVBOX_API IEventSource : public COMWrapBase
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

    class LIBVBOX_API IEventListener : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IEventListener)

        // TODO
    };

    class LIBVBOX_API IEvent : public COMWrapBase
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

    class LIBVBOX_API IReusableEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IReusableEvent)

        // TODO
    };

    class LIBVBOX_API IMachineEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMachineEvent)

        // TODO
    };

    class LIBVBOX_API IMachineStateChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IMachineStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IMachineDataChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IMachineDataChangedEvent)

        // TODO
    };

    class LIBVBOX_API IMediumRegisteredEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMediumRegisteredEvent)

        // TODO
    };

    class LIBVBOX_API IMediumConfigChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMediumConfigChangedEvent)

        // TODO
    };

    class LIBVBOX_API IMachineRegisteredEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IMachineRegisteredEvent)

        // TODO
    };

    class LIBVBOX_API ISessionStateChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::ISessionStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestPropertyChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IGuestPropertyChangedEvent)

        // TODO
    };

    class LIBVBOX_API ISnapshotEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::ISnapshotEvent)

        // TODO
    };

    class LIBVBOX_API ISnapshotTakenEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotTakenEvent)

        // TODO
    };

    class LIBVBOX_API ISnapshotDeletedEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotDeletedEvent)

        // TODO
    };

    class LIBVBOX_API ISnapshotRestoredEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotRestoredEvent)

        // TODO
    };

    class LIBVBOX_API ISnapshotChangedEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotChangedEvent)

        // TODO
    };

    class LIBVBOX_API IMousePointerShapeChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMousePointerShapeChangedEvent)

        // TODO
    };

    class LIBVBOX_API IMouseCapabilityChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMouseCapabilityChangedEvent)

        // TODO
    };

    class LIBVBOX_API IKeyboardLedsChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IKeyboardLedsChangedEvent)

        // TODO
    };

    class LIBVBOX_API IStateChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IAdditionsStateChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IAdditionsStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API INetworkAdapterChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::INetworkAdapterChangedEvent)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IAudioAdapterChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IAudioAdapterChangedEvent)

        // TODO
    };
#endif

    class LIBVBOX_API ISerialPortChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ISerialPortChangedEvent)

        // TODO
    };

    class LIBVBOX_API IParallelPortChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IParallelPortChangedEvent)

        // TODO
    };

    class LIBVBOX_API IStorageControllerChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IStorageControllerChangedEvent)

        // TODO
    };

    class LIBVBOX_API IMediumChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMediumChangedEvent)

        // TODO
    };

    class LIBVBOX_API IClipboardModeChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IClipboardModeChangedEvent)

        // TODO
    };

    class LIBVBOX_API IDnDModeChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IDnDModeChangedEvent)

        // TODO
    };

    class LIBVBOX_API ICPUChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ICPUChangedEvent)

        // TODO
    };

    class LIBVBOX_API ICPUExecutionCapChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ICPUExecutionCapChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestKeyboardEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestKeyboardEvent)

        // TODO
    };

    class LIBVBOX_API IGuestMouseEvent : public IReusableEvent
    {
    public:
        COM_WRAPPED(::IGuestMouseEvent)

        // TODO
    };

    class LIBVBOX_API IGuestMultiTouchEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestMultiTouchEvent)

        // TODO
    };

    class LIBVBOX_API IGuestSessionEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestSessionEvent)

        // TODO
    };

    class LIBVBOX_API IGuestSessionStateChangedEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestSessionStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestSessionRegisteredEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestSessionRegisteredEvent)

        // TODO
    };

    class LIBVBOX_API IGuestProcessEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessEvent)

        // TODO
    };

    class LIBVBOX_API IGuestProcessRegisteredEvent : public IGuestProcessEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessRegisteredEvent)

        // TODO
    };

    class LIBVBOX_API IGuestProcessStateChangedEvent : public IGuestProcessEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestProcessIOEvent : public IGuestProcessEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessIOEvent)

        // TODO
    };

    class LIBVBOX_API IGuestProcessInputNotifyEvent : public IGuestProcessIOEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessInputNotifyEvent)

        // TODO
    };

    class LIBVBOX_API IGuestProcessOutputEvent : public IGuestProcessIOEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessOutputEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestFileEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileRegisteredEvent : public IGuestFileEvent
    {
    public:
        COM_WRAPPED(::IGuestFileRegisteredEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileStateChangedEvent : public IGuestFileEvent
    {
    public:
        COM_WRAPPED(::IGuestFileStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileIOEvent : public IGuestFileEvent
    {
    public:
        COM_WRAPPED(::IGuestFileIOEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileOffsetChangedEvent : public IGuestFileIOEvent
    {
    public:
        COM_WRAPPED(::IGuestFileOffsetChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileReadEvent : public IGuestFileIOEvent
    {
    public:
        COM_WRAPPED(::IGuestFileReadEvent)

        // TODO
    };

    class LIBVBOX_API IGuestFileWriteEvent : public IGuestFileIOEvent
    {
    public:
        COM_WRAPPED(::IGuestFileWriteEvent)

        // TODO
    };

    class LIBVBOX_API IVRDEServerChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVRDEServerChangedEvent)

        // TODO
    };

    class LIBVBOX_API IVRDEServerInfoChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVRDEServerInfoChangedEvent)

        // TODO
    };

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IVideoCaptureChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVideoCaptureChangedEvent)

        // TODO
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IRecordingChangedEvent)

        // TODO
    };
#endif

    class LIBVBOX_API IUSBControllerChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IUSBControllerChangedEvent)

        // TODO
    };

    class LIBVBOX_API IUSBDeviceStateChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IUSBDeviceStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API ISharedFolderChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ISharedFolderChangedEvent)

        // TODO
    };

    class LIBVBOX_API IRuntimeErrorEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IRuntimeErrorEvent)

        // TODO
    };

    class LIBVBOX_API IEventSourceChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IEventSourceChangedEvent)

        // TODO
    };

    class LIBVBOX_API IExtraDataChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IExtraDataChangedEvent)

        // TODO
    };

    class LIBVBOX_API IVetoEvent : public IEvent
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

    class LIBVBOX_API IExtraDataCanChangeEvent : public IVetoEvent
    {
    public:
        COM_WRAPPED(::IExtraDataCanChangeEvent)

        // TODO
    };

    class LIBVBOX_API ICanShowWindowEvent : public IVetoEvent
    {
    public:
        COM_WRAPPED(::ICanShowWindowEvent)

        // TODO
    };

    class LIBVBOX_API IShowWindowEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IShowWindowEvent)

        // TODO
    };

    class LIBVBOX_API INATRedirectEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::INATRedirectEvent)

        // TODO
    };

    class LIBVBOX_API IHostPCIDevicePlugEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IHostPCIDevicePlugEvent)

        // TODO
    };

    class LIBVBOX_API IVBoxSVCAvailabilityChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVBoxSVCAvailabilityChangedEvent)

        // TODO
    };

    class LIBVBOX_API IBandwidthGroupChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IBandwidthGroupChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestMonitorChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestMonitorChangedEvent)

        // TODO
    };

    class LIBVBOX_API IGuestUserStateChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestUserStateChangedEvent)

        // TODO
    };

    class LIBVBOX_API IStorageDeviceChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IStorageDeviceChangedEvent)

        // TODO
    };

    class LIBVBOX_API INATNetworkChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::INATNetworkChangedEvent)

        // TODO
    };

    class LIBVBOX_API INATNetworkStartStopEvent : public INATNetworkChangedEvent
    {
    public:
        COM_WRAPPED(::INATNetworkStartStopEvent)

        // TODO
    };

    class LIBVBOX_API INATNetworkAlterEvent : public INATNetworkChangedEvent
    {
    public:
        COM_WRAPPED(::INATNetworkAlterEvent)

        // TODO
    };

    class LIBVBOX_API INATNetworkCreationDeletionEvent : public INATNetworkAlterEvent
    {
    public:
        COM_WRAPPED(::INATNetworkCreationDeletionEvent)

        // TODO
    };

    class LIBVBOX_API INATNetworkSettingEvent : public INATNetworkAlterEvent
    {
    public:
        COM_WRAPPED(::INATNetworkSettingEvent)

        // TODO
    };

    class LIBVBOX_API INATNetworkPortForwardEvent : public INATNetworkAlterEvent
    {
    public:
        COM_WRAPPED(::INATNetworkPortForwardEvent)

        // TODO
    };

    class LIBVBOX_API IHostNameResolutionConfigurationChangeEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IHostNameResolutionConfigurationChangeEvent)

        // TODO
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IProgressEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IProgressEvent)

        // TODO
    };

    class LIBVBOX_API IProgressPercentageChangedEvent : public IProgressEvent
    {
    public:
        COM_WRAPPED(::IProgressPercentageChangedEvent)

        // TODO
    };

    class LIBVBOX_API IProgressTaskCompletedEvent : public IProgressEvent
    {
    public:
        COM_WRAPPED(::IProgressTaskCompletedEvent)

        // TODO
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API ICursorPositionChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ICursorPositionChangedEvent)

        // TODO
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API ICloudClient : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ICloudClient)

        // TODO
    };

    class LIBVBOX_API ICloudProfile : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ICloudProfile)

        // TODO
    };

    class LIBVBOX_API ICloudProvider : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ICloudProvider)

        // TODO
    };

    class LIBVBOX_API ICloudProviderManager : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ICloudProviderManager)

        // TODO
    };
#endif
}

#endif /* _LIBVBOX_INTERFACES_H */
