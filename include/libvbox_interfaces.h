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
    class LIBVBOX_API IVirtualBoxErrorInfo : public COMErrorInfo
    {
    public:
        COM_WRAPPED(::IVirtualBoxErrorInfo)

        // Attributes
        VBox_PROPERTY_RO(int32_t, resultCode);
        VBox_PROPERTY_RO(int32_t, resultDetail);
        VBox_PROPERTY_RO(COMString, interfaceID);
        VBox_PROPERTY_RO(COMString, component);
        VBox_PROPERTY_RO(COMString, text);
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, next);
    };

    class LIBVBOX_API INATNetwork : public COMUnknown
    {
    public:
        COM_WRAPPED(::INATNetwork)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, networkName)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(COMString, network)
        VBox_PROPERTY_RO(COMString, gateway)
        VBox_PROPERTY_RW_V(bool, IPv6Enabled)
        VBox_PROPERTY_RW_R(COMString, IPv6Prefix)
        VBox_PROPERTY_RW_V(bool, advertiseDefaultIPv6RouteEnabled)
        VBox_PROPERTY_RW_V(bool, needDhcpServer)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::vector<COMString>, portForwardRules4)
        VBox_PROPERTY_RO(std::vector<COMString>, localMappings)
        VBox_PROPERTY_RW_V(int32_t, loopbackIp6)
        VBox_PROPERTY_RO(std::vector<COMString>, portForwardRules6)

        // Methods
        void addLocalMapping(
                /* in */ const COMString &hostid,
                /* in */ int32_t offset);
        void addPortForwardRule(
                /* in */ bool isIpv6,
                /* in */ const COMString &ruleName,
                /* in */ NATProtocol proto,
                /* in */ const COMString &hostIP,
                /* in */ uint16_t hostPort,
                /* in */ const COMString &guestIP,
                /* in */ uint16_t guestPort);
        void removePortForwardRule(
                /* in */ bool iSipv6,
                /* in */ const COMString &ruleName);
        void start(
                /* in */ const COMString &trunkType);
        void stop();
    };

    class LIBVBOX_API IDHCPServer : public COMUnknown
    {
    public:
        COM_WRAPPED(::IDHCPServer)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RO(COMString, IPAddress)
        VBox_PROPERTY_RO(COMString, networkMask)
        VBox_PROPERTY_RO(COMString, networkName)
        VBox_PROPERTY_RO(COMString, lowerIP)
        VBox_PROPERTY_RO(COMString, upperIP)
        VBox_PROPERTY_RO(std::vector<COMString>, globalOptions)
        VBox_PROPERTY_RO(std::vector<COMString>, vmConfigs)

        // Methods
        void addGlobalOption(
                /* in */ DhcpOpt option,
                /* in */ const COMString &value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeGlobalOption(
                /* in */ DhcpOpt option);
        void removeGlobalOptions();
#endif
        void addVmSlotOption(
                /* in */ const COMString &vmname,
                /* in */ int32_t slot,
                /* in */ DhcpOpt option,
                /* in */ const COMString &value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeVmSlotOption(
                /* in */ const COMString& vmname,
                /* in */ int32_t slot,
                /* in */ DhcpOpt option);
#endif
        void removeVmSlotOptions(
                /* in */ const COMString &vmname,
                /* in */ int32_t slot);
        std::vector<COMString> getVmSlotOptions(
                /* in */ const COMString &vmname,
                /* in */ int32_t slot);
        std::vector<COMString> getMacOptions(
                /* in */ const COMString &mac);
        void setConfiguration(
                /* in */ const COMString &IPAddress,
                /* in */ const COMString &networkMask,
                /* in */ const COMString &FromIPAddress,
                /* in */ const COMString &ToIPAddress);
        void start(
                /* in */ const COMString &networkName,
                /* in */ const COMString &trunkName,
                /* in */ const COMString &trunkType);
        void stop();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void restart();
#endif
    };

    class LIBVBOX_API IVirtualBox : public COMUnknown
    {
    public:
        COM_WRAPPED(::IVirtualBox)

        // Attributes
        VBox_PROPERTY_RO(COMString, version)
        VBox_PROPERTY_RO(COMString, versionNormalized)
        VBox_PROPERTY_RO(uint32_t, revision)
        VBox_PROPERTY_RO(COMString, packageType)
        VBox_PROPERTY_RO(COMString, APIVersion)
        VBox_PROPERTY_RO(int64_t, APIRevision)
        VBox_PROPERTY_RO(COMString, homeFolder)
        VBox_PROPERTY_RO(COMString, settingsFilePath)
        VBox_PROPERTY_RO(COMPtr<IHost>, host)
        VBox_PROPERTY_RO(COMPtr<ISystemProperties>, systemProperties)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMachine>>, machines)
        VBox_PROPERTY_RO(std::vector<COMString>, machineGroups)
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
        VBox_PROPERTY_RO(std::vector<COMString>, internalNetworks)
        VBox_PROPERTY_RO(std::vector<COMString>, genericNetworkDrivers)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(COMPtr<ICloudProviderManager>, cloudProviderManager)
#endif

        // Methods
        COMString composeMachineFilename(
                /* in */ const COMString &name,
                /* in */ const COMString &group,
                /* in */ const COMString &createFlags,
                /* in */ const COMString &baseFolder);
        COMPtr<IMachine> createMachine(
                /* in */ const COMString &settingsFile,
                /* in */ const COMString &name,
                /* in */ const std::vector<COMString> &groups,
                /* in */ const COMString &osTypeId,
                /* in */ const COMString &flags);
        COMPtr<IMachine> openMachine(
                /* in */ const COMString &settingsFile);
        void registerMachine(
                /* in */ const COMPtr<IMachine> &machine);
        COMPtr<IMachine> findMachine(
                /* in */ const COMString &nameOrId);
        std::vector<COMPtr<IMachine>> getMachinesByGroups(
                /* in */ const std::vector<COMString> &groups);
        std::vector<MachineState> getMachineStates(
                /* in */ const std::vector<COMPtr<IMachine>> &machines);
        COMPtr<IAppliance> createAppliance();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        COMPtr<IUnattended> createUnattendedInstaller();
#endif
        COMPtr<IMedium> createMedium(
                /* in */ const COMString &format,
                /* in */ const COMString &location,
                /* in */ AccessMode accessMode,
                /* in */ DeviceType aADeviceTypeType);
        COMPtr<IMedium> openMedium(
                /* in */ const COMString &location,
                /* in */ DeviceType deviceType,
                /* in */ AccessMode accessMode,
                /* in */ bool forceNewUuid);
        COMPtr<IGuestOSType> getGuestOSType(
                /* in */ const COMString &id);
        void createSharedFolder(
                /* in */ const COMString &name,
                /* in */ const COMString &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const COMString &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const COMString &name);
        std::vector<COMString> getExtraDataKeys();
        COMString getExtraData(
                /* in */ const COMString &key);
        void setExtraData(
                /* in */ const COMString &key,
                /* in */ const COMString &value);
        void setSettingsSecret(
                /* in */ const COMString &password);
        COMPtr<IDHCPServer> createDHCPServer(
                /* in */ const COMString &name);
        COMPtr<IDHCPServer> findDHCPServerByNetworkName(
                /* in */ const COMString &name);
        void removeDHCPServer(
                /* in */ const COMPtr<IDHCPServer> &server);
        COMPtr<INATNetwork> createNATNetwork(
                /* in */ const COMString &networkName);
        COMPtr<INATNetwork> findNATNetworkByName(
                /* in */ const COMString &networkName);
        void removeNATNetwork(
                /* in */ const COMPtr<INATNetwork> &network);
        bool checkFirmwarePresent(
                /* in */  FirmwareType firmwareType,
                /* in */  const COMString &version,
                /* out */ COMString &url,
                /* out */ COMString &file);
    };

    class LIBVBOX_API IVFSExplorer : public COMUnknown
    {
    public:
        COM_WRAPPED(::IVFSExplorer)

        // Attributes
        VBox_PROPERTY_RO(COMString, path)
        VBox_PROPERTY_RO(VFSType, type)

        // Methods
        COMPtr<IProgress> update();
        COMPtr<IProgress> cd(
                /* in */ const COMString &dir);
        COMPtr<IProgress> cdUp();
        void entryList(
                /* out */ std::vector<COMString> &names,
                /* out */ std::vector<uint32_t> &types,
                /* out */ std::vector<int64_t> &sizes,
                /* out */ std::vector<uint32_t> &modes);
        std::vector<COMString> exists(
                /* in */ const std::vector<COMString> &names);
        COMPtr<IProgress> remove(
                /* in */ const std::vector<COMString> &names);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API ICertificate : public COMUnknown
    {
    public:
        COM_WRAPPED(::ICertificate)

        // Attributes
        VBox_PROPERTY_RO(CertificateVersion, versionNumber)
        VBox_PROPERTY_RO(COMString, serialNumber)
        VBox_PROPERTY_RO(COMString, signatureAlgorithmOID)
        VBox_PROPERTY_RO(COMString, signatureAlgorithmName)
        VBox_PROPERTY_RO(std::vector<COMString>, issuerName)
        VBox_PROPERTY_RO(std::vector<COMString>, subjectName)
        VBox_PROPERTY_RO(COMString, friendlyName)
        VBox_PROPERTY_RO(COMString, validityPeriodNotBefore)
        VBox_PROPERTY_RO(COMString, validityPeriodNotAfter)
        VBox_PROPERTY_RO(COMString, publicKeyAlgorithmOID)
        VBox_PROPERTY_RO(COMString, publicKeyAlgorithm)
        VBox_PROPERTY_RO(std::vector<uint8_t>, subjectPublicKey)
        VBox_PROPERTY_RO(COMString, issuerUniqueIdentifier)
        VBox_PROPERTY_RO(COMString, subjectUniqueIdentifier)
        VBox_PROPERTY_RO(bool, certificateAuthority)
        VBox_PROPERTY_RO(uint32_t, keyUsage)
        VBox_PROPERTY_RO(std::vector<COMString>, extendedKeyUsage)
        VBox_PROPERTY_RO(std::vector<uint8_t>, rawCertData)
        VBox_PROPERTY_RO(bool, selfSigned)
        VBox_PROPERTY_RO(bool, trusted)
        VBox_PROPERTY_RO(bool, expired)

        // Methods
        bool isCurrentlyExpired();
        COMString queryInfo(
                /* in */ int32_t what);
    };
#endif

    class LIBVBOX_API IAppliance : public COMUnknown
    {
    public:
        COM_WRAPPED(::IAppliance)

        // Attributes
        VBox_PROPERTY_RO(COMString, path)
        VBox_PROPERTY_RO(std::vector<COMString>, disks)
        VBox_PROPERTY_RO(std::vector<COMPtr<IVirtualSystemDescription>>, virtualSystemDescriptions)
        VBox_PROPERTY_RO(std::vector<COMString>, machines)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(COMPtr<ICertificate>, certificate)
#endif

        // Methods
        COMPtr<IProgress> read(
                /* in */ const COMString &file);
        void interpret();
        COMPtr<IProgress> importMachines(
                /* in */ const std::vector<ImportOptions> &options);
        COMPtr<IVFSExplorer> createVFSExplorer(
                /* in */ const COMString &URI);
        COMPtr<IProgress> write(
                /* in */ const COMString &format,
                /* in */ const std::vector<ExportOptions> &options,
                /* in */ const COMString &path);
        std::vector<COMString> getWarnings();
        std::vector<COMString> getPasswordIds();
        std::vector<COMString> getMediumIdsForPasswordId(
                /* in */ const COMString &passwordId);
        void addPasswords(
                /* in */ const std::vector<COMString> &identifiers,
                /* in */ const std::vector<COMString> &passwords);
    };

    class LIBVBOX_API IVirtualSystemDescription : public COMUnknown
    {
    public:
        COM_WRAPPED(::IVirtualSystemDescription)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, count)

        // Methods
        void getDescription(
                /* out */ std::vector<VirtualSystemDescriptionType> &types,
                /* out */ std::vector<COMString> &refs,
                /* out */ std::vector<COMString> &OVFValues,
                /* out */ std::vector<COMString> &VBoxValues,
                /* out */ std::vector<COMString> &extraConfigValues);
        void getDescriptionByType(
                /* in  */ VirtualSystemDescriptionType type,
                /* out */ std::vector<VirtualSystemDescriptionType> &types,
                /* out */ std::vector<COMString> &refs,
                /* out */ std::vector<COMString> &OVFValues,
                /* out */ std::vector<COMString> &VBoxValues,
                /* out */ std::vector<COMString> &extraConfigValues);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeDescriptionByType(
                /* in */ VirtualSystemDescriptionType type);
#endif
        std::vector<COMString> getValuesByType(
                /* in */ VirtualSystemDescriptionType type,
                /* in */ VirtualSystemDescriptionValueType which);
        void setFinalValues(
                /* in */ const std::vector<bool> &enabled,
                /* in */ const std::vector<COMString> &VBoxValues,
                /* in */ const std::vector<COMString> &extraConfigValues);
        void addDescription(
                /* in */ VirtualSystemDescriptionType type,
                /* in */ const COMString &VBoxValue,
                /* in */ const COMString &extraConfigValue);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IUnattended : public COMUnknown
    {
    public:
        COM_WRAPPED(::IUnattended)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, isoPath)
        VBox_PROPERTY_RW_R(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RW_R(COMString, user)
        VBox_PROPERTY_RW_R(COMString, password)
        VBox_PROPERTY_RW_R(COMString, fullUserName)
        VBox_PROPERTY_RW_R(COMString, productKey)
        VBox_PROPERTY_RW_R(COMString, additionsIsoPath)
        VBox_PROPERTY_RW_V(bool, installGuestAdditions)
        VBox_PROPERTY_RW_R(COMString, validationKitIsoPath)
        VBox_PROPERTY_RW_V(bool, installTestExecService)
        VBox_PROPERTY_RW_R(COMString, timeZone)
        VBox_PROPERTY_RW_R(COMString, locale)
        VBox_PROPERTY_RW_R(COMString, language)
        VBox_PROPERTY_RW_R(COMString, country)
        VBox_PROPERTY_RW_R(COMString, proxy)
        VBox_PROPERTY_RW_R(COMString, packageSelectionAdjustments)
        VBox_PROPERTY_RW_R(COMString, hostname)
        VBox_PROPERTY_RW_R(COMString, auxiliaryBasePath)
        VBox_PROPERTY_RW_V(uint32_t, imageIndex)
        VBox_PROPERTY_RW_R(COMString, scriptTemplatePath)
        VBox_PROPERTY_RW_R(COMString, postInstallScriptTemplatePath)
        VBox_PROPERTY_RW_R(COMString, postInstallCommand)
        VBox_PROPERTY_RW_R(COMString, extraInstallKernelParameters)
        VBox_PROPERTY_RO(COMString, detectedOSTypeId)
        VBox_PROPERTY_RO(COMString, detectedOSVersion)
        VBox_PROPERTY_RO(COMString, detectedOSFlavor)
        VBox_PROPERTY_RO(COMString, detectedOSLanguages)
        VBox_PROPERTY_RO(COMString, detectedOSHints)

        // Methods
        void detectIsoOS();
        void prepare();
        void constructMedia();
        void reconfigureVM();
        void done();
    };
#endif

    class LIBVBOX_API IInternalMachineControl : public COMUnknown
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
                /* in */ const COMString &errMsg);
        void runUSBDeviceFilters(
                /* in  */ const COMPtr<IUSBDevice> &device,
                /* out */ bool &matched,
                /* out */ uint32_t &maskedInterfaces);
        void captureUSBDevice(
                /* in */ const COMString &id,
                /* in */ const COMString &captureFilename);
        void detachUSBDevice(
                /* in */ const COMString &id,
                /* in */ bool done);
        void autoCaptureUSBDevices();
        void detachAllUSBDevices(
                /* in */ bool done);
        COMPtr<IProgress> onSessionEnd(
                /* in */ const COMPtr<ISession> &session);
        void finishOnlineMergeMedium();
        void pullGuestProperties(
                /* out */ std::vector<COMString> &names,
                /* out */ std::vector<COMString> &values,
                /* out */ std::vector<int64_t> &timestamps,
                /* out */ std::vector<COMString> &flags);
        void pushGuestProperty(
                /* in */ const COMString &name,
                /* in */ const COMString &value,
                /* in */ int64_t timestamp,
                /* in */ const COMString &flags);
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
                /* in  */ const std::vector<COMString> &authParams,
                /* out */ COMString &result);
#endif
    };

    class LIBVBOX_API IBIOSSettings : public COMUnknown
    {
    public:
        COM_WRAPPED(::IBIOSSettings)

        // Attributes
        VBox_PROPERTY_RW_V(bool, logoFadeIn)
        VBox_PROPERTY_RW_V(bool, logoFadeOut)
        VBox_PROPERTY_RW_V(uint32_t, logoDisplayTime)
        VBox_PROPERTY_RW_R(COMString, logoImagePath)
        VBox_PROPERTY_RW_V(BIOSBootMenuMode, bootMenuMode)
        VBox_PROPERTY_RW_V(bool, ACPIEnabled)
        VBox_PROPERTY_RW_V(bool, IOAPICEnabled)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RW_V(VBox::APICMode, APICMode)
#endif
        VBox_PROPERTY_RW_V(int64_t, timeOffset)
        VBox_PROPERTY_RW_V(bool, PXEDebugEnabled)
        VBox_PROPERTY_RW_R(COMString, nonVolatileStorageFile)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingScreenSettings : public COMUnknown
    {
    public:
        COM_WRAPPED(::IRecordingScreenSettings)

        // Attributes
        VBox_PROPERTY_RW_V(uint32_t, id)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, features)
        VBox_PROPERTY_RW_V(RecordingDestination, destination)
        VBox_PROPERTY_RW_R(COMString, filename)
        VBox_PROPERTY_RW_V(uint32_t, maxTime)
        VBox_PROPERTY_RW_V(uint32_t, maxFileSize)
        VBox_PROPERTY_RW_R(COMString, options)
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

    class LIBVBOX_API IRecordingSettings : public COMUnknown
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

    class LIBVBOX_API IPCIAddress : public COMUnknown
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

    class LIBVBOX_API IPCIDeviceAttachment : public COMUnknown
    {
    public:
        COM_WRAPPED(::IPCIDeviceAttachment)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(bool, isPhysicalDevice)
        VBox_PROPERTY_RO(int32_t, hostAddress)
        VBox_PROPERTY_RO(int32_t, guestAddress)
    };

    class LIBVBOX_API IMachine : public COMUnknown
    {
    public:
        COM_WRAPPED(::IMachine)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IVirtualBox>, parent)
        VBox_PROPERTY_RW_R(std::vector<uint8_t>, icon)
        VBox_PROPERTY_RO(bool, accessible)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, accessError)
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RW_R(COMString, description)
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RW_R(std::vector<COMString>, groups)
        VBox_PROPERTY_RW_R(COMString, OSTypeId)
        VBox_PROPERTY_RW_R(COMString, hardwareVersion)
        VBox_PROPERTY_RW_R(COMString, hardwareUUID)
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
        VBox_PROPERTY_RW_R(COMString, videoCaptureFile)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureWidth)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureHeight)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureRate)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureFPS)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureMaxTime)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureMaxFileSize)
        VBox_PROPERTY_RW_R(COMString, videoCaptureOptions)
#endif
        VBox_PROPERTY_RO(COMPtr<IBIOSSettings>, BIOSSettings)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(COMPtr<IRecordingSettings>, recordingSettings)
#endif
        VBox_PROPERTY_RW_V(FirmwareType, firmwareType)
        VBox_PROPERTY_RW_V(PointingHIDType, pointingHIDType)
        VBox_PROPERTY_RW_V(KeyboardHIDType, keyboardHIDType)
        VBox_PROPERTY_RW_V(bool, HPETEnabled)
        VBox_PROPERTY_RW_V(ChipsetType, chipsetType)
        VBox_PROPERTY_RW_R(COMString, snapshotFolder)
        VBox_PROPERTY_RO(COMPtr<IVRDEServer>, VRDEServer)
        VBox_PROPERTY_RW_V(bool, emulatedUSBCardReaderEnabled)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMediumAttachment>>, mediumAttachments)
        VBox_PROPERTY_RO(std::vector<COMPtr<IUSBController>>, USBControllers)
        VBox_PROPERTY_RO(COMPtr<IUSBDeviceFilters>, USBDeviceFilters)
        VBox_PROPERTY_RO(COMPtr<IAudioAdapter>, audioAdapter)
        VBox_PROPERTY_RO(std::vector<COMPtr<IStorageController>>, storageControllers)
        VBox_PROPERTY_RO(COMString, settingsFilePath)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(COMString, settingsAuxFilePath)
#endif
        VBox_PROPERTY_RO(bool, settingsModified)
        VBox_PROPERTY_RO(SessionState, sessionState)
        VBox_PROPERTY_RO(COMString, sessionName)
        VBox_PROPERTY_RO(uint32_t, sessionPID)
        VBox_PROPERTY_RO(MachineState, state)
        VBox_PROPERTY_RO(int64_t, lastStateChange)
        VBox_PROPERTY_RO(COMString, stateFilePath)
        VBox_PROPERTY_RO(COMString, logFolder)
        VBox_PROPERTY_RO(COMPtr<ISnapshot>, currentSnapshot)
        VBox_PROPERTY_RO(uint32_t, snapshotCount)
        VBox_PROPERTY_RO(bool, currentStateModified)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISharedFolder>>, sharedFolders)
        VBox_PROPERTY_RW_V(ClipboardMode, clipboardMode)
        VBox_PROPERTY_RW_V(DnDMode, dnDMode)
        VBox_PROPERTY_RW_V(bool, teleporterEnabled)
        VBox_PROPERTY_RW_V(uint32_t, teleporterPort)
        VBox_PROPERTY_RW_R(COMString, teleporterAddress)
        VBox_PROPERTY_RW_R(COMString, teleporterPassword)
        VBox_PROPERTY_RW_V(ParavirtProvider, paravirtProvider)
        VBox_PROPERTY_RW_V(FaultToleranceState, faultToleranceState)
        VBox_PROPERTY_RW_V(uint32_t, faultTolerancePort)
        VBox_PROPERTY_RW_R(COMString, faultToleranceAddress)
        VBox_PROPERTY_RW_R(COMString, faultTolerancePassword)
        VBox_PROPERTY_RW_V(uint32_t, faultToleranceSyncInterval)
        VBox_PROPERTY_RW_V(bool, RTCUseUTC)
        VBox_PROPERTY_RW_V(bool, IOCacheEnabled)
        VBox_PROPERTY_RW_V(uint32_t, IOCacheSize)
        VBox_PROPERTY_RO(std::vector<COMPtr<IPCIDeviceAttachment>>, PCIDeviceAssignments)
        VBox_PROPERTY_RO(COMPtr<IBandwidthControl>, bandwidthControl)
        VBox_PROPERTY_RW_V(bool, tracingEnabled)
        VBox_PROPERTY_RW_R(COMString, tracingConfig)
        VBox_PROPERTY_RW_V(bool, allowTracingToAccessVM)
        VBox_PROPERTY_RW_V(bool, autostartEnabled)
        VBox_PROPERTY_RW_V(uint32_t, autostartDelay)
        VBox_PROPERTY_RW_V(AutostopType, autostopType)
        VBox_PROPERTY_RW_R(COMString, defaultFrontend)
        VBox_PROPERTY_RO(bool, USBProxyAvailable)
        VBox_PROPERTY_RW_R(COMString, VMProcessPriority)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RW_R(COMString, paravirtDebug)
        VBox_PROPERTY_RW_R(COMString, CPUProfile)
#endif

        // Methods
        void lockMachine(
                /* in */ const COMPtr<ISession> &session,
                /* in */ LockType lockType);
        COMPtr<IProgress> launchVMProcess(
                /* in */ const COMPtr<ISession> &session,
                /* in */ const COMString &name,
                /* in */ const COMString &environment);
        void setBootOrder(
                /* in */ uint32_t position,
                /* in */ DeviceType device);
        DeviceType getBootOrder(
                /* in */ uint32_t position) const;
        void attachDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ DeviceType type,
                /* in */ const COMPtr<IMedium> &medium);
        void attachDeviceWithoutMedium(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ DeviceType type);
        void detachDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void passthroughDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool passthrough);
        void temporaryEjectDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool temporaryEject);
        void nonRotationalDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool nonRotational);
        void setAutoDiscardForDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool discard);
        void setHotPluggableForDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool hotPluggable);
        void setBandwidthGroupForDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ const COMPtr<IBandwidthGroup> &bandwidthGroup);
        void setNoBandwidthGroupForDevice(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void unmountMedium(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool force);
        void mountMedium(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ const COMPtr<IMedium> &medium,
                /* in */ bool force);
        COMPtr<IMedium> getMedium(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device) const;
        std::vector<COMPtr<IMediumAttachment>> getMediumAttachmentsOfController(
                /* in */ const COMString &name) const;
        COMPtr<IMediumAttachment> getMediumAttachment(
                /* in */ const COMString &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device) const;
        void attachHostPCIDevice(
                /* in */ int32_t hostAddress,
                /* in */ int32_t desiredGuestAddress,
                /* in */ bool tryToUnbind);
        void detachHostPCIDevice(
                /* in */ int32_t hostAddress);
        COMPtr<INetworkAdapter> getNetworkAdapter(
                /* in */ uint32_t slot) const;
        COMPtr<IStorageController> addStorageController(
                /* in */ const COMString &name,
                /* in */ StorageBus connectionType);
        COMPtr<IStorageController> getStorageControllerByName(
                /* in */ const COMString &name) const;
        COMPtr<IStorageController> getStorageControllerByInstance(
                /* in */ StorageBus connectionType,
                /* in */ uint32_t instance) const;
        void removeStorageController(
                /* in */ const COMString &name);
        void setStorageControllerBootable(
                /* in */ const COMString &name,
                /* in */ bool bootable);
        COMPtr<IUSBController> addUSBController(
                /* in */ const COMString &name,
                /* in */ USBControllerType type);
        void removeUSBController(
                /* in */ const COMString &name);
        COMPtr<IUSBController> getUSBControllerByName(
                /* in */ const COMString &name) const;
        uint32_t getUSBControllerCountByType(
                /* in */ USBControllerType type) const;
        COMPtr<ISerialPort> getSerialPort(
                /* in */ uint32_t slot) const;
        COMPtr<IParallelPort> getParallelPort(
                /* in */ uint32_t slot) const;
        std::vector<COMString> getExtraDataKeys();
        COMString getExtraData(
                /* in */ const COMString &key);
        void setExtraData(
                /* in */ const COMString &key,
                /* in */ const COMString &value);
        bool getCPUProperty(
                /* in */ CPUPropertyType property) const;
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
                /* out */ uint32_t &valEdx) const;
#endif
        void getCPUIDLeaf(
                /* in  */ uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                /* in  */ uint32_t idxSub,
#endif
                /* out */ uint32_t &valEax,
                /* out */ uint32_t &valEbx,
                /* out */ uint32_t &valEcx,
                /* out */ uint32_t &valEdx) const;
        void setCPUIDLeaf(
                /* in */ uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                /* in */ uint32_t idxSub,
#endif
                /* in */ uint32_t valEax,
                /* in */ uint32_t valEbx,
                /* in */ uint32_t valEcx,
                /* in */ uint32_t valEdx);
        void removeCPUIDLeaf(
                /* in */ uint32_t idx
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
              , /* in */ uint32_t idxSub
#endif
                );
        void removeAllCPUIDLeaves();
        bool getHWVirtExProperty(
                /* in */ HWVirtExPropertyType property) const;
        void setHWVirtExProperty(
                /* in */ HWVirtExPropertyType property,
                /* in */ bool value);
        COMPtr<IProgress> setSettingsFilePath(
                /* in */ const COMString &settingsFilePath);
        void saveSettings();
        void discardSettings();
        std::vector<COMPtr<IMedium>> unregister(
                /* in */ CleanupMode cleanupMode);
        COMPtr<IProgress> deleteConfig(
                /* in */ const std::vector<COMPtr<IMedium>> &media);
        COMPtr<IVirtualSystemDescription> exportTo(
                /* in */ const COMPtr<IAppliance> &appliance,
                /* in */ const COMString &location);
        COMPtr<ISnapshot> findSnapshot(
                /* in */ const COMString &nameOrId);
        void createSharedFolder(
                /* in */ const COMString &name,
                /* in */ const COMString &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const COMString &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const COMString &name);
        bool canShowConsoleWindow();
        int64_t showConsoleWindow();
        void getGuestProperty(
                /* in  */ const COMString &name,
                /* out */ COMString &value,
                /* out */ int64_t &timestamp,
                /* out */ COMString &flags) const;
        COMString getGuestPropertyValue(
                /* in */ const COMString &property) const;
        int64_t getGuestPropertyTimestamp(
                /* in */ const COMString &property) const;
        void setGuestProperty(
                /* in */ const COMString &property,
                /* in */ const COMString &value,
                /* in */ const COMString &flags);
        void setGuestPropertyValue(
                /* in */ const COMString &property,
                /* in */ const COMString &value);
        void deleteGuestProperty(
                /* in */ const COMString &name) const;
        void enumerateGuestProperties(
                /* in  */ const COMString &patterns,
                /* out */ std::vector<COMString> &names,
                /* out */ std::vector<COMString> &values,
                /* out */ std::vector<int64_t> &timestamps,
                /* out */ std::vector<COMString> &flags) const;
        void querySavedGuestScreenInfo(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t &originX,
                /* out */ uint32_t &originY,
                /* out */ uint32_t &width,
                /* out */ uint32_t &height,
                /* out */ bool &enabled) const;
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
        ParavirtProvider getEffectiveParavirtProvider() const;
        COMString queryLogFilename(
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
                /* in */ const COMString &folder,
                /* in */ const COMString &type);
#endif
        COMPtr<IProgress> saveState();
        void adoptSavedState(
                /* in */ const COMString &savedStateFile);
        void discardSavedState(
                /* in */ bool fRemoveFile);
        COMPtr<IProgress> takeSnapshot(
                /* in  */ const COMString &name,
                /* in  */ const COMString &description,
                /* in  */ bool pause,
                /* out */ COMString &id);
        COMPtr<IProgress> deleteSnapshot(
                /* in */ const COMString &id);
        COMPtr<IProgress> deleteSnapshotAndAllChildren(
                /* in */ const COMString &id);
        COMPtr<IProgress> deleteSnapshotRange(
                /* in */ const COMString &startId,
                /* in */ const COMString &endId);
        COMPtr<IProgress> restoreSnapshot(
                /* in */ const COMPtr<ISnapshot> &snapshot);
        void applyDefaults(
                /* in */ const COMString &flags);
    };

    class LIBVBOX_API IEmulatedUSB : public COMUnknown
    {
    public:
        COM_WRAPPED(::IEmulatedUSB)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMString>, webcams)

        // Methods
        void webcamAttach(
                /* in */ const COMString &path,
                /* in */ const COMString &settings);
        void webcamDetach(
                /* in */ const COMString &path);
    };

    class LIBVBOX_API IVRDEServerInfo : public COMUnknown
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
        VBox_PROPERTY_RO(COMString, user)
        VBox_PROPERTY_RO(COMString, domain)
        VBox_PROPERTY_RO(COMString, clientName)
        VBox_PROPERTY_RO(COMString, clientIP)
        VBox_PROPERTY_RO(uint32_t, clientVersion)
        VBox_PROPERTY_RO(uint32_t, encryptionStyle)
    };

    class LIBVBOX_API IConsole : public COMUnknown
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
                /* in */ const COMString &id,
                /* in */ const COMString &captureFilename);
        COMPtr<IUSBDevice> detachUSBDevice(
                /* in */ const COMString &id);
        COMPtr<IUSBDevice> findUSBDeviceByAddress(
                /* in */ const COMString &name);
        COMPtr<IUSBDevice> findUSBDeviceById(
                /* in */ const COMString &id);
        void createSharedFolder(
                /* in */ const COMString &name,
                /* in */ const COMString &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const COMString &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const COMString &name);
        COMPtr<IProgress> teleport(
                /* in */ const COMString &hostname,
                /* in */ uint32_t tcpport,
                /* in */ const COMString &password,
                /* in */ uint32_t maxDowntime);
        void addDiskEncryptionPassword(
                /* in */ const COMString &id,
                /* in */ const COMString &password,
                /* in */ bool clearOnSuspend);
        void addDiskEncryptionPasswords(
                /* in */ const std::vector<COMString> &ids,
                /* in */ const std::vector<COMString> &passwords,
                /* in */ bool clearOnSuspend);
        void removeDiskEncryptionPassword(
                /* in */ const COMString &id);
        void clearAllDiskEncryptionPasswords();
    };

    class LIBVBOX_API IHostNetworkInterface : public COMUnknown
    {
    public:
        COM_WRAPPED(::IHostNetworkInterface)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, shortName)
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(COMString, networkName)
        VBox_PROPERTY_RO(bool, DHCPEnabled)
        VBox_PROPERTY_RO(COMString, IPAddress)
        VBox_PROPERTY_RO(COMString, networkMask)
        VBox_PROPERTY_RO(bool, IPV6Supported)
        VBox_PROPERTY_RO(COMString, IPV6Address)
        VBox_PROPERTY_RO(uint32_t, IPV6NetworkMaskPrefixLength)
        VBox_PROPERTY_RO(COMString, hardwareAddress)
        VBox_PROPERTY_RO(HostNetworkInterfaceMediumType, mediumType)
        VBox_PROPERTY_RO(HostNetworkInterfaceStatus, status)
        VBox_PROPERTY_RO(HostNetworkInterfaceType, interfaceType)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        VBox_PROPERTY_RO(bool, wireless)
#endif

        // Methods
        void enableStaticIPConfig(
                /* in */ const COMString &IPAddress,
                /* in */ const COMString &networkMask);
        void enableStaticIPConfigV6(
                /* in */ const COMString &IPV6Address,
                /* in */ uint32_t IPV6NetworkMaskPrefixLength);
        void enableDynamicIPConfig();
        void DHCPRediscover();
    };

    class LIBVBOX_API IHostVideoInputDevice : public COMUnknown
    {
    public:
        COM_WRAPPED(::IHostVideoInputDevice)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, path)
        VBox_PROPERTY_RO(COMString, alias)
    };

    class LIBVBOX_API IHost : public COMUnknown
    {
    public:
        COM_WRAPPED(::IHost)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, DVDDrives)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, floppyDrives)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDevice>>, USBDevices)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDeviceFilter>>, USBDeviceFilters)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostNetworkInterface>>, networkInterfaces)
        VBox_PROPERTY_RO(std::vector<COMString>, nameServers)
        VBox_PROPERTY_RO(COMString, domainName)
        VBox_PROPERTY_RO(std::vector<COMString>, searchStrings)
        VBox_PROPERTY_RO(uint32_t, processorCount)
        VBox_PROPERTY_RO(uint32_t, processorOnlineCount)
        VBox_PROPERTY_RO(uint32_t, processorCoreCount)
        VBox_PROPERTY_RO(uint32_t, processorOnlineCoreCount)
        VBox_PROPERTY_RO(uint32_t, memorySize)
        VBox_PROPERTY_RO(uint32_t, memoryAvailable)
        VBox_PROPERTY_RO(COMString, operatingSystem)
        VBox_PROPERTY_RO(COMString, OSVersion)
        VBox_PROPERTY_RO(int64_t, UTCTime)
        VBox_PROPERTY_RO(bool, acceleration3DAvailable)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostVideoInputDevice>>, videoInputDevices)

        // Methods
        uint32_t getProcessorSpeed(
                /* in */ uint32_t cpuId);
        bool getProcessorFeature(
                /* in */ ProcessorFeature feature);
        COMString getProcessorDescription(
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
                /* in */ const COMString &id);
        COMPtr<IHostUSBDeviceFilter> createUSBDeviceFilter(
                /* in */ const COMString name);
        void insertUSBDeviceFilter(
                /* in */ uint32_t position,
                /* in */ const COMPtr<IHostUSBDeviceFilter> &filter);
        void removeUSBDeviceFilter(
                /* in */ uint32_t position);
        COMPtr<IMedium> findHostDVDDrive(
                /* in */ const COMString &name);
        COMPtr<IMedium> findHostFloppyDrive(
                /* in */ const COMString &name);
        COMPtr<IHostNetworkInterface> findHostNetworkInterfaceByName(
                /* in */ const COMString &name);
        COMPtr<IHostNetworkInterface> findHostNetworkInterfaceById(
                /* in */ const COMString &id);
        std::vector<COMPtr<IHostNetworkInterface>> findHostNetworkInterfacesOfType(
                /* in */ HostNetworkInterfaceType type);
        COMPtr<IHostUSBDevice> findUSBDeviceById(
                /* in */ const COMString &id);
        COMPtr<IHostUSBDevice> findUSBDeviceByAddress(
                /* in */ const COMString &name);
        COMString generateMACAddress();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        void addUSBDeviceSource(
                /* in */ const COMString &backend,
                /* in */ const COMString &id,
                /* in */ const COMString &address,
                /* in */ const std::vector<COMString> &propertyNames,
                /* in */ const std::vector<COMString> &propertyValues);
        void removeUSBDeviceSource(
                /* in */ const COMString &id);
#endif
    };

    class LIBVBOX_API ISystemProperties : public COMUnknown
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
        VBox_PROPERTY_RW_R(COMString, defaultMachineFolder)
        VBox_PROPERTY_RW_R(COMString, loggingLevel)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMediumFormat>>, mediumFormats)
        VBox_PROPERTY_RW_R(COMString, defaultHardDiskFormat)
        VBox_PROPERTY_RW_V(int64_t, freeDiskSpaceWarning)
        VBox_PROPERTY_RW_V(uint32_t, freeDiskPercentWarning)
        VBox_PROPERTY_RW_V(int64_t, freeDiskSpaceError)
        VBox_PROPERTY_RW_V(uint32_t, freeDiskSpacePercentError)
        VBox_PROPERTY_RW_R(COMString, VRDEAuthLibrary)
        VBox_PROPERTY_RW_R(COMString, webServiceAuthLibrary)
        VBox_PROPERTY_RW_R(COMString, defaultVRDEExtPack)
        VBox_PROPERTY_RW_V(uint32_t, logHistoryCount)
        VBox_PROPERTY_RO(AudioDriverType, defaultAudioDriver)
        VBox_PROPERTY_RW_R(COMString, autostartDatabasePath)
        VBox_PROPERTY_RW_R(COMString, defaultAdditionsISO)
        VBox_PROPERTY_RW_R(COMString, defaultFrontend)
        VBox_PROPERTY_RO(std::vector<BitmapFormat>, screenShotFormats)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(ProxyMode, proxyMode)
        VBox_PROPERTY_RW_R(COMString, proxyURL)
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

    class LIBVBOX_API IGuestOSType : public COMUnknown
    {
    public:
        COM_WRAPPED(::IGuestOSType)

        // Attributes
        VBox_PROPERTY_RO(COMString, familyId)
        VBox_PROPERTY_RO(COMString, familyDescription)
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(COMString, description)
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

    class LIBVBOX_API IAdditionsFacility : public COMUnknown
    {
    public:
        COM_WRAPPED(::IAdditionsFacility)

        // Attributes
        VBox_PROPERTY_RO(AdditionsFacilityClass, classType)
        VBox_PROPERTY_RO(int64_t, lastUpdated)
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(AdditionsFacilityStatus, status)
        VBox_PROPERTY_RO(AdditionsFacilityType, type)
    };

    class LIBVBOX_API IDnDBase : public COMUnknown
    {
    public:
        COM_WRAPPED(::IDnDBase)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMString>, formats)
        VBox_PROPERTY_RO(uint32_t, protocolVersion)

        // Methods
        bool isFormatSupported(
                /* in */ const COMString &format);
        void addFormats(
                /* in */ const std::vector<COMString> &formats);
        void removeFormats(
                /* in */ const std::vector<COMString> &formats);
    };

    class LIBVBOX_API IDnDSource : public IDnDBase
    {
    public:
        COM_WRAPPED(::IDnDSource)

        // Methods
        DnDAction dragIsPending(
                /* in  */ uint32_t screenId,
                /* out */ std::vector<COMString> &formats,
                /* out */ std::vector<DnDAction> &allowedActions);
        COMPtr<IProgress> drop(
                /* in */ const COMString &format,
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
                /* in */ const std::vector<COMString> &formats);
        DnDAction move(
                /* in */ uint32_t screenId,
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ DnDAction defaultAction,
                /* in */ const std::vector<DnDAction> &allowedActions,
                /* in */ const std::vector<COMString> &formats);
        void leave(
                /* in */ uint32_t screenId);
        DnDAction drop(
                /* in  */ uint32_t screenId,
                /* in  */ uint32_t x,
                /* in  */ uint32_t y,
                /* in  */ DnDAction defaultAction,
                /* in  */ const std::vector<DnDAction> &allowedActions,
                /* in  */ const std::vector<COMString> &formats,
                /* out */ COMString &format);
        COMPtr<IProgress> sendData(
                /* in */ uint32_t screenId,
                /* in */ const COMString& format,
                /* in */ const std::vector<uint8_t> &data);
        bool cancel();
    };

    class LIBVBOX_API IGuestDnDTarget : public IDnDTarget
    {
    public:
        COM_WRAPPED(::IGuestDnDTarget)
    };

    class LIBVBOX_API IGuestSession : public COMUnknown
    {
    public:
        COM_WRAPPED(::IGuestSession)

        // Attributes
        VBox_PROPERTY_RO(COMString, user)
        VBox_PROPERTY_RO(COMString, domain)
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RW_V(uint32_t, timeout)
        VBox_PROPERTY_RO(uint32_t, protocolVersion)
        VBox_PROPERTY_RO(GuestSessionStatus, status)
        VBox_PROPERTY_RW_R(std::vector<COMString>, environmentChanges)
        VBox_PROPERTY_RO(std::vector<COMString>, environmentBase)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestProcess>>, processes)
        VBox_PROPERTY_RO(PathStyle, pathStyle)
        VBox_PROPERTY_RW_R(COMString, currentDirectory)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(COMString, userHome)
        VBox_PROPERTY_RO(COMString, userDocuments)
#endif
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestDirectory>>, directories)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestFile>>, files)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)

        // Methods
        void close();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> copyFromGuest(
                /* in */ const std::vector<COMString> &sources,
                /* in */ const std::vector<COMString> &filters,
                /* in */ const std::vector<COMString> &flags,
                /* in */ const COMString &destination);
        COMPtr<IProgress> copyToGuest(
                /* in */ const std::vector<COMString> &sources,
                /* in */ const std::vector<COMString> &filters,
                /* in */ const std::vector<COMString> &flags,
                /* in */ const COMString &destination);
#endif
        COMPtr<IProgress> directoryCopy(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        COMPtr<IProgress> directoryCopyFromGuest(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        COMPtr<IProgress> directoryCopyToGuest(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        void directoryCreate(
                /* in */ const COMString &path,
                /* in */ uint32_t mode,
                /* in */ const std::vector<DirectoryCreateFlag> &flags);
        COMString directoryCreateTemp(
                /* in */ const COMString &templateName,
                /* in */ uint32_t mode,
                /* in */ const COMString &path,
                /* in */ bool secure);
        bool directoryExists(
                /* in */ const COMString &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestDirectory> directoryOpen(
                /* in */ const COMString &path,
                /* in */ const COMString &filter,
                /* in */ const std::vector<DirectoryOpenFlag> &flags);
        void directoryRemove(
                /* in */ const COMString &path);
        COMPtr<IProgress> directoryRemoveRecursive(
                /* in */ const COMString &path,
                /* in */ const std::vector<DirectoryRemoveRecFlag> &flags);
        void environmentScheduleSet(
                /* in */ const COMString &name,
                /* in */ const COMString &value);
        void environmentScheduleUnset(
                /* in */ const COMString &name);
        COMString environmentGetBaseVariable(
                /* in */ const COMString &name);
        bool environmentDoesBaseVariableExist(
                /* in */ const COMString &name);
        COMPtr<IProgress> fileCopy(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<FileCopyFlag> flags);
        COMPtr<IProgress> fileCopyFromGuest(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IProgress> fileCopyToGuest(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IGuestFile> fileCreateTemp(
                /* in */ const COMString &templateName,
                /* in */ uint32_t mode,
                /* in */ const COMString &path,
                /* in */ bool secure);
        bool fileExists(
                /* in */ const COMString &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestFile> fileOpen(
                /* in */ const COMString &path,
                /* in */ FileAccessMode accessMode,
                /* in */ FileOpenAction openAction,
                /* in */ uint32_t creationMode);
        COMPtr<IGuestFile> fileOpenEx(
                /* in */ const COMString &path,
                /* in */ FileAccessMode accessMode,
                /* in */ FileOpenAction openAction,
                /* in */ FileSharingMode sharingMode,
                /* in */ uint32_t creationMode,
                /* in */ const std::vector<FileOpenExFlag> &flags);
        int64_t fileQuerySize(
                /* in */ const COMString &path,
                /* in */ bool followSymlinks);
        bool fsObjExists(
                /* in */ const COMString &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestFsObjInfo> fsObjQueryInfo(
                /* in */ const COMString &path,
                /* in */ bool followSymlinks);
        void fsObjRemove(
                /* in */ const COMString &path);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> fsObjRemoveArray(
                /* in */ const std::vector<COMString> &path);
#endif
        void fsObjRename(
                /* in */ const COMString &oldPath,
                /* in */ const COMString &newPath,
                /* in */ const std::vector<FsObjRenameFlag> &flags);
        COMPtr<IProgress> fsObjMove(
                /* in */ const COMString &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<FsObjMoveFlag> &flags);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> fsObjMoveArray(
                /* in */ const std::vector<COMString> &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<FsObjMoveFlag> &flags);
        COMPtr<IProgress> fsObjCopyArray(
                /* in */ const std::vector<COMString> &source,
                /* in */ const COMString &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
#endif
        void fsObjSetACL(
                /* in */ const COMString &path,
                /* in */ bool followSymlinks,
                /* in */ const COMString &acl,
                /* in */ uint32_t mode);
        COMPtr<IGuestProcess> processCreate(
                /* in */ const COMString &executable,
                /* in */ const std::vector<COMString> &arguments,
                /* in */ const std::vector<COMString> &environmentChanges,
                /* in */ const std::vector<ProcessCreateFlag> &flags,
                /* in */ uint32_t timeoutMS);
        COMPtr<IGuestProcess> processCreateEx(
                /* in */ const COMString &executable,
                /* in */ const std::vector<COMString> &arguments,
                /* in */ const std::vector<COMString> &environmentChanges,
                /* in */ const std::vector<ProcessCreateFlag> &flags,
                /* in */ uint32_t timeoutMS,
                /* in */ ProcessPriority priority,
                /* in */ const std::vector<int32_t> &affinity);
        COMPtr<IGuestProcess> processGet(
                /* in */ uint32_t pid);
        void symlinkCreate(
                /* in */ const COMString &symlink,
                /* in */ const COMString &target,
                /* in */ SymlinkType type);
        bool symlinkExists(
                /* in */ const COMString &symlink);
        COMString symlinkRead(
                /* in */ const COMString &symlink,
                /* in */ const std::vector<SymlinkReadFlag> &flags);
        GuestSessionWaitResult waitFor(
                /* in */ uint32_t waitFor,
                /* in */ uint32_t timeoutMS);
        GuestSessionWaitResult waitForArray(
                /* in */ const std::vector<GuestSessionWaitForFlag> &waitFor,
                /* in */ uint32_t timeoutMS);
    };

    class LIBVBOX_API IProcess : public COMUnknown
    {
    public:
        COM_WRAPPED(::IProcess)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMString>, arguments)
        VBox_PROPERTY_RO(std::vector<COMString>, environment)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(COMString, executablePath)
        VBox_PROPERTY_RO(int32_t, exitCode)
        VBox_PROPERTY_RO(COMString, name)
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

    class LIBVBOX_API IDirectory : public COMUnknown
    {
    public:
        COM_WRAPPED(::IDirectory)

        // Attributes
        VBox_PROPERTY_RO(COMString, directoryName)
        VBox_PROPERTY_RO(COMString, filter)

        // Methods
        void close();
        COMPtr<IFsObjInfo> read();
    };

    class LIBVBOX_API IGuestDirectory : public IDirectory
    {
    public:
        COM_WRAPPED(::IGuestDirectory)
    };

    class LIBVBOX_API IFile : public COMUnknown
    {
    public:
        COM_WRAPPED(::IFile)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RO(int64_t, initialSize)
        VBox_PROPERTY_RO(int64_t, offset)
        VBox_PROPERTY_RO(FileStatus, status)
        VBox_PROPERTY_RO(COMString, filename)
        VBox_PROPERTY_RO(COMString, fileName)    // Old name for "filename" attribute
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
                /* in */ const COMString &acl,
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

    class LIBVBOX_API IFsObjInfo : public COMUnknown
    {
    public:
        COM_WRAPPED(::IFsObjInfo)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(FsObjType, type)
        VBox_PROPERTY_RO(COMString, fileAttributes)
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
        VBox_PROPERTY_RO(COMString, userName)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(int32_t, GID)
#else
        VBox_PROPERTY_RO(uint32_t, GID)
#endif
        VBox_PROPERTY_RO(COMString, groupName)
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

    class LIBVBOX_API IGuest : public COMUnknown
    {
    public:
        COM_WRAPPED(::IGuest)

        // Attributes
        VBox_PROPERTY_RO(COMString, OSTypeId)
        VBox_PROPERTY_RO(AdditionsRunLevelType, additionsRunLevel)
        VBox_PROPERTY_RO(COMString, additionsVersion)
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
                /* in */ const COMString &userName,
                /* in */ const COMString &password,
                /* in */ const COMString &domain,
                /* in */ bool allowInteractiveLogon);
        COMPtr<IGuestSession> createSession(
                /* in */ const COMString &user,
                /* in */ const COMString &password,
                /* in */ const COMString &domain,
                /* in */ const COMString &sessionName);
        std::vector<COMPtr<IGuestSession>> findSession(
                /* in */ const COMString &sessionName);
        COMPtr<IProgress> updateGuestAdditions(
                /* in */ const COMString &source,
                /* in */ const std::vector<COMString> &arguments,
                /* in */ const std::vector<AdditionsUpdateFlag> &flags);
    };

    class LIBVBOX_API IProgress : public COMUnknown
    {
    public:
        COM_WRAPPED(::IProgress)

        // Attributes
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(COMString, description)
        VBox_PROPERTY_RO(COMPtr<COMUnknown>, initiator)
        VBox_PROPERTY_RO(bool, cancelable)
        VBox_PROPERTY_RO(uint32_t, percent)
        VBox_PROPERTY_RO(int32_t, timeRemaining)
        VBox_PROPERTY_RO(bool, completed)
        VBox_PROPERTY_RO(bool, canceled)
        VBox_PROPERTY_RO(int32_t, resultCode)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, errorInfo)
        VBox_PROPERTY_RO(uint32_t, operationCount)
        VBox_PROPERTY_RO(uint32_t, operation)
        VBox_PROPERTY_RO(COMString, operationDescription)
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
                /* in */ const COMString &nextOperationDescription,
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
    class LIBVBOX_API IInternalProgressControl : public COMUnknown
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
                /* in */ const COMString &nextOperationDescription,
                /* in */ uint32_t nextOperationsWeight);
        void notifyPointOfNoReturn();
        void notifyComplete(
                /* in */ int32_t resultCode,
                /* in */ const COMPtr<IVirtualBoxErrorInfo> &errorInfo);
    };
#endif

    class LIBVBOX_API ISnapshot : public COMUnknown
    {
    public:
        COM_WRAPPED(::ISnapshot)

        // Attributes
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RW_R(COMString, description)
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

    class LIBVBOX_API IMediumAttachment : public COMUnknown
    {
    public:
        COM_WRAPPED(::IMediumAttachment)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMedium>, medium)
        VBox_PROPERTY_RO(COMString, controller)
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

    class LIBVBOX_API IMedium : public COMUnknown
    {
    public:
        COM_WRAPPED(::IMedium)

        // Attributes
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RW_R(COMString, description)
        VBox_PROPERTY_RO(MediumState, state)
        VBox_PROPERTY_RO(std::vector<MediumVariant>, variant)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_R(COMString, location)
#else
        VBox_PROPERTY_RO(COMString, location)
#endif
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(DeviceType, deviceType)
        VBox_PROPERTY_RO(bool, hostDrive)
        VBox_PROPERTY_RO(int64_t, size)
        VBox_PROPERTY_RO(COMString, format)
        VBox_PROPERTY_RO(COMPtr<IMediumFormat>, mediumFormat)
        VBox_PROPERTY_RW_V(MediumType, type)
        VBox_PROPERTY_RO(std::vector<MediumType>, allowedTypes)
        VBox_PROPERTY_RO(COMPtr<IMedium>, parent)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, children)
        VBox_PROPERTY_RO(COMPtr<IMedium>, base)
        VBox_PROPERTY_RO(bool, readOnly)
        VBox_PROPERTY_RO(int64_t, logicalSize)
        VBox_PROPERTY_RW_V(bool, autoReset)
        VBox_PROPERTY_RO(COMString, lastAccessError)
        VBox_PROPERTY_RO(std::vector<COMString>, machineIds)

        // Methods
        void setIds(
                /* in */ bool setImageId,
                /* in */ const COMString &imageId,
                /* in */ bool setParentId,
                /* in */ const COMString &parentId);
        MediumState refreshState();
        std::vector<COMString> getSnapshotIds(
                /* in */ const COMString &machineId);
        COMPtr<IToken> lockRead();
        COMPtr<IToken> lockWrite();
        void close();
        COMString getProperty(
                /* in */ const COMString &name) const;
        void setProperty(
                /* in */ const COMString &name,
                /* in */ const COMString &value);
        std::vector<COMString> getProperties(
                /* in  */ const COMString &names,
                /* out */ std::vector<COMString> &returnNames) const;
        void setProperties(
                /* in */ const std::vector<COMString> &names,
                /* in */ const std::vector<COMString> &values);
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
                /* in */ const COMString &location);     // Old name for moveTo()
        COMPtr<IProgress> moveTo(
                /* in */ const COMString &location);
        COMPtr<IProgress> compact();
        COMPtr<IProgress> resize(
                /* in */ int64_t logicalSize);
        COMPtr<IProgress> reset();
        COMPtr<IProgress> changeEncryption(
                /* in */ const COMString &currentPassword,
                /* in */ const COMString &cipher,
                /* in */ const COMString &newPassword,
                /* in */ const COMString &newPasswordId);
        COMString getEncryptionSettings(
                /* out */ COMString &cipher) const;
        void checkEncryptionPassword(
                /* in */ const COMString &password) const;
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IMediumIO> openForIO(
                /* in */ bool writable,
                /* in */ const COMString &password);
#endif
    };

    class LIBVBOX_API IMediumFormat : public COMUnknown
    {
    public:
        COM_WRAPPED(::IMediumFormat)

        // Attributes
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(std::vector<MediumFormatCapabilities>, capabilities)

        // Methods
        void describeFileExtensions(
                /* out */ std::vector<COMString> &extensions,
                /* out */ std::vector<DeviceType> &types);
        void describeProperties(
                /* out */ std::vector<COMString> &names,
                /* out */ std::vector<COMString> &descriptions,
                /* out */ std::vector<DataType> &types,
                /* out */ std::vector<uint32_t> &flags,
                /* out */ std::vector<COMString> &defaults) const;
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IDataStream : public COMUnknown
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

    class LIBVBOX_API IMediumIO : public COMUnknown
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
                /* in  */ const COMString &format,
                /* in  */ const std::vector<MediumVariant> &variant,
                /* in  */ uint32_t bufferSize,
                /* out */ COMPtr<IDataStream> &stream);
        void close();
    };
#endif

    class LIBVBOX_API IToken : public COMUnknown
    {
    public:
        COM_WRAPPED(::IToken)

        // Methods
        void abandon();
        void dummy();
    };

    class LIBVBOX_API IKeyboard : public COMUnknown
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

    class LIBVBOX_API IMousePointerShape : public COMUnknown
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

    class LIBVBOX_API IMouse : public COMUnknown
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
                /* in */ const COMString &contacts,
                /* in */ uint32_t scanTime);
    };

    class LIBVBOX_API IDisplaySourceBitmap : public COMUnknown
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

    class LIBVBOX_API IFramebuffer : public COMUnknown
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
    class LIBVBOX_API IGuestScreenInfo : public COMUnknown
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
        VBox_PROPERTY_RO(COMString, extendedInfo)
#endif
    };
#endif

    class LIBVBOX_API IDisplay : public COMUnknown
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
        COMString attachFramebuffer(
                /* in */ uint32_t screenId,
                /* in */ const COMPtr<IFramebuffer> &framebuffer);
        void detachFramebuffer(
                /* in */ uint32_t screenId,
                /* in */ const COMString &id);
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

    class LIBVBOX_API INetworkAdapter : public COMUnknown
    {
    public:
        COM_WRAPPED(::INetworkAdapter)

        // Attributes
        VBox_PROPERTY_RW_V(NetworkAdapterType, adapterType)
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(COMString, MACAddress)
        VBox_PROPERTY_RW_V(NetworkAttachmentType, attachmentType)
        VBox_PROPERTY_RW_R(COMString, bridgedInterface)
        VBox_PROPERTY_RW_R(COMString, hostOnlyInterface)
        VBox_PROPERTY_RW_R(COMString, internalNetwork)
        VBox_PROPERTY_RW_R(COMString, NATNetwork)
        VBox_PROPERTY_RW_R(COMString, genericDriver)
        VBox_PROPERTY_RW_V(bool, cableConnected)
        VBox_PROPERTY_RW_V(uint32_t, lineSpeed)
        VBox_PROPERTY_RW_V(NetworkAdapterPromiscModePolicy, promiscModePolicy)
        VBox_PROPERTY_RW_V(bool, traceEnabled)
        VBox_PROPERTY_RW_R(COMString, traceFile)
        VBox_PROPERTY_RO(COMPtr<INATEngine>, NATEngine)
        VBox_PROPERTY_RW_V(uint32_t, bootPriority)
        VBox_PROPERTY_RW_R(COMPtr<IBandwidthGroup>, bandwidthGroup)

        // Methods
        COMString getProperty(
                /* in */ const COMString &key) const;
        void setProperty(
                /* in */ const COMString &key,
                /* in */ const COMString &value);
        std::vector<COMString> getProperties(
                /* in  */ const COMString &names,
                /* out */ std::vector<COMString> &returnNames) const;
    };

    class LIBVBOX_API ISerialPort : public COMUnknown
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
        VBox_PROPERTY_RW_R(COMString, path)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(UartType, uartType)
#endif
    };

    class LIBVBOX_API IParallelPort : public COMUnknown
    {
    public:
        COM_WRAPPED(::IParallelPort)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, IOBase)
        VBox_PROPERTY_RW_V(uint32_t, IRQ)
        VBox_PROPERTY_RW_R(COMString, path)
    };

    class LIBVBOX_API IMachineDebugger : public COMUnknown
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
        VBox_PROPERTY_RO(COMString, logDbgFlags)
        VBox_PROPERTY_RO(COMString, logDbgGroups)
        VBox_PROPERTY_RO(COMString, logDbgDestinations)
        VBox_PROPERTY_RO(COMString, logRelFlags)
        VBox_PROPERTY_RO(COMString, logRelGroups)
        VBox_PROPERTY_RO(COMString, logRelDestinations)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(VMExecutionEngine, executionEngine)
#endif
        VBox_PROPERTY_RO(bool, HWVirtExEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExNestedPagingEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExVPIDEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExUXEnabled)
        VBox_PROPERTY_RO(COMString, OSName)
        VBox_PROPERTY_RO(COMString, OSVersion)
        VBox_PROPERTY_RO(bool, PAEEnabled)
        VBox_PROPERTY_RW_V(uint32_t, virtualTimeRate)
        VBox_PROPERTY_RO(int64_t, VM)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 4)
        VBox_PROPERTY_RO(int64_t, uptime)
#endif

        // Methods
        void dumpGuestCore(
                /* in */ const COMString &filename,
                /* in */ const COMString &compression);
        void dumpHostProcessCore(
                /* in */ const COMString &filename,
                /* in */ const COMString &compression);
        COMString info(
                /* in */ const COMString &name,
                /* in */ const COMString &args);
        void injectNMI();
        void modifyLogGroups(
                /* in */ const COMString &settings);
        void modifyLogFlags(
                /* in */ const COMString &settings);
        void modifyLogDestinations(
                /* in */ const COMString &settings);
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
        COMString loadPlugIn(
                /* in */ const COMString &name);
        void unloadPlugIn(
                /* in */ const COMString &name);
        COMString detectOS();
        COMString queryOSKernelLog(
                /* in */ uint32_t maxMessages);
        COMString getRegister(
                /* in */ uint32_t cpuId,
                /* in */ const COMString &name);
        void getRegisters(
                /* in  */ uint32_t cpuId,
                /* out */ std::vector<COMString> &names,
                /* out */ std::vector<COMString> &values);
        void setRegister(
                /* in */ uint32_t cpuId,
                /* in */ const COMString &name,
                /* in */ const COMString &value);
        void setRegisters(
                /* in */ uint32_t cpuId,
                /* in */ const std::vector<COMString> &names,
                /* in */ const std::vector<COMString> &values);
        COMString dumpGuestStack(
                /* in */ uint32_t cpuId);
        void resetStats(
                /* in */ const COMString &pattern);
        void dumpStats(
                /* in */ const COMString &pattern);
        COMString getStats(
                /* in */ const COMString &pattern,
                /* in */ bool withDescriptions);
    };

    class LIBVBOX_API IUSBDeviceFilters : public COMUnknown
    {
    public:
        COM_WRAPPED(::IUSBDeviceFilters)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IUSBDeviceFilter>>, deviceFilters)

        // Methods
        COMPtr<IUSBDeviceFilter> createDeviceFilter(
                /* in */ const COMString &name);
        void insertDeviceFilter(
                /* in */ uint32_t position,
                /* in */ const COMPtr<IUSBDeviceFilter> &filter);
        COMPtr<IUSBDeviceFilter> removeDeviceFilter(
                /* in */ uint32_t position);
    };

    class LIBVBOX_API IUSBController : public COMUnknown
    {
    public:
        COM_WRAPPED(::IUSBController)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RW_V(USBControllerType, type)
        VBox_PROPERTY_RO(uint16_t, USBStandard)
    };

    class LIBVBOX_API IUSBDevice : public COMUnknown
    {
    public:
        COM_WRAPPED(::IUSBDevice)

        // Attributes
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(uint16_t, vendorId)
        VBox_PROPERTY_RO(uint16_t, productId)
        VBox_PROPERTY_RO(uint16_t, revision)
        VBox_PROPERTY_RO(COMString, manufacturer)
        VBox_PROPERTY_RO(COMString, product)
        VBox_PROPERTY_RO(COMString, serialNumber)
        VBox_PROPERTY_RO(COMString, address)
        VBox_PROPERTY_RO(uint16_t, port)
        VBox_PROPERTY_RO(uint16_t, version)
        VBox_PROPERTY_RO(uint16_t, portVersion)
        VBox_PROPERTY_RO(USBConnectionSpeed, speed)
        VBox_PROPERTY_RO(bool, remote)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 0, 14)
        VBox_PROPERTY_RO(std::vector<COMString>, deviceInfo)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(COMString, backend)
#endif
    };

    class LIBVBOX_API IUSBDeviceFilter : public COMUnknown
    {
    public:
        COM_WRAPPED(::IUSBDeviceFilter)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RW_V(bool, active)
        VBox_PROPERTY_RW_R(COMString, vendorId)
        VBox_PROPERTY_RW_R(COMString, productId)
        VBox_PROPERTY_RW_R(COMString, revision)
        VBox_PROPERTY_RW_R(COMString, manufacturer)
        VBox_PROPERTY_RW_R(COMString, product)
        VBox_PROPERTY_RW_R(COMString, serialNumber)
        VBox_PROPERTY_RW_R(COMString, port)
        VBox_PROPERTY_RW_R(COMString, remote)
        VBox_PROPERTY_RW_V(uint32_t, maskedInterfaces)
    };

    class LIBVBOX_API IHostUSBDevice : public IUSBDevice
    {
    public:
        COM_WRAPPED(::IHostUSBDevice)

        // Attributes
        VBox_PROPERTY_RO(USBDeviceState, state)
    };

    class LIBVBOX_API IHostUSBDeviceFilter : public IUSBDeviceFilter
    {
    public:
        COM_WRAPPED(::IHostUSBDeviceFilter)

        // Attributes
        VBox_PROPERTY_RW_V(USBDeviceFilterAction, action)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API IUSBProxyBackend : public COMUnknown
    {
    public:
        COM_WRAPPED(::IUSBProxyBackend)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, type)
    };
#endif

    class LIBVBOX_API IAudioAdapter : public COMUnknown
    {
    public:
        COM_WRAPPED(::IAudioAdapter)

        // Attributes
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(bool, enabledIn)
        VBox_PROPERTY_RW_V(bool, enabledOut)
        VBox_PROPERTY_RW_V(AudioControllerType, audioController)
        VBox_PROPERTY_RW_V(AudioCodecType, audioCodec)
        VBox_PROPERTY_RW_V(AudioDriverType, audioDriver)
        VBox_PROPERTY_RO(std::vector<COMString>, propertiesList)

        // Methods
        void setProperty(
                /* in */ const COMString &key,
                /* in */ const COMString &value);
        COMString getProperty(
                /* in */ const COMString &key) const;
    };

    class LIBVBOX_API IVRDEServer : public COMUnknown
    {
    public:
        COM_WRAPPED(::IVRDEServer)

        // Attributes
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(AuthType, authType)
        VBox_PROPERTY_RW_V(uint32_t, authTimeout)
        VBox_PROPERTY_RW_V(bool, allowMultiConnection)
        VBox_PROPERTY_RW_V(bool, reuseSingleConnection)
        VBox_PROPERTY_RW_R(COMString, VRDEExtPack)
        VBox_PROPERTY_RW_R(COMString, authLibrary)
        VBox_PROPERTY_RO(std::vector<COMString>, VRDEProperties)

        // Methods
        void setVRDEProperty(
                /* in */ const COMString &key,
                /* in */ const COMString &value);
        COMString getVRDEProperty(
                /* in */ const COMString &key) const;
    };

    class LIBVBOX_API ISharedFolder : public COMUnknown
    {
    public:
        COM_WRAPPED(::ISharedFolder)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, hostPath)
        VBox_PROPERTY_RO(bool, accessible)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(bool, writable)
        VBox_PROPERTY_RW_V(bool, autoMount)
        VBox_PROPERTY_RW_R(COMString, autoMountPoint)
#else
        VBox_PROPERTY_RO(bool, writable)
        VBox_PROPERTY_RO(bool, autoMount)
#endif
        VBox_PROPERTY_RO(COMString, lastAccessError)
    };

    class LIBVBOX_API IInternalSessionControl : public COMUnknown
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
                /* in */ const COMString &captureFilename);
        void onUSBDeviceDetach(
                /* in */ const COMString &id,
                /* in */ const COMPtr<IVirtualBoxErrorInfo> &error);
        void onShowWindow(
                /* in  */ bool check,
                /* out */ bool &canShow,
                /* out */ int64_t &winId);
        void onBandwidthGroupChange(
                /* in */ const COMPtr<IBandwidthGroup> &bandwidthGroup);
        void accessGuestProperty(
                /* in  */ const COMString &name,
                /* in  */ const COMString &value,
                /* in  */ const COMString &flags,
                /* in  */ uint32_t accessMode,
                /* out */ COMString &retValue,
                /* out */ int64_t &retTimestamp,
                /* out */ COMString &retFlags);
        void enumerateGuestProperties(
                /* in  */ const COMString &patterns,
                /* out */ std::vector<COMString> &keys,
                /* out */ std::vector<COMString> &values,
                /* out */ std::vector<int64_t> &timestamps,
                /* out */ std::vector<COMString> &flags) const;
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
                /* in */ const COMString &stateFilePath,
                /* in */ bool pauseVM);
        void cancelSaveStateWithReason();
    };

    class LIBVBOX_API ISession : public COMUnknown
    {
    public:
        COM_WRAPPED(::ISession)

        // Attributes
        VBox_PROPERTY_RO(SessionState, state)
        VBox_PROPERTY_RO(SessionType, type)
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RO(COMPtr<IConsole>, console)

        // Methods
        void unlockMachine();
    };

    class LIBVBOX_API IStorageController : public COMUnknown
    {
    public:
        COM_WRAPPED(::IStorageController)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RO(uint32_t, maxDevicesPerPortCount)
        VBox_PROPERTY_RO(uint32_t, minPortCount)
        VBox_PROPERTY_RO(uint32_t, maxPortCount)
        VBox_PROPERTY_RW_V(uint32_t, instance)
        VBox_PROPERTY_RW_V(uint32_t, portCount)
        VBox_PROPERTY_RO(StorageBus, bus)
        VBox_PROPERTY_RW_V(StorageControllerType, controllerType)
        VBox_PROPERTY_RW_V(bool, useHostIOCache)
        VBox_PROPERTY_RO(bool, bootable)
    };

    class LIBVBOX_API IPerformanceMetric : public COMUnknown
    {
    public:
        COM_WRAPPED(::IPerformanceMetric)

        // Attributes
        VBox_PROPERTY_RO(COMString, metricName)
        VBox_PROPERTY_RO(COMPtr<COMUnknown>, object)
        VBox_PROPERTY_RO(COMString, description)
        VBox_PROPERTY_RO(uint32_t, period)
        VBox_PROPERTY_RO(uint32_t, count)
        VBox_PROPERTY_RO(COMString, unit)
        VBox_PROPERTY_RO(int32_t, minimumValue)
        VBox_PROPERTY_RO(int32_t, maximumValue)
    };

    class LIBVBOX_API IPerformanceCollector : public COMUnknown
    {
    public:
        COM_WRAPPED(::IPerformanceCollector)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMString>, metricNames)

        // Methods
        std::vector<COMPtr<IPerformanceMetric>> getMetrics(
                /* in */ const std::vector<COMString> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects);
        std::vector<COMPtr<IPerformanceMetric>> setupMetrics(
                /* in */ const std::vector<COMString> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects,
                /* in */ uint32_t period,
                /* in */ uint32_t count);
        std::vector<COMPtr<IPerformanceMetric>> enableMetrics(
                /* in */ const std::vector<COMString> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects);
        std::vector<COMPtr<IPerformanceMetric>> disableMetrics(
                /* in */ const std::vector<COMString> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects);
        std::vector<int32_t> queryMetricsData(
                /* in  */ const std::vector<COMString> &metricNames,
                /* in  */ const std::vector<COMPtr<COMUnknown>> &objects,
                /* out */ std::vector<COMString> &returnMetricNames,
                /* out */ std::vector<COMPtr<COMUnknown>> &returnObjects,
                /* out */ std::vector<COMString> &returnUnits,
                /* out */ std::vector<uint32_t> &returnScales,
                /* out */ std::vector<uint32_t> &returnSequenceNumbers,
                /* out */ std::vector<uint32_t> &returnDataIndices,
                /* out */ std::vector<uint32_t> &returnDataLengths);
    };

    class LIBVBOX_API INATEngine : public COMUnknown
    {
    public:
        COM_WRAPPED(::INATEngine)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, network)
        VBox_PROPERTY_RW_R(COMString, hostIP)
        VBox_PROPERTY_RW_R(COMString, TFTPPrefix)
        VBox_PROPERTY_RW_R(COMString, TFTPBootFile)
        VBox_PROPERTY_RW_R(COMString, TFTPNextServer)
        VBox_PROPERTY_RW_V(uint32_t, aliasMode)
        VBox_PROPERTY_RW_V(bool, DNSPassDomain)
        VBox_PROPERTY_RW_V(bool, DNSProxy)
        VBox_PROPERTY_RW_V(bool, DNSUseHostResolver)
        VBox_PROPERTY_RO(std::vector<COMString>, redirects)

        // Methods
        void setNetworkSettings(
                /* in */ uint32_t mtu,
                /* in */ uint32_t sockSnd,
                /* in */ uint32_t sockRcv,
                /* in */ uint32_t TcpWndSnd,
                /* in */ uint32_t TcpWndRcv);
        void getNetworkSettings(
                /* out */ uint32_t &mtu,
                /* out */ uint32_t &sockSnd,
                /* out */ uint32_t &sockRcv,
                /* out */ uint32_t &TcpWndSnd,
                /* out */ uint32_t &TcpWndRcv);
        void addRedirect(
                /* in */ const COMString &name,
                /* in */ NATProtocol proto,
                /* in */ const COMString &hostIP,
                /* in */ uint16_t hostPort,
                /* in */ const COMString &guestIP,
                /* in */ uint16_t guestPort);
        void removeRedirect(
                /* in */ const COMString &name);
    };

    class LIBVBOX_API IExtPackPlugIn : public COMUnknown
    {
    public:
        COM_WRAPPED(::IExtPackPlugIn)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, description)
        VBox_PROPERTY_RO(COMString, frontend)
        VBox_PROPERTY_RO(COMString, modulePath)
    };

    class LIBVBOX_API IExtPackBase : public COMUnknown
    {
    public:
        COM_WRAPPED(::IExtPackBase)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, description)
        VBox_PROPERTY_RO(COMString, version)
        VBox_PROPERTY_RO(uint32_t, revision)
        VBox_PROPERTY_RO(COMString, edition)
        VBox_PROPERTY_RO(COMString, VRDEModule)
        VBox_PROPERTY_RO(std::vector<COMPtr<IExtPackPlugIn>>, plugIns)
        VBox_PROPERTY_RO(bool, usable)
        VBox_PROPERTY_RO(COMString, whyUnusable)
        VBox_PROPERTY_RO(bool, showLicense)
        VBox_PROPERTY_RO(COMString, license)

        // Methods
        COMString queryLicense(
                /* in */ const COMString &preferredLocale,
                /* in */ const COMString &preferredLanguage,
                /* in */ const COMString &format);
    };

    class LIBVBOX_API IExtPack : public IExtPackBase
    {
    public:
        COM_WRAPPED(::IExtPack)

        // Methods
        COMPtr<COMUnknown> queryObject(
                /* in */ const COMString objUuid);
    };

    class LIBVBOX_API IExtPackFile : public IExtPackBase
    {
    public:
        COM_WRAPPED(::IExtPackFile)

        // Attributes
        VBox_PROPERTY_RO(COMString, filePath)

        // Methods
        COMPtr<IProgress> install(
                /* in */ bool replace,
                /* in */ const COMString &displayInfo);
    };

    class LIBVBOX_API IExtPackManager : public COMUnknown
    {
    public:
        COM_WRAPPED(::IExtPackManager)

        // Attributes
        VBox_PROPERTY_RO(std::vector<IExtPack>, installedExtPacks)

        // Methods
        COMPtr<IExtPack> find(
                /* in */ const COMString &name);
        COMPtr<IExtPackFile> openExtPackFile(
                /* in */ const COMString &path);
        COMPtr<IProgress> uninstall(
                /* in */ const COMString &name,
                /* in */ bool forcedRemoval,
                /* in */ const COMString &displayInfo);
        void cleanup();
        std::vector<COMString> queryAllPlugInsForFrontend(
                /* in */ const COMString &frontendName);
        bool isExtPackUsable(
                /* in */ const COMString &name);
    };

    class LIBVBOX_API IBandwidthGroup : public COMUnknown
    {
    public:
        COM_WRAPPED(::IBandwidthGroup)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(BandwidthGroupType, type)
        VBox_PROPERTY_RO(uint32_t, reference)
        VBox_PROPERTY_RW_V(int64_t, maxBytesPerSec)
    };

    class LIBVBOX_API IBandwidthControl : public COMUnknown
    {
    public:
        COM_WRAPPED(::IBandwidthControl)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, numGroups)

        // Methods
        void createBandwidthGroup(
                /* in */ const COMString &name,
                /* in */ BandwidthGroupType type,
                /* in */ int64_t maxBytesPerSec);
        void deleteBandwidthGroup(
                /* in */ const COMString &name);
        COMPtr<IBandwidthGroup> getBandwidthGroup(
                /* in */ const COMString &name) const;
        std::vector<COMPtr<IBandwidthGroup>> getAllBandwidthGroups() const;
    };

    class LIBVBOX_API IVirtualBoxClient : public COMUnknown
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

    class LIBVBOX_API IEventSource : public COMUnknown
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

    class LIBVBOX_API IEventListener : public COMUnknown
    {
    public:
        COM_WRAPPED(::IEventListener)

        // Methods
        void handleEvent(
                /* in */ const COMPtr<IEvent> &event);
    };

    class LIBVBOX_API IEvent : public COMUnknown
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

        // Attributes
        VBox_PROPERTY_RO(uint32_t, generation)

        // Methods
        void reuse();
    };

    class LIBVBOX_API IMachineEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMachineEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, machineId)
    };

    class LIBVBOX_API IMachineStateChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IMachineStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(MachineState, state)
    };

    class LIBVBOX_API IMachineDataChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IMachineDataChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, temporary)
    };

    class LIBVBOX_API IMediumRegisteredEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMediumRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, mediumId)
        VBox_PROPERTY_RO(DeviceType, mediumType)
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IMediumConfigChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMediumConfigChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMedium>, medium)
    };

    class LIBVBOX_API IMachineRegisteredEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IMachineRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API ISessionStateChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::ISessionStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(SessionState, state)
    };

    class LIBVBOX_API IGuestPropertyChangedEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IGuestPropertyChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, value)
        VBox_PROPERTY_RO(COMString, flags)
    };

    class LIBVBOX_API ISnapshotEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::ISnapshotEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, snapshotId)
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

        // Attributes
        VBox_PROPERTY_RO(bool, visible)
        VBox_PROPERTY_RO(bool, alpha)
        VBox_PROPERTY_RO(uint32_t, xhot)
        VBox_PROPERTY_RO(uint32_t, yhot)
        VBox_PROPERTY_RO(uint32_t, width)
        VBox_PROPERTY_RO(uint32_t, height)
        VBox_PROPERTY_RO(std::vector<uint8_t>, shape)
    };

    class LIBVBOX_API IMouseCapabilityChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IMouseCapabilityChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, supportsAbsolute)
        VBox_PROPERTY_RO(bool, supportsRelative)
        VBox_PROPERTY_RO(bool, supportsMultiTouch)
        VBox_PROPERTY_RO(bool, needsHostCursor)
    };

    class LIBVBOX_API IKeyboardLedsChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IKeyboardLedsChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, numLock)
        VBox_PROPERTY_RO(bool, capsLock)
        VBox_PROPERTY_RO(bool, scrollLock)
    };

    class LIBVBOX_API IStateChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(MachineState, state)
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

        // Attributes
        VBox_PROPERTY_RO(COMPtr<INetworkAdapter>, networkAdapter)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IAudioAdapterChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IAudioAdapterChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IAudioAdapter>, audioAdapter)
    };
#endif

    class LIBVBOX_API ISerialPortChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ISerialPortChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<ISerialPort>, serialPort)
    };

    class LIBVBOX_API IParallelPortChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IParallelPortChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IParallelPort>, parallelPort)
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

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMediumAttachment>, mediumAttachment)
    };

    class LIBVBOX_API IClipboardModeChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IClipboardModeChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(ClipboardMode, clipboardMode)
    };

    class LIBVBOX_API IDnDModeChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IDnDModeChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(DnDMode, dndMode)
    };

    class LIBVBOX_API ICPUChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ICPUChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, CPU)
        VBox_PROPERTY_RO(bool, add)
    };

    class LIBVBOX_API ICPUExecutionCapChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ICPUExecutionCapChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, executionCap)
    };

    class LIBVBOX_API IGuestKeyboardEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestKeyboardEvent)

        // Attributes
        VBox_PROPERTY_RO(std::vector<int32_t>, scancodes)
    };

    class LIBVBOX_API IGuestMouseEvent : public IReusableEvent
    {
    public:
        COM_WRAPPED(::IGuestMouseEvent)

        // Attributes
        VBox_PROPERTY_RO(GuestMouseEventMode, mode)
        VBox_PROPERTY_RO(int32_t, x)
        VBox_PROPERTY_RO(int32_t, y)
        VBox_PROPERTY_RO(int32_t, z)
        VBox_PROPERTY_RO(int32_t, w)
        VBox_PROPERTY_RO(int32_t, buttons)
    };

    class LIBVBOX_API IGuestMultiTouchEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestMultiTouchEvent)

        // Attributes
        VBox_PROPERTY_RO(int32_t, contactCount)
        VBox_PROPERTY_RO(std::vector<int16_t>, xPositions)
        VBox_PROPERTY_RO(std::vector<int16_t>, yPositions)
        VBox_PROPERTY_RO(std::vector<int16_t>, contactIds)
        VBox_PROPERTY_RO(std::vector<int16_t>, contactFlags)
        VBox_PROPERTY_RO(uint32_t, scanTime)
    };

    class LIBVBOX_API IGuestSessionEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestSessionEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IGuestSession>, session)
    };

    class LIBVBOX_API IGuestSessionStateChangedEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestSessionStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RO(GuestSessionStatus, status)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API IGuestSessionRegisteredEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestSessionRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IGuestProcessEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IGuestProcess>, process)
        VBox_PROPERTY_RO(uint32_t, pid)
    };

    class LIBVBOX_API IGuestProcessRegisteredEvent : public IGuestProcessEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IGuestProcessStateChangedEvent : public IGuestProcessEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(ProcessStatus, status)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API IGuestProcessIOEvent : public IGuestProcessEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessIOEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, handle)
        VBox_PROPERTY_RO(uint32_t, processed)
    };

    class LIBVBOX_API IGuestProcessInputNotifyEvent : public IGuestProcessIOEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessInputNotifyEvent)

        // Attributes
        VBox_PROPERTY_RO(ProcessInputStatus, status)
    };

    class LIBVBOX_API IGuestProcessOutputEvent : public IGuestProcessIOEvent
    {
    public:
        COM_WRAPPED(::IGuestProcessOutputEvent)

        // Attributes
        VBox_PROPERTY_RO(std::vector<uint8_t>, data)
    };

    class LIBVBOX_API IGuestFileEvent : public IGuestSessionEvent
    {
    public:
        COM_WRAPPED(::IGuestFileEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IGuestFile>, file)
    };

    class LIBVBOX_API IGuestFileRegisteredEvent : public IGuestFileEvent
    {
    public:
        COM_WRAPPED(::IGuestFileRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IGuestFileStateChangedEvent : public IGuestFileEvent
    {
    public:
        COM_WRAPPED(::IGuestFileStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(FileStatus, status)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API IGuestFileIOEvent : public IGuestFileEvent
    {
    public:
        COM_WRAPPED(::IGuestFileIOEvent)

        // Attributes
        VBox_PROPERTY_RO(int64_t, offset)
        VBox_PROPERTY_RO(uint32_t, processed)
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

        // Attributes
        VBox_PROPERTY_RO(std::vector<uint8_t>, data)
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

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IUSBDevice>, device)
        VBox_PROPERTY_RO(bool, attached)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API ISharedFolderChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ISharedFolderChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(Scope, scope)
    };

    class LIBVBOX_API IRuntimeErrorEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IRuntimeErrorEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, fatal)
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(COMString, message)
    };

    class LIBVBOX_API IEventSourceChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IEventSourceChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventListener>, listener)
        VBox_PROPERTY_RO(bool, add)
    };

    class LIBVBOX_API IExtraDataChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IExtraDataChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, machineId)
        VBox_PROPERTY_RO(COMString, key)
        VBox_PROPERTY_RO(COMString, value)
    };

    class LIBVBOX_API IVetoEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVetoEvent)

        // Methods
        void addVeto(
                /* in */ const COMString &reason);
        bool isVetoed();
        std::vector<COMString> getVetos();
        void addApproval(
                /* in */ const COMString &reason);
        bool isApproved();
        std::vector<COMString> getApprovals();
    };

    class LIBVBOX_API IExtraDataCanChangeEvent : public IVetoEvent
    {
    public:
        COM_WRAPPED(::IExtraDataCanChangeEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, machineId)
        VBox_PROPERTY_RO(COMString, key)
        VBox_PROPERTY_RO(COMString, value)
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

        // Attributes
        VBox_PROPERTY_RW_V(int64_t, winId)
    };

    class LIBVBOX_API INATRedirectEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::INATRedirectEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RO(bool, remove)
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(NATProtocol, proto)
        VBox_PROPERTY_RO(COMString, hostIP)
        VBox_PROPERTY_RO(int32_t, hostPort)
        VBox_PROPERTY_RO(COMString, guestIP)
        VBox_PROPERTY_RO(int32_t, guestPort)
    };

    class LIBVBOX_API IHostPCIDevicePlugEvent : public IMachineEvent
    {
    public:
        COM_WRAPPED(::IHostPCIDevicePlugEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, plugged)
        VBox_PROPERTY_RO(bool, success)
        VBox_PROPERTY_RO(COMPtr<IPCIDeviceAttachment>, attachment)
        VBox_PROPERTY_RO(COMString, message)
    };

    class LIBVBOX_API IVBoxSVCAvailabilityChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IVBoxSVCAvailabilityChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, available)
    };

    class LIBVBOX_API IBandwidthGroupChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IBandwidthGroupChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IBandwidthGroup>, bandwidthGroup)
    };

    class LIBVBOX_API IGuestMonitorChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestMonitorChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(GuestMonitorChangedEventType, changeType)
        VBox_PROPERTY_RO(uint32_t, screenId)
        VBox_PROPERTY_RO(uint32_t, originX)
        VBox_PROPERTY_RO(uint32_t, originY)
        VBox_PROPERTY_RO(uint32_t, width)
        VBox_PROPERTY_RO(uint32_t, height)
    };

    class LIBVBOX_API IGuestUserStateChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IGuestUserStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, domain)
        VBox_PROPERTY_RO(GuestUserState, state)
        VBox_PROPERTY_RO(COMString, stateDetails)
    };

    class LIBVBOX_API IStorageDeviceChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::IStorageDeviceChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMediumAttachment>, storageDevice)
        VBox_PROPERTY_RO(bool, removed)
        VBox_PROPERTY_RO(bool, silent)
    };

    class LIBVBOX_API INATNetworkChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::INATNetworkChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMString, networkName)
    };

    class LIBVBOX_API INATNetworkStartStopEvent : public INATNetworkChangedEvent
    {
    public:
        COM_WRAPPED(::INATNetworkStartStopEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, startEvent)
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

        // Attributes
        VBox_PROPERTY_RO(bool, creationEvent)
    };

    class LIBVBOX_API INATNetworkSettingEvent : public INATNetworkAlterEvent
    {
    public:
        COM_WRAPPED(::INATNetworkSettingEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, enabled)
        VBox_PROPERTY_RO(COMString, network)
        VBox_PROPERTY_RO(COMString, gateway)
        VBox_PROPERTY_RO(bool, advertiseDefaultIPv6RouteEnabled)
        VBox_PROPERTY_RO(bool, needDhcpServer)
    };

    class LIBVBOX_API INATNetworkPortForwardEvent : public INATNetworkAlterEvent
    {
    public:
        COM_WRAPPED(::INATNetworkPortForwardEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, create)
        VBox_PROPERTY_RO(bool, ipv6)
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(NATProtocol, proto)
        VBox_PROPERTY_RO(COMString, hostIp)
        VBox_PROPERTY_RO(int32_t, hostPort)
        VBox_PROPERTY_RO(COMString, guestIp)
        VBox_PROPERTY_RO(int32_t, guestPort)
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

        // Attributes
        VBox_PROPERTY_RO(COMString, progressId)
    };

    class LIBVBOX_API IProgressPercentageChangedEvent : public IProgressEvent
    {
    public:
        COM_WRAPPED(::IProgressPercentageChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(int32_t, percent)
    };

    class LIBVBOX_API IProgressTaskCompletedEvent : public IProgressEvent
    {
    public:
        COM_WRAPPED(::IProgressTaskCompletedEvent)
    };
#endif

#if defined(VBOX_MSCOM) && (VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0))
    class LIBVBOX_API IVBoxSVCRegistration : public COMUnknown
    {
    public:
        COM_WRAPPED(::IVBoxSVCRegistration)

        // Methods
        COMPtr<COMUnknown> getVirtualBox();
    };

    class LIBVBOX_API IVirtualBoxSDS : public COMUnknown
    {
    public:
        COM_WRAPPED(::IVirtualBoxSDS)

        // Methods
        COMPtr<COMUnknown> registerVBoxSVC(
                /* in */ const COMPtr<IVBoxSVCRegistration> &vboxSVC,
                /* in */ int32_t pid);
        void deregisterVBoxSVC(
                /* in */ const COMPtr<IVBoxSVCRegistration> &vboxSVC,
                /* in */ int32_t pid);
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API ICursorPositionChangedEvent : public IEvent
    {
    public:
        COM_WRAPPED(::ICursorPositionChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, hasData)
        VBox_PROPERTY_RO(uint32_t, x)
        VBox_PROPERTY_RO(uint32_t, y)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API ICloudClient : public COMUnknown
    {
    public:
        COM_WRAPPED(::ICloudClient)

        // Methods
        COMString getExportLaunchParameters() const;
        void exportLaunchVM(
                /* in */ const COMPtr<IVirtualSystemDescription> &description,
                /* in */ const COMPtr<IProgress> &progress,
                /* in */ const COMPtr<IVirtualBox> &virtualBox);
    };

    class LIBVBOX_API ICloudProfile : public COMUnknown
    {
    public:
        COM_WRAPPED(::ICloudProfile)

        // Attributes
        VBox_PROPERTY_RW_R(COMString, name)
        VBox_PROPERTY_RO(COMString, providerId)

        // Methods
        COMString getProperty(
                /* in */ const COMString &name) const;
        void setProperty(
                /* in */ const COMString &name,
                /* in */ const COMString &value) const;
        std::vector<COMString> getProperties(
                /* in  */ const COMString &names,
                /* out */ std::vector<COMString> &returnNames) const;
        void setProperties(
                /* in */ const std::vector<COMString> &names,
                /* in */ const std::vector<COMString> &values);
        void remove();
        COMPtr<ICloudClient> createCloudClient();
    };

    class LIBVBOX_API ICloudProvider : public COMUnknown
    {
    public:
        COM_WRAPPED(::ICloudProvider)

        // Attributes
        VBox_PROPERTY_RO(COMString, name)
        VBox_PROPERTY_RO(COMString, shortName)
        VBox_PROPERTY_RO(COMString, id)
        VBox_PROPERTY_RO(std::vector<COMPtr<ICloudProfile>>, profiles)
        VBox_PROPERTY_RO(std::vector<COMString>, profileNames)
        VBox_PROPERTY_RO(std::vector<COMString>, supportedPropertyNames)

        // Methods
        COMString getPropertyDescription(
                /* in */ const COMString &name) const;
        void createProfile(
                /* in */ const COMString &profileName,
                /* in */ const std::vector<COMString> &names,
                /* in */ const std::vector<COMString> &values);
        void importProfiles();
        void restoreProfiles();
        void saveProfiles();
        COMPtr<ICloudProfile> getProfileByName(
                /* in */ const COMString &profileName);
        void prepareUninstall();
    };

    class LIBVBOX_API ICloudProviderManager : public COMUnknown
    {
    public:
        COM_WRAPPED(::ICloudProviderManager)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<ICloudProvider>>, providers)

        // Methods
        COMPtr<ICloudProvider> getProviderById(
                /* in */ const COMString &providerId);
        COMPtr<ICloudProvider> getProviderByShortName(
                /* in */ const COMString &providerName);
        COMPtr<ICloudProvider> getProviderByName(
                /* in */ const COMString &providerName);
    };
#endif
}

#endif /* _LIBVBOX_INTERFACES_H */
