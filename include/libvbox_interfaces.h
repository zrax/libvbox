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

        // Attributes
        VBox_PROPERTY_RW_R(std::wstring, networkName)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(std::wstring, network)
        VBox_PROPERTY_RO(std::wstring, gateway)
        VBox_PROPERTY_RW_V(bool, IPv6Enabled)
        VBox_PROPERTY_RW_R(std::wstring, IPv6Prefix)
        VBox_PROPERTY_RW_V(bool, advertiseDefaultIPv6RouteEnabled)
        VBox_PROPERTY_RW_V(bool, needDhcpServer)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::vector<std::wstring>, portForwardRules4)
        VBox_PROPERTY_RO(std::vector<std::wstring>, localMappings)
        VBox_PROPERTY_RW_V(int32_t, loopbackIp6)
        VBox_PROPERTY_RO(std::vector<std::wstring>, portForwardRules6)

        // Methods
        void addLocalMapping(
                /* in */ const std::wstring &hostid,
                /* in */ int32_t offset);
        void addPortForwardRule(
                /* in */ bool isIpv6,
                /* in */ const std::wstring &ruleName,
                /* in */ NATProtocol proto,
                /* in */ const std::wstring &hostIP,
                /* in */ uint16_t hostPort,
                /* in */ const std::wstring &guestIP,
                /* in */ uint16_t guestPort);
        void removePortForwardRule(
                /* in */ bool iSipv6,
                /* in */ const std::wstring &ruleName);
        void start(
                /* in */ const std::wstring &trunkType);
        void stop();
    };

    class LIBVBOX_API IDHCPServer : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDHCPServer)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RO(std::wstring, IPAddress)
        VBox_PROPERTY_RO(std::wstring, networkMask)
        VBox_PROPERTY_RO(std::wstring, networkName)
        VBox_PROPERTY_RO(std::wstring, lowerIP)
        VBox_PROPERTY_RO(std::wstring, upperIP)
        VBox_PROPERTY_RO(std::vector<std::wstring>, globalOptions)
        VBox_PROPERTY_RO(std::vector<std::wstring>, vmConfigs)

        // Methods
        void addGlobalOption(
                /* in */ DhcpOpt option,
                /* in */ const std::wstring &value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeGlobalOption(
                /* in */ DhcpOpt option);
        void removeGlobalOptions();
#endif
        void addVmSlotOption(
                /* in */ const std::wstring &vmname,
                /* in */ int32_t slot,
                /* in */ DhcpOpt option,
                /* in */ const std::wstring &value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeVmSlotOption(
                /* in */ const std::wstring& vmname,
                /* in */ int32_t slot,
                /* in */ DhcpOpt option);
#endif
        void removeVmSlotOptions(
                /* in */ const std::wstring &vmname,
                /* in */ int32_t slot);
        std::vector<std::wstring> getVmSlotOptions(
                /* in */ const std::wstring &vmname,
                /* in */ int32_t slot);
        std::vector<std::wstring> getMacOptions(
                /* in */ const std::wstring &mac);
        void setConfiguration(
                /* in */ const std::wstring &IPAddress,
                /* in */ const std::wstring &networkMask,
                /* in */ const std::wstring &FromIPAddress,
                /* in */ const std::wstring &ToIPAddress);
        void start(
                /* in */ const std::wstring &networkName,
                /* in */ const std::wstring &trunkName,
                /* in */ const std::wstring &trunkType);
        void stop();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void restart();
#endif
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
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const std::wstring &autoMountPoint
#endif
                );
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

        // Attributes
        VBox_PROPERTY_RO(std::wstring, path)
        VBox_PROPERTY_RO(VFSType, type)

        // Methods
        COMPtr<IProgress> update();
        COMPtr<IProgress> cd(
                /* in */ const std::wstring &dir);
        COMPtr<IProgress> cdUp();
        void entryList(
                /* out */ std::vector<std::wstring> &names,
                /* out */ std::vector<uint32_t> &types,
                /* out */ std::vector<int64_t> &sizes,
                /* out */ std::vector<uint32_t> &modes);
        std::vector<std::wstring> exists(
                /* in */ const std::vector<std::wstring> &names);
        COMPtr<IProgress> remove(
                /* in */ const std::vector<std::wstring> &names);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API ICertificate : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ICertificate)

        // Attributes
        VBox_PROPERTY_RO(CertificateVersion, versionNumber)
        VBox_PROPERTY_RO(std::wstring, serialNumber)
        VBox_PROPERTY_RO(std::wstring, signatureAlgorithmOID)
        VBox_PROPERTY_RO(std::wstring, signatureAlgorithmName)
        VBox_PROPERTY_RO(std::vector<std::wstring>, issuerName)
        VBox_PROPERTY_RO(std::vector<std::wstring>, subjectName)
        VBox_PROPERTY_RO(std::wstring, friendlyName)
        VBox_PROPERTY_RO(std::wstring, validityPeriodNotBefore)
        VBox_PROPERTY_RO(std::wstring, validityPeriodNotAfter)
        VBox_PROPERTY_RO(std::wstring, publicKeyAlgorithmOID)
        VBox_PROPERTY_RO(std::wstring, publicKeyAlgorithm)
        VBox_PROPERTY_RO(std::vector<uint8_t>, subjectPublicKey)
        VBox_PROPERTY_RO(std::wstring, issuerUniqueIdentifier)
        VBox_PROPERTY_RO(std::wstring, subjectUniqueIdentifier)
        VBox_PROPERTY_RO(bool, certificateAuthority)
        VBox_PROPERTY_RO(uint32_t, keyUsage)
        VBox_PROPERTY_RO(std::vector<std::wstring>, extendedKeyUsage)
        VBox_PROPERTY_RO(std::vector<uint8_t>, rawCertData)
        VBox_PROPERTY_RO(bool, selfSigned)
        VBox_PROPERTY_RO(bool, trusted)
        VBox_PROPERTY_RO(bool, expired)

        // Methods
        bool isCurrentlyExpired();
        std::wstring queryInfo(
                /* in */ int32_t what);
    };
#endif

    class LIBVBOX_API IAppliance : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IAppliance)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, path)
        VBox_PROPERTY_RO(std::vector<std::wstring>, disks)
        VBox_PROPERTY_RO(std::vector<COMPtr<IVirtualSystemDescription>>, virtualSystemDescriptions)
        VBox_PROPERTY_RO(std::vector<std::wstring>, machines)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(COMPtr<ICertificate>, certificate)
#endif

        // Methods
        COMPtr<IProgress> read(
                /* in */ const std::wstring &file);
        void interpret();
        COMPtr<IProgress> importMachines(
                /* in */ const std::vector<ImportOptions> &options);
        COMPtr<IVFSExplorer> createVFSExplorer(
                /* in */ const std::wstring &URI);
        COMPtr<IProgress> write(
                /* in */ const std::wstring &format,
                /* in */ const std::vector<ExportOptions> &options,
                /* in */ const std::wstring &path);
        std::vector<std::wstring> getWarnings();
        std::vector<std::wstring> getPasswordIds();
        std::vector<std::wstring> getMediumIdsForPasswordId(
                /* in */ const std::wstring &passwordId);
        void addPasswords(
                /* in */ const std::vector<std::wstring> &identifiers,
                /* in */ const std::vector<std::wstring> &passwords);
    };

    class LIBVBOX_API IVirtualSystemDescription : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVirtualSystemDescription)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, count)

        // Methods
        void getDescription(
                /* out */ std::vector<VirtualSystemDescriptionType> &types,
                /* out */ std::vector<std::wstring> &refs,
                /* out */ std::vector<std::wstring> &OVFValues,
                /* out */ std::vector<std::wstring> &VBoxValues,
                /* out */ std::vector<std::wstring> &extraConfigValues);
        void getDescriptionByType(
                /* in  */ VirtualSystemDescriptionType type,
                /* out */ std::vector<VirtualSystemDescriptionType> &types,
                /* out */ std::vector<std::wstring> &refs,
                /* out */ std::vector<std::wstring> &OVFValues,
                /* out */ std::vector<std::wstring> &VBoxValues,
                /* out */ std::vector<std::wstring> &extraConfigValues);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeDescriptionByType(
                /* in */ VirtualSystemDescriptionType type);
#endif
        std::vector<std::wstring> getValuesByType(
                /* in */ VirtualSystemDescriptionType type,
                /* in */ VirtualSystemDescriptionValueType which);
        void setFinalValues(
                /* in */ const std::vector<bool> &enabled,
                /* in */ const std::vector<std::wstring> &VBoxValues,
                /* in */ const std::vector<std::wstring> &extraConfigValues);
        void addDescription(
                /* in */ VirtualSystemDescriptionType type,
                /* in */ const std::wstring &VBoxValue,
                /* in */ const std::wstring &extraConfigValue);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IUnattended : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IUnattended)

        // Attributes
        VBox_PROPERTY_RW_R(std::wstring, isoPath)
        VBox_PROPERTY_RW_R(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RW_R(std::wstring, user)
        VBox_PROPERTY_RW_R(std::wstring, password)
        VBox_PROPERTY_RW_R(std::wstring, fullUserName)
        VBox_PROPERTY_RW_R(std::wstring, productKey)
        VBox_PROPERTY_RW_R(std::wstring, additionsIsoPath)
        VBox_PROPERTY_RW_V(bool, installGuestAdditions)
        VBox_PROPERTY_RW_R(std::wstring, validationKitIsoPath)
        VBox_PROPERTY_RW_V(bool, installTestExecService)
        VBox_PROPERTY_RW_R(std::wstring, timeZone)
        VBox_PROPERTY_RW_R(std::wstring, locale)
        VBox_PROPERTY_RW_R(std::wstring, language)
        VBox_PROPERTY_RW_R(std::wstring, country)
        VBox_PROPERTY_RW_R(std::wstring, proxy)
        VBox_PROPERTY_RW_R(std::wstring, packageSelectionAdjustments)
        VBox_PROPERTY_RW_R(std::wstring, hostname)
        VBox_PROPERTY_RW_R(std::wstring, auxiliaryBasePath)
        VBox_PROPERTY_RW_V(uint32_t, imageIndex)
        VBox_PROPERTY_RW_R(std::wstring, scriptTemplatePath)
        VBox_PROPERTY_RW_R(std::wstring, postInstallScriptTemplatePath)
        VBox_PROPERTY_RW_R(std::wstring, postInstallCommand)
        VBox_PROPERTY_RW_R(std::wstring, extraInstallKernelParameters)
        VBox_PROPERTY_RO(std::wstring, detectedOSTypeId)
        VBox_PROPERTY_RO(std::wstring, detectedOSVersion)
        VBox_PROPERTY_RO(std::wstring, detectedOSFlavor)
        VBox_PROPERTY_RO(std::wstring, detectedOSLanguages)
        VBox_PROPERTY_RO(std::wstring, detectedOSHints)

        // Methods
        void detectIsoOS();
        void prepare();
        void constructMedia();
        void reconfigureVM();
        void done();
    };
#endif

    class LIBVBOX_API IInternalMachineControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IInternalMachineControl)

        // Methods
        void updateState(
                /* in */ MachineState state);
        void beginPowerUp(
                /* in */ const COMPtr<IProgress> &progress);
        void endPowerUp(
                /* in */ int32_t result);
        void beginPoweringDown(
                /* out */ COMPtr<IProgress> &progress);
        void endPoweringDown(
                /* in */ int32_t result,
                /* in */ const std::wstring &errMsg);
        void runUSBDeviceFilters(
                /* in  */ const COMPtr<IUSBDevice> &device,
                /* out */ bool &matched,
                /* out */ uint32_t &maskedInterfaces);
        void captureUSBDevice(
                /* in */ const std::wstring &id,
                /* in */ const std::wstring &captureFilename);
        void detachUSBDevice(
                /* in */ const std::wstring &id,
                /* in */ bool done);
        void autoCaptureUSBDevices();
        void detachAllUSBDevices(
                /* in */ bool done);
        COMPtr<IProgress> onSessionEnd(
                /* in */ const COMPtr<ISession> &session);
        void finishOnlineMergeMedium();
        void pullGuestProperties(
                /* out */ std::vector<std::wstring> &names,
                /* out */ std::vector<std::wstring> &values,
                /* out */ std::vector<int64_t> &timestamps,
                /* out */ std::vector<std::wstring> &flags);
        void pushGuestProperty(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &value,
                /* in */ int64_t timestamp,
                /* in */ const std::wstring &flags);
        void lockMedia();
        void unlockMedia();
        COMPtr<IMediumAttachment> ejectMedium(
                /* in */ const COMPtr<IMediumAttachment> &attachment);
        void reportVmStatistics(
                /* in */ uint32_t validStats,
                /* in */ uint32_t cpuUser,
                /* in */ uint32_t cpuKernel,
                /* in */ uint32_t cpuIdle,
                /* in */ uint32_t memTotal,
                /* in */ uint32_t memFree,
                /* in */ uint32_t memBalloon,
                /* in */ uint32_t memShared,
                /* in */ uint32_t memCache,
                /* in */ uint32_t pagedTotal,
                /* in */ uint32_t memAllocTotal,
                /* in */ uint32_t memFreeTotal,
                /* in */ uint32_t memBalloonTotal,
                /* in */ uint32_t memSharedTotal,
                /* in */ uint32_t vmNetRx,
                /* in */ uint32_t vmNetTx);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 0, 10)
        void authenticateExternal(
                /* in  */ const std::vector<std::wstring> &authParams,
                /* out */ std::wstring &result);
#endif
    };

    class LIBVBOX_API IBIOSSettings : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IBIOSSettings)

        // Attributes
        VBox_PROPERTY_RW_V(bool, logoFadeIn)
        VBox_PROPERTY_RW_V(bool, logoFadeOut)
        VBox_PROPERTY_RW_V(uint32_t, logoDisplayTime)
        VBox_PROPERTY_RW_R(std::wstring, logoImagePath)
        VBox_PROPERTY_RW_V(BIOSBootMenuMode, bootMenuMode)
        VBox_PROPERTY_RW_V(bool, ACPIEnabled)
        VBox_PROPERTY_RW_V(bool, IOAPICEnabled)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RW_V(VBox::APICMode, APICMode)
#endif
        VBox_PROPERTY_RW_V(int64_t, timeOffset)
        VBox_PROPERTY_RW_V(bool, PXEDebugEnabled)
        VBox_PROPERTY_RW_R(std::wstring, nonVolatileStorageFile)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingScreenSettings : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IRecordingScreenSettings)

        // Attributes
        VBox_PROPERTY_RW_V(uint32_t, id)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, features)
        VBox_PROPERTY_RW_V(RecordingDestination, destination)
        VBox_PROPERTY_RW_R(std::wstring, filename)
        VBox_PROPERTY_RW_V(uint32_t, maxTime)
        VBox_PROPERTY_RW_V(uint32_t, maxFileSize)
        VBox_PROPERTY_RW_R(std::wstring, options)
        VBox_PROPERTY_RW_V(RecordingAudioCodec, audioCodec)
        VBox_PROPERTY_RW_V(uint32_t, audioHz)
        VBox_PROPERTY_RW_V(uint32_t, audioBits)
        VBox_PROPERTY_RW_V(uint32_t, audioChannels)
        VBox_PROPERTY_RW_V(RecordingVideoCodec, videoCodec)
        VBox_PROPERTY_RW_V(uint32_t, videoWidth)
        VBox_PROPERTY_RW_V(uint32_t, videoHeight)
        VBox_PROPERTY_RW_V(uint32_t, videoRate)
        VBox_PROPERTY_RW_V(RecordingVideoRateControlMode, videoRateControlMode)
        VBox_PROPERTY_RW_V(uint32_t, videoFPS)
        VBox_PROPERTY_RW_V(RecordingVideoScalingMethod, videoScalingMethod)

        // Methods
        bool isFeatureEnabled(
                /* in */ RecordingFeature feature);
    };

    class LIBVBOX_API IRecordingSettings : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IRecordingSettings)

        // Attributes
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RO(std::vector<COMPtr<IRecordingScreenSettings>>, screens)

        // Methods
        COMPtr<IRecordingScreenSettings> getScreenSettings(
                /* in */ uint32_t screenId);
    };
#endif

    class LIBVBOX_API IPCIAddress : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IPCIAddress)

        // Attributes
        VBox_PROPERTY_RW_V(int16_t, bus)
        VBox_PROPERTY_RW_V(int16_t, device)
        VBox_PROPERTY_RW_V(int16_t, devFunction)

        // Methods
        int32_t asLong();
        void fromLong(
                /* in */ int32_t number);
    };

    class LIBVBOX_API IPCIDeviceAttachment : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IPCIDeviceAttachment)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(bool, isPhysicalDevice)
        VBox_PROPERTY_RO(int32_t, hostAddress)
        VBox_PROPERTY_RO(int32_t, guestAddress)
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
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(std::wstring, settingsAuxFilePath)
#endif
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

        // Methods
        void lockMachine(
                /* in */ const COMPtr<ISession> &session,
                /* in */ LockType lockType);
        COMPtr<IProgress> launchVMProcess(
                /* in */ const COMPtr<ISession> &session,
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &environment);
        void setBootOrder(
                /* in */ uint32_t position,
                /* in */ DeviceType device);
        DeviceType getBootOrder(
                /* in */ uint32_t position);
        void attachDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ DeviceType type,
                /* in */ const COMPtr<IMedium> &medium);
        void attachDeviceWithoutMedium(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ DeviceType type);
        void detachDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void passthroughDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool passthrough);
        void temporaryEjectDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool temporaryEject);
        void nonRotationalDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool nonRotational);
        void setAutoDiscardForDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool discard);
        void setHotPluggableForDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool hotPluggable);
        void setBandwidthGroupForDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ const COMPtr<IBandwidthGroup> &bandwidthGroup);
        void setNoBandwidthGroupForDevice(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void unmountMedium(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool force);
        void mountMedium(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ const COMPtr<IMedium> &medium,
                /* in */ bool force);
        COMPtr<IMedium> getMedium(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        std::vector<COMPtr<IMediumAttachment>> getMediumAttachmentsOfController(
                /* in */ const std::wstring &name);
        COMPtr<IMediumAttachment> getMediumAttachment(
                /* in */ const std::wstring &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void attachHostPCIDevice(
                /* in */ int32_t hostAddress,
                /* in */ int32_t desiredGuestAddress,
                /* in */ bool tryToUnbind);
        void detachHostPCIDevice(
                /* in */ int32_t hostAddress);
        COMPtr<INetworkAdapter> getNetworkAdapter(
                /* in */ uint32_t slot);
        COMPtr<IStorageController> addStorageController(
                /* in */ const std::wstring &name,
                /* in */ StorageBus connectionType);
        COMPtr<IStorageController> getStorageControllerByName(
                /* in */ const std::wstring &name);
        COMPtr<IStorageController> getStorageControllerByInstance(
                /* in */ StorageBus connectionType,
                /* in */ uint32_t instance);
        void removeStorageController(
                /* in */ const std::wstring &name);
        void setStorageControllerBootable(
                /* in */ const std::wstring &name,
                /* in */ bool bootable);
        COMPtr<IUSBController> addUSBController(
                /* in */ const std::wstring &name,
                /* in */ USBControllerType type);
        void removeUSBController(
                /* in */ const std::wstring &name);
        COMPtr<IUSBController> getUSBControllerByName(
                /* in */ const std::wstring &name);
        uint32_t getUSBControllerCountByType(
                /* in */ USBControllerType type);
        COMPtr<ISerialPort> getSerialPort(
                /* in */ uint32_t slot);
        COMPtr<IParallelPort> getParallelPort(
                /* in */ uint32_t slot);
        std::vector<std::wstring> getExtraDataKeys();
        std::wstring getExtraData(
                /* in */ const std::wstring &key);
        void setExtraData(
                /* in */ const std::wstring &key,
                /* in */ const std::wstring &value);
        bool getCPUProperty(
                /* in */ CPUPropertyType property);
        void setCPUProperty(
                /* in */ CPUPropertyType property,
                /* in */ bool value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        void getCPUIDLeafByOrdinal(
                /* in  */ uint32_t ordinal,
                /* out */ uint32_t &idx,
                /* out */ uint32_t &idxSub,
                /* out */ uint32_t &valEax,
                /* out */ uint32_t &valEbx,
                /* out */ uint32_t &valEcx,
                /* out */ uint32_t &valEdx);
#endif
        void getCPUIDLeaf(
                /* in  */ uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                /* in  */ uint32_t idxSub,
#endif
                /* out */ uint32_t &valEax,
                /* out */ uint32_t &valEbx,
                /* out */ uint32_t &valEcx,
                /* out */ uint32_t &valEdx);
        void setCPUIDLeaf(
                /* in  */ uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                /* in  */ uint32_t idxSub,
#endif
                /* out */ uint32_t &valEax,
                /* out */ uint32_t &valEbx,
                /* out */ uint32_t &valEcx,
                /* out */ uint32_t &valEdx);
        void removeCPUIDLeaf(
                /* in */ uint32_t idx
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
              , /* in */ uint32_t idxSub
#endif
                );
        void removeAllCPUIDLeaves();
        bool getHWVirtExProperty(
                /* in */ HWVirtExPropertyType property);
        void setHWVirtExProperty(
                /* in */ HWVirtExPropertyType property,
                /* in */ bool value);
        COMPtr<IProgress> setSettingsFilePath(
                /* in */ const std::wstring &settingsFilePath);
        void saveSettings();
        void discardSettings();
        std::vector<COMPtr<IMedium>> unregister(
                /* in */ CleanupMode cleanupMode);
        COMPtr<IProgress> deleteConfig(
                /* in */ const std::vector<COMPtr<IMedium>> &media);
        COMPtr<IVirtualSystemDescription> exportTo(
                /* in */ const COMPtr<IAppliance> &appliance,
                /* in */ const std::wstring &location);
        COMPtr<ISnapshot> findSnapshot(
                /* in */ const std::wstring &nameOrId);
        void createSharedFolder(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const std::wstring &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const std::wstring &name);
        bool canShowConsoleWindow();
        int64_t showConsoleWindow();
        void getGuestProperty(
                /* in  */ const std::wstring &name,
                /* out */ std::wstring &value,
                /* out */ int64_t &timestamp,
                /* out */ std::wstring &flags);
        std::wstring getGuestPropertyValue(
                /* in */ const std::wstring &property);
        int64_t getGuestPropertyTimestamp(
                /* in */ const std::wstring &property);
        void setGuestProperty(
                /* in */ const std::wstring &property,
                /* in */ const std::wstring &value,
                /* in */ const std::wstring &flags);
        void setGuestPropertyValue(
                /* in */ const std::wstring &property,
                /* in */ const std::wstring &value);
        void deleteGuestProperty(
                /* in */ const std::wstring &name);
        void enumerateGuestProperties(
                /* in  */ const std::wstring &patterns,
                /* out */ std::vector<std::wstring> &names,
                /* out */ std::vector<std::wstring> &values,
                /* out */ std::vector<int64_t> &timestamps,
                /* out */ std::vector<std::wstring> &flags);
        void querySavedGuestScreenInfo(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t &originX,
                /* out */ uint32_t &originY,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height,
                /* out */ bool &enabled);
        std::vector<uint8_t> readSavedThumbnailToArray(
                /* in  */ uint32_t screenId,
                /* in  */ BitmapFormat bitmapFormat,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height);
        std::vector<BitmapFormat> querySavedScreenshotInfo(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height);
        std::vector<uint8_t> readSavedScreenshotToArray(
                /* in  */ uint32_t screenId,
                /* in  */ BitmapFormat bitmapFormat,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height);
        void hotPlugCPU(
                /* in */ uint32_t cpu);
        void hotUnplugCPU(
                /* in */ uint32_t cpu);
        bool getCPUStatus(
                /* in */ uint32_t cpu);
        ParavirtProvider getEffectiveParavirtProvider();
        std::wstring queryLogFilename(
                /* in */ uint32_t idx);
        std::vector<uint8_t> readLog(
                /* in */ uint32_t idx,
                /* in */ int64_t offset,
                /* in */ int64_t size);
        COMPtr<IProgress> cloneTo(
                /* in */ const COMPtr<IMachine> &target,
                /* in */ CloneMode mode,
                /* in */ const std::vector<CloneOptions> &options);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> moveTo(
                /* in */ const std::wstring &folder,
                /* in */ const std::wstring &type);
#endif
        COMPtr<IProgress> saveState();
        void adoptSavedState(
                /* in */ const std::wstring &savedStateFile);
        void discardSavedState(
                /* in */ bool fRemoveFile);
        COMPtr<IProgress> takeSnapshot(
                /* in  */ const std::wstring &name,
                /* in  */ const std::wstring &description,
                /* in  */ bool pause,
                /* out */ std::wstring &id);
        COMPtr<IProgress> deleteSnapshot(
                /* in */ const std::wstring &id);
        COMPtr<IProgress> deleteSnapshotAndAllChildren(
                /* in */ const std::wstring &id);
        COMPtr<IProgress> deleteSnapshotRange(
                /* in */ const std::wstring &startId,
                /* in */ const std::wstring &endId);
        COMPtr<IProgress> restoreSnapshot(
                /* in */ const COMPtr<ISnapshot> &snapshot);
        void applyDefaults(
                /* in */ const std::wstring &flags);
    };

    class LIBVBOX_API IEmulatedUSB : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IEmulatedUSB)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::wstring>, webcams)

        // Methods
        void webcamAttach(
                /* in */ const std::wstring &path,
                /* in */ const std::wstring &settings);
        void webcamDetach(
                /* in */ const std::wstring &path);
    };

    class LIBVBOX_API IVRDEServerInfo : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVRDEServerInfo)

        // Attributes
        VBox_PROPERTY_RO(bool, active)
        VBox_PROPERTY_RO(int32_t, port)
        VBox_PROPERTY_RO(uint32_t, numberOfClients)
        VBox_PROPERTY_RO(int64_t, beginTime)
        VBox_PROPERTY_RO(int64_t, endTime)
        VBox_PROPERTY_RO(int64_t, bytesSent)
        VBox_PROPERTY_RO(int64_t, bytesSentTotal)
        VBox_PROPERTY_RO(int64_t, bytesReceived)
        VBox_PROPERTY_RO(int64_t, bytesReceivedTotal)
        VBox_PROPERTY_RO(std::wstring, user)
        VBox_PROPERTY_RO(std::wstring, domain)
        VBox_PROPERTY_RO(std::wstring, clientName)
        VBox_PROPERTY_RO(std::wstring, clientIP)
        VBox_PROPERTY_RO(uint32_t, clientVersion)
        VBox_PROPERTY_RO(uint32_t, encryptionStyle)
    };

    class LIBVBOX_API IConsole : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IConsole)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RO(MachineState, state)
        VBox_PROPERTY_RO(COMPtr<IGuest>, guest)
        VBox_PROPERTY_RO(COMPtr<IKeyboard>, keyboard)
        VBox_PROPERTY_RO(COMPtr<IMouse>, mouse)
        VBox_PROPERTY_RO(COMPtr<IDisplay>, display)
        VBox_PROPERTY_RO(COMPtr<IMachineDebugger>, debugger)
        VBox_PROPERTY_RO(std::vector<COMPtr<IUSBDevice>>, USBDevices)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDevice>>, remoteUSBDevices)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISharedFolder>>, sharedFolders)
        VBox_PROPERTY_RO(COMPtr<IVRDEServerInfo>, VRDEServerInfo)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::vector<COMPtr<IPCIDeviceAttachment>>, attachedPCIDevices)
        VBox_PROPERTY_RW_V(bool, useHostClipboard)
        VBox_PROPERTY_RO(COMPtr<IEmulatedUSB>, emulatedUSB)

        // Methods
        COMPtr<IProgress> powerUp();
        COMPtr<IProgress> powerUpPaused();
        COMPtr<IProgress> powerDown();
        void reset();
        void pause();
        void resume();
        void powerButton();
        void sleepButton();
        bool getPowerButtonHandled();
        bool getGuestEnteredACPIMode();
        std::vector<DeviceActivity> getDeviceActivity(
                /* in */ const std::vector<DeviceType> &type);
        void attachUSBDevice(
                /* in */ const std::wstring &id,
                /* in */ const std::wstring &captureFilename);
        COMPtr<IUSBDevice> detachUSBDevice(
                /* in */ const std::wstring &id);
        COMPtr<IUSBDevice> findUSBDeviceByAddress(
                /* in */ const std::wstring &name);
        COMPtr<IUSBDevice> findUSBDeviceById(
                /* in */ const std::wstring &id);
        void createSharedFolder(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const std::wstring &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const std::wstring &name);
        COMPtr<IProgress> teleport(
                /* in */ const std::wstring &hostname,
                /* in */ uint32_t tcpport,
                /* in */ const std::wstring &password,
                /* in */ uint32_t maxDowntime);
        void addDiskEncryptionPassword(
                /* in */ const std::wstring &id,
                /* in */ const std::wstring &password,
                /* in */ bool clearOnSuspend);
        void addDiskEncryptionPasswords(
                /* in */ const std::vector<std::wstring> &ids,
                /* in */ const std::vector<std::wstring> &passwords,
                /* in */ bool clearOnSuspend);
        void removeDiskEncryptionPassword(
                /* in */ const std::wstring &id);
        void clearAllDiskEncryptionPasswords();
    };

    class LIBVBOX_API IHostNetworkInterface : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IHostNetworkInterface)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(std::wstring, shortName)
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RO(std::wstring, networkName)
        VBox_PROPERTY_RO(bool, DHCPEnabled)
        VBox_PROPERTY_RO(std::wstring, IPAddress)
        VBox_PROPERTY_RO(std::wstring, networkMask)
        VBox_PROPERTY_RO(bool, IPV6Supported)
        VBox_PROPERTY_RO(std::wstring, IPV6Address)
        VBox_PROPERTY_RO(uint32_t, IPV6NetworkMaskPrefixLength)
        VBox_PROPERTY_RO(std::wstring, hardwareAddress)
        VBox_PROPERTY_RO(HostNetworkInterfaceMediumType, mediumType)
        VBox_PROPERTY_RO(HostNetworkInterfaceStatus, status)
        VBox_PROPERTY_RO(HostNetworkInterfaceType, interfaceType)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        VBox_PROPERTY_RO(bool, wireless)
#endif

        // Methods
        void enableStaticIPConfig(
                /* in */ const std::wstring &IPAddress,
                /* in */ const std::wstring &networkMask);
        void enableStaticIPConfigV6(
                /* in */ const std::wstring &IPV6Address,
                /* in */ uint32_t IPV6NetworkMaskPrefixLength);
        void enableDynamicIPConfig();
        void DHCPRediscover();
    };

    class LIBVBOX_API IHostVideoInputDevice : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IHostVideoInputDevice)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(std::wstring, path)
        VBox_PROPERTY_RO(std::wstring, alias)
    };

    class LIBVBOX_API IHost : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IHost)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, DVDDrives)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, floppyDrives)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDevice>>, USBDevices)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDeviceFilter>>, USBDeviceFilters)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostNetworkInterface>>, networkInterfaces)
        VBox_PROPERTY_RO(std::vector<std::wstring>, nameServers)
        VBox_PROPERTY_RO(std::wstring, domainName)
        VBox_PROPERTY_RO(std::vector<std::wstring>, searchStrings)
        VBox_PROPERTY_RO(uint32_t, processorCount)
        VBox_PROPERTY_RO(uint32_t, processorOnlineCount)
        VBox_PROPERTY_RO(uint32_t, processorCoreCount)
        VBox_PROPERTY_RO(uint32_t, processorOnlineCoreCount)
        VBox_PROPERTY_RO(uint32_t, memorySize)
        VBox_PROPERTY_RO(uint32_t, memoryAvailable)
        VBox_PROPERTY_RO(std::wstring, operatingSystem)
        VBox_PROPERTY_RO(std::wstring, OSVersion)
        VBox_PROPERTY_RO(int64_t, UTCTime)
        VBox_PROPERTY_RO(bool, acceleration3DAvailable)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostVideoInputDevice>>, videoInputDevices)

        // Methods
        uint32_t getProcessorSpeed(
                /* in */ uint32_t cpuId);
        bool getProcessorFeature(
                /* in */ ProcessorFeature feature);
        std::wstring getProcessorDescription(
                /* in */ uint32_t cpuId);
        void getProcessorCPUIDLeaf(
                /* in  */ uint32_t cpuId,
                /* in  */ uint32_t leaf,
                /* in  */ uint32_t subLeaf,
                /* out */ uint32_t &valEax,
                /* out */ uint32_t &valEbx,
                /* out */ uint32_t &valEcx,
                /* out */ uint32_t &valEdx);
        COMPtr<IProgress> createHostOnlyNetworkInterface(
                /* out */ COMPtr<IHostNetworkInterface> &hostInterface);
        COMPtr<IProgress> removeHostOnlyNetworkInterface(
                /* in */ const std::wstring &id);
        COMPtr<IHostUSBDeviceFilter> createUSBDeviceFilter(
                /* in */ const std::wstring name);
        void insertUSBDeviceFilter(
                /* in */ uint32_t position,
                /* in */ const COMPtr<IHostUSBDeviceFilter> &filter);
        void removeUSBDeviceFilter(
                /* in */ uint32_t position);
        COMPtr<IMedium> findHostDVDDrive(
                /* in */ const std::wstring &name);
        COMPtr<IMedium> findHostFloppyDrive(
                /* in */ const std::wstring &name);
        COMPtr<IHostNetworkInterface> findHostNetworkInterfaceByName(
                /* in */ const std::wstring &name);
        COMPtr<IHostNetworkInterface> findHostNetworkInterfaceById(
                /* in */ const std::wstring &id);
        std::vector<COMPtr<IHostNetworkInterface>> findHostNetworkInterfacesOfType(
                /* in */ HostNetworkInterfaceType type);
        COMPtr<IHostUSBDevice> findUSBDeviceById(
                /* in */ const std::wstring &id);
        COMPtr<IHostUSBDevice> findUSBDeviceByAddress(
                /* in */ const std::wstring &name);
        std::wstring generateMACAddress();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        void addUSBDeviceSource(
                /* in */ const std::wstring &backend,
                /* in */ const std::wstring &id,
                /* in */ const std::wstring &address,
                /* in */ const std::vector<std::wstring> &propertyNames,
                /* in */ const std::vector<std::wstring> &propertyValues);
        void removeUSBDeviceSource(
                /* in */ const std::wstring &id);
#endif
    };

    class LIBVBOX_API ISystemProperties : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISystemProperties)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, minGuestRAM)
        VBox_PROPERTY_RO(uint32_t, maxGuestRAM)
        VBox_PROPERTY_RO(uint32_t, minGuestVRAM)
        VBox_PROPERTY_RO(uint32_t, maxGuestVRAM)
        VBox_PROPERTY_RO(uint32_t, minGuestCPUCount)
        VBox_PROPERTY_RO(uint32_t, maxGuestCPUCount)
        VBox_PROPERTY_RO(uint32_t, maxGuestMonitors)
        VBox_PROPERTY_RO(int64_t, infoVDSize)
        VBox_PROPERTY_RO(uint32_t, serialPortCount)
        VBox_PROPERTY_RO(uint32_t, parallelPortCount)
        VBox_PROPERTY_RO(uint32_t, maxBootPosition)
        VBox_PROPERTY_RO(bool, rawModeSupported)
        VBox_PROPERTY_RW_V(bool, exclusiveHwVirt)
        VBox_PROPERTY_RW_R(std::wstring, defaultMachineFolder)
        VBox_PROPERTY_RW_R(std::wstring, loggingLevel)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMediumFormat>>, mediumFormats)
        VBox_PROPERTY_RW_R(std::wstring, defaultHardDiskFormat)
        VBox_PROPERTY_RW_V(int64_t, freeDiskSpaceWarning)
        VBox_PROPERTY_RW_V(uint32_t, freeDiskPercentWarning)
        VBox_PROPERTY_RW_V(int64_t, freeDiskSpaceError)
        VBox_PROPERTY_RW_V(uint32_t, freeDiskSpacePercentError)
        VBox_PROPERTY_RW_R(std::wstring, VRDEAuthLibrary)
        VBox_PROPERTY_RW_R(std::wstring, webServiceAuthLibrary)
        VBox_PROPERTY_RW_R(std::wstring, defaultVRDEExtPack)
        VBox_PROPERTY_RW_V(uint32_t, logHistoryCount)
        VBox_PROPERTY_RO(AudioDriverType, defaultAudioDriver)
        VBox_PROPERTY_RW_R(std::wstring, autostartDatabasePath)
        VBox_PROPERTY_RW_R(std::wstring, defaultAdditionsISO)
        VBox_PROPERTY_RW_R(std::wstring, defaultFrontend)
        VBox_PROPERTY_RO(std::vector<BitmapFormat>, screenShotFormats)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(ProxyMode, proxyMode)
        VBox_PROPERTY_RW_R(std::wstring, proxyURL)
#endif

        // Methods
        uint32_t getMaxNetworkAdapters(
                /* in */ ChipsetType chipset);
        uint32_t getMaxNetworkAdaptersOfType(
                /* in */ ChipsetType chipset,
                /* in */ NetworkAttachmentType type);
        uint32_t getMaxDevicesPerPortForStorageBus(
                /* in */ StorageBus bus);
        uint32_t getMinPortCountForStorageBus(
                /* in */ StorageBus bus);
        uint32_t getMaxPortCountForStorageBus(
                /* in */ StorageBus bus);
        uint32_t getMaxInstancesOfStorageBus(
                /* in */ ChipsetType chipset,
                /* in */ StorageBus bus);
        std::vector<DeviceType> getDeviceTypesForStorageBus(
                /* in */ StorageBus bus);
        bool getDefaultIoCacheSettingForStorageController(
                /* in */ StorageControllerType controllerType);
        bool getStorageControllerHotplugCapable(
                /* in */ StorageControllerType controllerType);
        uint32_t getMaxInstancesOfUSBControllerType(
                /* in */ ChipsetType chipset,
                /* in */ USBControllerType type);
    };

    class LIBVBOX_API IGuestOSType : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuestOSType)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, familyId)
        VBox_PROPERTY_RO(std::wstring, familyDescription)
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RO(std::wstring, description)
        VBox_PROPERTY_RO(bool, is64Bit)
        VBox_PROPERTY_RO(bool, recommendedIOAPIC)
        VBox_PROPERTY_RO(bool, recommendedVirtEx)
        VBox_PROPERTY_RO(uint32_t, recommendedRAM)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(GraphicsControllerType, recommendedGraphicsController)
#endif
        VBox_PROPERTY_RO(uint32_t, recommendedVRAM)
        VBox_PROPERTY_RO(bool, recommended2DVideoAcceleration)
        VBox_PROPERTY_RO(bool, recommended3DAcceleration)
        VBox_PROPERTY_RO(int64_t, recommendedHDD)
        VBox_PROPERTY_RO(NetworkAdapterType, adapterType)
        VBox_PROPERTY_RO(bool, recommendedPAE)
        VBox_PROPERTY_RO(StorageControllerType, recommendedDVDStorageController)
        VBox_PROPERTY_RO(StorageBus, recommendedDVDStorageBus)
        VBox_PROPERTY_RO(StorageControllerType, recommendedHDStorageController)
        VBox_PROPERTY_RO(StorageBus, recommendedHDStorageBus)
        VBox_PROPERTY_RO(FirmwareType, recommendedFirmware)
        VBox_PROPERTY_RO(bool, recommendedUSBHID)
        VBox_PROPERTY_RO(bool, recommendedHPET)
        VBox_PROPERTY_RO(bool, recommendedUSBTablet)
        VBox_PROPERTY_RO(bool, recommendedRTCUseUTC)
        VBox_PROPERTY_RO(ChipsetType, recommendedChipset)
        VBox_PROPERTY_RO(AudioControllerType, recommendedAudioController)
        VBox_PROPERTY_RO(AudioCodecType, recommendedAudioCodec)
        VBox_PROPERTY_RO(bool, recommendedFloppy)
        VBox_PROPERTY_RO(bool, recommendedUSB)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(bool, recommendedUSB3)
#endif
        VBox_PROPERTY_RO(bool, recommendedTFReset)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(bool, recommendedX2APIC)
#endif
    };

    class LIBVBOX_API IAdditionsFacility : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IAdditionsFacility)

        // Attributes
        VBox_PROPERTY_RO(AdditionsFacilityClass, classType)
        VBox_PROPERTY_RO(int64_t, lastUpdated)
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(AdditionsFacilityStatus, status)
        VBox_PROPERTY_RO(AdditionsFacilityType, type)
    };

    class LIBVBOX_API IDnDBase : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDnDBase)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::wstring>, formats)
        VBox_PROPERTY_RO(uint32_t, protocolVersion)

        // Methods
        bool isFormatSupported(
                /* in */ const std::wstring &format);
        void addFormats(
                /* in */ const std::vector<std::wstring> &formats);
        void removeFormats(
                /* in */ const std::vector<std::wstring> &formats);
    };

    class LIBVBOX_API IDnDSource : public IDnDBase
    {
    public:
        COM_WRAPPED(::IDnDSource)

        // Methods
        DnDAction dragIsPending(
                /* in  */ uint32_t screenId,
                /* out */ std::vector<std::wstring> &formats,
                /* out */ std::vector<DnDAction> &allowedActions);
        COMPtr<IProgress> drop(
                /* in */ const std::wstring &format,
                /* in */ DnDAction action);
        std::vector<uint8_t> receiveData();
    };

    class LIBVBOX_API IGuestDnDSource : public IDnDSource
    {
    public:
        COM_WRAPPED(::IGuestDnDSource)
    };

    class LIBVBOX_API IDnDTarget : public IDnDBase
    {
    public:
        COM_WRAPPED(::IDnDTarget)

        // Methods
        DnDAction enter(
                /* in */ uint32_t screenId,
                /* in */ uint32_t y,
                /* in */ uint32_t x,
                /* in */ DnDAction defaultAction,
                /* in */ const std::vector<DnDAction> &allowedActions,
                /* in */ const std::vector<std::wstring> &formats);
        DnDAction move(
                /* in */ uint32_t screenId,
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ DnDAction defaultAction,
                /* in */ const std::vector<DnDAction> &allowedActions,
                /* in */ const std::vector<std::wstring> &formats);
        void leave(
                /* in */ uint32_t screenId);
        DnDAction drop(
                /* in  */ uint32_t screenId,
                /* in  */ uint32_t x,
                /* in  */ uint32_t y,
                /* in  */ DnDAction defaultAction,
                /* in  */ const std::vector<DnDAction> &allowedActions,
                /* in  */ const std::vector<std::wstring> &formats,
                /* out */ std::wstring &format);
        COMPtr<IProgress> sendData(
                /* in */ uint32_t screenId,
                /* in */ const std::wstring& format,
                /* in */ const std::vector<uint8_t> &data);
        bool cancel();
    };

    class LIBVBOX_API IGuestDnDTarget : public IDnDTarget
    {
    public:
        COM_WRAPPED(::IGuestDnDTarget)
    };

    class LIBVBOX_API IGuestSession : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuestSession)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, user)
        VBox_PROPERTY_RO(std::wstring, domain)
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RW_V(uint32_t, timeout)
        VBox_PROPERTY_RO(uint32_t, protocolVersion)
        VBox_PROPERTY_RO(GuestSessionStatus, status)
        VBox_PROPERTY_RW_R(std::vector<std::wstring>, environmentChanges)
        VBox_PROPERTY_RO(std::vector<std::wstring>, environmentBase)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestProcess>>, processes)
        VBox_PROPERTY_RO(PathStyle, pathStyle)
        VBox_PROPERTY_RW_R(std::wstring, currentDirectory)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(std::wstring, userHome)
        VBox_PROPERTY_RO(std::wstring, userDocuments)
#endif
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestDirectory>>, directories)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestFile>>, files)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)

        // Methods
        void close();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> copyFromGuest(
                /* in */ const std::vector<std::wstring> &sources,
                /* in */ const std::vector<std::wstring> &filters,
                /* in */ const std::vector<std::wstring> &flags,
                /* in */ const std::wstring &destination);
        COMPtr<IProgress> copyToGuest(
                /* in */ const std::vector<std::wstring> &sources,
                /* in */ const std::vector<std::wstring> &filters,
                /* in */ const std::vector<std::wstring> &flags,
                /* in */ const std::wstring &destination);
#endif
        COMPtr<IProgress> directoryCopy(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        COMPtr<IProgress> directoryCopyFromGuest(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        COMPtr<IProgress> directoryCopyToGuest(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        void directoryCreate(
                /* in */ const std::wstring &path,
                /* in */ uint32_t mode,
                /* in */ const std::vector<DirectoryCreateFlag> &flags);
        std::wstring directoryCreateTemp(
                /* in */ const std::wstring &templateName,
                /* in */ uint32_t mode,
                /* in */ const std::wstring &path,
                /* in */ bool secure);
        bool directoryExists(
                /* in */ const std::wstring &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestDirectory> directoryOpen(
                /* in */ const std::wstring &path,
                /* in */ const std::wstring &filter,
                /* in */ const std::vector<DirectoryOpenFlag> &flags);
        void directoryRemove(
                /* in */ const std::wstring &path);
        COMPtr<IProgress> directoryRemoveRecursive(
                /* in */ const std::wstring &path,
                /* in */ const std::vector<DirectoryRemoveRecFlag> &flags);
        void environmentScheduleSet(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &value);
        void environmentScheduleUnset(
                /* in */ const std::wstring &name);
        std::wstring environmentGetBaseVariable(
                /* in */ const std::wstring &name);
        bool environmentDoesBaseVariableExist(
                /* in */ const std::wstring &name);
        COMPtr<IProgress> fileCopy(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<FileCopyFlag> flags);
        COMPtr<IProgress> fileCopyFromGuest(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IProgress> fileCopyToGuest(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IGuestFile> fileCreateTemp(
                /* in */ const std::wstring &templateName,
                /* in */ uint32_t mode,
                /* in */ const std::wstring &path,
                /* in */ bool secure);
        bool fileExists(
                /* in */ const std::wstring &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestFile> fileOpen(
                /* in */ const std::wstring &path,
                /* in */ FileAccessMode accessMode,
                /* in */ FileOpenAction openAction,
                /* in */ uint32_t creationMode);
        COMPtr<IGuestFile> fileOpenEx(
                /* in */ const std::wstring &path,
                /* in */ FileAccessMode accessMode,
                /* in */ FileOpenAction openAction,
                /* in */ FileSharingMode sharingMode,
                /* in */ uint32_t creationMode,
                /* in */ const std::vector<FileOpenExFlag> &flags);
        int64_t fileQuerySize(
                /* in */ const std::wstring &path,
                /* in */ bool followSymlinks);
        bool fsObjExists(
                /* in */ const std::wstring &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestFsObjInfo> fsObjQueryInfo(
                /* in */ const std::wstring &path,
                /* in */ bool followSymlinks);
        void fsObjRemove(
                /* in */ const std::wstring &path);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> fsObjRemoveArray(
                /* in */ const std::vector<std::wstring> &path);
#endif
        void fsObjRename(
                /* in */ const std::wstring &oldPath,
                /* in */ const std::wstring &newPath,
                /* in */ const std::vector<FsObjRenameFlag> &flags);
        COMPtr<IProgress> fsObjMove(
                /* in */ const std::wstring &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<FsObjMoveFlag> &flags);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> fsObjMoveArray(
                /* in */ const std::vector<std::wstring> &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<FsObjMoveFlag> &flags);
        COMPtr<IProgress> fsObjCopyArray(
                /* in */ const std::vector<std::wstring> &source,
                /* in */ const std::wstring &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
#endif
        void fsObjSetACL(
                /* in */ const std::wstring &path,
                /* in */ bool followSymlinks,
                /* in */ const std::wstring &acl,
                /* in */ uint32_t mode);
        COMPtr<IGuestProcess> processCreate(
                /* in */ const std::wstring &executable,
                /* in */ const std::vector<std::wstring> &arguments,
                /* in */ const std::vector<std::wstring> &environmentChanges,
                /* in */ const std::vector<ProcessCreateFlag> &flags,
                /* in */ uint32_t timeoutMS);
        COMPtr<IGuestProcess> processCreateEx(
                /* in */ const std::wstring &executable,
                /* in */ const std::vector<std::wstring> &arguments,
                /* in */ const std::vector<std::wstring> &environmentChanges,
                /* in */ const std::vector<ProcessCreateFlag> &flags,
                /* in */ uint32_t timeoutMS,
                /* in */ ProcessPriority priority,
                /* in */ const std::vector<int32_t> &affinity);
        COMPtr<IGuestProcess> processGet(
                /* in */ uint32_t pid);
        void symlinkCreate(
                /* in */ const std::wstring &symlink,
                /* in */ const std::wstring &target,
                /* in */ SymlinkType type);
        bool symlinkExists(
                /* in */ const std::wstring &symlink);
        std::wstring symlinkRead(
                /* in */ const std::wstring &symlink,
                /* in */ const std::vector<SymlinkReadFlag> &flags);
        GuestSessionWaitResult waitFor(
                /* in */ uint32_t waitFor,
                /* in */ uint32_t timeoutMS);
        GuestSessionWaitResult waitForArray(
                /* in */ const std::vector<GuestSessionWaitForFlag> &waitFor,
                /* in */ uint32_t timeoutMS);
    };

    class LIBVBOX_API IProcess : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IProcess)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::wstring>, arguments)
        VBox_PROPERTY_RO(std::vector<std::wstring>, environment)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::wstring, executablePath)
        VBox_PROPERTY_RO(int32_t, exitCode)
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(uint32_t, PID)
        VBox_PROPERTY_RO(ProcessStatus, status)

        // Methods
        ProcessWaitResult waitFor(
                /* in */ uint32_t waitFor,
                /* in */ uint32_t timeoutMS);
        ProcessWaitResult waitForArray(
                /* in */ const std::vector<ProcessWaitForFlag> &waitFor,
                /* in */ uint32_t timeoutMS);
        std::vector<uint8_t> read(
                /* in */ uint32_t handle,
                /* in */ uint32_t toRead,
                /* in */ uint32_t timeoutMS);
        uint32_t write(
                /* in */ uint32_t handle,
                /* in */ uint32_t flags,
                /* in */ const std::vector<uint8_t> &data,
                /* in */ uint32_t timeoutMS);
        uint32_t writeArray(
                /* in */ uint32_t handle,
                /* in */ const std::vector<ProcessInputFlag> &flags,
                /* in */ const std::vector<uint8_t> &data,
                /* in */ uint32_t timeoutMS);
        void terminate();
    };

    class LIBVBOX_API IGuestProcess : public IProcess
    {
    public:
        COM_WRAPPED(::IGuestProcess)
    };

    class LIBVBOX_API IDirectory : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDirectory)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, directoryName)
        VBox_PROPERTY_RO(std::wstring, filter)

        // Methods
        void close();
        COMPtr<IFsObjInfo> read();
    };

    class LIBVBOX_API IGuestDirectory : public IDirectory
    {
    public:
        COM_WRAPPED(::IGuestDirectory)
    };

    class LIBVBOX_API IFile : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IFile)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RO(int64_t, initialSize)
        VBox_PROPERTY_RO(int64_t, offset)
        VBox_PROPERTY_RO(FileStatus, status)
        VBox_PROPERTY_RO(std::wstring, filename)
        VBox_PROPERTY_RO(std::wstring, fileName)    // Old name for "filename" attribute
        VBox_PROPERTY_RO(uint32_t, creationMode)
        VBox_PROPERTY_RO(FileOpenAction, openAction)
        VBox_PROPERTY_RO(FileAccessMode, accessMode)

        // Methods
        void close();
        COMPtr<IFsObjInfo> queryInfo();
        int64_t querySize();
        std::vector<uint8_t> read(
                /* in */ uint32_t toRead,
                /* in */ uint32_t timeoutMS);
        std::vector<uint8_t> readAt(
                /* in */ int64_t offset,
                /* in */ uint32_t toRead,
                /* in */ uint32_t timeoutMS);
        int64_t seek(
                /* in */ int64_t offset,
                /* in */ FileSeekOrigin whence);
        void setACL(
                /* in */ const std::wstring &acl,
                /* in */ uint32_t mode);
        void setSize(
                /* in */ int64_t size);
        uint32_t write(
                /* in */ const std::vector<uint8_t> &data,
                /* in */ uint32_t timeoutMS);
        uint32_t writeAt(
                /* in */ int64_t offset,
                /* in */ const std::vector<uint8_t> &data,
                /* in */ uint32_t timeoutMS);
    };

    class LIBVBOX_API IGuestFile : public IFile
    {
    public:
        COM_WRAPPED(::IGuestFile)
    };

    class LIBVBOX_API IFsObjInfo : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IFsObjInfo)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(FsObjType, type)
        VBox_PROPERTY_RO(std::wstring, fileAttributes)
        VBox_PROPERTY_RO(int64_t, objectSize)
        VBox_PROPERTY_RO(int64_t, allocatedSize)
        VBox_PROPERTY_RO(int64_t, accessTime)
        VBox_PROPERTY_RO(int64_t, birthTime)
        VBox_PROPERTY_RO(int64_t, changeTime)
        VBox_PROPERTY_RO(int64_t, modificationTime)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(int32_t, UID)
#else
        VBox_PROPERTY_RO(uint32_t, UID)
#endif
        VBox_PROPERTY_RO(std::wstring, userName)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(int32_t, GID)
#else
        VBox_PROPERTY_RO(uint32_t, GID)
#endif
        VBox_PROPERTY_RO(std::wstring, groupName)
        VBox_PROPERTY_RO(int64_t, nodeId)
        VBox_PROPERTY_RO(uint32_t, nodeIdDevice)
        VBox_PROPERTY_RO(uint32_t, hardLinks)
        VBox_PROPERTY_RO(uint32_t, deviceNumber)
        VBox_PROPERTY_RO(uint32_t, generationId)
        VBox_PROPERTY_RO(uint32_t, userFlags)
    };

    class LIBVBOX_API IGuestFsObjInfo : public IFsObjInfo
    {
    public:
        COM_WRAPPED(::IGuestFsObjInfo)
    };

    class LIBVBOX_API IGuest : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuest)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, OSTypeId)
        VBox_PROPERTY_RO(AdditionsRunLevelType, additionsRunLevel)
        VBox_PROPERTY_RO(std::wstring, additionsVersion)
        VBox_PROPERTY_RO(uint32_t, additions_revision)
        VBox_PROPERTY_RO(COMPtr<IGuestDnDSource>, dnDSource)
        VBox_PROPERTY_RO(COMPtr<IGuestDnDTarget>, dnDTarget)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::vector<COMPtr<IAdditionsFacility>>, facilities)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestSession>>, sessions)
        VBox_PROPERTY_RW_V(uint32_t, memoryBalloonSize)
        VBox_PROPERTY_RW_V(uint32_t, statisticsUpdateInterval)

        // Methods
        void internalGetStatistics(
                /* out */ uint32_t &cpuUser,
                /* out */ uint32_t &cpuKernel,
                /* out */ uint32_t &cpuIdle,
                /* out */ uint32_t &memTotal,
                /* out */ uint32_t &memFree,
                /* out */ uint32_t &memBalloon,
                /* out */ uint32_t &memShared,
                /* out */ uint32_t &memCache,
                /* out */ uint32_t &pagedTotal,
                /* out */ uint32_t &memAllocTotal,
                /* out */ uint32_t &memFreeTotal,
                /* out */ uint32_t &memBalloonTotal,
                /* out */ uint32_t &memSharedTotal);
        AdditionsFacilityStatus getFacilityStatus(
                /* in  */ AdditionsFacilityType facility,
                /* out */ int64_t &timestamp);
        bool getAdditionsStatus(
                /* in */ AdditionsRunLevelType level);
        void setCredentials(
                /* in */ const std::wstring &userName,
                /* in */ const std::wstring &password,
                /* in */ const std::wstring &domain,
                /* in */ bool allowInteractiveLogon);
        COMPtr<IGuestSession> createSession(
                /* in */ const std::wstring &user,
                /* in */ const std::wstring &password,
                /* in */ const std::wstring &domain,
                /* in */ const std::wstring &sessionName);
        std::vector<COMPtr<IGuestSession>> findSession(
                /* in */ const std::wstring &sessionName);
        COMPtr<IProgress> updateGuestAdditions(
                /* in */ const std::wstring &source,
                /* in */ const std::vector<std::wstring> &arguments,
                /* in */ const std::vector<AdditionsUpdateFlag> &flags);
    };

    class LIBVBOX_API IProgress : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IProgress)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RO(std::wstring, description)
        VBox_PROPERTY_RO(COMPtr<COMWrapBase>, initiator)
        VBox_PROPERTY_RO(bool, cancelable)
        VBox_PROPERTY_RO(uint32_t, percent)
        VBox_PROPERTY_RO(int32_t, timeRemaining)
        VBox_PROPERTY_RO(bool, completed)
        VBox_PROPERTY_RO(bool, canceled)
        VBox_PROPERTY_RO(int32_t, resultCode)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, errorInfo)
        VBox_PROPERTY_RO(uint32_t, operationCount)
        VBox_PROPERTY_RO(uint32_t, operation)
        VBox_PROPERTY_RO(std::wstring, operationDescription)
        VBox_PROPERTY_RO(uint32_t, operationPercent)
        VBox_PROPERTY_RO(uint32_t, operationWeight)
        VBox_PROPERTY_RW_V(uint32_t, timeout)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
#endif

        // Methods
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
        void setCurrentOperationProgress(
                /* in */ uint32_t percent);
        void setNextOperation(
                /* in */ const std::wstring &nextOperationDescription,
                /* in */ uint32_t nextOperationsWeight);
#endif
        void waitForCompletion(
                /* in */ int32_t timeout);
        void waitForOperationCompletion(
                /* in */ uint32_t operation,
                /* in */ int32_t timeout);
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
        void waitForAsyncProgressCompletion(
                /* in */ const COMPtr<IProgress> &pProgressAsync);
#endif
        void cancel();
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IInternalProgressControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IInternalProgressControl)

        // Methods
        void setCurrentOperationProgress(
                /* in */ uint32_t percent);
        void waitForOtherProgressCompletion(
                /* in */ const COMPtr<IProgress> &progressOther,
                /* in */ uint32_t timeoutMS);
        void setNextOperation(
                /* in */ const std::wstring &nextOperationDescription,
                /* in */ uint32_t nextOperationsWeight);
        void notifyPointOfNoReturn();
        void notifyComplete(
                /* in */ int32_t resultCode,
                /* in */ const COMPtr<IVirtualBoxErrorInfo> &errorInfo);
    };
#endif

    class LIBVBOX_API ISnapshot : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISnapshot)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RW_R(std::wstring, name)
        VBox_PROPERTY_RW_R(std::wstring, description)
        VBox_PROPERTY_RO(int64_t, timeStamp)
        VBox_PROPERTY_RO(bool, online)
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RO(COMPtr<ISnapshot>, parent)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISnapshot>>, children)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(uint32_t, childrenCount)
#endif

        // Methods
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
        uint32_t getChildrenCount() const;
#endif
    };

    class LIBVBOX_API IMediumAttachment : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMediumAttachment)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMedium>, medium)
        VBox_PROPERTY_RO(std::wstring, controller)
        VBox_PROPERTY_RO(int32_t, port)
        VBox_PROPERTY_RO(int32_t, device)
        VBox_PROPERTY_RO(DeviceType, type)
        VBox_PROPERTY_RO(bool, passthrough)
        VBox_PROPERTY_RO(bool, temporaryEject)
        VBox_PROPERTY_RO(bool, isEjected)
        VBox_PROPERTY_RO(bool, nonRotational)
        VBox_PROPERTY_RO(bool, discard)
        VBox_PROPERTY_RO(bool, hotPluggable)
        VBox_PROPERTY_RO(COMPtr<IBandwidthGroup>, bandwidthGroup)
    };

    class LIBVBOX_API IMedium : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMedium)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RW_R(std::wstring, description)
        VBox_PROPERTY_RO(MediumState, state)
        VBox_PROPERTY_RO(std::vector<MediumVariant>, variant)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_R(std::wstring, location)
#else
        VBox_PROPERTY_RO(std::wstring, location)
#endif
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(DeviceType, deviceType)
        VBox_PROPERTY_RO(bool, hostDrive)
        VBox_PROPERTY_RO(int64_t, size)
        VBox_PROPERTY_RO(std::wstring, format)
        VBox_PROPERTY_RO(COMPtr<IMediumFormat>, mediumFormat)
        VBox_PROPERTY_RW_V(MediumType, type)
        VBox_PROPERTY_RO(std::vector<MediumType>, allowedTypes)
        VBox_PROPERTY_RO(COMPtr<IMedium>, parent)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, children)
        VBox_PROPERTY_RO(COMPtr<IMedium>, base)
        VBox_PROPERTY_RO(bool, readOnly)
        VBox_PROPERTY_RO(int64_t, logicalSize)
        VBox_PROPERTY_RW_V(bool, autoReset)
        VBox_PROPERTY_RO(std::wstring, lastAccessError)
        VBox_PROPERTY_RO(std::vector<std::wstring>, machineIds)

        // Methods
        void setIds(
                /* in */ bool setImageId,
                /* in */ const std::wstring &imageId,
                /* in */ bool setParentId,
                /* in */ const std::wstring &parentId);
        MediumState refreshState();
        std::vector<std::wstring> getSnapshotIds(
                /* in */ const std::wstring &machineId);
        COMPtr<IToken> lockRead();
        COMPtr<IToken> lockWrite();
        void close();
        std::wstring getProperty(
                /* in */ const std::wstring &name);
        void setProperty(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &value);
        std::vector<std::wstring> getProperties(
                /* in  */ const std::wstring &names,
                /* out */ std::vector<std::wstring> &returnNames);
        void setProperties(
                /* in */ const std::vector<std::wstring> &names,
                /* in */ const std::vector<std::wstring> &values);
        COMPtr<IProgress> createBaseStorage(
                /* in */ int64_t logicalSize,
                /* in */ const std::vector<MediumVariant> &variant);
        COMPtr<IProgress> deleteStorage();
        COMPtr<IProgress> createDiffStorage(
                /* in */ const COMPtr<IMedium> &target,
                /* in */ const std::vector<MediumVariant> &variant);
        COMPtr<IProgress> mergeTo(
                /* in */ const COMPtr<IMedium> &target);
        COMPtr<IProgress> cloneTo(
                /* in */ const COMPtr<IMedium> &target,
                /* in */ const std::vector<MediumVariant> &variant,
                /* in */ const COMPtr<IMedium> &parent);
        COMPtr<IProgress> cloneToBase(
                /* in */ const COMPtr<IMedium> &target,
                /* in */ const std::vector<MediumVariant> &variant);
        COMPtr<IProgress> setLocation(
                /* in */ const std::wstring &location);     // Old name for moveTo()
        COMPtr<IProgress> moveTo(
                /* in */ const std::wstring &location);
        COMPtr<IProgress> compact();
        COMPtr<IProgress> resize(
                /* in */ int64_t logicalSize);
        COMPtr<IProgress> reset();
        COMPtr<IProgress> changeEncryption(
                /* in */ const std::wstring &currentPassword,
                /* in */ const std::wstring &cipher,
                /* in */ const std::wstring &newPassword,
                /* in */ const std::wstring &newPasswordId);
        std::wstring getEncryptionSettings(
                /* out */ std::wstring &cipher);
        void checkEncryptionPassword(
                /* in */ const std::wstring &password);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IMediumIO> openForIO(
                /* in */ bool writable,
                /* in */ const std::wstring &password);
#endif
    };

    class LIBVBOX_API IMediumFormat : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMediumFormat)

        // Attributes
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(std::vector<MediumFormatCapabilities>, capabilities)

        // Methods
        void describeFileExtensions(
                /* out */ std::vector<std::wstring> &extensions,
                /* out */ std::vector<DeviceType> &types);
        void describeProperties(
                /* out */ std::vector<std::wstring> &names,
                /* out */ std::vector<std::wstring> &descriptions,
                /* out */ std::vector<DataType> &types,
                /* out */ std::vector<uint32_t> &flags,
                /* out */ std::vector<std::wstring> &defaults);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IDataStream : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDataStream)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, readSize)

        // Methods
        std::vector<uint8_t> read(
                /* in */ uint32_t size,
                /* in */ uint32_t timeoutMS);
    };

    class LIBVBOX_API IMediumIO : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMediumIO)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMedium>, medium)
        VBox_PROPERTY_RO(bool, writable)
        VBox_PROPERTY_RO(COMPtr<IVFSExplorer>, explorer)

        // Methods
        std::vector<uint8_t> read(
                /* in */ int64_t offset,
                /* in */ uint32_t size);
        uint32_t write(
                /* in */ int64_t offset,
                /* in */ const std::vector<uint8_t> &data);
        void formatFAT(
                /* in */ bool quick);
        void initializePartitionTable(
                /* in */ PartitionTableType format,
                /* in */ bool wholeDiskInOneEntry);
        COMPtr<IProgress> convertToStream(
                /* in  */ const std::wstring &format,
                /* in  */ const std::vector<MediumVariant> &variant,
                /* in  */ uint32_t bufferSize,
                /* out */ COMPtr<IDataStream> &stream);
        void close();
    };
#endif

    class LIBVBOX_API IToken : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IToken)

        // Methods
        void abandon();
        void dummy();
    };

    class LIBVBOX_API IKeyboard : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IKeyboard)

        // Attributes
        VBox_PROPERTY_RO(std::vector<KeyboardLED>, keyboardLEDs)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)

        // Methods
        void putScancode(
                /* in */ int32_t scancode);
        uint32_t putScancodes(
                /* in */ const std::vector<int32_t> &scancodes);
        void putCAD();
        void releaseKeys();
    };

    class LIBVBOX_API IMousePointerShape : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMousePointerShape)

        // Attributes
        VBox_PROPERTY_RO(bool, visible)
        VBox_PROPERTY_RO(bool, alpha)
        VBox_PROPERTY_RO(uint32_t, hotX)
        VBox_PROPERTY_RO(uint32_t, hotY)
        VBox_PROPERTY_RO(uint32_t, width)
        VBox_PROPERTY_RO(uint32_t, height)
        VBox_PROPERTY_RO(std::vector<uint8_t>, shape)
    };

    class LIBVBOX_API IMouse : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMouse)

        // Attributes
        VBox_PROPERTY_RO(bool, absoluteSupported)
        VBox_PROPERTY_RO(bool, relativeSupported)
        VBox_PROPERTY_RO(bool, multiTouchSupported)
        VBox_PROPERTY_RO(bool, needsHostCursor)
        VBox_PROPERTY_RO(COMPtr<IMousePointerShape>, pointerShape)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)

        // Methods
        void putMouseEvent(
                /* in */ int32_t dx,
                /* in */ int32_t dy,
                /* in */ int32_t dz,
                /* in */ int32_t dw,
                /* in */ int32_t buttonState);
        void putMouseEventAbsolute(
                /* in */ int32_t x,
                /* in */ int32_t y,
                /* in */ int32_t dz,
                /* in */ int32_t dw,
                /* in */ int32_t buttonState);
        void putEventMultiTouch(
                /* in */ int32_t count,
                /* in */ const std::vector<int64_t> &contacts,
                /* in */ uint32_t scanTime);
        void putEventMultiTouchString(
                /* in */ int32_t count,
                /* in */ const std::wstring &contacts,
                /* in */ uint32_t scanTime);
    };

    class LIBVBOX_API IDisplaySourceBitmap : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDisplaySourceBitmap)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, screenId)

        // Methods
        void queryBitmapInfo(
                /* out */ uint8_t *&address,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height,
                /* out */ uint32_t &bitsPerPixel,
                /* out */ uint32_t &bytesPerLine,
                /* out */ BitmapFormat &bitmapFormat);
    };

    class LIBVBOX_API IFramebuffer : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IFramebuffer)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, width)
        VBox_PROPERTY_RO(uint32_t, height)
        VBox_PROPERTY_RO(uint32_t, bitsPerPixel)
        VBox_PROPERTY_RO(uint32_t, bytesPerLine)
        VBox_PROPERTY_RO(BitmapFormat, pixelFormat)
        VBox_PROPERTY_RO(uint32_t, heightReduction)
        VBox_PROPERTY_RO(COMPtr<IFramebufferOverlay>, overlay)
        VBox_PROPERTY_RO(int64_t, winId)
        VBox_PROPERTY_RO(std::vector<FramebufferCapabilities>, capabilities)

        // Methods
        void notifyUpdate(
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ uint32_t width,
                /* in */ uint32_t height);
        void notifyUpdateImage(
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ uint32_t width,
                /* in */ uint32_t height,
                /* in */ const std::vector<uint8_t> &image);
        void notifyChange(
                /* in */ uint32_t screenId,
                /* in */ uint32_t xOrigin,
                /* in */ uint32_t yOrigin,
                /* in */ uint32_t width,
                /* in */ uint32_t height);
        bool videoModeSupported(
                /* in */ uint32_t width,
                /* in */ uint32_t height,
                /* in */ uint32_t bpp);
        uint32_t getVisibleRegion(
                /* in */ uint8_t *rectangles,
                /* in */ uint32_t count);
        void setVisibleRegion(
                /* in */ uint8_t *rectangles,
                /* in */ uint32_t count);
        void processVHWACommand(
                /* in */ uint8_t *command
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(5, 2, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 36) )
              , /* in */ int32_t enmCmd,
                /* in */ bool fromGuest
#endif
                );
        void notify3DEvent(
                /* in */ uint32_t type,
                /* in */ const std::vector<uint8_t> &data);
    };

    class LIBVBOX_API IFramebufferOverlay : public IFramebuffer
    {
    public:
        COM_WRAPPED(::IFramebufferOverlay)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, x)
        VBox_PROPERTY_RO(uint32_t, y)
        VBox_PROPERTY_RW_V(bool, visible)
        VBox_PROPERTY_RW_V(uint32_t, alpha)

        // Methods
        void move(
                /* in */ uint32_t x,
                /* in */ uint32_t y);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API IGuestScreenInfo : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IGuestScreenInfo)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, screenId)
        VBox_PROPERTY_RO(GuestMonitorStatus, guestMonitorStatus)
        VBox_PROPERTY_RO(bool, primary)
        VBox_PROPERTY_RO(bool, origin)
        VBox_PROPERTY_RO(int32_t, originX)
        VBox_PROPERTY_RO(int32_t, originY)
        VBox_PROPERTY_RO(uint32_t, width)
        VBox_PROPERTY_RO(uint32_t, height)
        VBox_PROPERTY_RO(uint32_t, bitsPerPixel)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        VBox_PROPERTY_RO(std::wstring, extendedInfo)
#endif
    };
#endif

    class LIBVBOX_API IDisplay : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IDisplay)

        // Attributes
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestScreenInfo>>, guestScreenLayout)
#endif

        // Methods
        void getScreenResolution(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height,
                /* out */ uint32_t &bitsPerPixel,
                /* out */ int32_t &xOrigin,
                /* out */ int32_t &yOrigin,
                /* out */ GuestMonitorStatus &guestMonitorStatus);
        std::wstring attachFramebuffer(
                /* in */ uint32_t screenId,
                /* in */ const COMPtr<IFramebuffer> &framebuffer);
        void detachFramebuffer(
                /* in */ uint32_t screenId,
                /* in */ const std::wstring &id);
        COMPtr<IFramebuffer> queryFramebuffer(
                /* in */ uint32_t screenId);
        void setVideoModeHint(
                /* in */ uint32_t display,
                /* in */ bool enabled,
                /* in */ bool changeOrigin,
                /* in */ int32_t originX,
                /* in */ int32_t originY,
                /* in */ uint32_t width,
                /* in */ uint32_t height,
                /* in */ uint32_t bitsPerPixel);
        void setSeamlessMode(
                /* in */ bool enabled);
        void takeScreenShot(
                /* in */ uint32_t screenId,
                /* in */ uint8_t *address,
                /* in */ uint32_t width,
                /* in */ uint32_t height,
                /* in */ BitmapFormat bitmapFormat);
        std::vector<uint8_t> takeScreenShotToArray(
                /* in */ uint32_t screenId,
                /* in */ uint32_t width,
                /* in */ uint32_t height,
                /* in */ BitmapFormat bitmapFormat);
        void drawToScreen(
                /* in */ uint32_t screenId,
                /* in */ uint8_t *address,
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ uint32_t width,
                /* in */ uint32_t height);
        void invalidateAndUpdate();
        void invalidateAndUpdateScreen(
                /* in */ uint32_t screenId);
        void completeVHWACommand(
                /* in */ uint8_t *command);
        void viewportChanged(
                /* in */ uint32_t screenId,
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ uint32_t width,
                /* in */ uint32_t height);
        void querySourceBitmap(
                /* in  */ uint32_t screenId,
                /* out */ COMPtr<IDisplaySourceBitmap> &displaySourceBitmap);
        void notifyScaleFactorChange(
                /* in */ uint32_t screenId,
                /* in */ uint32_t u32ScaleFactorWMultiplied,
                /* in */ uint32_t u32ScaleFactorHMultiplied);
        void notifyHiDPIOutputPolicyChange(
                /* in */ bool fUnscaledHiDPI);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        void setScreenLayout(
                /* in */ ScreenLayoutMode screenLayoutMode,
                /* in */ const std::vector<COMPtr<IGuestScreenInfo>> &guestScreenInfo);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        void detachScreens(
                /* in */ const std::vector<int32_t> &screenIds);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IGuestScreenInfo> createGuestScreenInfo(
                /* in */ uint32_t display,
                /* in */ GuestMonitorStatus status,
                /* in */ bool primary,
                /* in */ bool changeOrigin,
                /* in */ int32_t originX,
                /* in */ int32_t originY,
                /* in */ uint32_t width,
                /* in */ uint32_t height,
                /* in */ uint32_t bitsPerPixel);
#endif
    };

    class LIBVBOX_API INetworkAdapter : public COMWrapBase
    {
    public:
        COM_WRAPPED(::INetworkAdapter)

        // Attributes
        VBox_PROPERTY_RW_V(NetworkAdapterType, adapterType)
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(std::wstring, MACAddress)
        VBox_PROPERTY_RW_V(NetworkAttachmentType, attachmentType)
        VBox_PROPERTY_RW_R(std::wstring, bridgedInterface)
        VBox_PROPERTY_RW_R(std::wstring, hostOnlyInterface)
        VBox_PROPERTY_RW_R(std::wstring, internalNetwork)
        VBox_PROPERTY_RW_R(std::wstring, NATNetwork)
        VBox_PROPERTY_RW_R(std::wstring, genericDriver)
        VBox_PROPERTY_RW_V(bool, cableConnected)
        VBox_PROPERTY_RW_V(uint32_t, lineSpeed)
        VBox_PROPERTY_RW_V(NetworkAdapterPromiscModePolicy, promiscModePolicy)
        VBox_PROPERTY_RW_V(bool, traceEnabled)
        VBox_PROPERTY_RW_R(std::wstring, traceFile)
        VBox_PROPERTY_RO(COMPtr<INATEngine>, NATEngine)
        VBox_PROPERTY_RW_V(uint32_t, bootPriority)
        VBox_PROPERTY_RW_R(COMPtr<IBandwidthGroup>, bandwidthGroup)

        // Methods
        std::wstring getProperty(
                /* in */ const std::wstring &key);
        void setProperty(
                /* in */ const std::wstring &key,
                /* in */ const std::wstring &value);
        std::vector<std::wstring> getProperties(
                /* in  */ const std::wstring &names,
                /* out */ std::vector<std::wstring> &returnNames);
    };

    class LIBVBOX_API ISerialPort : public COMWrapBase
    {
    public:
        COM_WRAPPED(::ISerialPort)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, IOBase)
        VBox_PROPERTY_RW_V(uint32_t, IRQ)
        VBox_PROPERTY_RW_V(PortMode, hostMode)
        VBox_PROPERTY_RW_V(bool, server)
        VBox_PROPERTY_RW_R(std::wstring, path)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(UartType, uartType)
#endif
    };

    class LIBVBOX_API IParallelPort : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IParallelPort)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, IOBase)
        VBox_PROPERTY_RW_V(uint32_t, IRQ)
        VBox_PROPERTY_RW_R(std::wstring, path)
    };

    class LIBVBOX_API IMachineDebugger : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IMachineDebugger)

        // Attributes
        VBox_PROPERTY_RW_V(bool, singleStep)
        VBox_PROPERTY_RW_V(bool, recompileUser)
        VBox_PROPERTY_RW_V(bool, recompileSupervisor)
        VBox_PROPERTY_RW_V(bool, executeAllInIEM)
        VBox_PROPERTY_RW_V(bool, PATMEnabled)
        VBox_PROPERTY_RW_V(bool, CSAMEnabled)
        VBox_PROPERTY_RW_V(bool, logEnabled)
        VBox_PROPERTY_RO(std::wstring, logDbgFlags)
        VBox_PROPERTY_RO(std::wstring, logDbgGroups)
        VBox_PROPERTY_RO(std::wstring, logDbgDestinations)
        VBox_PROPERTY_RO(std::wstring, logRelFlags)
        VBox_PROPERTY_RO(std::wstring, logRelGroups)
        VBox_PROPERTY_RO(std::wstring, logRelDestinations)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(VMExecutionEngine, executionEngine)
#endif
        VBox_PROPERTY_RO(bool, HWVirtExEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExNestedPagingEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExVPIDEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExUXEnabled)
        VBox_PROPERTY_RO(std::wstring, OSName)
        VBox_PROPERTY_RO(std::wstring, OSVersion)
        VBox_PROPERTY_RO(bool, PAEEnabled)
        VBox_PROPERTY_RW_V(uint32_t, virtualTimeRate)
        VBox_PROPERTY_RO(int64_t, VM)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 4)
        VBox_PROPERTY_RO(int64_t, uptime)
#endif

        // Methods
        void dumpGuestCore(
                /* in */ const std::wstring &filename,
                /* in */ const std::wstring &compression);
        void dumpHostProcessCore(
                /* in */ const std::wstring &filename,
                /* in */ const std::wstring &compression);
        std::wstring info(
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &args);
        void injectNMI();
        void modifyLogGroups(
                /* in */ const std::wstring &settings);
        void modifyLogFlags(
                /* in */ const std::wstring &settings);
        void modifyLogDestinations(
                /* in */ const std::wstring &settings);
        std::vector<uint8_t> readPhysicalMemory(
                /* in  */ int64_t address,
                /* in  */ uint32_t size);
        void writePhysicalMemory(
                /* in */ int64_t address,
                /* in */ uint32_t size,
                /* in */ const std::vector<uint8_t> &bytes);
        std::vector<uint8_t> readVirtualMemory(
                /* in */ uint32_t cpuId,
                /* in */ int64_t address,
                /* in */ uint32_t size);
        void writeVirtualMemory(
                /* in */ uint32_t cpuId,
                /* in */ int64_t address,
                /* in */ uint32_t size,
                /* in */ const std::vector<uint8_t> &bytes);
        std::wstring loadPlugIn(
                /* in */ const std::wstring &name);
        void unloadPlugIn(
                /* in */ const std::wstring &name);
        std::wstring detectOS();
        std::wstring queryOSKernelLog(
                /* in */ uint32_t maxMessages);
        std::wstring getRegister(
                /* in */ uint32_t cpuId,
                /* in */ const std::wstring &name);
        void getRegisters(
                /* in  */ uint32_t cpuId,
                /* out */ std::vector<std::wstring> &names,
                /* out */ std::vector<std::wstring> &values);
        void setRegister(
                /* in */ uint32_t cpuId,
                /* in */ const std::wstring &name,
                /* in */ const std::wstring &value);
        void setRegisters(
                /* in */ uint32_t cpuId,
                /* in */ const std::vector<std::wstring> &names,
                /* in */ const std::vector<std::wstring> &values);
        std::wstring dumpGuestStack(
                /* in */ uint32_t cpuId);
        void resetStats(
                /* in */ const std::wstring &pattern);
        void dumpStats(
                /* in */ const std::wstring &pattern);
        std::wstring getStats(
                /* in */ const std::wstring &pattern,
                /* in */ bool withDescriptions);
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

        // Attributes
        VBox_PROPERTY_RO(std::wstring, id)
        VBox_PROPERTY_RO(uint16_t, vendorId)
        VBox_PROPERTY_RO(uint16_t, productId)
        VBox_PROPERTY_RO(uint16_t, revision)
        VBox_PROPERTY_RO(std::wstring, manufacturer)
        VBox_PROPERTY_RO(std::wstring, product)
        VBox_PROPERTY_RO(std::wstring, serialNumber)
        VBox_PROPERTY_RO(std::wstring, address)
        VBox_PROPERTY_RO(uint16_t, port)
        VBox_PROPERTY_RO(uint16_t, version)
        VBox_PROPERTY_RO(uint16_t, portVersion)
        VBox_PROPERTY_RO(USBConnectionSpeed, speed)
        VBox_PROPERTY_RO(bool, remote)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 0, 14)
        VBox_PROPERTY_RO(std::vector<std::wstring>, deviceInfo)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(std::wstring, backend)
#endif
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

        // Attributes
        VBox_PROPERTY_RO(std::wstring, name)
        VBox_PROPERTY_RO(std::wstring, hostPath)
        VBox_PROPERTY_RO(bool, accessible)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(bool, writable)
        VBox_PROPERTY_RW_V(bool, autoMount)
        VBox_PROPERTY_RW_R(std::wstring, autoMountPoint)
#else
        VBox_PROPERTY_RO(bool, writable)
        VBox_PROPERTY_RO(bool, autoMount)
#endif
        VBox_PROPERTY_RO(std::wstring, lastAccessError)
    };

    class LIBVBOX_API IInternalSessionControl : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IInternalSessionControl)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, PID)
        VBox_PROPERTY_RO(COMPtr<IConsole>, remoteConsole)
        VBox_PROPERTY_RO(MachineState, nominalState)

        // Methods
        void assignRemoteMachine(
                /* in */ const COMPtr<IMachine> &machine,
                /* in */ const COMPtr<IConsole> &console);
        void updateMachineState(
                /* in */ MachineState machineState);
        void uninitialize();
        void onNetworkAdapterChange(
                /* in */ const COMPtr<INetworkAdapter> &networkAdapter,
                /* in */ bool changeAdapter);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        void onAudioAdapterChange(
                /* in */ const COMPtr<IAudioAdapter> &audioAdapter);
#endif
        void onSerialPortChange(
                /* in */ const COMPtr<ISerialPort> &serialPort);
        void onParallelPortChange(
                /* in */ const COMPtr<IParallelPort> &parallelPort);
        void onStorageControllerChange();
        void onMediumChange(
                /* in */ const COMPtr<IMediumAttachment> &mediumAttachment,
                /* in */ bool force);
        void onStorageDeviceChange(
                /* in */ const COMPtr<IMediumAttachment> &mediumAttachment,
                /* in */ bool remove,
                /* in */ bool silent);
        void onClipboardModeChange(
                /* in */ ClipboardMode clipboardMode);
        void onDnDModeChange(
                /* in */ DnDMode dndMode);
        void onCPUChange(
                /* in */ uint32_t cpu,
                /* in */ bool add);
        void onCPUExecutionCapChange(
                /* in */ uint32_t executionCap);
        void onVRDEServerChange(
                /* in */ bool restart);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void onRecordingChange(
                /* in */ bool enable);
#else
        void onVideoCaptureChange();
#endif
        void onUSBControllerChange();
        void onSharedFolderChange(
                /* in */ bool global);
        void onUSBDeviceAttach(
                /* in */ const COMPtr<IUSBDevice> &device,
                /* in */ const COMPtr<IVirtualBoxErrorInfo> &error,
                /* in */ uint32_t maskedInterfaces,
                /* in */ const std::wstring &captureFilename);
        void onUSBDeviceDetach(
                /* in */ const std::wstring &id,
                /* in */ const COMPtr<IVirtualBoxErrorInfo> &error);
        void onShowWindow(
                /* in  */ bool check,
                /* out */ bool &canShow,
                /* out */ int64_t &winId);
        void onBandwidthGroupChange(
                /* in */ const COMPtr<IBandwidthGroup> &bandwidthGroup);
        void accessGuestProperty(
                /* in  */ const std::wstring &name,
                /* in  */ const std::wstring &value,
                /* in  */ const std::wstring &flags,
                /* in  */ uint32_t accessMode,
                /* out */ std::wstring &retValue,
                /* out */ int64_t &retTimestamp,
                /* out */ std::wstring &retFlags);
        void enumerateGuestProperties(
                /* in  */ const std::wstring &patterns,
                /* out */ std::vector<std::wstring> &keys,
                /* out */ std::vector<std::wstring> &values,
                /* out */ std::vector<int64_t> &timestamps,
                /* out */ std::vector<std::wstring> &flags);
        void onlineMergeMedium(
                /* in */ const COMPtr<IMediumAttachment> &mediumAttachment,
                /* in */ uint32_t sourceIdx,
                /* in */ uint32_t targetIdx,
                /* in */ const COMPtr<IProgress> &progress);
        void reconfigureMediumAttachments(
                /* in */ const std::vector<COMPtr<IMediumAttachment>> &attachments);
        void enableVMMStatistics(
                /* in */ bool enable);
        void pauseWithReason(
                /* in */ Reason reason);
        void resumeWithReason(
                /* in */ Reason reason);
        bool saveStateWithReason(
                /* in */ Reason reason,
                /* in */ const COMPtr<IProgress> &progress,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                /* in */ const COMPtr<ISnapshot> &snapshot,
#endif
                /* in */ const std::wstring &stateFilePath,
                /* in */ bool pauseVM);
        void cancelSaveStateWithReason();
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
        void checkMachineError(
                /* in */ const COMPtr<IMachine> &machine);
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
        bool waitProcessed(
                /* in */ int32_t timeout);
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
    };

    class LIBVBOX_API ISnapshotDeletedEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotDeletedEvent)
    };

    class LIBVBOX_API ISnapshotRestoredEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotRestoredEvent)
    };

    class LIBVBOX_API ISnapshotChangedEvent : public ISnapshotEvent
    {
    public:
        COM_WRAPPED(::ISnapshotChangedEvent)
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
    };

    class LIBVBOX_API IVRDEServerChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVRDEServerChangedEvent)
    };

    class LIBVBOX_API IVRDEServerInfoChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVRDEServerInfoChangedEvent)
    };

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IVideoCaptureChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVideoCaptureChangedEvent)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IRecordingChangedEvent)
    };
#endif

    class LIBVBOX_API IUSBControllerChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IUSBControllerChangedEvent)
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
        void addVeto(
                /* in */ const std::wstring &reason);
        bool isVetoed();
        std::vector<std::wstring> getVetos();
        void addApproval(
                /* in */ const std::wstring &reason);
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
    };
#endif

#if defined(VBOX_MSCOM) && (VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0))
    class LIBVBOX_API IVBoxSVCRegistration : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVBoxSVCRegistration)

        // TODO
    };

    class LIBVBOX_API IVirtualBoxSDS : public COMWrapBase
    {
    public:
        COM_WRAPPED(::IVirtualBoxSDS)

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
