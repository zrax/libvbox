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
        VBox_COM_WRAPPED(::IVirtualBoxErrorInfo)

        // Attributes
        VBox_PROPERTY_RO(int32_t, resultCode);
        VBox_PROPERTY_RO(int32_t, resultDetail);
        VBox_PROPERTY_RO(std::u16string, interfaceID);
        VBox_PROPERTY_RO(std::u16string, component);
        VBox_PROPERTY_RO(std::u16string, text);
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, next);
    };

    class LIBVBOX_API INATNetwork : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::INATNetwork)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, networkName)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(std::u16string, network)
        VBox_PROPERTY_RO(std::u16string, gateway)
        VBox_PROPERTY_RW_V(bool, IPv6Enabled)
        VBox_PROPERTY_RW_R(std::u16string, IPv6Prefix)
        VBox_PROPERTY_RW_V(bool, advertiseDefaultIPv6RouteEnabled)
        VBox_PROPERTY_RW_V(bool, needDhcpServer)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::vector<std::u16string>, portForwardRules4)
        VBox_PROPERTY_RO(std::vector<std::u16string>, localMappings)
        VBox_PROPERTY_RW_V(int32_t, loopbackIp6)
        VBox_PROPERTY_RO(std::vector<std::u16string>, portForwardRules6)

        // Methods
        void addLocalMapping(
                /* in */ const std::u16string &hostid,
                /* in */ int32_t offset);
        void addPortForwardRule(
                /* in */ bool isIpv6,
                /* in */ const std::u16string &ruleName,
                /* in */ NATProtocol proto,
                /* in */ const std::u16string &hostIP,
                /* in */ uint16_t hostPort,
                /* in */ const std::u16string &guestIP,
                /* in */ uint16_t guestPort);
        void removePortForwardRule(
                /* in */ bool iSipv6,
                /* in */ const std::u16string &ruleName);
        void start(
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
                /* in */ const std::u16string &trunkType
#endif
                );
        void stop();
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API ICloudNetwork : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudNetwork)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, networkName)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(std::u16string, provider)
        VBox_PROPERTY_RW_R(std::u16string, profile)
        VBox_PROPERTY_RW_R(std::u16string, networkId)
    };
#endif

    class LIBVBOX_API IDHCPServer : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDHCPServer)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RO(std::u16string, IPAddress)
        VBox_PROPERTY_RO(std::u16string, networkMask)
        VBox_PROPERTY_RO(std::u16string, networkName)
        VBox_PROPERTY_RO(std::u16string, lowerIP)
        VBox_PROPERTY_RO(std::u16string, upperIP)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(std::vector<std::u16string>, globalOptions)
        VBox_PROPERTY_RO(std::vector<std::u16string>, vmConfigs)
#else
        VBox_PROPERTY_RO(COMPtr<IDHCPGlobalConfig>, globalConfig)
        VBox_PROPERTY_RO(std::vector<COMPtr<IDHCPGroupConfig>>, groupConfigs)
        VBox_PROPERTY_RO(std::vector<COMPtr<IDHCPIndividualConfig>>, individualConfigs)
#endif

        // Methods
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        void addGlobalOption(
                /* in */ DhcpOpt option,
                /* in */ const std::u16string &value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeGlobalOption(
                /* in */ DhcpOpt option);
        void removeGlobalOptions();
#endif
        void addVmSlotOption(
                /* in */ const std::u16string &vmname,
                /* in */ int32_t slot,
                /* in */ DhcpOpt option,
                /* in */ const std::u16string &value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeVmSlotOption(
                /* in */ const std::u16string& vmname,
                /* in */ int32_t slot,
                /* in */ DhcpOpt option);
#endif
        void removeVmSlotOptions(
                /* in */ const std::u16string &vmname,
                /* in */ int32_t slot);
        std::vector<std::u16string> getVmSlotOptions(
                /* in */ const std::u16string &vmname,
                /* in */ int32_t slot);
        std::vector<std::u16string> getMacOptions(
                /* in */ const std::u16string &mac);
#endif
        void setConfiguration(
                /* in */ const std::u16string &IPAddress,
                /* in */ const std::u16string &networkMask,
                /* in */ const std::u16string &FromIPAddress,
                /* in */ const std::u16string &ToIPAddress);
        void start(
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
                /* in */ const std::u16string &networkName,
#endif
                /* in */ const std::u16string &trunkName,
                /* in */ const std::u16string &trunkType);
        void stop();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void restart();
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        void findLeaseByMAC(
                /* in  */ const std::u16string &mac,
                /* in  */ int32_t type,
                /* out */ std::u16string *address,
                /* out */ std::u16string *state,
                /* out */ int64_t *issued,
                /* out */ int64_t *expire);
        COMPtr<IDHCPConfig> getConfig(
                /* in */ DHCPConfigScope scope,
                /* in */ const std::u16string &name,
                /* in */ uint32_t slot,
                /* in */ bool mayAdd);
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IDHCPConfig : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDHCPConfig)

        // Attributes
        VBox_PROPERTY_RO(DHCPConfigScope, scope)
        VBox_PROPERTY_RW_V(uint32_t, minLeaseTime)
        VBox_PROPERTY_RW_V(uint32_t, defaultLeaseTime)
        VBox_PROPERTY_RW_V(uint32_t, maxLeaseTime)
        VBox_PROPERTY_RW_R(std::vector<DHCPOption>, forcedOptions)
        VBox_PROPERTY_RW_R(std::vector<DHCPOption>, suppressedOptions)

        // Methods
        void setOption(
                /* in */ DHCPOption option,
                /* in */ DHCPOptionEncoding encoding,
                /* in */ const std::u16string &value);
        void removeOption(
                /* in */ DHCPOption option);
        void removeAllOptions();
        std::u16string getOption(
                /* in  */ DHCPOption option,
                /* out */ DHCPOptionEncoding *encoding);
        std::vector<std::u16string> getAllOptions(
                /* out */ std::vector<DHCPOption> *options,
                /* out */ std::vector<DHCPOptionEncoding> *encodings);
        void remove();
    };

    class LIBVBOX_API IDHCPGlobalConfig : public IDHCPConfig
    {
    public:
        VBox_COM_WRAPPED(::IDHCPGlobalConfig)
    };

    class LIBVBOX_API IDHCPGroupCondition : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDHCPGroupCondition)

        // Attributes
        VBox_PROPERTY_RW_V(bool, inclusive)
        VBox_PROPERTY_RW_V(DHCPGroupConditionType, type)
        VBox_PROPERTY_RW_R(std::u16string, value)

        // Methods
        void remove();
    };

    class LIBVBOX_API IDHCPGroupConfig : public IDHCPConfig
    {
    public:
        VBox_COM_WRAPPED(::IDHCPGroupConfig)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RO(std::vector<COMPtr<IDHCPGroupCondition>>, conditions)

        // Methods
        COMPtr<IDHCPGroupCondition> addCondition(
                /* in */ bool inclusive,
                /* in */ DHCPGroupConditionType type,
                /* in */ const std::u16string &value);
        void removeAllConditions();
    };

    class LIBVBOX_API IDHCPIndividualConfig : public IDHCPConfig
    {
    public:
        VBox_COM_WRAPPED(::IDHCPIndividualConfig)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, MACAddress)
        VBox_PROPERTY_RO(std::u16string, machineId)
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_R(std::u16string, fixedAddress)
    };
#endif

    class LIBVBOX_API IVirtualBox : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IVirtualBox)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, version)
        VBox_PROPERTY_RO(std::u16string, versionNormalized)
        VBox_PROPERTY_RO(uint32_t, revision)
        VBox_PROPERTY_RO(std::u16string, packageType)
        VBox_PROPERTY_RO(std::u16string, APIVersion)
        VBox_PROPERTY_RO(int64_t, APIRevision)
        VBox_PROPERTY_RO(std::u16string, homeFolder)
        VBox_PROPERTY_RO(std::u16string, settingsFilePath)
        VBox_PROPERTY_RO(COMPtr<IHost>, host)
        VBox_PROPERTY_RO(COMPtr<ISystemProperties>, systemProperties)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMachine>>, machines)
        VBox_PROPERTY_RO(std::vector<std::u16string>, machineGroups)
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
        VBox_PROPERTY_RO(std::vector<std::u16string>, internalNetworks)
        VBox_PROPERTY_RO(std::vector<std::u16string>, genericNetworkDrivers)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(std::vector<COMPtr<ICloudNetwork>>, cloudNetworks)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(COMPtr<ICloudProviderManager>, cloudProviderManager)
#endif

        // Methods
        std::u16string composeMachineFilename(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &group,
                /* in */ const std::u16string &createFlags,
                /* in */ const std::u16string &baseFolder);
        COMPtr<IMachine> createMachine(
                /* in */ const std::u16string &settingsFile,
                /* in */ const std::u16string &name,
                /* in */ const std::vector<std::u16string> &groups,
                /* in */ const std::u16string &osTypeId,
                /* in */ const std::u16string &flags);
        COMPtr<IMachine> openMachine(
                /* in */ const std::u16string &settingsFile);
        void registerMachine(
                /* in */ const COMPtr<IMachine> &machine);
        COMPtr<IMachine> findMachine(
                /* in */ const std::u16string &nameOrId);
        std::vector<COMPtr<IMachine>> getMachinesByGroups(
                /* in */ const std::vector<std::u16string> &groups);
        std::vector<MachineState> getMachineStates(
                /* in */ const std::vector<COMPtr<IMachine>> &machines);
        COMPtr<IAppliance> createAppliance();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        COMPtr<IUnattended> createUnattendedInstaller();
#endif
        COMPtr<IMedium> createMedium(
                /* in */ const std::u16string &format,
                /* in */ const std::u16string &location,
                /* in */ AccessMode accessMode,
                /* in */ DeviceType aADeviceTypeType);
        COMPtr<IMedium> openMedium(
                /* in */ const std::u16string &location,
                /* in */ DeviceType deviceType,
                /* in */ AccessMode accessMode,
                /* in */ bool forceNewUuid);
        COMPtr<IGuestOSType> getGuestOSType(
                /* in */ const std::u16string &id);
        void createSharedFolder(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const std::u16string &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const std::u16string &name);
        std::vector<std::u16string> getExtraDataKeys();
        std::u16string getExtraData(
                /* in */ const std::u16string &key);
        void setExtraData(
                /* in */ const std::u16string &key,
                /* in */ const std::u16string &value);
        void setSettingsSecret(
                /* in */ const std::u16string &password);
        COMPtr<IDHCPServer> createDHCPServer(
                /* in */ const std::u16string &name);
        COMPtr<IDHCPServer> findDHCPServerByNetworkName(
                /* in */ const std::u16string &name);
        void removeDHCPServer(
                /* in */ const COMPtr<IDHCPServer> &server);
        COMPtr<INATNetwork> createNATNetwork(
                /* in */ const std::u16string &networkName);
        COMPtr<INATNetwork> findNATNetworkByName(
                /* in */ const std::u16string &networkName);
        void removeNATNetwork(
                /* in */ const COMPtr<INATNetwork> &network);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        COMPtr<ICloudNetwork> createCloudNetwork(
                /* in */ const std::u16string &networkName);
        COMPtr<ICloudNetwork> findCloudNetworkByName(
                /* in */ const std::u16string &networkName);
        void removeCloudNetwork(
                /* in */ const COMPtr<ICloudNetwork> &network);
#endif
        bool checkFirmwarePresent(
                /* in */  FirmwareType firmwareType,
                /* in */  const std::u16string &version,
                /* out */ std::u16string *url,
                /* out */ std::u16string *file);
    };

    class LIBVBOX_API IVFSExplorer : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IVFSExplorer)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, path)
        VBox_PROPERTY_RO(VFSType, type)

        // Methods
        COMPtr<IProgress> update();
        COMPtr<IProgress> cd(
                /* in */ const std::u16string &dir);
        COMPtr<IProgress> cdUp();
        void entryList(
                /* out */ std::vector<std::u16string> *names,
                /* out */ std::vector<uint32_t> *types,
                /* out */ std::vector<int64_t> *sizes,
                /* out */ std::vector<uint32_t> *modes);
        std::vector<std::u16string> exists(
                /* in */ const std::vector<std::u16string> &names);
        COMPtr<IProgress> remove(
                /* in */ const std::vector<std::u16string> &names);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API ICertificate : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICertificate)

        // Attributes
        VBox_PROPERTY_RO(CertificateVersion, versionNumber)
        VBox_PROPERTY_RO(std::u16string, serialNumber)
        VBox_PROPERTY_RO(std::u16string, signatureAlgorithmOID)
        VBox_PROPERTY_RO(std::u16string, signatureAlgorithmName)
        VBox_PROPERTY_RO(std::vector<std::u16string>, issuerName)
        VBox_PROPERTY_RO(std::vector<std::u16string>, subjectName)
        VBox_PROPERTY_RO(std::u16string, friendlyName)
        VBox_PROPERTY_RO(std::u16string, validityPeriodNotBefore)
        VBox_PROPERTY_RO(std::u16string, validityPeriodNotAfter)
        VBox_PROPERTY_RO(std::u16string, publicKeyAlgorithmOID)
        VBox_PROPERTY_RO(std::u16string, publicKeyAlgorithm)
        VBox_PROPERTY_RO(std::vector<uint8_t>, subjectPublicKey)
        VBox_PROPERTY_RO(std::u16string, issuerUniqueIdentifier)
        VBox_PROPERTY_RO(std::u16string, subjectUniqueIdentifier)
        VBox_PROPERTY_RO(bool, certificateAuthority)
        VBox_PROPERTY_RO(uint32_t, keyUsage)
        VBox_PROPERTY_RO(std::vector<std::u16string>, extendedKeyUsage)
        VBox_PROPERTY_RO(std::vector<uint8_t>, rawCertData)
        VBox_PROPERTY_RO(bool, selfSigned)
        VBox_PROPERTY_RO(bool, trusted)
        VBox_PROPERTY_RO(bool, expired)

        // Methods
        bool isCurrentlyExpired();
        std::u16string queryInfo(
                /* in */ int32_t what);
    };
#endif

    class LIBVBOX_API IAppliance : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IAppliance)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, path)
        VBox_PROPERTY_RO(std::vector<std::u16string>, disks)
        VBox_PROPERTY_RO(std::vector<COMPtr<IVirtualSystemDescription>>, virtualSystemDescriptions)
        VBox_PROPERTY_RO(std::vector<std::u16string>, machines)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(COMPtr<ICertificate>, certificate)
#endif

        // Methods
        COMPtr<IProgress> read(
                /* in */ const std::u16string &file);
        void interpret();
        COMPtr<IProgress> importMachines(
                /* in */ const std::vector<ImportOptions> &options);
        COMPtr<IVFSExplorer> createVFSExplorer(
                /* in */ const std::u16string &URI);
        COMPtr<IProgress> write(
                /* in */ const std::u16string &format,
                /* in */ const std::vector<ExportOptions> &options,
                /* in */ const std::u16string &path);
        std::vector<std::u16string> getWarnings();
        std::vector<std::u16string> getPasswordIds();
        std::vector<std::u16string> getMediumIdsForPasswordId(
                /* in */ const std::u16string &passwordId);
        void addPasswords(
                /* in */ const std::vector<std::u16string> &identifiers,
                /* in */ const std::vector<std::u16string> &passwords);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        uint32_t createVirtualSystemDescriptions(
                /* in */ uint32_t requested);
#endif
    };

    class LIBVBOX_API IVirtualSystemDescription : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IVirtualSystemDescription)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, count)

        // Methods
        void getDescription(
                /* out */ std::vector<VirtualSystemDescriptionType> *types,
                /* out */ std::vector<std::u16string> *refs,
                /* out */ std::vector<std::u16string> *OVFValues,
                /* out */ std::vector<std::u16string> *VBoxValues,
                /* out */ std::vector<std::u16string> *extraConfigValues);
        void getDescriptionByType(
                /* in  */ VirtualSystemDescriptionType type,
                /* out */ std::vector<VirtualSystemDescriptionType> *types,
                /* out */ std::vector<std::u16string> *refs,
                /* out */ std::vector<std::u16string> *OVFValues,
                /* out */ std::vector<std::u16string> *VBoxValues,
                /* out */ std::vector<std::u16string> *extraConfigValues);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        void removeDescriptionByType(
                /* in */ VirtualSystemDescriptionType type);
#endif
        std::vector<std::u16string> getValuesByType(
                /* in */ VirtualSystemDescriptionType type,
                /* in */ VirtualSystemDescriptionValueType which);
        void setFinalValues(
                /* in */ const std::vector<bool> &enabled,
                /* in */ const std::vector<std::u16string> &VBoxValues,
                /* in */ const std::vector<std::u16string> &extraConfigValues);
        void addDescription(
                /* in */ VirtualSystemDescriptionType type,
                /* in */ const std::u16string &VBoxValue,
                /* in */ const std::u16string &extraConfigValue);
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IUnattended : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IUnattended)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, isoPath)
        VBox_PROPERTY_RW_R(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RW_R(std::u16string, user)
        VBox_PROPERTY_RW_R(std::u16string, password)
        VBox_PROPERTY_RW_R(std::u16string, fullUserName)
        VBox_PROPERTY_RW_R(std::u16string, productKey)
        VBox_PROPERTY_RW_R(std::u16string, additionsIsoPath)
        VBox_PROPERTY_RW_V(bool, installGuestAdditions)
        VBox_PROPERTY_RW_R(std::u16string, validationKitIsoPath)
        VBox_PROPERTY_RW_V(bool, installTestExecService)
        VBox_PROPERTY_RW_R(std::u16string, timeZone)
        VBox_PROPERTY_RW_R(std::u16string, locale)
        VBox_PROPERTY_RW_R(std::u16string, language)
        VBox_PROPERTY_RW_R(std::u16string, country)
        VBox_PROPERTY_RW_R(std::u16string, proxy)
        VBox_PROPERTY_RW_R(std::u16string, packageSelectionAdjustments)
        VBox_PROPERTY_RW_R(std::u16string, hostname)
        VBox_PROPERTY_RW_R(std::u16string, auxiliaryBasePath)
        VBox_PROPERTY_RW_V(uint32_t, imageIndex)
        VBox_PROPERTY_RW_R(std::u16string, scriptTemplatePath)
        VBox_PROPERTY_RW_R(std::u16string, postInstallScriptTemplatePath)
        VBox_PROPERTY_RW_R(std::u16string, postInstallCommand)
        VBox_PROPERTY_RW_R(std::u16string, extraInstallKernelParameters)
        VBox_PROPERTY_RO(std::u16string, detectedOSTypeId)
        VBox_PROPERTY_RO(std::u16string, detectedOSVersion)
        VBox_PROPERTY_RO(std::u16string, detectedOSFlavor)
        VBox_PROPERTY_RO(std::u16string, detectedOSLanguages)
        VBox_PROPERTY_RO(std::u16string, detectedOSHints)

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
        VBox_COM_WRAPPED(::IInternalMachineControl)

        // Methods
        void updateState(
                /* in */ MachineState state);
        void beginPowerUp(
                /* in */ const COMPtr<IProgress> &progress);
        void endPowerUp(
                /* in */ int32_t result);
        void beginPoweringDown(
                /* out */ COMPtr<IProgress> *progress);
        void endPoweringDown(
                /* in */ int32_t result,
                /* in */ const std::u16string &errMsg);
        void runUSBDeviceFilters(
                /* in  */ const COMPtr<IUSBDevice> &device,
                /* out */ bool *matched,
                /* out */ uint32_t *maskedInterfaces);
        void captureUSBDevice(
                /* in */ const std::u16string &id,
                /* in */ const std::u16string &captureFilename);
        void detachUSBDevice(
                /* in */ const std::u16string &id,
                /* in */ bool done);
        void autoCaptureUSBDevices();
        void detachAllUSBDevices(
                /* in */ bool done);
        COMPtr<IProgress> onSessionEnd(
                /* in */ const COMPtr<ISession> &session);
        void finishOnlineMergeMedium();
        void pullGuestProperties(
                /* out */ std::vector<std::u16string> *names,
                /* out */ std::vector<std::u16string> *values,
                /* out */ std::vector<int64_t> *timestamps,
                /* out */ std::vector<std::u16string> *flags);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        void clipboardAreaRegister(
                /* in  */ const std::vector<std::u16string> &parms,
                /* out */ uint32_t *id);
        void clipboardAreaUnregister(
                /* in */ uint32_t id);
        void clipboardAreaAttach(
                /* in */ uint32_t id);
        void clipboardAreaDetach(
                /* in */ uint32_t id);
        void clipboardAreaGetMostRecent(
                /* out */ uint32_t *id);
        void clipboardAreaGetRefCount(
                /* in  */ uint32_t id,
                /* out */ uint32_t *refcount);
#endif
        void pushGuestProperty(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &value,
                /* in */ int64_t timestamp,
                /* in */ const std::u16string &flags);
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
                /* in  */ const std::vector<std::u16string> &authParams,
                /* out */ std::u16string *result);
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IGraphicsAdapter : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IGraphicsAdapter)

        // Attributes
        VBox_PROPERTY_RW_V(GraphicsControllerType, graphicsControllerType)
        VBox_PROPERTY_RW_V(uint32_t, VRAMSize)
        VBox_PROPERTY_RW_V(bool, accelerate3DEnabled)
        VBox_PROPERTY_RW_V(bool, accelerate2DVideoEnabled)
        VBox_PROPERTY_RW_V(uint32_t, monitorCount)
    };
#endif

    class LIBVBOX_API IBIOSSettings : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IBIOSSettings)

        // Attributes
        VBox_PROPERTY_RW_V(bool, logoFadeIn)
        VBox_PROPERTY_RW_V(bool, logoFadeOut)
        VBox_PROPERTY_RW_V(uint32_t, logoDisplayTime)
        VBox_PROPERTY_RW_R(std::u16string, logoImagePath)
        VBox_PROPERTY_RW_V(BIOSBootMenuMode, bootMenuMode)
        VBox_PROPERTY_RW_V(bool, ACPIEnabled)
        VBox_PROPERTY_RW_V(bool, IOAPICEnabled)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RW_V(VBox::APICMode, APICMode)
#endif
        VBox_PROPERTY_RW_V(int64_t, timeOffset)
        VBox_PROPERTY_RW_V(bool, PXEDebugEnabled)
        VBox_PROPERTY_RO(std::u16string, nonVolatileStorageFile)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_V(bool, SMBIOSUuidLittleEndian)
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingScreenSettings : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IRecordingScreenSettings)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, features)
        VBox_PROPERTY_RW_V(RecordingDestination, destination)
        VBox_PROPERTY_RW_R(std::u16string, filename)
        VBox_PROPERTY_RW_V(uint32_t, maxTime)
        VBox_PROPERTY_RW_V(uint32_t, maxFileSize)
        VBox_PROPERTY_RW_R(std::u16string, options)
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
        VBox_COM_WRAPPED(::IRecordingSettings)

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
        VBox_COM_WRAPPED(::IPCIAddress)

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
        VBox_COM_WRAPPED(::IPCIDeviceAttachment)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(bool, isPhysicalDevice)
        VBox_PROPERTY_RO(int32_t, hostAddress)
        VBox_PROPERTY_RO(int32_t, guestAddress)
    };

    class LIBVBOX_API IMachine : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IMachine)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IVirtualBox>, parent)
        VBox_PROPERTY_RW_R(std::vector<uint8_t>, icon)
        VBox_PROPERTY_RO(bool, accessible)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, accessError)
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RW_R(std::u16string, description)
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RW_R(std::vector<std::u16string>, groups)
        VBox_PROPERTY_RW_R(std::u16string, OSTypeId)
        VBox_PROPERTY_RW_R(std::u16string, hardwareVersion)
        VBox_PROPERTY_RW_R(std::u16string, hardwareUUID)
        VBox_PROPERTY_RW_V(uint32_t, CPUCount)
        VBox_PROPERTY_RW_V(bool, CPUHotPlugEnabled)
        VBox_PROPERTY_RW_V(uint32_t, CPUExecutionCap)
        VBox_PROPERTY_RW_V(uint32_t, CPUIDPortabilityLevel)
        VBox_PROPERTY_RW_V(uint32_t, memorySize)
        VBox_PROPERTY_RW_V(uint32_t, memoryBalloonSize)
        VBox_PROPERTY_RW_V(bool, pageFusionEnabled)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_V(GraphicsControllerType, graphicsControllerType)
        VBox_PROPERTY_RW_V(uint32_t, VRAMSize)
        VBox_PROPERTY_RW_V(bool, accelerate3DEnabled)
        VBox_PROPERTY_RW_V(bool, accelerate2DVideoEnabled)
        VBox_PROPERTY_RW_V(uint32_t, monitorCount)
#else
        VBox_PROPERTY_RO(COMPtr<IGraphicsAdapter>, graphicsAdapter)
#endif
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(bool, videoCaptureEnabled)
        VBox_PROPERTY_RW_R(std::vector<bool>, videoCaptureScreens)
        VBox_PROPERTY_RW_R(std::u16string, videoCaptureFile)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureWidth)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureHeight)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureRate)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureFPS)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureMaxTime)
        VBox_PROPERTY_RW_V(uint32_t, videoCaptureMaxFileSize)
        VBox_PROPERTY_RW_R(std::u16string, videoCaptureOptions)
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
        VBox_PROPERTY_RW_R(std::u16string, snapshotFolder)
        VBox_PROPERTY_RO(COMPtr<IVRDEServer>, VRDEServer)
        VBox_PROPERTY_RW_V(bool, emulatedUSBCardReaderEnabled)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMediumAttachment>>, mediumAttachments)
        VBox_PROPERTY_RO(std::vector<COMPtr<IUSBController>>, USBControllers)
        VBox_PROPERTY_RO(COMPtr<IUSBDeviceFilters>, USBDeviceFilters)
        VBox_PROPERTY_RO(COMPtr<IAudioAdapter>, audioAdapter)
        VBox_PROPERTY_RO(std::vector<COMPtr<IStorageController>>, storageControllers)
        VBox_PROPERTY_RO(std::u16string, settingsFilePath)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(std::u16string, settingsAuxFilePath)
#endif
        VBox_PROPERTY_RO(bool, settingsModified)
        VBox_PROPERTY_RO(SessionState, sessionState)
        VBox_PROPERTY_RO(std::u16string, sessionName)
        VBox_PROPERTY_RO(uint32_t, sessionPID)
        VBox_PROPERTY_RO(MachineState, state)
        VBox_PROPERTY_RO(int64_t, lastStateChange)
        VBox_PROPERTY_RO(std::u16string, stateFilePath)
        VBox_PROPERTY_RO(std::u16string, logFolder)
        VBox_PROPERTY_RO(COMPtr<ISnapshot>, currentSnapshot)
        VBox_PROPERTY_RO(uint32_t, snapshotCount)
        VBox_PROPERTY_RO(bool, currentStateModified)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISharedFolder>>, sharedFolders)
        VBox_PROPERTY_RW_V(ClipboardMode, clipboardMode)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_V(bool, clipboardFileTransfersEnabled)
#endif
        VBox_PROPERTY_RW_V(DnDMode, dnDMode)
        VBox_PROPERTY_RW_V(bool, teleporterEnabled)
        VBox_PROPERTY_RW_V(uint32_t, teleporterPort)
        VBox_PROPERTY_RW_R(std::u16string, teleporterAddress)
        VBox_PROPERTY_RW_R(std::u16string, teleporterPassword)
        VBox_PROPERTY_RW_V(ParavirtProvider, paravirtProvider)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_V(FaultToleranceState, faultToleranceState)
        VBox_PROPERTY_RW_V(uint32_t, faultTolerancePort)
        VBox_PROPERTY_RW_R(std::u16string, faultToleranceAddress)
        VBox_PROPERTY_RW_R(std::u16string, faultTolerancePassword)
        VBox_PROPERTY_RW_V(uint32_t, faultToleranceSyncInterval)
#endif
        VBox_PROPERTY_RW_V(bool, RTCUseUTC)
        VBox_PROPERTY_RW_V(bool, IOCacheEnabled)
        VBox_PROPERTY_RW_V(uint32_t, IOCacheSize)
        VBox_PROPERTY_RO(std::vector<COMPtr<IPCIDeviceAttachment>>, PCIDeviceAssignments)
        VBox_PROPERTY_RO(COMPtr<IBandwidthControl>, bandwidthControl)
        VBox_PROPERTY_RW_V(bool, tracingEnabled)
        VBox_PROPERTY_RW_R(std::u16string, tracingConfig)
        VBox_PROPERTY_RW_V(bool, allowTracingToAccessVM)
        VBox_PROPERTY_RW_V(bool, autostartEnabled)
        VBox_PROPERTY_RW_V(uint32_t, autostartDelay)
        VBox_PROPERTY_RW_V(AutostopType, autostopType)
        VBox_PROPERTY_RW_R(std::u16string, defaultFrontend)
        VBox_PROPERTY_RO(bool, USBProxyAvailable)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_R(std::u16string, VMProcessPriority)
#else
        VBox_PROPERTY_RW_V(VMProcPriority, VMProcessPriority)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RW_R(std::u16string, paravirtDebug)
        VBox_PROPERTY_RW_R(std::u16string, CPUProfile)
#endif

        // Methods
        void lockMachine(
                /* in */ const COMPtr<ISession> &session,
                /* in */ LockType lockType);
        COMPtr<IProgress> launchVMProcess(
                /* in */ const COMPtr<ISession> &session,
                /* in */ const std::u16string &name,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
                /* in */ const std::u16string &environment
#else
                /* in */ const std::vector<std::u16string> &environmentChanges
#endif
                );
        void setBootOrder(
                /* in */ uint32_t position,
                /* in */ DeviceType device);
        DeviceType getBootOrder(
                /* in */ uint32_t position) const;
        void attachDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ DeviceType type,
                /* in */ const COMPtr<IMedium> &medium);
        void attachDeviceWithoutMedium(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ DeviceType type);
        void detachDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void passthroughDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool passthrough);
        void temporaryEjectDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool temporaryEject);
        void nonRotationalDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool nonRotational);
        void setAutoDiscardForDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool discard);
        void setHotPluggableForDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool hotPluggable);
        void setBandwidthGroupForDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ const COMPtr<IBandwidthGroup> &bandwidthGroup);
        void setNoBandwidthGroupForDevice(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device);
        void unmountMedium(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ bool force);
        void mountMedium(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device,
                /* in */ const COMPtr<IMedium> &medium,
                /* in */ bool force);
        COMPtr<IMedium> getMedium(
                /* in */ const std::u16string &name,
                /* in */ int32_t controllerPort,
                /* in */ int32_t device) const;
        std::vector<COMPtr<IMediumAttachment>> getMediumAttachmentsOfController(
                /* in */ const std::u16string &name) const;
        COMPtr<IMediumAttachment> getMediumAttachment(
                /* in */ const std::u16string &name,
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
                /* in */ const std::u16string &name,
                /* in */ StorageBus connectionType);
        COMPtr<IStorageController> getStorageControllerByName(
                /* in */ const std::u16string &name) const;
        COMPtr<IStorageController> getStorageControllerByInstance(
                /* in */ StorageBus connectionType,
                /* in */ uint32_t instance) const;
        void removeStorageController(
                /* in */ const std::u16string &name);
        void setStorageControllerBootable(
                /* in */ const std::u16string &name,
                /* in */ bool bootable);
        COMPtr<IUSBController> addUSBController(
                /* in */ const std::u16string &name,
                /* in */ USBControllerType type);
        void removeUSBController(
                /* in */ const std::u16string &name);
        COMPtr<IUSBController> getUSBControllerByName(
                /* in */ const std::u16string &name) const;
        uint32_t getUSBControllerCountByType(
                /* in */ USBControllerType type) const;
        COMPtr<ISerialPort> getSerialPort(
                /* in */ uint32_t slot) const;
        COMPtr<IParallelPort> getParallelPort(
                /* in */ uint32_t slot) const;
        std::vector<std::u16string> getExtraDataKeys();
        std::u16string getExtraData(
                /* in */ const std::u16string &key);
        void setExtraData(
                /* in */ const std::u16string &key,
                /* in */ const std::u16string &value);
        bool getCPUProperty(
                /* in */ CPUPropertyType property) const;
        void setCPUProperty(
                /* in */ CPUPropertyType property,
                /* in */ bool value);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        void getCPUIDLeafByOrdinal(
                /* in  */ uint32_t ordinal,
                /* out */ uint32_t *idx,
                /* out */ uint32_t *idxSub,
                /* out */ uint32_t *valEax,
                /* out */ uint32_t *valEbx,
                /* out */ uint32_t *valEcx,
                /* out */ uint32_t *valEdx) const;
#endif
        void getCPUIDLeaf(
                /* in  */ uint32_t idx,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
                /* in  */ uint32_t idxSub,
#endif
                /* out */ uint32_t *valEax,
                /* out */ uint32_t *valEbx,
                /* out */ uint32_t *valEcx,
                /* out */ uint32_t *valEdx) const;
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
                /* in */ const std::u16string &settingsFilePath);
        void saveSettings();
        void discardSettings();
        std::vector<COMPtr<IMedium>> unregister(
                /* in */ CleanupMode cleanupMode);
        COMPtr<IProgress> deleteConfig(
                /* in */ const std::vector<COMPtr<IMedium>> &media);
        COMPtr<IVirtualSystemDescription> exportTo(
                /* in */ const COMPtr<IAppliance> &appliance,
                /* in */ const std::u16string &location);
        COMPtr<ISnapshot> findSnapshot(
                /* in */ const std::u16string &nameOrId);
        void createSharedFolder(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const std::u16string &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const std::u16string &name);
        bool canShowConsoleWindow();
        int64_t showConsoleWindow();
        void getGuestProperty(
                /* in  */ const std::u16string &name,
                /* out */ std::u16string *value,
                /* out */ int64_t *timestamp,
                /* out */ std::u16string *flags) const;
        std::u16string getGuestPropertyValue(
                /* in */ const std::u16string &property) const;
        int64_t getGuestPropertyTimestamp(
                /* in */ const std::u16string &property) const;
        void setGuestProperty(
                /* in */ const std::u16string &property,
                /* in */ const std::u16string &value,
                /* in */ const std::u16string &flags);
        void setGuestPropertyValue(
                /* in */ const std::u16string &property,
                /* in */ const std::u16string &value);
        void deleteGuestProperty(
                /* in */ const std::u16string &name) const;
        void enumerateGuestProperties(
                /* in  */ const std::u16string &patterns,
                /* out */ std::vector<std::u16string> *names,
                /* out */ std::vector<std::u16string> *values,
                /* out */ std::vector<int64_t> *timestamps,
                /* out */ std::vector<std::u16string> *flags) const;
        void querySavedGuestScreenInfo(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t *originX,
                /* out */ uint32_t *originY,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height,
                /* out */ bool *enabled) const;
        std::vector<uint8_t> readSavedThumbnailToArray(
                /* in  */ uint32_t screenId,
                /* in  */ BitmapFormat bitmapFormat,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height);
        std::vector<BitmapFormat> querySavedScreenshotInfo(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height);
        std::vector<uint8_t> readSavedScreenshotToArray(
                /* in  */ uint32_t screenId,
                /* in  */ BitmapFormat bitmapFormat,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height);
        void hotPlugCPU(
                /* in */ uint32_t cpu);
        void hotUnplugCPU(
                /* in */ uint32_t cpu);
        bool getCPUStatus(
                /* in */ uint32_t cpu);
        ParavirtProvider getEffectiveParavirtProvider() const;
        std::u16string queryLogFilename(
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
                /* in */ const std::u16string &folder,
                /* in */ const std::u16string &type);
#endif
        COMPtr<IProgress> saveState();
        void adoptSavedState(
                /* in */ const std::u16string &savedStateFile);
        void discardSavedState(
                /* in */ bool fRemoveFile);
        COMPtr<IProgress> takeSnapshot(
                /* in  */ const std::u16string &name,
                /* in  */ const std::u16string &description,
                /* in  */ bool pause,
                /* out */ std::u16string *id);
        COMPtr<IProgress> deleteSnapshot(
                /* in */ const std::u16string &id);
        COMPtr<IProgress> deleteSnapshotAndAllChildren(
                /* in */ const std::u16string &id);
        COMPtr<IProgress> deleteSnapshotRange(
                /* in */ const std::u16string &startId,
                /* in */ const std::u16string &endId);
        COMPtr<IProgress> restoreSnapshot(
                /* in */ const COMPtr<ISnapshot> &snapshot);
        void applyDefaults(
                /* in */ const std::u16string &flags);
    };

    class LIBVBOX_API IEmulatedUSB : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IEmulatedUSB)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::u16string>, webcams)

        // Methods
        void webcamAttach(
                /* in */ const std::u16string &path,
                /* in */ const std::u16string &settings);
        void webcamDetach(
                /* in */ const std::u16string &path);
    };

    class LIBVBOX_API IVRDEServerInfo : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IVRDEServerInfo)

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
        VBox_PROPERTY_RO(std::u16string, user)
        VBox_PROPERTY_RO(std::u16string, domain)
        VBox_PROPERTY_RO(std::u16string, clientName)
        VBox_PROPERTY_RO(std::u16string, clientIP)
        VBox_PROPERTY_RO(uint32_t, clientVersion)
        VBox_PROPERTY_RO(uint32_t, encryptionStyle)
    };

    class LIBVBOX_API IConsole : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IConsole)

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
                /* in */ const std::u16string &id,
                /* in */ const std::u16string &captureFilename);
        COMPtr<IUSBDevice> detachUSBDevice(
                /* in */ const std::u16string &id);
        COMPtr<IUSBDevice> findUSBDeviceByAddress(
                /* in */ const std::u16string &name);
        COMPtr<IUSBDevice> findUSBDeviceById(
                /* in */ const std::u16string &id);
        void createSharedFolder(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &hostPath,
                /* in */ bool writable,
                /* in */ bool automount
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
              , /* in */ const std::u16string &autoMountPoint
#endif
                );
        void removeSharedFolder(
                /* in */ const std::u16string &name);
        COMPtr<IProgress> teleport(
                /* in */ const std::u16string &hostname,
                /* in */ uint32_t tcpport,
                /* in */ const std::u16string &password,
                /* in */ uint32_t maxDowntime);
        void addDiskEncryptionPassword(
                /* in */ const std::u16string &id,
                /* in */ const std::u16string &password,
                /* in */ bool clearOnSuspend);
        void addDiskEncryptionPasswords(
                /* in */ const std::vector<std::u16string> &ids,
                /* in */ const std::vector<std::u16string> &passwords,
                /* in */ bool clearOnSuspend);
        void removeDiskEncryptionPassword(
                /* in */ const std::u16string &id);
        void clearAllDiskEncryptionPasswords();
    };

    class LIBVBOX_API IHostNetworkInterface : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IHostNetworkInterface)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, shortName)
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(std::u16string, networkName)
        VBox_PROPERTY_RO(bool, DHCPEnabled)
        VBox_PROPERTY_RO(std::u16string, IPAddress)
        VBox_PROPERTY_RO(std::u16string, networkMask)
        VBox_PROPERTY_RO(bool, IPV6Supported)
        VBox_PROPERTY_RO(std::u16string, IPV6Address)
        VBox_PROPERTY_RO(uint32_t, IPV6NetworkMaskPrefixLength)
        VBox_PROPERTY_RO(std::u16string, hardwareAddress)
        VBox_PROPERTY_RO(HostNetworkInterfaceMediumType, mediumType)
        VBox_PROPERTY_RO(HostNetworkInterfaceStatus, status)
        VBox_PROPERTY_RO(HostNetworkInterfaceType, interfaceType)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        VBox_PROPERTY_RO(bool, wireless)
#endif

        // Methods
        void enableStaticIPConfig(
                /* in */ const std::u16string &IPAddress,
                /* in */ const std::u16string &networkMask);
        void enableStaticIPConfigV6(
                /* in */ const std::u16string &IPV6Address,
                /* in */ uint32_t IPV6NetworkMaskPrefixLength);
        void enableDynamicIPConfig();
        void DHCPRediscover();
    };

    class LIBVBOX_API IHostVideoInputDevice : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IHostVideoInputDevice)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, path)
        VBox_PROPERTY_RO(std::u16string, alias)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IHostUpdate : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IHostUpdate)
    };
#endif

    class LIBVBOX_API IHost : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IHost)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, DVDDrives)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, floppyDrives)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDevice>>, USBDevices)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostUSBDeviceFilter>>, USBDeviceFilters)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostNetworkInterface>>, networkInterfaces)
        VBox_PROPERTY_RO(std::vector<std::u16string>, nameServers)
        VBox_PROPERTY_RO(std::u16string, domainName)
        VBox_PROPERTY_RO(std::vector<std::u16string>, searchStrings)
        VBox_PROPERTY_RO(uint32_t, processorCount)
        VBox_PROPERTY_RO(uint32_t, processorOnlineCount)
        VBox_PROPERTY_RO(uint32_t, processorCoreCount)
        VBox_PROPERTY_RO(uint32_t, processorOnlineCoreCount)
        VBox_PROPERTY_RO(uint32_t, memorySize)
        VBox_PROPERTY_RO(uint32_t, memoryAvailable)
        VBox_PROPERTY_RO(std::u16string, operatingSystem)
        VBox_PROPERTY_RO(std::u16string, OSVersion)
        VBox_PROPERTY_RO(int64_t, UTCTime)
        VBox_PROPERTY_RO(bool, acceleration3DAvailable)
        VBox_PROPERTY_RO(std::vector<COMPtr<IHostVideoInputDevice>>, videoInputDevices)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(COMPtr<IHostUpdate>, update)
#endif

        // Methods
        uint32_t getProcessorSpeed(
                /* in */ uint32_t cpuId);
        bool getProcessorFeature(
                /* in */ ProcessorFeature feature);
        std::u16string getProcessorDescription(
                /* in */ uint32_t cpuId);
        void getProcessorCPUIDLeaf(
                /* in  */ uint32_t cpuId,
                /* in  */ uint32_t leaf,
                /* in  */ uint32_t subLeaf,
                /* out */ uint32_t *valEax,
                /* out */ uint32_t *valEbx,
                /* out */ uint32_t *valEcx,
                /* out */ uint32_t *valEdx);
        COMPtr<IProgress> createHostOnlyNetworkInterface(
                /* out */ COMPtr<IHostNetworkInterface> *hostInterface);
        COMPtr<IProgress> removeHostOnlyNetworkInterface(
                /* in */ const std::u16string &id);
        COMPtr<IHostUSBDeviceFilter> createUSBDeviceFilter(
                /* in */ const std::u16string name);
        void insertUSBDeviceFilter(
                /* in */ uint32_t position,
                /* in */ const COMPtr<IHostUSBDeviceFilter> &filter);
        void removeUSBDeviceFilter(
                /* in */ uint32_t position);
        COMPtr<IMedium> findHostDVDDrive(
                /* in */ const std::u16string &name);
        COMPtr<IMedium> findHostFloppyDrive(
                /* in */ const std::u16string &name);
        COMPtr<IHostNetworkInterface> findHostNetworkInterfaceByName(
                /* in */ const std::u16string &name);
        COMPtr<IHostNetworkInterface> findHostNetworkInterfaceById(
                /* in */ const std::u16string &id);
        std::vector<COMPtr<IHostNetworkInterface>> findHostNetworkInterfacesOfType(
                /* in */ HostNetworkInterfaceType type);
        COMPtr<IHostUSBDevice> findUSBDeviceById(
                /* in */ const std::u16string &id);
        COMPtr<IHostUSBDevice> findUSBDeviceByAddress(
                /* in */ const std::u16string &name);
        std::u16string generateMACAddress();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        void addUSBDeviceSource(
                /* in */ const std::u16string &backend,
                /* in */ const std::u16string &id,
                /* in */ const std::u16string &address,
                /* in */ const std::vector<std::u16string> &propertyNames,
                /* in */ const std::vector<std::u16string> &propertyValues);
        void removeUSBDeviceSource(
                /* in */ const std::u16string &id);
#endif
    };

    class LIBVBOX_API ISystemProperties : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ISystemProperties)

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
        VBox_PROPERTY_RW_R(std::u16string, defaultMachineFolder)
        VBox_PROPERTY_RW_R(std::u16string, loggingLevel)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMediumFormat>>, mediumFormats)
        VBox_PROPERTY_RW_R(std::u16string, defaultHardDiskFormat)
        VBox_PROPERTY_RW_V(int64_t, freeDiskSpaceWarning)
        VBox_PROPERTY_RW_V(uint32_t, freeDiskSpacePercentWarning)
        VBox_PROPERTY_RW_V(int64_t, freeDiskSpaceError)
        VBox_PROPERTY_RW_V(uint32_t, freeDiskSpacePercentError)
        VBox_PROPERTY_RW_R(std::u16string, VRDEAuthLibrary)
        VBox_PROPERTY_RW_R(std::u16string, webServiceAuthLibrary)
        VBox_PROPERTY_RW_R(std::u16string, defaultVRDEExtPack)
        VBox_PROPERTY_RW_V(uint32_t, logHistoryCount)
        VBox_PROPERTY_RO(AudioDriverType, defaultAudioDriver)
        VBox_PROPERTY_RW_R(std::u16string, autostartDatabasePath)
        VBox_PROPERTY_RW_R(std::u16string, defaultAdditionsISO)
        VBox_PROPERTY_RW_R(std::u16string, defaultFrontend)
        VBox_PROPERTY_RO(std::vector<BitmapFormat>, screenShotFormats)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(ProxyMode, proxyMode)
        VBox_PROPERTY_RW_R(std::u16string, proxyURL)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(std::vector<ParavirtProvider>, supportedParavirtProviders)
        VBox_PROPERTY_RO(std::vector<ClipboardMode>, supportedClipboardModes)
        VBox_PROPERTY_RO(std::vector<DnDMode>, supportedDnDModes)
        VBox_PROPERTY_RO(std::vector<FirmwareType>, supportedFirmwareTypes)
        VBox_PROPERTY_RO(std::vector<PointingHIDType>, supportedPointingHIDTypes)
        VBox_PROPERTY_RO(std::vector<KeyboardHIDType>, supportedKeyboardHIDTypes)
        VBox_PROPERTY_RO(std::vector<VFSType>, supportedVFSTypes)
        VBox_PROPERTY_RO(std::vector<ImportOptions>, supportedImportOptions)
        VBox_PROPERTY_RO(std::vector<ExportOptions>, supportedExportOptions)
        VBox_PROPERTY_RO(std::vector<RecordingAudioCodec>, supportedRecordingAudioCodecs)
        VBox_PROPERTY_RO(std::vector<RecordingVideoCodec>, supportedRecordingVideoCodecs)
        VBox_PROPERTY_RO(std::vector<RecordingVideoScalingMethod>, supportedRecordingVSMethods)
        VBox_PROPERTY_RO(std::vector<RecordingVideoRateControlMode>, supportedRecordingVRCModes)
        VBox_PROPERTY_RO(std::vector<GraphicsControllerType>, supportedGraphicsControllerTypes)
        VBox_PROPERTY_RO(std::vector<CloneOptions>, supportedCloneOptions)
        VBox_PROPERTY_RO(std::vector<AutostopType>, supportedAutostopTypes)
        VBox_PROPERTY_RO(std::vector<VMProcPriority>, supportedVMProcPriorities)
        VBox_PROPERTY_RO(std::vector<NetworkAttachmentType>, supportedNetworkAttachmentTypes)
        VBox_PROPERTY_RO(std::vector<NetworkAdapterType>, supportedNetworkAdapterTypes)
        VBox_PROPERTY_RO(std::vector<PortMode>, supportedPortModes)
        VBox_PROPERTY_RO(std::vector<UartType>, supportedUartTypes)
        VBox_PROPERTY_RO(std::vector<USBControllerType>, supportedUSBControllerTypes)
        VBox_PROPERTY_RO(std::vector<AudioDriverType>, supportedAudioDriverTypes)
        VBox_PROPERTY_RO(std::vector<AudioControllerType>, supportedAudioControllerTypes)
        VBox_PROPERTY_RO(std::vector<StorageBus>, supportedStorageBuses)
        VBox_PROPERTY_RO(std::vector<StorageControllerType>, supportedStorageControllerTypes)
        VBox_PROPERTY_RO(std::vector<ChipsetType>, supportedChipsetTypes)
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
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        StorageBus getStorageBusForStorageControllerType(
                /* in */ StorageControllerType storageControllerType);
        std::vector<StorageControllerType> getStorageControllerTypesForStorageBus(
                /* in */ StorageBus storageBus);
#endif
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
        VBox_COM_WRAPPED(::IGuestOSType)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, familyId)
        VBox_PROPERTY_RO(std::u16string, familyDescription)
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(std::u16string, description)
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
        VBox_COM_WRAPPED(::IAdditionsFacility)

        // Attributes
        VBox_PROPERTY_RO(AdditionsFacilityClass, classType)
        VBox_PROPERTY_RO(int64_t, lastUpdated)
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(AdditionsFacilityStatus, status)
        VBox_PROPERTY_RO(AdditionsFacilityType, type)
    };

    class LIBVBOX_API IDnDBase : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDnDBase)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::u16string>, formats)
        VBox_PROPERTY_RO(uint32_t, protocolVersion)

        // Methods
        bool isFormatSupported(
                /* in */ const std::u16string &format);
        void addFormats(
                /* in */ const std::vector<std::u16string> &formats);
        void removeFormats(
                /* in */ const std::vector<std::u16string> &formats);
    };

    class LIBVBOX_API IDnDSource : public IDnDBase
    {
    public:
        VBox_COM_WRAPPED(::IDnDSource)

        // Methods
        DnDAction dragIsPending(
                /* in  */ uint32_t screenId,
                /* out */ std::vector<std::u16string> *formats,
                /* out */ std::vector<DnDAction> *allowedActions);
        COMPtr<IProgress> drop(
                /* in */ const std::u16string &format,
                /* in */ DnDAction action);
        std::vector<uint8_t> receiveData();
    };

    class LIBVBOX_API IGuestDnDSource : public IDnDSource
    {
    public:
        VBox_COM_WRAPPED(::IGuestDnDSource)
    };

    class LIBVBOX_API IDnDTarget : public IDnDBase
    {
    public:
        VBox_COM_WRAPPED(::IDnDTarget)

        // Methods
        DnDAction enter(
                /* in */ uint32_t screenId,
                /* in */ uint32_t y,
                /* in */ uint32_t x,
                /* in */ DnDAction defaultAction,
                /* in */ const std::vector<DnDAction> &allowedActions,
                /* in */ const std::vector<std::u16string> &formats);
        DnDAction move(
                /* in */ uint32_t screenId,
                /* in */ uint32_t x,
                /* in */ uint32_t y,
                /* in */ DnDAction defaultAction,
                /* in */ const std::vector<DnDAction> &allowedActions,
                /* in */ const std::vector<std::u16string> &formats);
        void leave(
                /* in */ uint32_t screenId);
        DnDAction drop(
                /* in  */ uint32_t screenId,
                /* in  */ uint32_t x,
                /* in  */ uint32_t y,
                /* in  */ DnDAction defaultAction,
                /* in  */ const std::vector<DnDAction> &allowedActions,
                /* in  */ const std::vector<std::u16string> &formats,
                /* out */ std::u16string *format);
        COMPtr<IProgress> sendData(
                /* in */ uint32_t screenId,
                /* in */ const std::u16string& format,
                /* in */ const std::vector<uint8_t> &data);
        bool cancel();
    };

    class LIBVBOX_API IGuestDnDTarget : public IDnDTarget
    {
    public:
        VBox_COM_WRAPPED(::IGuestDnDTarget)
    };

    class LIBVBOX_API IGuestSession : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IGuestSession)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, user)
        VBox_PROPERTY_RO(std::u16string, domain)
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RW_V(uint32_t, timeout)
        VBox_PROPERTY_RO(uint32_t, protocolVersion)
        VBox_PROPERTY_RO(GuestSessionStatus, status)
        VBox_PROPERTY_RW_R(std::vector<std::u16string>, environmentChanges)
        VBox_PROPERTY_RO(std::vector<std::u16string>, environmentBase)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestProcess>>, processes)
        VBox_PROPERTY_RO(PathStyle, pathStyle)
        VBox_PROPERTY_RW_R(std::u16string, currentDirectory)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(std::u16string, userHome)
        VBox_PROPERTY_RO(std::u16string, userDocuments)
#endif
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestDirectory>>, directories)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestFile>>, files)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)

        // Methods
        void close();
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> copyFromGuest(
                /* in */ const std::vector<std::u16string> &sources,
                /* in */ const std::vector<std::u16string> &filters,
                /* in */ const std::vector<std::u16string> &flags,
                /* in */ const std::u16string &destination);
        COMPtr<IProgress> copyToGuest(
                /* in */ const std::vector<std::u16string> &sources,
                /* in */ const std::vector<std::u16string> &filters,
                /* in */ const std::vector<std::u16string> &flags,
                /* in */ const std::u16string &destination);
#endif
        COMPtr<IProgress> directoryCopy(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        COMPtr<IProgress> directoryCopyFromGuest(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        COMPtr<IProgress> directoryCopyToGuest(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<DirectoryCopyFlag> &flags);
        void directoryCreate(
                /* in */ const std::u16string &path,
                /* in */ uint32_t mode,
                /* in */ const std::vector<DirectoryCreateFlag> &flags);
        std::u16string directoryCreateTemp(
                /* in */ const std::u16string &templateName,
                /* in */ uint32_t mode,
                /* in */ const std::u16string &path,
                /* in */ bool secure);
        bool directoryExists(
                /* in */ const std::u16string &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestDirectory> directoryOpen(
                /* in */ const std::u16string &path,
                /* in */ const std::u16string &filter,
                /* in */ const std::vector<DirectoryOpenFlag> &flags);
        void directoryRemove(
                /* in */ const std::u16string &path);
        COMPtr<IProgress> directoryRemoveRecursive(
                /* in */ const std::u16string &path,
                /* in */ const std::vector<DirectoryRemoveRecFlag> &flags);
        void environmentScheduleSet(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &value);
        void environmentScheduleUnset(
                /* in */ const std::u16string &name);
        std::u16string environmentGetBaseVariable(
                /* in */ const std::u16string &name);
        bool environmentDoesBaseVariableExist(
                /* in */ const std::u16string &name);
        COMPtr<IProgress> fileCopy(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IProgress> fileCopyFromGuest(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IProgress> fileCopyToGuest(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
        COMPtr<IGuestFile> fileCreateTemp(
                /* in */ const std::u16string &templateName,
                /* in */ uint32_t mode,
                /* in */ const std::u16string &path,
                /* in */ bool secure);
        bool fileExists(
                /* in */ const std::u16string &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestFile> fileOpen(
                /* in */ const std::u16string &path,
                /* in */ FileAccessMode accessMode,
                /* in */ FileOpenAction openAction,
                /* in */ uint32_t creationMode);
        COMPtr<IGuestFile> fileOpenEx(
                /* in */ const std::u16string &path,
                /* in */ FileAccessMode accessMode,
                /* in */ FileOpenAction openAction,
                /* in */ FileSharingMode sharingMode,
                /* in */ uint32_t creationMode,
                /* in */ const std::vector<FileOpenExFlag> &flags);
        int64_t fileQuerySize(
                /* in */ const std::u16string &path,
                /* in */ bool followSymlinks);
        bool fsObjExists(
                /* in */ const std::u16string &path,
                /* in */ bool followSymlinks);
        COMPtr<IGuestFsObjInfo> fsObjQueryInfo(
                /* in */ const std::u16string &path,
                /* in */ bool followSymlinks);
        void fsObjRemove(
                /* in */ const std::u16string &path);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> fsObjRemoveArray(
                /* in */ const std::vector<std::u16string> &path);
#endif
        void fsObjRename(
                /* in */ const std::u16string &oldPath,
                /* in */ const std::u16string &newPath,
                /* in */ const std::vector<FsObjRenameFlag> &flags);
        COMPtr<IProgress> fsObjMove(
                /* in */ const std::u16string &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<FsObjMoveFlag> &flags);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IProgress> fsObjMoveArray(
                /* in */ const std::vector<std::u16string> &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<FsObjMoveFlag> &flags);
        COMPtr<IProgress> fsObjCopyArray(
                /* in */ const std::vector<std::u16string> &source,
                /* in */ const std::u16string &destination,
                /* in */ const std::vector<FileCopyFlag> &flags);
#endif
        void fsObjSetACL(
                /* in */ const std::u16string &path,
                /* in */ bool followSymlinks,
                /* in */ const std::u16string &acl,
                /* in */ uint32_t mode);
        COMPtr<IGuestProcess> processCreate(
                /* in */ const std::u16string &executable,
                /* in */ const std::vector<std::u16string> &arguments,
                /* in */ const std::vector<std::u16string> &environmentChanges,
                /* in */ const std::vector<ProcessCreateFlag> &flags,
                /* in */ uint32_t timeoutMS);
        COMPtr<IGuestProcess> processCreateEx(
                /* in */ const std::u16string &executable,
                /* in */ const std::vector<std::u16string> &arguments,
                /* in */ const std::vector<std::u16string> &environmentChanges,
                /* in */ const std::vector<ProcessCreateFlag> &flags,
                /* in */ uint32_t timeoutMS,
                /* in */ ProcessPriority priority,
                /* in */ const std::vector<int32_t> &affinity);
        COMPtr<IGuestProcess> processGet(
                /* in */ uint32_t pid);
        void symlinkCreate(
                /* in */ const std::u16string &symlink,
                /* in */ const std::u16string &target,
                /* in */ SymlinkType type);
        bool symlinkExists(
                /* in */ const std::u16string &symlink);
        std::u16string symlinkRead(
                /* in */ const std::u16string &symlink,
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
        VBox_COM_WRAPPED(::IProcess)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::u16string>, arguments)
        VBox_PROPERTY_RO(std::vector<std::u16string>, environment)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::u16string, executablePath)
        VBox_PROPERTY_RO(int32_t, exitCode)
        VBox_PROPERTY_RO(std::u16string, name)
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
        VBox_COM_WRAPPED(::IGuestProcess)
    };

    class LIBVBOX_API IDirectory : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDirectory)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, directoryName)
        VBox_PROPERTY_RO(std::u16string, filter)

        // Methods
        void close();
        COMPtr<IFsObjInfo> read();
    };

    class LIBVBOX_API IGuestDirectory : public IDirectory
    {
    public:
        VBox_COM_WRAPPED(::IGuestDirectory)
    };

    class LIBVBOX_API IFile : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IFile)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RO(int64_t, initialSize)
        VBox_PROPERTY_RO(int64_t, offset)
        VBox_PROPERTY_RO(FileStatus, status)
        VBox_PROPERTY_RO(std::u16string, filename)
        VBox_PROPERTY_RO(std::u16string, fileName)    // Old name for "filename" attribute
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
                /* in */ const std::u16string &acl,
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
        VBox_COM_WRAPPED(::IGuestFile)
    };

    class LIBVBOX_API IFsObjInfo : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IFsObjInfo)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(FsObjType, type)
        VBox_PROPERTY_RO(std::u16string, fileAttributes)
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
        VBox_PROPERTY_RO(std::u16string, userName)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(int32_t, GID)
#else
        VBox_PROPERTY_RO(uint32_t, GID)
#endif
        VBox_PROPERTY_RO(std::u16string, groupName)
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
        VBox_COM_WRAPPED(::IGuestFsObjInfo)
    };

    class LIBVBOX_API IGuest : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IGuest)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, OSTypeId)
        VBox_PROPERTY_RO(AdditionsRunLevelType, additionsRunLevel)
        VBox_PROPERTY_RO(std::u16string, additionsVersion)
        VBox_PROPERTY_RO(uint32_t, additionsRevision)
        VBox_PROPERTY_RO(COMPtr<IGuestDnDSource>, dnDSource)
        VBox_PROPERTY_RO(COMPtr<IGuestDnDTarget>, dnDTarget)
        VBox_PROPERTY_RO(COMPtr<IEventSource>, eventSource)
        VBox_PROPERTY_RO(std::vector<COMPtr<IAdditionsFacility>>, facilities)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestSession>>, sessions)
        VBox_PROPERTY_RW_V(uint32_t, memoryBalloonSize)
        VBox_PROPERTY_RW_V(uint32_t, statisticsUpdateInterval)

        // Methods
        void internalGetStatistics(
                /* out */ uint32_t *cpuUser,
                /* out */ uint32_t *cpuKernel,
                /* out */ uint32_t *cpuIdle,
                /* out */ uint32_t *memTotal,
                /* out */ uint32_t *memFree,
                /* out */ uint32_t *memBalloon,
                /* out */ uint32_t *memShared,
                /* out */ uint32_t *memCache,
                /* out */ uint32_t *pagedTotal,
                /* out */ uint32_t *memAllocTotal,
                /* out */ uint32_t *memFreeTotal,
                /* out */ uint32_t *memBalloonTotal,
                /* out */ uint32_t *memSharedTotal);
        AdditionsFacilityStatus getFacilityStatus(
                /* in  */ AdditionsFacilityType facility,
                /* out */ int64_t *timestamp);
        bool getAdditionsStatus(
                /* in */ AdditionsRunLevelType level);
        void setCredentials(
                /* in */ const std::u16string &userName,
                /* in */ const std::u16string &password,
                /* in */ const std::u16string &domain,
                /* in */ bool allowInteractiveLogon);
        COMPtr<IGuestSession> createSession(
                /* in */ const std::u16string &user,
                /* in */ const std::u16string &password,
                /* in */ const std::u16string &domain,
                /* in */ const std::u16string &sessionName);
        std::vector<COMPtr<IGuestSession>> findSession(
                /* in */ const std::u16string &sessionName);
        COMPtr<IProgress> updateGuestAdditions(
                /* in */ const std::u16string &source,
                /* in */ const std::vector<std::u16string> &arguments,
                /* in */ const std::vector<AdditionsUpdateFlag> &flags);
    };

    class LIBVBOX_API IProgress : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IProgress)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(std::u16string, description)
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
        VBox_PROPERTY_RO(std::u16string, operationDescription)
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
                /* in */ const std::u16string &nextOperationDescription,
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
        VBox_COM_WRAPPED(::IInternalProgressControl)

        // Methods
        void setCurrentOperationProgress(
                /* in */ uint32_t percent);
        void waitForOtherProgressCompletion(
                /* in */ const COMPtr<IProgress> &progressOther,
                /* in */ uint32_t timeoutMS);
        void setNextOperation(
                /* in */ const std::u16string &nextOperationDescription,
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
        VBox_COM_WRAPPED(::ISnapshot)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RW_R(std::u16string, description)
        VBox_PROPERTY_RO(int64_t, timeStamp)
        VBox_PROPERTY_RO(bool, online)
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RO(COMPtr<ISnapshot>, parent)
        VBox_PROPERTY_RO(std::vector<COMPtr<ISnapshot>>, children)
        VBox_PROPERTY_RO(uint32_t, childrenCount)

        // Methods
        uint32_t getChildrenCount() const;  // Old name for childrenCount property
    };

    class LIBVBOX_API IMediumAttachment : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IMediumAttachment)

        // Attributes
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
#endif
        VBox_PROPERTY_RO(COMPtr<IMedium>, medium)
        VBox_PROPERTY_RO(std::u16string, controller)
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
        VBox_COM_WRAPPED(::IMedium)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RW_R(std::u16string, description)
        VBox_PROPERTY_RO(MediumState, state)
        VBox_PROPERTY_RO(std::vector<MediumVariant>, variant)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_R(std::u16string, location)
#else
        VBox_PROPERTY_RO(std::u16string, location)
#endif
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(DeviceType, deviceType)
        VBox_PROPERTY_RO(bool, hostDrive)
        VBox_PROPERTY_RO(int64_t, size)
        VBox_PROPERTY_RO(std::u16string, format)
        VBox_PROPERTY_RO(COMPtr<IMediumFormat>, mediumFormat)
        VBox_PROPERTY_RW_V(MediumType, type)
        VBox_PROPERTY_RO(std::vector<MediumType>, allowedTypes)
        VBox_PROPERTY_RO(COMPtr<IMedium>, parent)
        VBox_PROPERTY_RO(std::vector<COMPtr<IMedium>>, children)
        VBox_PROPERTY_RO(COMPtr<IMedium>, base)
        VBox_PROPERTY_RO(bool, readOnly)
        VBox_PROPERTY_RO(int64_t, logicalSize)
        VBox_PROPERTY_RW_V(bool, autoReset)
        VBox_PROPERTY_RO(std::u16string, lastAccessError)
        VBox_PROPERTY_RO(std::vector<std::u16string>, machineIds)

        // Methods
        void setIds(
                /* in */ bool setImageId,
                /* in */ const std::u16string &imageId,
                /* in */ bool setParentId,
                /* in */ const std::u16string &parentId);
        MediumState refreshState();
        std::vector<std::u16string> getSnapshotIds(
                /* in */ const std::u16string &machineId);
        COMPtr<IToken> lockRead();
        COMPtr<IToken> lockWrite();
        void close();
        std::u16string getProperty(
                /* in */ const std::u16string &name) const;
        void setProperty(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &value);
        std::vector<std::u16string> getProperties(
                /* in  */ const std::u16string &names,
                /* out */ std::vector<std::u16string> *returnNames) const;
        void setProperties(
                /* in */ const std::vector<std::u16string> &names,
                /* in */ const std::vector<std::u16string> &values);
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
                /* in */ const std::u16string &location);     // Old name for moveTo()
        COMPtr<IProgress> moveTo(
                /* in */ const std::u16string &location);
        COMPtr<IProgress> compact();
        COMPtr<IProgress> resize(
                /* in */ int64_t logicalSize);
        COMPtr<IProgress> reset();
        COMPtr<IProgress> changeEncryption(
                /* in */ const std::u16string &currentPassword,
                /* in */ const std::u16string &cipher,
                /* in */ const std::u16string &newPassword,
                /* in */ const std::u16string &newPasswordId);
        std::u16string getEncryptionSettings(
                /* out */ std::u16string *cipher) const;
        void checkEncryptionPassword(
                /* in */ const std::u16string &password) const;
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        COMPtr<IMediumIO> openForIO(
                /* in */ bool writable,
                /* in */ const std::u16string &password);
#endif
    };

    class LIBVBOX_API IMediumFormat : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IMediumFormat)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::vector<MediumFormatCapabilities>, capabilities)

        // Methods
        void describeFileExtensions(
                /* out */ std::vector<std::u16string> *extensions,
                /* out */ std::vector<DeviceType> *types);
        void describeProperties(
                /* out */ std::vector<std::u16string> *names,
                /* out */ std::vector<std::u16string> *descriptions,
                /* out */ std::vector<DataType> *types,
                /* out */ std::vector<uint32_t> *flags,
                /* out */ std::vector<std::u16string> *defaults) const;
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IDataStream : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDataStream)

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
        VBox_COM_WRAPPED(::IMediumIO)

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
                /* in  */ const std::u16string &format,
                /* in  */ const std::vector<MediumVariant> &variant,
                /* in  */ uint32_t bufferSize,
                /* out */ COMPtr<IDataStream> *stream);
        void close();
    };
#endif

    class LIBVBOX_API IToken : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IToken)

        // Methods
        void abandon();
        void dummy();
    };

    class LIBVBOX_API IKeyboard : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IKeyboard)

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
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        void putUsageCode(
                /* in */ int32_t usageCode,
                /* in */ int32_t usagePage,
                /* in */ bool keyRelease);
#endif
    };

    class LIBVBOX_API IMousePointerShape : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IMousePointerShape)

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
        VBox_COM_WRAPPED(::IMouse)

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
                /* in */ const std::u16string &contacts,
                /* in */ uint32_t scanTime);
    };

    class LIBVBOX_API IDisplaySourceBitmap : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDisplaySourceBitmap)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, screenId)

        // Methods
        void queryBitmapInfo(
                /* out */ uint8_t **address,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height,
                /* out */ uint32_t *bitsPerPixel,
                /* out */ uint32_t *bytesPerLine,
                /* out */ BitmapFormat *bitmapFormat);
    };

    class LIBVBOX_API IFramebuffer : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IFramebuffer)

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
        VBox_COM_WRAPPED(::IFramebufferOverlay)

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
        VBox_COM_WRAPPED(::IGuestScreenInfo)

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
        VBox_PROPERTY_RO(std::u16string, extendedInfo)
#endif
    };
#endif

    class LIBVBOX_API IDisplay : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IDisplay)

        // Attributes
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(std::vector<COMPtr<IGuestScreenInfo>>, guestScreenLayout)
#endif

        // Methods
        void getScreenResolution(
                /* in  */ uint32_t screenId,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height,
                /* out */ uint32_t *bitsPerPixel,
                /* out */ int32_t *xOrigin,
                /* out */ int32_t *yOrigin,
                /* out */ GuestMonitorStatus *guestMonitorStatus);
        std::u16string attachFramebuffer(
                /* in */ uint32_t screenId,
                /* in */ const COMPtr<IFramebuffer> &framebuffer);
        void detachFramebuffer(
                /* in */ uint32_t screenId,
                /* in */ const std::u16string &id);
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
                /* in */ uint32_t bitsPerPixel
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
              , /* in */ bool notify
#endif
                );
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        void getVideoModeHint(
                /* in  */ uint32_t display,
                /* out */ bool *enabled,
                /* out */ bool *changeOrigin,
                /* out */ int32_t *originX,
                /* out */ int32_t *originY,
                /* out */ uint32_t *width,
                /* out */ uint32_t *height,
                /* out */ uint32_t *bitsPerPixel);
#endif
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
                /* out */ COMPtr<IDisplaySourceBitmap> *displaySourceBitmap);
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
        VBox_COM_WRAPPED(::INetworkAdapter)

        // Attributes
        VBox_PROPERTY_RW_V(NetworkAdapterType, adapterType)
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_R(std::u16string, MACAddress)
        VBox_PROPERTY_RW_V(NetworkAttachmentType, attachmentType)
        VBox_PROPERTY_RW_R(std::u16string, bridgedInterface)
        VBox_PROPERTY_RW_R(std::u16string, hostOnlyInterface)
        VBox_PROPERTY_RW_R(std::u16string, internalNetwork)
        VBox_PROPERTY_RW_R(std::u16string, NATNetwork)
        VBox_PROPERTY_RW_R(std::u16string, genericDriver)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_R(std::u16string, cloudNetwork)
#endif
        VBox_PROPERTY_RW_V(bool, cableConnected)
        VBox_PROPERTY_RW_V(uint32_t, lineSpeed)
        VBox_PROPERTY_RW_V(NetworkAdapterPromiscModePolicy, promiscModePolicy)
        VBox_PROPERTY_RW_V(bool, traceEnabled)
        VBox_PROPERTY_RW_R(std::u16string, traceFile)
        VBox_PROPERTY_RO(COMPtr<INATEngine>, NATEngine)
        VBox_PROPERTY_RW_V(uint32_t, bootPriority)
        VBox_PROPERTY_RW_R(COMPtr<IBandwidthGroup>, bandwidthGroup)

        // Methods
        std::u16string getProperty(
                /* in */ const std::u16string &key) const;
        void setProperty(
                /* in */ const std::u16string &key,
                /* in */ const std::u16string &value);
        std::vector<std::u16string> getProperties(
                /* in  */ const std::u16string &names,
                /* out */ std::vector<std::u16string> *returnNames) const;
    };

    class LIBVBOX_API ISerialPort : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ISerialPort)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, IOBase)
        VBox_PROPERTY_RW_V(uint32_t, IRQ)
        VBox_PROPERTY_RW_V(PortMode, hostMode)
        VBox_PROPERTY_RW_V(bool, server)
        VBox_PROPERTY_RW_R(std::u16string, path)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(UartType, uartType)
#endif
    };

    class LIBVBOX_API IParallelPort : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IParallelPort)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(uint32_t, IOBase)
        VBox_PROPERTY_RW_V(uint32_t, IRQ)
        VBox_PROPERTY_RW_R(std::u16string, path)
    };

    class LIBVBOX_API IMachineDebugger : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IMachineDebugger)

        // Attributes
        VBox_PROPERTY_RW_V(bool, singleStep)
        VBox_PROPERTY_RW_V(bool, recompileUser)
        VBox_PROPERTY_RW_V(bool, recompileSupervisor)
        VBox_PROPERTY_RW_V(bool, executeAllInIEM)
        VBox_PROPERTY_RW_V(bool, PATMEnabled)
        VBox_PROPERTY_RW_V(bool, CSAMEnabled)
        VBox_PROPERTY_RW_V(bool, logEnabled)
        VBox_PROPERTY_RO(std::u16string, logDbgFlags)
        VBox_PROPERTY_RO(std::u16string, logDbgGroups)
        VBox_PROPERTY_RO(std::u16string, logDbgDestinations)
        VBox_PROPERTY_RO(std::u16string, logRelFlags)
        VBox_PROPERTY_RO(std::u16string, logRelGroups)
        VBox_PROPERTY_RO(std::u16string, logRelDestinations)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RO(VMExecutionEngine, executionEngine)
#endif
        VBox_PROPERTY_RO(bool, HWVirtExEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExNestedPagingEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExVPIDEnabled)
        VBox_PROPERTY_RO(bool, HWVirtExUXEnabled)
        VBox_PROPERTY_RO(std::u16string, OSName)
        VBox_PROPERTY_RO(std::u16string, OSVersion)
        VBox_PROPERTY_RO(bool, PAEEnabled)
        VBox_PROPERTY_RW_V(uint32_t, virtualTimeRate)
        VBox_PROPERTY_RO(int64_t, VM)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 4)
        VBox_PROPERTY_RO(int64_t, uptime)
#endif

        // Methods
        void dumpGuestCore(
                /* in */ const std::u16string &filename,
                /* in */ const std::u16string &compression);
        void dumpHostProcessCore(
                /* in */ const std::u16string &filename,
                /* in */ const std::u16string &compression);
        std::u16string info(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &args);
        void injectNMI();
        void modifyLogGroups(
                /* in */ const std::u16string &settings);
        void modifyLogFlags(
                /* in */ const std::u16string &settings);
        void modifyLogDestinations(
                /* in */ const std::u16string &settings);
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
        std::u16string loadPlugIn(
                /* in */ const std::u16string &name);
        void unloadPlugIn(
                /* in */ const std::u16string &name);
        std::u16string detectOS();
        std::u16string queryOSKernelLog(
                /* in */ uint32_t maxMessages);
        std::u16string getRegister(
                /* in */ uint32_t cpuId,
                /* in */ const std::u16string &name);
        void getRegisters(
                /* in  */ uint32_t cpuId,
                /* out */ std::vector<std::u16string> *names,
                /* out */ std::vector<std::u16string> *values);
        void setRegister(
                /* in */ uint32_t cpuId,
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &value);
        void setRegisters(
                /* in */ uint32_t cpuId,
                /* in */ const std::vector<std::u16string> &names,
                /* in */ const std::vector<std::u16string> &values);
        std::u16string dumpGuestStack(
                /* in */ uint32_t cpuId);
        void resetStats(
                /* in */ const std::u16string &pattern);
        void dumpStats(
                /* in */ const std::u16string &pattern);
        std::u16string getStats(
                /* in */ const std::u16string &pattern,
                /* in */ bool withDescriptions);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        int64_t getCPULoad(
                /* in  */ uint32_t cpuId,
                /* out */ uint32_t *pctExecuting,
                /* out */ uint32_t *pctHalted,
                /* out */ uint32_t *pctOther);
#endif
    };

    class LIBVBOX_API IUSBDeviceFilters : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IUSBDeviceFilters)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IUSBDeviceFilter>>, deviceFilters)

        // Methods
        COMPtr<IUSBDeviceFilter> createDeviceFilter(
                /* in */ const std::u16string &name);
        void insertDeviceFilter(
                /* in */ uint32_t position,
                /* in */ const COMPtr<IUSBDeviceFilter> &filter);
        COMPtr<IUSBDeviceFilter> removeDeviceFilter(
                /* in */ uint32_t position);
    };

    class LIBVBOX_API IUSBController : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IUSBController)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RW_V(USBControllerType, type)
        VBox_PROPERTY_RO(uint16_t, USBStandard)
    };

    class LIBVBOX_API IUSBDevice : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IUSBDevice)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(uint16_t, vendorId)
        VBox_PROPERTY_RO(uint16_t, productId)
        VBox_PROPERTY_RO(uint16_t, revision)
        VBox_PROPERTY_RO(std::u16string, manufacturer)
        VBox_PROPERTY_RO(std::u16string, product)
        VBox_PROPERTY_RO(std::u16string, serialNumber)
        VBox_PROPERTY_RO(std::u16string, address)
        VBox_PROPERTY_RO(uint16_t, port)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(std::u16string, portPath)
#endif
        VBox_PROPERTY_RO(uint16_t, version)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(uint16_t, portVersion)
#endif
        VBox_PROPERTY_RO(USBConnectionSpeed, speed)
        VBox_PROPERTY_RO(bool, remote)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 0, 14)
        VBox_PROPERTY_RO(std::vector<std::u16string>, deviceInfo)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        VBox_PROPERTY_RO(std::u16string, backend)
#endif
    };

    class LIBVBOX_API IUSBDeviceFilter : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IUSBDeviceFilter)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RW_V(bool, active)
        VBox_PROPERTY_RW_R(std::u16string, vendorId)
        VBox_PROPERTY_RW_R(std::u16string, productId)
        VBox_PROPERTY_RW_R(std::u16string, revision)
        VBox_PROPERTY_RW_R(std::u16string, manufacturer)
        VBox_PROPERTY_RW_R(std::u16string, product)
        VBox_PROPERTY_RW_R(std::u16string, serialNumber)
        VBox_PROPERTY_RW_R(std::u16string, port)
        VBox_PROPERTY_RW_R(std::u16string, remote)
        VBox_PROPERTY_RW_V(uint32_t, maskedInterfaces)
    };

    class LIBVBOX_API IHostUSBDevice : public IUSBDevice
    {
    public:
        VBox_COM_WRAPPED(::IHostUSBDevice)

        // Attributes
        VBox_PROPERTY_RO(USBDeviceState, state)
    };

    class LIBVBOX_API IHostUSBDeviceFilter : public IUSBDeviceFilter
    {
    public:
        VBox_COM_WRAPPED(::IHostUSBDeviceFilter)

        // Attributes
        VBox_PROPERTY_RW_V(USBDeviceFilterAction, action)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    class LIBVBOX_API IUSBProxyBackend : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IUSBProxyBackend)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, type)
    };
#endif

    class LIBVBOX_API IAudioAdapter : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IAudioAdapter)

        // Attributes
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(bool, enabledIn)
        VBox_PROPERTY_RW_V(bool, enabledOut)
        VBox_PROPERTY_RW_V(AudioControllerType, audioController)
        VBox_PROPERTY_RW_V(AudioCodecType, audioCodec)
        VBox_PROPERTY_RW_V(AudioDriverType, audioDriver)
        VBox_PROPERTY_RO(std::vector<std::u16string>, propertiesList)

        // Methods
        void setProperty(
                /* in */ const std::u16string &key,
                /* in */ const std::u16string &value);
        std::u16string getProperty(
                /* in */ const std::u16string &key) const;
    };

    class LIBVBOX_API IVRDEServer : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IVRDEServer)

        // Attributes
        VBox_PROPERTY_RW_V(bool, enabled)
        VBox_PROPERTY_RW_V(AuthType, authType)
        VBox_PROPERTY_RW_V(uint32_t, authTimeout)
        VBox_PROPERTY_RW_V(bool, allowMultiConnection)
        VBox_PROPERTY_RW_V(bool, reuseSingleConnection)
        VBox_PROPERTY_RW_R(std::u16string, VRDEExtPack)
        VBox_PROPERTY_RW_R(std::u16string, authLibrary)
        VBox_PROPERTY_RO(std::vector<std::u16string>, VRDEProperties)

        // Methods
        void setVRDEProperty(
                /* in */ const std::u16string &key,
                /* in */ const std::u16string &value);
        std::u16string getVRDEProperty(
                /* in */ const std::u16string &key) const;
    };

    class LIBVBOX_API ISharedFolder : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ISharedFolder)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, hostPath)
        VBox_PROPERTY_RO(bool, accessible)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBox_PROPERTY_RW_V(bool, writable)
        VBox_PROPERTY_RW_V(bool, autoMount)
        VBox_PROPERTY_RW_R(std::u16string, autoMountPoint)
#else
        VBox_PROPERTY_RO(bool, writable)
        VBox_PROPERTY_RO(bool, autoMount)
#endif
        VBox_PROPERTY_RO(std::u16string, lastAccessError)
    };

    class LIBVBOX_API IInternalSessionControl : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IInternalSessionControl)

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
        void onStorageControllerChange(
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
                /* in */ const std::u16string &machineId,
                /* in */ const std::u16string &controllerName
#endif
                );
        void onMediumChange(
                /* in */ const COMPtr<IMediumAttachment> &mediumAttachment,
                /* in */ bool force);
        void onStorageDeviceChange(
                /* in */ const COMPtr<IMediumAttachment> &mediumAttachment,
                /* in */ bool remove,
                /* in */ bool silent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        void onVMProcessPriorityChange(
                /* in */ VMProcPriority priority);
#endif
        void onClipboardModeChange(
                /* in */ ClipboardMode clipboardMode);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        void onClipboardFileTransferModeChange(
                /* in */ bool enabled);
#endif
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
                /* in */ const std::u16string &captureFilename);
        void onUSBDeviceDetach(
                /* in */ const std::u16string &id,
                /* in */ const COMPtr<IVirtualBoxErrorInfo> &error);
        void onShowWindow(
                /* in  */ bool check,
                /* out */ bool *canShow,
                /* out */ int64_t *winId);
        void onBandwidthGroupChange(
                /* in */ const COMPtr<IBandwidthGroup> &bandwidthGroup);
        void accessGuestProperty(
                /* in  */ const std::u16string &name,
                /* in  */ const std::u16string &value,
                /* in  */ const std::u16string &flags,
                /* in  */ uint32_t accessMode,
                /* out */ std::u16string *retValue,
                /* out */ int64_t *retTimestamp,
                /* out */ std::u16string *retFlags);
        void enumerateGuestProperties(
                /* in  */ const std::u16string &patterns,
                /* out */ std::vector<std::u16string> *keys,
                /* out */ std::vector<std::u16string> *values,
                /* out */ std::vector<int64_t> *timestamps,
                /* out */ std::vector<std::u16string> *flags) const;
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
                /* in */ const std::u16string &stateFilePath,
                /* in */ bool pauseVM);
        void cancelSaveStateWithReason();
    };

    class LIBVBOX_API ISession : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ISession)

        // Attributes
        VBox_PROPERTY_RO(SessionState, state)
        VBox_PROPERTY_RO(SessionType, type)
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RO(COMPtr<IMachine>, machine)
        VBox_PROPERTY_RO(COMPtr<IConsole>, console)

        // Methods
        void unlockMachine();
    };

    class LIBVBOX_API IStorageController : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IStorageController)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, name)
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
        VBox_COM_WRAPPED(::IPerformanceMetric)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, metricName)
        VBox_PROPERTY_RO(COMPtr<COMUnknown>, object)
        VBox_PROPERTY_RO(std::u16string, description)
        VBox_PROPERTY_RO(uint32_t, period)
        VBox_PROPERTY_RO(uint32_t, count)
        VBox_PROPERTY_RO(std::u16string, unit)
        VBox_PROPERTY_RO(int32_t, minimumValue)
        VBox_PROPERTY_RO(int32_t, maximumValue)
    };

    class LIBVBOX_API IPerformanceCollector : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IPerformanceCollector)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::u16string>, metricNames)

        // Methods
        std::vector<COMPtr<IPerformanceMetric>> getMetrics(
                /* in */ const std::vector<std::u16string> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects);
        std::vector<COMPtr<IPerformanceMetric>> setupMetrics(
                /* in */ const std::vector<std::u16string> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects,
                /* in */ uint32_t period,
                /* in */ uint32_t count);
        std::vector<COMPtr<IPerformanceMetric>> enableMetrics(
                /* in */ const std::vector<std::u16string> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects);
        std::vector<COMPtr<IPerformanceMetric>> disableMetrics(
                /* in */ const std::vector<std::u16string> &metricNames,
                /* in */ const std::vector<COMPtr<COMUnknown>> &objects);
        std::vector<int32_t> queryMetricsData(
                /* in  */ const std::vector<std::u16string> &metricNames,
                /* in  */ const std::vector<COMPtr<COMUnknown>> &objects,
                /* out */ std::vector<std::u16string> *returnMetricNames,
                /* out */ std::vector<COMPtr<COMUnknown>> *returnObjects,
                /* out */ std::vector<std::u16string> *returnUnits,
                /* out */ std::vector<uint32_t> *returnScales,
                /* out */ std::vector<uint32_t> *returnSequenceNumbers,
                /* out */ std::vector<uint32_t> *returnDataIndices,
                /* out */ std::vector<uint32_t> *returnDataLengths);
    };

    class LIBVBOX_API INATEngine : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::INATEngine)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, network)
        VBox_PROPERTY_RW_R(std::u16string, hostIP)
        VBox_PROPERTY_RW_R(std::u16string, TFTPPrefix)
        VBox_PROPERTY_RW_R(std::u16string, TFTPBootFile)
        VBox_PROPERTY_RW_R(std::u16string, TFTPNextServer)
        VBox_PROPERTY_RW_V(uint32_t, aliasMode)
        VBox_PROPERTY_RW_V(bool, DNSPassDomain)
        VBox_PROPERTY_RW_V(bool, DNSProxy)
        VBox_PROPERTY_RW_V(bool, DNSUseHostResolver)
        VBox_PROPERTY_RO(std::vector<std::u16string>, redirects)

        // Methods
        void setNetworkSettings(
                /* in */ uint32_t mtu,
                /* in */ uint32_t sockSnd,
                /* in */ uint32_t sockRcv,
                /* in */ uint32_t TcpWndSnd,
                /* in */ uint32_t TcpWndRcv);
        void getNetworkSettings(
                /* out */ uint32_t *mtu,
                /* out */ uint32_t *sockSnd,
                /* out */ uint32_t *sockRcv,
                /* out */ uint32_t *TcpWndSnd,
                /* out */ uint32_t *TcpWndRcv);
        void addRedirect(
                /* in */ const std::u16string &name,
                /* in */ NATProtocol proto,
                /* in */ const std::u16string &hostIP,
                /* in */ uint16_t hostPort,
                /* in */ const std::u16string &guestIP,
                /* in */ uint16_t guestPort);
        void removeRedirect(
                /* in */ const std::u16string &name);
    };

    class LIBVBOX_API IExtPackPlugIn : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IExtPackPlugIn)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, description)
        VBox_PROPERTY_RO(std::u16string, frontend)
        VBox_PROPERTY_RO(std::u16string, modulePath)
    };

    class LIBVBOX_API IExtPackBase : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IExtPackBase)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, description)
        VBox_PROPERTY_RO(std::u16string, version)
        VBox_PROPERTY_RO(uint32_t, revision)
        VBox_PROPERTY_RO(std::u16string, edition)
        VBox_PROPERTY_RO(std::u16string, VRDEModule)
        VBox_PROPERTY_RO(std::vector<COMPtr<IExtPackPlugIn>>, plugIns)
        VBox_PROPERTY_RO(bool, usable)
        VBox_PROPERTY_RO(std::u16string, whyUnusable)
        VBox_PROPERTY_RO(bool, showLicense)
        VBox_PROPERTY_RO(std::u16string, license)

        // Methods
        std::u16string queryLicense(
                /* in */ const std::u16string &preferredLocale,
                /* in */ const std::u16string &preferredLanguage,
                /* in */ const std::u16string &format);
    };

    class LIBVBOX_API IExtPack : public IExtPackBase
    {
    public:
        VBox_COM_WRAPPED(::IExtPack)

        // Methods
        COMPtr<COMUnknown> queryObject(
                /* in */ const std::u16string &objUuid);
    };

    class LIBVBOX_API IExtPackFile : public IExtPackBase
    {
    public:
        VBox_COM_WRAPPED(::IExtPackFile)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, filePath)

        // Methods
        COMPtr<IProgress> install(
                /* in */ bool replace,
                /* in */ const std::u16string &displayInfo);
    };

    class LIBVBOX_API IExtPackManager : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IExtPackManager)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IExtPack>>, installedExtPacks)

        // Methods
        COMPtr<IExtPack> find(
                /* in */ const std::u16string &name);
        COMPtr<IExtPackFile> openExtPackFile(
                /* in */ const std::u16string &path);
        COMPtr<IProgress> uninstall(
                /* in */ const std::u16string &name,
                /* in */ bool forcedRemoval,
                /* in */ const std::u16string &displayInfo);
        void cleanup();
        std::vector<std::u16string> queryAllPlugInsForFrontend(
                /* in */ const std::u16string &frontendName);
        bool isExtPackUsable(
                /* in */ const std::u16string &name);
    };

    class LIBVBOX_API IBandwidthGroup : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IBandwidthGroup)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(BandwidthGroupType, type)
        VBox_PROPERTY_RO(uint32_t, reference)
        VBox_PROPERTY_RW_V(int64_t, maxBytesPerSec)
    };

    class LIBVBOX_API IBandwidthControl : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IBandwidthControl)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, numGroups)

        // Methods
        void createBandwidthGroup(
                /* in */ const std::u16string &name,
                /* in */ BandwidthGroupType type,
                /* in */ int64_t maxBytesPerSec);
        void deleteBandwidthGroup(
                /* in */ const std::u16string &name);
        COMPtr<IBandwidthGroup> getBandwidthGroup(
                /* in */ const std::u16string &name) const;
        std::vector<COMPtr<IBandwidthGroup>> getAllBandwidthGroups() const;
    };

    class LIBVBOX_API IVirtualBoxClient : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IVirtualBoxClient)

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
        VBox_COM_WRAPPED(::IEventSource)

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
        VBox_COM_WRAPPED(::IEventListener)

        // Methods
        void handleEvent(
                /* in */ const COMPtr<IEvent> &event);
    };

    class LIBVBOX_API IEvent : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IEvent)

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
        VBox_COM_WRAPPED(::IReusableEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, generation)

        // Methods
        void reuse();
    };

    class LIBVBOX_API IMachineEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IMachineEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, machineId)
    };

    class LIBVBOX_API IMachineStateChangedEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::IMachineStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(MachineState, state)
    };

    class LIBVBOX_API IMachineDataChangedEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::IMachineDataChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, temporary)
    };

    class LIBVBOX_API IMediumRegisteredEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IMediumRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, mediumId)
        VBox_PROPERTY_RO(DeviceType, mediumType)
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IMediumConfigChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IMediumConfigChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMedium>, medium)
    };

    class LIBVBOX_API IMachineRegisteredEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::IMachineRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API ISessionStateChangedEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::ISessionStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(SessionState, state)
    };

    class LIBVBOX_API IGuestPropertyChangedEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestPropertyChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, value)
        VBox_PROPERTY_RO(std::u16string, flags)
    };

    class LIBVBOX_API ISnapshotEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::ISnapshotEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, snapshotId)
    };

    class LIBVBOX_API ISnapshotTakenEvent : public ISnapshotEvent
    {
    public:
        VBox_COM_WRAPPED(::ISnapshotTakenEvent)
    };

    class LIBVBOX_API ISnapshotDeletedEvent : public ISnapshotEvent
    {
    public:
        VBox_COM_WRAPPED(::ISnapshotDeletedEvent)
    };

    class LIBVBOX_API ISnapshotRestoredEvent : public ISnapshotEvent
    {
    public:
        VBox_COM_WRAPPED(::ISnapshotRestoredEvent)
    };

    class LIBVBOX_API ISnapshotChangedEvent : public ISnapshotEvent
    {
    public:
        VBox_COM_WRAPPED(::ISnapshotChangedEvent)
    };

    class LIBVBOX_API IMousePointerShapeChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IMousePointerShapeChangedEvent)

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
        VBox_COM_WRAPPED(::IMouseCapabilityChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, supportsAbsolute)
        VBox_PROPERTY_RO(bool, supportsRelative)
        VBox_PROPERTY_RO(bool, supportsMultiTouch)
        VBox_PROPERTY_RO(bool, needsHostCursor)
    };

    class LIBVBOX_API IKeyboardLedsChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IKeyboardLedsChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, numLock)
        VBox_PROPERTY_RO(bool, capsLock)
        VBox_PROPERTY_RO(bool, scrollLock)
    };

    class LIBVBOX_API IStateChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(MachineState, state)
    };

    class LIBVBOX_API IAdditionsStateChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IAdditionsStateChangedEvent)
    };

    class LIBVBOX_API INetworkAdapterChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::INetworkAdapterChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<INetworkAdapter>, networkAdapter)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IAudioAdapterChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IAudioAdapterChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IAudioAdapter>, audioAdapter)
    };
#endif

    class LIBVBOX_API ISerialPortChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::ISerialPortChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<ISerialPort>, serialPort)
    };

    class LIBVBOX_API IParallelPortChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IParallelPortChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IParallelPort>, parallelPort)
    };

    class LIBVBOX_API IStorageControllerChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IStorageControllerChangedEvent)

        // Attributes
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RO(std::u16string, machinId)
        VBox_PROPERTY_RO(std::u16string, controllerName)
#endif
    };

    class LIBVBOX_API IMediumChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IMediumChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMediumAttachment>, mediumAttachment)
    };

    class LIBVBOX_API IClipboardModeChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IClipboardModeChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(ClipboardMode, clipboardMode)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IClipboardFileTransferModeChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IClipboardFileTransferModeChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, enabled)
    };
#endif

    class LIBVBOX_API IDnDModeChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IDnDModeChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(DnDMode, dndMode)
    };

    class LIBVBOX_API ICPUChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::ICPUChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, CPU)
        VBox_PROPERTY_RO(bool, add)
    };

    class LIBVBOX_API ICPUExecutionCapChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::ICPUExecutionCapChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, executionCap)
    };

    class LIBVBOX_API IGuestKeyboardEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestKeyboardEvent)

        // Attributes
        VBox_PROPERTY_RO(std::vector<int32_t>, scancodes)
    };

    class LIBVBOX_API IGuestMouseEvent : public IReusableEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestMouseEvent)

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
        VBox_COM_WRAPPED(::IGuestMultiTouchEvent)

        // Attributes
        VBox_PROPERTY_RO(int32_t, contactCount)
        VBox_PROPERTY_RO(std::vector<int16_t>, xPositions)
        VBox_PROPERTY_RO(std::vector<int16_t>, yPositions)
        VBox_PROPERTY_RO(std::vector<uint16_t>, contactIds)
        VBox_PROPERTY_RO(std::vector<uint16_t>, contactFlags)
        VBox_PROPERTY_RO(uint32_t, scanTime)
    };

    class LIBVBOX_API IGuestSessionEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestSessionEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IGuestSession>, session)
    };

    class LIBVBOX_API IGuestSessionStateChangedEvent : public IGuestSessionEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestSessionStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, id)
        VBox_PROPERTY_RO(GuestSessionStatus, status)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API IGuestSessionRegisteredEvent : public IGuestSessionEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestSessionRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IGuestProcessEvent : public IGuestSessionEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestProcessEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IGuestProcess>, process)
        VBox_PROPERTY_RO(uint32_t, pid)
    };

    class LIBVBOX_API IGuestProcessRegisteredEvent : public IGuestProcessEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestProcessRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IGuestProcessStateChangedEvent : public IGuestProcessEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestProcessStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(ProcessStatus, status)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API IGuestProcessIOEvent : public IGuestProcessEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestProcessIOEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, handle)
        VBox_PROPERTY_RO(uint32_t, processed)
    };

    class LIBVBOX_API IGuestProcessInputNotifyEvent : public IGuestProcessIOEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestProcessInputNotifyEvent)

        // Attributes
        VBox_PROPERTY_RO(ProcessInputStatus, status)
    };

    class LIBVBOX_API IGuestProcessOutputEvent : public IGuestProcessIOEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestProcessOutputEvent)

        // Attributes
        VBox_PROPERTY_RO(std::vector<uint8_t>, data)
    };

    class LIBVBOX_API IGuestFileEvent : public IGuestSessionEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IGuestFile>, file)
    };

    class LIBVBOX_API IGuestFileRegisteredEvent : public IGuestFileEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileRegisteredEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, registered)
    };

    class LIBVBOX_API IGuestFileStateChangedEvent : public IGuestFileEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(FileStatus, status)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API IGuestFileIOEvent : public IGuestFileEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileIOEvent)

        // Attributes
        VBox_PROPERTY_RO(int64_t, offset)
        VBox_PROPERTY_RO(uint32_t, processed)
    };

    class LIBVBOX_API IGuestFileOffsetChangedEvent : public IGuestFileIOEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileOffsetChangedEvent)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 32) )
    class LIBVBOX_API IGuestFileSizeChangedEvent : public IGuestFileEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileSizeChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(int64_t, newSize);
    };
#endif

    class LIBVBOX_API IGuestFileReadEvent : public IGuestFileIOEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileReadEvent)

        // Attributes
        VBox_PROPERTY_RO(std::vector<uint8_t>, data)
    };

    class LIBVBOX_API IGuestFileWriteEvent : public IGuestFileIOEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestFileWriteEvent)
    };

    class LIBVBOX_API IVRDEServerChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IVRDEServerChangedEvent)
    };

    class LIBVBOX_API IVRDEServerInfoChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IVRDEServerInfoChangedEvent)
    };

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IVideoCaptureChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IVideoCaptureChangedEvent)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API IRecordingChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IRecordingChangedEvent)
    };
#endif

    class LIBVBOX_API IUSBControllerChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IUSBControllerChangedEvent)
    };

    class LIBVBOX_API IUSBDeviceStateChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IUSBDeviceStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IUSBDevice>, device)
        VBox_PROPERTY_RO(bool, attached)
        VBox_PROPERTY_RO(COMPtr<IVirtualBoxErrorInfo>, error)
    };

    class LIBVBOX_API ISharedFolderChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::ISharedFolderChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(Scope, scope)
    };

    class LIBVBOX_API IRuntimeErrorEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IRuntimeErrorEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, fatal)
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(std::u16string, message)
    };

    class LIBVBOX_API IEventSourceChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IEventSourceChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IEventListener>, listener)
        VBox_PROPERTY_RO(bool, add)
    };

    class LIBVBOX_API IExtraDataChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IExtraDataChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, machineId)
        VBox_PROPERTY_RO(std::u16string, key)
        VBox_PROPERTY_RO(std::u16string, value)
    };

    class LIBVBOX_API IVetoEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IVetoEvent)

        // Methods
        void addVeto(
                /* in */ const std::u16string &reason);
        bool isVetoed();
        std::vector<std::u16string> getVetos();
        void addApproval(
                /* in */ const std::u16string &reason);
        bool isApproved();
        std::vector<std::u16string> getApprovals();
    };

    class LIBVBOX_API IExtraDataCanChangeEvent : public IVetoEvent
    {
    public:
        VBox_COM_WRAPPED(::IExtraDataCanChangeEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, machineId)
        VBox_PROPERTY_RO(std::u16string, key)
        VBox_PROPERTY_RO(std::u16string, value)
    };

    class LIBVBOX_API ICanShowWindowEvent : public IVetoEvent
    {
    public:
        VBox_COM_WRAPPED(::ICanShowWindowEvent)
    };

    class LIBVBOX_API IShowWindowEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IShowWindowEvent)

        // Attributes
        VBox_PROPERTY_RW_V(int64_t, winId)
    };

    class LIBVBOX_API INATRedirectEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::INATRedirectEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, slot)
        VBox_PROPERTY_RO(bool, remove)
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(NATProtocol, proto)
        VBox_PROPERTY_RO(std::u16string, hostIP)
        VBox_PROPERTY_RO(int32_t, hostPort)
        VBox_PROPERTY_RO(std::u16string, guestIP)
        VBox_PROPERTY_RO(int32_t, guestPort)
    };

    class LIBVBOX_API IHostPCIDevicePlugEvent : public IMachineEvent
    {
    public:
        VBox_COM_WRAPPED(::IHostPCIDevicePlugEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, plugged)
        VBox_PROPERTY_RO(bool, success)
        VBox_PROPERTY_RO(COMPtr<IPCIDeviceAttachment>, attachment)
        VBox_PROPERTY_RO(std::u16string, message)
    };

    class LIBVBOX_API IVBoxSVCAvailabilityChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IVBoxSVCAvailabilityChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, available)
    };

    class LIBVBOX_API IBandwidthGroupChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IBandwidthGroupChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IBandwidthGroup>, bandwidthGroup)
    };

    class LIBVBOX_API IGuestMonitorChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestMonitorChangedEvent)

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
        VBox_COM_WRAPPED(::IGuestUserStateChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, domain)
        VBox_PROPERTY_RO(GuestUserState, state)
        VBox_PROPERTY_RO(std::u16string, stateDetails)
    };

    class LIBVBOX_API IStorageDeviceChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IStorageDeviceChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(COMPtr<IMediumAttachment>, storageDevice)
        VBox_PROPERTY_RO(bool, removed)
        VBox_PROPERTY_RO(bool, silent)
    };

    class LIBVBOX_API INATNetworkChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::INATNetworkChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, networkName)
    };

    class LIBVBOX_API INATNetworkStartStopEvent : public INATNetworkChangedEvent
    {
    public:
        VBox_COM_WRAPPED(::INATNetworkStartStopEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, startEvent)
    };

    class LIBVBOX_API INATNetworkAlterEvent : public INATNetworkChangedEvent
    {
    public:
        VBox_COM_WRAPPED(::INATNetworkAlterEvent)
    };

    class LIBVBOX_API INATNetworkCreationDeletionEvent : public INATNetworkAlterEvent
    {
    public:
        VBox_COM_WRAPPED(::INATNetworkCreationDeletionEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, creationEvent)
    };

    class LIBVBOX_API INATNetworkSettingEvent : public INATNetworkAlterEvent
    {
    public:
        VBox_COM_WRAPPED(::INATNetworkSettingEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, enabled)
        VBox_PROPERTY_RO(std::u16string, network)
        VBox_PROPERTY_RO(std::u16string, gateway)
        VBox_PROPERTY_RO(bool, advertiseDefaultIPv6RouteEnabled)
        VBox_PROPERTY_RO(bool, needDhcpServer)
    };

    class LIBVBOX_API INATNetworkPortForwardEvent : public INATNetworkAlterEvent
    {
    public:
        VBox_COM_WRAPPED(::INATNetworkPortForwardEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, create)
        VBox_PROPERTY_RO(bool, ipv6)
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(NATProtocol, proto)
        VBox_PROPERTY_RO(std::u16string, hostIp)
        VBox_PROPERTY_RO(int32_t, hostPort)
        VBox_PROPERTY_RO(std::u16string, guestIp)
        VBox_PROPERTY_RO(int32_t, guestPort)
    };

    class LIBVBOX_API IHostNameResolutionConfigurationChangeEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IHostNameResolutionConfigurationChangeEvent)
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
    class LIBVBOX_API IProgressEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IProgressEvent)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, progressId)
    };

    class LIBVBOX_API IProgressPercentageChangedEvent : public IProgressEvent
    {
    public:
        VBox_COM_WRAPPED(::IProgressPercentageChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(int32_t, percent)
    };

    class LIBVBOX_API IProgressTaskCompletedEvent : public IProgressEvent
    {
    public:
        VBox_COM_WRAPPED(::IProgressTaskCompletedEvent)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API ICursorPositionChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::ICursorPositionChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(bool, hasData)
        VBox_PROPERTY_RO(uint32_t, x)
        VBox_PROPERTY_RO(uint32_t, y)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 32) )
    class LIBVBOX_API IGuestAdditionsStatusChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestAdditionsStatusChangedEvent)

        // Attributes
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        VBox_PROPERTY_RW_V(AdditionsFacilityType, facility);
#else
        VBox_PROPERTY_RO(AdditionsFacilityType, facility);
#endif
        VBox_PROPERTY_RO(AdditionsFacilityStatus, status);
        VBox_PROPERTY_RO(AdditionsRunLevelType, runLevel);
        VBox_PROPERTY_RO(int64_t, timestamp);
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IGuestMonitorInfoChangedEvent : public IEvent
    {
    public:
        VBox_COM_WRAPPED(::IGuestMonitorInfoChangedEvent)

        // Attributes
        VBox_PROPERTY_RO(uint32_t, output)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IStringArray : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IStringArray)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::u16string>, values)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    class LIBVBOX_API IFormValue : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IFormValue)

        // Attributes
        VBox_PROPERTY_RO(FormValueType, type)
        VBox_PROPERTY_RO(int32_t, generation)
        VBox_PROPERTY_RO(bool, enabled)
        VBox_PROPERTY_RO(bool, visible)
        VBox_PROPERTY_RO(std::u16string, label)
        VBox_PROPERTY_RO(std::u16string, description)
        VBox_PROPERTY_RO(std::u16string, help)
    };

    class LIBVBOX_API IBooleanFormValue : public IFormValue
    {
    public:
        VBox_COM_WRAPPED(::IBooleanFormValue)

        // Methods
        bool getSelected();
        COMPtr<IProgress> setSelected(
                /* in */ bool selected);
    };

    class LIBVBOX_API IRangedIntegerFormValue : public IFormValue
    {
    public:
        VBox_COM_WRAPPED(::IRangedIntegerFormValue)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, suffix)
        VBox_PROPERTY_RO(int32_t, minimum)
        VBox_PROPERTY_RO(int32_t, maximum)

        // Methods
        int32_t getInteger();
        COMPtr<IProgress> setInteger(
                /* in */ int32_t value);
    };

    class LIBVBOX_API IStringFormValue : public IFormValue
    {
    public:
        VBox_COM_WRAPPED(::IStringFormValue)

        // Attributes
        VBox_PROPERTY_RO(bool, multiline)

        // Methods
        std::u16string getString();
        COMPtr<IProgress> setString(
                /* in */ const std::u16string &text);
    };

    class LIBVBOX_API IChoiceFormValue : public IFormValue
    {
    public:
        VBox_COM_WRAPPED(::IChoiceFormValue)

        // Attributes
        VBox_PROPERTY_RO(std::vector<std::u16string>, values)

        // Methods
        int32_t getSelectedIndex();
        COMPtr<IProgress> setSelectedIndex(
                /* in */ int32_t index);
    };

    class LIBVBOX_API IForm : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::IForm)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<IFormValue>>, values)
    };

    class LIBVBOX_API IVirtualSystemDescriptionForm : public IForm
    {
    public:
        VBox_COM_WRAPPED(::IVirtualSystemDescriptionForm)

        // Methods
        COMPtr<IVirtualSystemDescription> getVirtualSystemDescription();
    };

    class LIBVBOX_API ICloudNetworkGatewayInfo : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudNetworkGatewayInfo)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, publicIP)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 12)
        VBox_PROPERTY_RO(std::u16string, secondaryPublicIP)
        VBox_PROPERTY_RO(std::u16string, macAddress)
        VBox_PROPERTY_RO(std::u16string, instanceId)
#endif
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 12)
    class LIBVBOX_API ICloudNetworkEnvironmentInfo : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudNetworkEnvironmentInfo)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, tunnelNetworkId)
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    class LIBVBOX_API ICloudClient : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudClient)

        // Methods
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        std::u16string getExportLaunchParameters() const;
        void exportLaunchVM(
                /* in */ const COMPtr<IVirtualSystemDescription> &description,
                /* in */ const COMPtr<IProgress> &progress,
                /* in */ const COMPtr<IVirtualBox> &virtualBox);
#else
        COMPtr<IProgress> getExportDescriptionForm(
                /* in  */ const COMPtr<IVirtualSystemDescription> &description,
                /* out */ COMPtr<IVirtualSystemDescriptionForm> *form);
        void exportVM(
                /* in */ const COMPtr<IVirtualSystemDescription> &description,
                /* in */ const COMPtr<IProgress> &progress);
        COMPtr<IProgress> getLaunchDescriptionForm(
                /* in  */ const COMPtr<IVirtualSystemDescription> &description,
                /* out */ COMPtr<IVirtualSystemDescriptionForm> *form);
        COMPtr<IProgress> launchVM(
                /* in */ const COMPtr<IVirtualSystemDescription> &description);
        COMPtr<IProgress> getImportDescriptionForm(
                /* in  */ const COMPtr<IVirtualSystemDescription> &description,
                /* out */ COMPtr<IVirtualSystemDescriptionForm> *form);
        void importInstance(
                /* in */ const COMPtr<IVirtualSystemDescription> &description,
                /* in */ const COMPtr<IProgress> &progress);
        COMPtr<IProgress> listInstances(
                /* in  */ const std::vector<CloudMachineState> &machineState,
                /* out */ COMPtr<IStringArray> *returnNames,
                /* out */ COMPtr<IStringArray> *returnIds);
        COMPtr<IProgress> listImages(
                /* in  */ const std::vector<CloudImageState> &imageState,
                /* out */ COMPtr<IStringArray> *returnNames,
                /* out */ COMPtr<IStringArray> *returnIds);
        COMPtr<IProgress> getInstanceInfo(
                /* in */ const std::u16string &uid,
                /* in */ const COMPtr<IVirtualSystemDescription> &description);
        COMPtr<IProgress> startInstance(
                /* in */ const std::u16string &uid);
        COMPtr<IProgress> pauseInstance(
                /* in */ const std::u16string &uid);
        COMPtr<IProgress> terminateInstance(
                /* in */ const std::u16string &uid);
        COMPtr<IProgress> createImage(
                /* in */ std::vector<std::u16string> &parameters);
        COMPtr<IProgress> exportImage(
                /* in */ const COMPtr<IMedium> &image,
                /* in */ const std::vector<std::u16string> &parameters);
        COMPtr<IProgress> importImage(
                /* in */ const std::u16string &uid,
                /* in */ const std::vector<std::u16string> &parameters);
        COMPtr<IProgress> deleteImage(
                /* in */ const std::u16string &uid);
        COMPtr<IProgress> getImageInfo(
                /* in  */ const std::u16string &uid,
                /* out */ COMPtr<IStringArray> *infoArray);
        COMPtr<IProgress> startCloudNetworkGateway(
                /* in  */ const COMPtr<ICloudNetwork> &network,
                /* in  */ const std::u16string &sshPublicKey,
                /* out */ COMPtr<ICloudNetworkGatewayInfo> *gatewayInfo);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 12)
        COMPtr<IProgress> setupCloudNetworkEnvironment(
                /* in  */ const std::u16string& tunnelNetworkName,
                /* in  */ const std::u16string& tunnelNetworkRange,
                /* in  */ const std::u16string& gatewayOsName,
                /* in  */ const std::u16string& gatewayOsVersion,
                /* in  */ const std::u16string& gatewayShape,
                /* out */ COMPtr<ICloudNetworkEnvironmentInfo> *networkEnvironmentInfo);
#endif
    };

    class LIBVBOX_API ICloudProfile : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudProfile)

        // Attributes
        VBox_PROPERTY_RW_R(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, providerId)

        // Methods
        std::u16string getProperty(
                /* in */ const std::u16string &name) const;
        void setProperty(
                /* in */ const std::u16string &name,
                /* in */ const std::u16string &value) const;
        std::vector<std::u16string> getProperties(
                /* in  */ const std::u16string &names,
                /* out */ std::vector<std::u16string> *returnNames) const;
        void setProperties(
                /* in */ const std::vector<std::u16string> &names,
                /* in */ const std::vector<std::u16string> &values);
        void remove();
        COMPtr<ICloudClient> createCloudClient();
    };

    class LIBVBOX_API ICloudProvider : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudProvider)

        // Attributes
        VBox_PROPERTY_RO(std::u16string, name)
        VBox_PROPERTY_RO(std::u16string, shortName)
        VBox_PROPERTY_RO(std::u16string, id)
        VBox_PROPERTY_RO(std::vector<COMPtr<ICloudProfile>>, profiles)
        VBox_PROPERTY_RO(std::vector<std::u16string>, profileNames)
        VBox_PROPERTY_RO(std::vector<std::u16string>, supportedPropertyNames)

        // Methods
        std::u16string getPropertyDescription(
                /* in */ const std::u16string &name) const;
        void createProfile(
                /* in */ const std::u16string &profileName,
                /* in */ const std::vector<std::u16string> &names,
                /* in */ const std::vector<std::u16string> &values);
        void importProfiles();
        void restoreProfiles();
        void saveProfiles();
        COMPtr<ICloudProfile> getProfileByName(
                /* in */ const std::u16string &profileName);
        void prepareUninstall();
    };

    class LIBVBOX_API ICloudProviderManager : public COMUnknown
    {
    public:
        VBox_COM_WRAPPED(::ICloudProviderManager)

        // Attributes
        VBox_PROPERTY_RO(std::vector<COMPtr<ICloudProvider>>, providers)

        // Methods
        COMPtr<ICloudProvider> getProviderById(
                /* in */ const std::u16string &providerId);
        COMPtr<ICloudProvider> getProviderByShortName(
                /* in */ const std::u16string &providerName);
        COMPtr<ICloudProvider> getProviderByName(
                /* in */ const std::u16string &providerName);
    };
#endif
}

#endif /* _LIBVBOX_INTERFACES_H */
