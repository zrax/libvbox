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

#ifndef _LIBVBOX_VBOXSDK_TYPES_H
#define _LIBVBOX_VBOXSDK_TYPES_H

#include <type_traits>

#include "libvbox_vboxsdk_version.h"

// Some of the below enums need bitwise operators to behave properly
#define VBox_ENUM_BITWISE(Enum)                                         \
    inline Enum operator&(Enum lhs, Enum rhs)                           \
    {                                                                   \
        return static_cast<Enum>(                                       \
                     static_cast<std::underlying_type<Enum>::type>(lhs) \
                   & static_cast<std::underlying_type<Enum>::type>(rhs) \
               );                                                       \
    }                                                                   \
    inline Enum operator|(Enum lhs, Enum rhs)                           \
    {                                                                   \
        return static_cast<Enum>(                                       \
                     static_cast<std::underlying_type<Enum>::type>(lhs) \
                   | static_cast<std::underlying_type<Enum>::type>(rhs) \
               );                                                       \
    }                                                                   \
    inline Enum operator^(Enum lhs, Enum rhs)                           \
    {                                                                   \
        return static_cast<Enum>(                                       \
                     static_cast<std::underlying_type<Enum>::type>(lhs) \
                   ^ static_cast<std::underlying_type<Enum>::type>(rhs) \
               );                                                       \
    }                                                                   \
    inline Enum operator~(Enum rhs)                                     \
    {                                                                   \
        return static_cast<Enum>(                                       \
                   ~static_cast<std::underlying_type<Enum>::type>(rhs)  \
               );                                                       \
    }                                                                   \
    inline Enum operator&=(Enum lhs, Enum rhs)                          \
    {                                                                   \
        lhs = static_cast<Enum>(                                        \
                     static_cast<std::underlying_type<Enum>::type>(lhs) \
                   & static_cast<std::underlying_type<Enum>::type>(rhs) \
               );                                                       \
        return lhs;                                                     \
    }                                                                   \
    inline Enum operator|=(Enum lhs, Enum rhs)                          \
    {                                                                   \
        lhs = static_cast<Enum>(                                        \
                     static_cast<std::underlying_type<Enum>::type>(lhs) \
                   | static_cast<std::underlying_type<Enum>::type>(rhs) \
               );                                                       \
        return lhs;                                                     \
    }                                                                   \
    inline Enum operator^=(Enum lhs, Enum rhs)                          \
    {                                                                   \
        lhs = static_cast<Enum>(                                        \
                     static_cast<std::underlying_type<Enum>::type>(lhs) \
                   ^ static_cast<std::underlying_type<Enum>::type>(rhs) \
               );                                                       \
        return lhs;                                                     \
    }

// Reimplemented enum types to avoid pulling in COM headers
namespace VBox
{
    enum class AccessMode
    {
        ReadOnly = 1,
        ReadWrite = 2,
    };

    enum class AdditionsFacilityClass
    {
        None = 0,
        Driver = 10,
        Service = 30,
        Program = 50,
        Feature = 100,
        ThirdParty = 999,
        All = 2147483646,
    };

    enum class AdditionsFacilityStatus
    {
        Inactive = 0,
        Paused = 1,
        PreInit = 20,
        Init = 30,
        Active = 50,
        Terminating = 100,
        Terminated = 101,
        Failed = 800,
        Unknown = 999,
    };

    enum class AdditionsFacilityType
    {
        None = 0,
        VBoxGuestDriver = 20,
        AutoLogon = 90,
        VBoxService = 100,
        VBoxTrayClient = 101,
        Seamless = 1000,
        Graphics = 1100,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        MonitorAttach = 1101,
#endif
        All = 2147483646,
    };

    enum class AdditionsRunLevelType
    {
        None = 0,
        System = 1,
        Userland = 2,
        Desktop = 3,
    };

    enum class AdditionsUpdateFlag
    {
        None = 0,
        WaitForUpdateStartOnly = 1,
    };
    VBox_ENUM_BITWISE(AdditionsUpdateFlag)

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    enum class APICMode
    {
        Disabled = 0,
        APIC = 1,
        X2APIC = 2,
    };
#endif

    enum class AudioCodecType
    {
        Null = 0,
        SB16 = 1,
        STAC9700 = 2,
        AD1980 = 3,
        STAC9221 = 4,
    };

    enum class AudioControllerType
    {
        AC97 = 0,
        SB16 = 1,
        HDA = 2,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        VirtioSound = 3,
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class AudioDeviceState
    {
        Unknown = 0,
        Active = 1,
        Disabled = 2,
        NotPresent = 3,
        Unplugged = 4,
    };

    enum class AudioDeviceType
    {
        Unknown = 0,
        BuiltLin = 1,
        ExternalUSB = 2,
        ExternalOther = 3,
    };

    enum class AudioDirection
    {
        Unknown = 0,
        In = 1,
        Out = 2,
        Duplex = 3,
    };
#endif

    enum class AudioDriverType
    {
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        Default,
#endif
        Null,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
        WinMM,
#endif
        OSS,
        ALSA,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        Pulse,
        WinMM,
#endif
        DirectSound,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        WAS,
#endif
        CoreAudio,
        MMPM,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
        Pulse,
#endif
        SolAudio,
    };

    enum class AuthType
    {
        Null = 0,
        External = 1,
        Guest = 2,
    };

    enum class AutostopType
    {
        Disabled = 1,
        SaveState = 2,
        PowerOff = 3,
        AcpiShutdown = 4,
    };

    enum class BandwidthGroupType
    {
        Null = 0,
        Disk = 1,
        Network = 2,
    };

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
    enum class BIOSBootMenuMode
#else
    enum class FirmwareBootMenuMode
#endif
    {
        Disabled = 0,
        MenuOnly = 1,
        MessageAndMenu = 2,
    };

    enum class BitmapFormat
    {
        Opaque = 0,
        BGR = 0x20524742,
        BGR0 = 0x30524742,
        BGRA = 0x41524742,
        RGBA = 0x41424752,
        PNG = 0x20474e50,
        JPEG = 0x4745504a,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    enum class CertificateVersion
    {
        V1 = 1,
        V2 = 2,
        V3 = 3,
        Unknown = 99,
    };
#endif

    enum class ChipsetType
    {
        Null = 0,
        PIIX3 = 1,
        ICH9 = 2,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        ARMv8Virtual = 3,
#endif
    };

    enum class CleanupMode
    {
        UnregisterOnly = 1,
        DetachAllReturnNone = 2,
        DetachAllReturnHardDisksOnly = 3,
        Full = 4,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 6)
        DetachAllReturnHardDisksAndVMRemovable = 5,
#endif
    };

    enum class ClipboardMode
    {
        Disabled = 0,
        HostToGuest = 1,
        GuestToHost = 2,
        Bidirectional = 3,
    };

    enum class CloneMode
    {
        MachineState = 1,
        MachineAndChildStates = 2,
        AllStates = 3,
    };

    enum class CloneOptions
    {
        Link = 1,
        KeepAllMACs = 2,
        KeepNATMACs = 3,
        KeepDiskNames = 4,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        KeepHwUUIDs = 5,
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    enum class CloudImageState
    {
        Invalid = 0,
        Provisioning = 1,
        Importing = 2,
        Available = 3,
        Exporting = 4,
        Disabled = 5,
        Deleted = 6,
    };

    enum class CloudMachineState
    {
        Invalid = 0,
        Provisioning = 1,
        Running = 2,
        Starting = 3,
        Stopping = 4,
        Stopped = 5,
        CreatingImage = 6,
        Terminating = 7,
        Terminated = 8,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class CPUArchitecture
    {
        Any = 0,
        x86 = 1,
        AMD64 = 2,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        ARMv8_32 = 3,
        ARMv8_64 = 4,
#endif
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
    enum class CPUPropertyTypeARM
    {
        Null = 0,
        HWVirt = 1,
        GICITS = 2,
    };
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
    enum class CPUPropertyType
#else
    enum class CPUPropertyTypeX86
#endif
    {
        Null = 0,
        PAE = 1,
        LongMode = 2,
        TripleFaultReset = 3,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        APIC = 4,
        X2APIC = 5,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 6)                 \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(5, 2, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 32) )
        IBPBOnVMExit = 6,
        IBPBOnVMEntry = 7,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        HWVirt = 8,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 8)                 \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(5, 2, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 36) )
        SpecCtrl = 9,
        SpecCtrlByHost = 10,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 2)                 \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 18) )
        L1DFlushOnEMTScheduling = 11,
        L1DFlushOnVMEntry = 12,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 8)                 \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 30) )
        MDSClearOnEMTScheduling = 13,
        MDSClearOnVMEntry = 14,
#endif
    };

    enum class DataFlags
    {
        None = 0,
        Mandatory = 0x1,
        Expert = 0x2,
        Array = 0x4,
        FlagMask = 0x7,
    };
    VBox_ENUM_BITWISE(DataFlags)

    enum class DataType
    {
        Int32 = 0,
        Int8 = 1,
        String = 2,
    };

    enum class DeviceActivity
    {
        Null = 0,
        Idle = 1,
        Reading = 2,
        Writing = 3,
    };

    enum class DeviceType
    {
        Null = 0,
        Floppy = 1,
        DVD = 2,
        HardDisk = 3,
        Network = 4,
        USB = 5,
        SharedFolder = 6,
        Graphics3D = 7,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 8)
        End = 8,
#endif
    };

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
    enum class DhcpOpt
    {
        SubnetMask = 1,
        TimeOffset = 2,
        Router = 3,
        TimeServer = 4,
        NameServer = 5,
        DomainNameServer = 6,
        LogServer = 7,
        Cookie = 8,
        LPRServer = 9,
        ImpressServer = 10,
        ResourseLocationServer = 11,
        HostName = 12,
        BootFileSize = 13,
        MeritDumpFile = 14,
        DomainName = 15,
        SwapServer = 16,
        RootPath = 17,
        ExtensionPath = 18,
        IPForwardingEnableDisable = 19,
        NonLocalSourceRoutingEnableDisable = 20,
        PolicyFilter = 21,
        MaximumDatagramReassemblySize = 22,
        DefaultIPTime2Live = 23,
        PathMTUAgingTimeout = 24,
        IPLayerParametersPerInterface = 25,
        InterfaceMTU = 26,
        AllSubnetsAreLocal = 27,
        BroadcastAddress = 28,
        PerformMaskDiscovery = 29,
        MaskSupplier = 30,
        PerformRouteDiscovery = 31,
        RouterSolicitationAddress = 32,
        StaticRoute = 33,
        TrailerEncapsulation = 34,
        ARPCacheTimeout = 35,
        EthernetEncapsulation = 36,
        TCPDefaultTTL = 37,
        TCPKeepAliveInterval = 38,
        TCPKeepAliveGarbage = 39,
        NetworkInformationServiceDomain = 40,
        NetworkInformationServiceServers = 41,
        NetworkTimeProtocolServers = 42,
        VendorSpecificInformation = 43,
        Option_44 = 44,
        Option_45 = 45,
        Option_46 = 46,
        Option_47 = 47,
        Option_48 = 48,
        Option_49 = 49,
        IPAddressLeaseTime = 51,
        Option_64 = 64,
        Option_65 = 65,
        TFTPServerName = 66,
        BootfileName = 67,
        Option_68 = 68,
        Option_69 = 69,
        Option_70 = 70,
        Option_71 = 71,
        Option_72 = 72,
        Option_73 = 73,
        Option_74 = 74,
        Option_75 = 75,
        Option_119 = 119,
    };
#else
    // This is essentially the same enum, but VBox has tweaked most of the names
    // and added several entries...
    enum class DHCPOption
    {
        SubnetMask = 1,
        TimeOffset = 2,
        Routers = 3,
        TimeServers = 4,
        NameServers = 5,
        DomainNameServers = 6,
        LogServers = 7,
        CookieServers = 8,
        LPRServers = 9,
        ImpressServers = 10,
        ResourseLocationServers = 11,
        HostName = 12,
        BootFileSize = 13,
        MeritDumpFile = 14,
        DomainName = 15,
        SwapServer = 16,
        RootPath = 17,
        ExtensionPath = 18,
        IPForwarding = 19,
        OptNonLocalSourceRouting = 20,
        PolicyFilter = 21,
        MaximumDgramReassemblySize = 22,
        DefaultIPTTL = 23,
        PathMTUAgingTimeout = 24,
        PathMTUPlateauTable = 25,
        InterfaceMTU = 26,
        AllSubnetsAreLocal = 27,
        BroadcastAddress = 28,
        PerformMaskDiscovery = 29,
        MaskSupplier = 30,
        PerformRouterDiscovery = 31,
        RouterSolicitationAddress = 32,
        StaticRoute = 33,
        TrailerEncapsulation = 34,
        ARPCacheTimeout = 35,
        EthernetEncapsulation = 36,
        TCPDefaultTTL = 37,
        TCPKeepaliveInterval = 38,
        TCPKeepaliveGarbage = 39,
        NISDomain = 40,
        NISServers = 41,
        NTPServers = 42,
        VendorSpecificInfo = 43,
        NetBIOSNameServers = 44,
        NetBIOSDatagramServers = 45,
        NetBIOSNodeType = 46,
        NetBIOSScope = 47,
        XWindowsFontServers = 48,
        XWindowsDisplayManager = 49,
        NetWareIPDomainName = 62,
        NetWareIPInformation = 63,
        NISPlusDomain = 64,
        NISPlusServers = 65,
        TFTPServerName = 66,
        BootfileName = 67,
        MobileIPHomeAgents = 68,
        SMTPServers = 69,
        POP3Servers = 70,
        NNTPServers = 71,
        WWWServers = 72,
        FingerServers = 73,
        IRCServers = 74,
        StreetTalkServers = 75,
        STDAServers = 76,
        SLPDirectoryAgent = 78,
        SLPServiceScope = 79,
        DomainSearch = 119,
    };
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
    enum class DhcpOptEncoding
    {
        Legacy = 0,
        Hex = 1,
    };
#else
    enum class DHCPOptionEncoding
    {
        Normal = 0,
        Hex = 1,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    enum class DHCPConfigScope
    {
        Global = 0,
        Group = 1,
        MachineNIC = 2,
        MAC = 3,
    };

    enum class DHCPGroupConditionType
    {
        MAC = 0,
        MACWildcard = 1,
        vendorClassID = 2,
        vendorClassIDWildcard = 3,
        userClassID = 4,
        userClassIDWildcard = 5,
    };
#endif

    enum class DirectoryCopyFlag
    {
        None = 0,
        CopyIntoExisting = 0x1,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        Recursive = 0x2,
        FollowLinks = 0x4,
#endif
    };
    VBox_ENUM_BITWISE(DirectoryCopyFlag)
    // Old name for this enum
    typedef DirectoryCopyFlag DirectoryCopyFlags;

    enum class DirectoryCreateFlag
    {
        None = 0,
        Parents = 1,
    };
    VBox_ENUM_BITWISE(DirectoryCreateFlag)

    enum class DirectoryOpenFlag
    {
        None = 0,
        NoSymlinks = 1,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        DenyAscent = 2,
        NoFollowSymlinks = 4,
#endif
    };
    VBox_ENUM_BITWISE(DirectoryOpenFlag)

    enum class DirectoryRemoveRecFlag
    {
        None = 0,
        ContentAndDir = 1,
        ContentOnly = 2,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
    enum class DirectoryStatus
    {
        Undefined = 0,
        Open = 1,
        Close = 2,
        Rewind = 3,
        Down = 4,
        Error = 5,
    };
#endif

    enum class DnDAction
    {
        Ignore = 0,
        Copy = 1,
        Move = 2,
        Link = 3,
    };

    enum class DnDMode
    {
        Disabled = 0,
        HostToGuest = 1,
        GuestToHost = 2,
        Bidirectional = 3,
    };

    enum class ExportOptions
    {
        CreateManifest = 1,
        ExportDVDImages = 2,
        StripAllMACs = 3,
        StripAllNonNATMACs = 4,
    };

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
    enum class FaultToleranceState
    {
        Inactive = 1,
        Master = 2,
        Standby = 3,
    };
#endif

    enum class FileAccessMode
    {
        ReadOnly = 1,
        WriteOnly = 2,
        ReadWrite = 3,
        AppendOnly = 4,
        AppendRead = 5,
    };

    enum class FileCopyFlag
    {
        None = 0,
        NoReplace = 1,
        FollowLinks = 2,
        Update = 4,
    };
    VBox_ENUM_BITWISE(FileCopyFlag)

    enum class FileOpenAction
    {
        OpenExisting = 1,
        OpenOrCreate = 2,
        CreateNew = 3,
        CreateOrReplace = 4,
        OpenExistingTruncated = 5,
        AppendOrCreate = 99,
    };

    enum class FileOpenExFlag
    {
        None = 0,
    };
    VBox_ENUM_BITWISE(FileOpenExFlag)
    // Old name for this enum
    typedef FileOpenExFlag FileOpenExFlags;

    enum class FileSeekOrigin
    {
        None = 0,
        EndOfFile = 1,
    };

    enum class FileSharingMode
    {
        Read = 1,
        Write = 2,
        ReadWrite = 3,
        Delete = 4,
        ReadDelete = 5,
        WriteDelete = 6,
        All = 7,
    };
    VBox_ENUM_BITWISE(FileSharingMode)

    enum class FileStatus
    {
        Undefined = 0,
        Opening = 10,
        Open = 100,
        Closing = 150,
        Closed = 200,
        Down = 600,
        Error = 800,
    };

    enum class FirmwareType
    {
        BIOS = 1,
        EFI = 2,
        EFI32 = 3,
        EFI64 = 4,
        EFIDUAL = 5,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    enum class FormValueType
    {
        Boolean = 0,
        String = 1,
        Choice = 2,
        RangedInteger = 3,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 14)
        RangedInteger64 = 4,
#endif
    };
#endif

    enum class FramebufferCapabilities
    {
        UpdateImage = 0x1,
        VHWA = 0x2,
        VisibleRegion = 0x4,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 6)
        RenderCursor = 0x8,
        MoveCursor = 0x10,
#endif
    };
    VBox_ENUM_BITWISE(FramebufferCapabilities)

    enum class FsObjMoveFlag
    {
        None = 0,
        Replace = 1,
        FollowLinks = 2,
        AllowDirectoryMoves = 4,
    };
    VBox_ENUM_BITWISE(FsObjMoveFlag)
    // Old name for this enum
    typedef FsObjMoveFlag FsObjMoveFlags;

    enum class FsObjRenameFlag
    {
        NoReplace = 0,
        Replace = 1,
    };
    VBox_ENUM_BITWISE(FsObjRenameFlag)

    enum class FsObjType
    {
        Unknown = 1,
        Fifo = 2,
        DevChar = 3,
        Directory = 4,
        DevBlock = 5,
        File = 6,
        Symlink = 7,
        Socket = 8,
        WhiteOut = 9,
    };

    enum class GraphicsControllerType
    {
        Null = 0,
        VBoxVGA = 1,
        VMSVGA = 2,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        VBoxSVGA = 3,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        QemuRamFB = 4,
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
    enum class GraphicsFeature
    {
        None = 0,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 2, 0)
        Acceleration2DVideo = 1,
#endif
        Acceleration3D = 2,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class GuestDebugIoProvider
    {
        None = 0,
        TCP = 1,
        UDP = 2,
        IPC = 3,
    };

    enum class GuestDebugProvider
    {
        None = 0,
        Native = 1,
        GDB = 2,
        KD = 3,
    };
#endif

    enum class GuestMonitorChangedEventType
    {
        Enabled = 0,
        Disabled = 1,
        NewOrigin = 2,
    };

    enum class GuestMonitorStatus
    {
        Disabled = 0,
        Enabled = 1,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        Blank = 2,
#endif
    };

    enum class GuestMouseEventMode
    {
        Relative = 0,
        Absolute = 1,
    };

    enum class GuestSessionStatus
    {
        Undefined = 0,
        Starting = 10,
        Started = 100,
        Terminating = 480,
        Terminated = 500,
        TimedOutKilled = 512,
        TimedOutAbnormally = 513,
        Down = 600,
        Error = 800,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class GuestShutdownFlag
    {
        None = 0,
        PowerOff = 0x1,
        Reboot = 0x2,
        Force = 0x4,
    };
    VBox_ENUM_BITWISE(GuestShutdownFlag)
#endif

    enum class GuestUserState
    {
        Unknown = 0,
        LoggedIn = 1,
        LoggedOut = 2,
        Locked = 3,
        Unlocked = 4,
        Disabled = 5,
        Idle = 6,
        InUse = 7,
        Created = 8,
        Deleted = 9,
        SessionChanged = 10,
        CredentialsChanged = 11,
        RoleChanged = 12,
        GroupAdded = 13,
        GroupRemoved = 14,
        Elevated = 15,
    };

    enum class GuestSessionWaitForFlag
    {
        None = 0,
        Start = 1,
        Terminate = 2,
        Status = 4,
    };
    VBox_ENUM_BITWISE(GuestSessionWaitForFlag)

    enum class GuestSessionWaitResult
    {
        None = 0,
        Start = 1,
        Terminate = 2,
        Status = 3,
        Error = 4,
        Timeout = 5,
        WaitFlagNotSupported = 6,
    };

    enum class HostNetworkInterfaceMediumType
    {
        Unknown = 0,
        Ethernet = 1,
        PPP = 2,
        SLIP = 3,
    };

    enum class HostNetworkInterfaceStatus
    {
        Unknown = 0,
        Up = 1,
        Down = 2,
    };

    enum class HostNetworkInterfaceType
    {
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
        Invalid = 0,
#endif
        Bridged = 1,
        HostOnly = 2,
    };

    enum class HWVirtExPropertyType
    {
        Null = 0,
        Enabled = 1,
        VPID = 2,
        NestedPaging = 3,
        UnrestrictedExecution = 4,
        LargePages = 5,
        Force = 6,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        UseNativeApi = 7,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        VirtVmsaveVmload = 8,
#endif
    };

    enum class ImportOptions
    {
        KeepAllMACs = 1,
        KeepNATMACs = 2,
        ImportToVDI = 3,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class IommuType
    {
        None = 0,
        Automatic = 1,
        AMD = 2,
        Intel = 3,
    };
#endif

    enum class KeyboardHIDType
    {
        None = 1,
        PS2Keyboard = 2,
        USBKeyboard = 3,
        ComboKeyboard = 5,
    };

    enum class KeyboardLED
    {
        NumLock = 0x1,
        CapsLock = 0x2,
        ScrollLock = 0x4,
    };
    VBox_ENUM_BITWISE(KeyboardLED)

    enum class LockType
    {
        Null = 0,
        Shared = 1,
        Write = 2,
        VM = 3,
    };

    enum class MachineState
    {
        Null = 0,
        PoweredOff,
        Saved,
        Teleported,
        Aborted,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        AbortedSaved,
#endif
        Running,
        Paused,
        Stuck,
        Teleporting,
        LiveSnapshotting,
        Starting,
        Stopping,
        Saving,
        Restoring,
        TeleportingPausedVM,
        TeleportingIn,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        FaultTolerantSyncing,
#endif
        DeletingSnapshotOnline,
        DeletingSnapshotPaused,
        OnlineSnapshotting,
        RestoringSnapshot,
        DeletingSnapshot,
        SettingUp,
        Snapshotting,
        FirstOnline = Running,
        LastOnline = OnlineSnapshotting,
        FirstTransient = Teleporting,
        LastTransient = Snapshotting,
    };

    enum class MediumFormatCapabilities
    {
        Uuid = 0x1,
        CreateFixed = 0x2,
        CreateDynamic = 0x4,
        CreateSplit2G = 0x8,
        Differencing = 0x10,
        Asynchronous = 0x20,
        File = 0x40,
        Properties = 0x80,
        TcpNetworking = 0x100,
        VFS = 0x200,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        Discard = 0x400,
        Preferred = 0x800,
        CapabilityMask = 0xfff,
#else
        CapabilityMask = 0x3ff,
#endif
    };
    VBox_ENUM_BITWISE(MediumFormatCapabilities)

    enum class MediumState
    {
        NotCreated = 0,
        Created = 1,
        LockedRead = 2,
        LockedWrite = 3,
        Inaccessible = 4,
        Creating = 5,
        Deleting = 6,
    };

    enum class MediumType
    {
        Normal = 0,
        Immutable = 1,
        Writethrough = 2,
        Shareable = 3,
        Readonly = 4,
        MultiAttach = 5,
    };

    enum class MediumVariant
    {
        Standard = 0,
        VmdkSplit2G = 0x1,
        VmdkRawDisk = 0x2,
        VmdkStreamOptimized = 0x4,
        VmdkESX = 0x8,
        VdiZeroExpand = 0x100,
        Fixed = 0x10000,
        Diff = 0x20000,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        Formatted = 0x20000000,
#endif
        NoCreateDir = 0x40000000,
    };
    VBox_ENUM_BITWISE(MediumVariant)

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
    enum class MetricType
    {
        Invalid = 0,
        CpuUtilization = 1,
        MemoryUtilization = 2,
        DiskBytesRead = 3,
        DiskBytesWritten = 4,
        NetworksBytesIn = 5,
        NetworksBytesOut = 6,
    };
#endif

    enum class MouseButtonState
    {
        LeftButton = 0x1,
        RightButton = 0x2,
        MiddleButton = 0x4,
        WheelUp = 0x8,
        WheelDown = 0x10,
        XButton1 = 0x20,
        XButton2 = 0x40,
        MouseStateMask = 0x7f,
    };
    VBox_ENUM_BITWISE(MouseButtonState)

    enum class NATAliasMode
    {
        AliasLog = 0x1,
        AliasProxyOnly = 0x2,
        AliasUseSamePorts = 0x4,
    };
    VBox_ENUM_BITWISE(NATAliasMode)

    enum class NATProtocol
    {
        UDP = 0,
        TCP = 1,
    };

    enum class NetworkAdapterPromiscModePolicy
    {
        Deny = 1,
        AllowNetwork = 2,
        AllowAll = 3,
    };

    enum class NetworkAdapterType
    {
        Null = 0,
        Am79C970A = 1,
        Am79C973 = 2,
        I82540EM = 3,
        I82543GC = 4,
        I82545EM = 5,
        Virtio = 6,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        Am79C960 = 7,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 2)                 \
    && VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
        Virtio_1_0 = 8,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        NE2000 = 8,
        NE1000 = 9,
        WD8013 = 10,
        WD8003 = 11,
        ELNK2 = 12,
        ELNK1 = 13,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
        UsbNet = 14,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 2)
        I82583V = 15,
#endif
    };

    enum class NetworkAttachmentType
    {
        Null = 0,
        NAT = 1,
        Bridged = 2,
        Internal = 3,
        HostOnly = 4,
        Generic = 5,
        NATNetwork = 6,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        Cloud = 7,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        HostOnlyNetwork = 8,
#endif
    };

    enum class ParavirtProvider
    {
        None = 0,
        Default = 1,
        Legacy = 2,
        Minimal = 3,
        HyperV = 4,
        KVM = 5,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class PartitioningType
    {
        MBR = 0,
        GPT = 1,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class PartitionTableType
    {
        MBR = 1,
        GPT = 2,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class PartitionType
    {
        Empty = 0,
        FAT12 = 1,
        FAT16 = 4,
        FAT = 6,
        IFS = 7,
        FAT32CHS = 11,
        FAT32LBA = 12,
        FAT16B = 14,
        Extended = 15,
        WindowsRE = 39,
        LinuxSwapOld = 66,
        LinuxOld = 67,
        DragonFlyBSDSlice = 108,
        LinuxSwap = 130,
        Linux = 131,
        LinuxExtended = 133,
        LinuxLVM = 142,
        BSDSlice = 165,
        AppleUFS = 168,
        AppleHFS = 175,
        Solaris = 191,
        GPT = 238,
        EFI = 239,
        Unknown = 256,
        MBR = 257,
        iFFS = 258,
        SonyBoot = 259,
        LenovoBoot = 260,
        WindowsMSR = 270,
        WindowsBasicData = 271,
        WindowsLDMMeta = 272,
        WindowsLDMData = 273,
        WindowsRecovery = 274,
        WindowsStorageSpaces = 276,
        WindowsStorageReplica = 277,
        IBMGPFS = 275,
        LinuxData = 300,
        LinuxRAID = 301,
        LinuxRootX86 = 302,
        LinuxRootAMD64 = 303,
        LinuxRootARM32 = 304,
        LinuxRootARM64 = 305,
        LinuxHome = 306,
        LinuxSrv = 307,
        LinuxPlainDmCrypt = 308,
        LinuxLUKS = 309,
        LinuxReserved = 310,
        FreeBSDBoot = 330,
        FreeBSDData = 331,
        FreeBSDSwap = 332,
        FreeBSDUFS = 333,
        FreeBSDVinum = 334,
        FreeBSDZFS = 335,
        FreeBSDUnknown = 359,
        AppleHFSPlus = 360,
        AppleAPFS = 361,
        AppleRAID = 362,
        AppleRAIDOffline = 363,
        AppleBoot = 364,
        AppleLabel = 365,
        AppleTvRecovery = 366,
        AppleCoreStorage = 367,
        SoftRAIDStatus = 370,
        SoftRAIDScratch = 371,
        SoftRAIDVolume = 372,
        SoftRAIDCache = 373,
        AppleUnknown = 389,
        SolarisBoot = 390,
        SolarisRoot = 391,
        SolarisSwap = 392,
        SolarisBackup = 393,
        SolarisUsr = 394,
        SolarisVar = 395,
        SolarisHome = 396,
        SolarisAltSector = 397,
        SolarisReserved = 398,
        SolarisUnknown = 419,
        NetBSDSwap = 420,
        NetBSDFFS = 421,
        NetBSDLFS = 422,
        NetBSDRAID = 423,
        NetBSDConcatenated = 424,
        NetBSDEncrypted = 425,
        NetBSDUnknown = 449,
        ChromeOSKernel = 450,
        ChromeOSRootFS = 451,
        ChromeOSFuture = 452,
        ContLnxUsr = 480,
        ContLnxRoot = 481,
        ContLnxReserved = 482,
        ContLnxRootRAID = 483,
        HaikuBFS = 510,
        MidntBSDBoot = 540,
        MidntBSDData = 541,
        MidntBSDSwap = 542,
        MidntBSDUFS = 543,
        MidntBSDVium = 544,
        MidntBSDZFS = 545,
        MidntBSDUnknown = 569,
        OpenBSDData = 570,
        QNXPowerSafeFS = 600,
        Plan9 = 630,
        VMWareVMKCore = 660,
        VMWareVMFS = 661,
        VMWareReserved = 662,
        VMWareUnknown = 689,
        AndroidX86Bootloader = 690,
        AndroidX86Bootloader2 = 691,
        AndroidX86Boot = 692,
        AndroidX86Recovery = 693,
        AndroidX86Misc = 694,
        AndroidX86Metadata = 695,
        AndroidX86System = 696,
        AndroidX86Cache = 697,
        AndroidX86Data = 698,
        AndroidX86Persistent = 699,
        AndroidX86Vendor = 700,
        AndroidX86Config = 701,
        AndroidX86Factory = 702,
        AndroidX86FactoryAlt = 703,
        AndroidX86Fastboot = 704,
        AndroidX86OEM = 705,
        AndroidARMMeta = 720,
        AndroidARMExt = 721,
        ONIEBoot = 750,
        ONIEConfig = 751,
        PowerPCPrep = 780,
        XDGShrBootConfig = 810,
        CephBlock = 830,
        CephBlockDB = 831,
        CephBlockDBDmc = 832,
        CephBlockDBDmcLUKS = 833,
        CephBlockDmc = 834,
        CephBlockDmcLUKS = 835,
        CephBlockWALog = 836,
        CephBlockWALogDmc = 837,
        CephBlockWALogDmcLUKS = 838,
        CephDisk = 839,
        CephDiskDmc = 840,
        CephJournal = 841,
        CephJournalDmc = 842,
        CephJournalDmcLUKS = 843,
        CephLockbox = 844,
        CephMultipathBlock1 = 845,
        CephMultipathBlock2 = 846,
        CephMultipathBlockDB = 847,
        CephMultipathBLockWALog = 848,
        CephMultipathJournal = 849,
        CephMultipathOSD = 851,
        CephOSD = 852,
        CephOSDDmc = 853,
        CephOSDDmcLUKS = 854,
    };
#endif

    enum class PathStyle
    {
        DOS = 1,
        UNIX = 2,
        Unknown = 8,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
    enum class PlatformArchitecture
    {
        None = 0,
        x86 = 1,
        ARM = 2,
    };
#endif

    enum class PointingHIDType
    {
        None = 1,
        PS2Mouse = 2,
        USBMouse = 3,
        USBTablet = 4,
        ComboMouse = 5,
        USBMultiTouch = 6,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        USBMultiTouchScreenPlusPad = 7,
#endif
    };

    enum class PortMode
    {
        Disconnected = 0,
        HostPipe = 1,
        HostDevice = 2,
        RawFile = 3,
        TCP = 4,
    };

    enum class ProcessCreateFlag
    {
        None = 0,
        WaitForProcessStartOnly = 1,
        IgnoreOrphanedProcesses = 2,
        Hidden = 4,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        Profile = 8,
#else
        NoProfile = 8,
#endif
        WaitForStdOut = 16,
        WaitForStdErr = 32,
        ExpandArguments = 64,
        UnquotedArguments = 128,
    };
    VBox_ENUM_BITWISE(ProcessCreateFlag)

    enum class ProcessInputFlag
    {
        None = 0,
        EndOfFile = 1,
    };
    VBox_ENUM_BITWISE(ProcessInputFlag)

    enum class ProcessInputStatus
    {
        Undefined = 0,
        Broken = 1,
        Available = 10,
        Written = 50,
        Overflow = 100,
    };

    enum class ProcessorFeature
    {
        HWVirtEx = 0,
        PAE = 1,
        LongMode = 2,
        NestedPaging = 3,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        UnrestrictedGuest = 4,
        NestedHWVirt = 5,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        VirtVmsaveVmload = 6,
#endif
    };

    enum class ProcessOutputFlag
    {
        None = 0,
        StdErr = 1,
    };
    VBox_ENUM_BITWISE(ProcessOutputFlag)

    enum class ProcessPriority
    {
        Invalid = 0,
        Default = 1,
    };

    enum class ProcessStatus
    {
        Undefined = 0,
        Starting = 10,
        Started = 100,
        Paused = 110,
        Terminating = 480,
        TerminatedNormally = 500,
        TerminatedSignal = 510,
        TerminatedAbnormally = 511,
        TimedOutKilled = 512,
        TimedOutAbnormally = 513,
        Down = 600,
        Error = 800,
    };

    enum class ProcessWaitForFlag
    {
        None = 0,
        Start = 1,
        Terminate = 2,
        StdIn = 4,
        StdOut = 8,
        StdErr = 16,
    };
    VBox_ENUM_BITWISE(ProcessWaitForFlag)

    enum class ProcessWaitResult
    {
        None = 0,
        Start = 1,
        Terminate = 2,
        Status = 3,
        Error = 4,
        Timeout = 5,
        StdIn = 6,
        StdOut = 7,
        StdErr = 8,
        WaitFlagNotSupported = 9,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class ProxyMode
    {
        System = 0,
        NoProxy = 1,
        Manual = 2,
    };
#endif

    enum class Reason
    {
        Unspecified = 0,
        HostSuspend = 1,
        HostResume = 2,
        HostBatteryLow = 3,
        Snapshot = 4,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class RecordingAudioCodec
    {
        None = 0,
        WavPCM,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        MP3,
        OggVorbis,
#endif
        Opus,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        Other,
#endif
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class RecordingCodecDeadline
    {
        Default = 0,
        Realtime = 1,
        Good = 2,
        Best = 3,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class RecordingDestination
    {
        None = 0,
        File = 1,
    };

    enum class RecordingFeature
    {
        None = 0,
        Video = 0x1,
        Audio = 0x2,
    };
    VBox_ENUM_BITWISE(RecordingFeature)
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
    enum class RecordingState
    {
        Unknown = 0,
        Initializing = 1,
        Started = 2,
        Paused = 3,
        Resumed = 4,
        Finalizing = 5,
        Stopped = 6,
        Canceled = 7,
        LimitReached = 8,
        Error = 9,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class RecordingVideoCodec
    {
        None = 0,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        MJPEG,
        H262,
        H264,
        H265,
        H266,
#endif
        VP8,
        VP9,
        AV1,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        Other,
#endif
    };

    enum class RecordingRateControlMode
    {
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        ABR,
#endif
        CBR,
        VBR,
    };
    // Old name for this enum
    typedef RecordingRateControlMode RecordingVideoRateControlMode;

    enum class RecordingVideoScalingMode
    {
        None = 0,
        NearestNeighbor = 1,
        Bilinear = 2,
        Bicubic = 3,
    };
    // Old name for this enum
    typedef RecordingVideoScalingMode RecordingVideoScalingMethod;
#endif

    enum class Scope
    {
        Global = 0,
        Machine = 1,
        Session = 2,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
    enum class ScreenLayoutMode
    {
        Apply = 0,
        Reset = 1,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        Attach = 2,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        Silent = 3,
#endif
    };
#endif

    enum class SessionState
    {
        Null = 0,
        Unlocked = 1,
        Locked = 2,
        Spawning = 3,
        Unlocking = 4,
    };

    enum class SessionType
    {
        Null = 0,
        WriteLock = 1,
        Remote = 2,
        Shared = 3,
    };

    enum class SettingsVersion
    {
        Null = 0,
        v1_0 = 1,
        v1_1 = 2,
        v1_2 = 3,
        v1_3pre = 4,
        v1_3 = 5,
        v1_4 = 6,
        v1_5 = 7,
        v1_6 = 8,
        v1_7 = 9,
        v1_8 = 10,
        v1_9 = 11,
        v1_10 = 12,
        v1_11 = 13,
        v1_12 = 14,
        v1_13 = 15,
        v1_14 = 16,
        v1_15 = 17,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        v1_16 = 18,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        v1_17 = 19,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        v1_18 = 20,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        v1_19 = 21,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        v1_20 = 22,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
        v1_21 = 23,
#endif
        Future = 99999,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class SignatureType
    {
        X509 = 0,
        Sha256 = 1,
    };
#endif

    enum class StorageBus
    {
        Null = 0,
        IDE = 1,
        SATA = 2,
        SCSI = 3,
        Floppy = 4,
        SAS = 5,
        USB = 6,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        PCIe = 7,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VirtioSCSI = 8,
#endif
    };

    enum class StorageControllerType
    {
        Null = 0,
        LsiLogic = 1,
        BusLogic = 2,
        IntelAhci = 3,
        PIIX3 = 4,
        PIIX4 = 5,
        ICH6 = 6,
        I82078 = 7,
        LsiLogicSas = 8,
        USB = 9,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
        NVMe = 10,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        VirtioSCSI = 11,
#endif
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
    enum class SymlinkPolicy
    {
        None = 0,
        Forbidden = 1,
        AllowedInShareSubtree = 2,
        AllowedToRelativeTargets = 3,
        AllowedToAnyTarget = 4,
    };
#endif

    enum class SymlinkReadFlag
    {
        None = 0,
        NoSymlinks = 1,
    };
    VBox_ENUM_BITWISE(SymlinkReadFlag)

    enum class SymlinkType
    {
        Unknown = 0,
        Directory = 1,
        File = 2,
    };

    enum class TouchContactState
    {
        None = 0,
        InContact = 0x1,
        InRange = 0x2,
        ContactStateMask = 0x3,
    };
    VBox_ENUM_BITWISE(TouchContactState)

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class TpmType
    {
        None = 0,
        v1_2 = 1,
        v2_0 = 2,
        Host = 3,
        Swtpm = 4,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
    enum class TrackedObjectState
    {
        None = 0,
        Alive = 1,
        Deleted = 2,
        Invalid = 3,
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class UartType
    {
        U16450 = 0,
        U16550A = 1,
        U16750 = 2
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class UefiVariableAttributes
    {
        None = 0,
        NonVolatile = 0x1,
        BootServiceAccess = 0x2,
        RuntimeAccess = 0x4,
        HwErrorRecord = 0x8,
        AuthWriteAccess = 0x100,
        AuthTimeBasedWriteAccess = 0x200,
        AuthAppendWrite = 0x400,
    };
    VBox_ENUM_BITWISE(UefiVariableAttributes)
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
    enum class UpdateChannel
    {
        Invalid = 0,
        Stable = 1,
        All = 2,
        WithBetas = 3,
        WithTesting = 4,
    };

    enum class UpdateSeverity
    {
        Invalid = 0,
        Critical = 1,
        Major = 2,
        Minor = 3,
        Testing = 4,
    };

    enum class UpdateState
    {
        Invalid = 0,
        Available = 1,
        NotAvailable = 2,
        Downloading = 3,
        Downloaded = 4,
        Installing = 5,
        Installed = 6,
        UserInteraction = 7,
        Canceled = 8,
        Maintenance = 9,
        Error = 10,
    };
#endif

    enum class USBConnectionSpeed
    {
        Null = 0,
        Low = 1,
        Full = 2,
        High = 3,
        Super = 4,
        SuperPlus = 5,
    };

    enum class USBControllerType
    {
        Null = 0,
        OHCI = 1,
        EHCI = 2,
        XHCI = 3,
        Last = 4,
    };

    enum class USBDeviceFilterAction
    {
        Null = 0,
        Ignore = 1,
        Hold = 2,
    };

    enum class USBDeviceState
    {
        NotSupported = 0,
        Unavailable = 1,
        Busy = 2,
        Available = 3,
        Held = 4,
        Captured = 5,
    };

    enum class VBoxEventType
    {
        Invalid = 0,
        Any,
        Vetoable,
        MachineEvent,
        SnapshotEvent,
        InputEvent,
        LastWildcard = 31,
        OnMachineStateChanged,
        OnMachineDataChanged,
        OnExtraDataChanged,
        OnExtraDataCanChange,
        OnMediumRegistered,
        OnMachineRegistered,
        OnSessionStateChanged,
        OnSnapshotTaken,
        OnSnapshotDeleted,
        OnSnapshotChanged,
        OnGuestPropertyChanged,
        OnMousePointerShapeChanged,
        OnMouseCapabilityChanged,
        OnKeyboardLedsChanged,
        OnStateChanged,
        OnAdditionsStateChanged,
        OnNetworkAdapterChanged,
        OnSerialPortChanged,
        OnParallelPortChanged,
        OnStorageControllerChanged,
        OnMediumChanged,
        OnVRDEServerChanged,
        OnUSBControllerChanged,
        OnUSBDeviceStateChanged,
        OnSharedFolderChanged,
        OnRuntimeError,
        OnCanShowWindow,
        OnShowWindow,
        OnCPUChanged,
        OnVRDEServerInfoChanged,
        OnEventSourceChanged,
        OnCPUExecutionCapChanged,
        OnGuestKeyboard,
        OnGuestMouse,
        OnNATRedirect,
        OnHostPCIDevicePlug,
        OnVBoxSVCAvailabilityChanged,
        OnBandwidthGroupChanged,
        OnGuestMonitorChanged,
        OnStorageDeviceChanged,
        OnClipboardModeChanged,
        OnDnDModeChanged,
        OnNATNetworkChanged,
        OnNATNetworkStartStop,
        OnNATNetworkAlter,
        OnNATNetworkCreationDeletion,
        OnNATNetworkSetting,
        OnNATNetworkPortForward,
        OnGuestSessionStateChanged,
        OnGuestSessionRegistered,
        OnGuestProcessRegistered,
        OnGuestProcessStateChanged,
        OnGuestProcessInputNotify,
        OnGuestProcessOutput,
        OnGuestFileRegistered,
        OnGuestFileStateChanged,
        OnGuestFileOffsetChanged,
        OnGuestFileRead,
        OnGuestFileWrite,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
        OnVideoCaptureChanged,
#elif VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
        OnRecordingChanged,
#else
        OnRecordingStateChanged,
#endif
        OnGuestUserStateChanged,
        OnGuestMultiTouch,
        OnHostNameResolutionConfigurationChange,
        OnSnapshotRestored,
        OnMediumConfigChanged,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
        OnAudioAdapterChanged,
        OnProgressPercentageChanged,
        OnProgressTaskCompleted,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        OnCursorPositionChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 32) )
        OnGuestAdditionsStatusChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        OnGuestMonitorInfoChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 10)                \
    || (    VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)          \
         && VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 32) )
        OnGuestFileSizeChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        OnClipboardFileTransferModeChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        OnCloudProviderListChanged,
        OnCloudProviderRegistered,
        OnCloudProviderUninstall,
        OnCloudProfileRegistered,
        OnCloudProfileChanged,
        OnProgressCreated,
        OnLanguageChanged,
        OnUpdateAgentAvailable,
        OnUpdateAgentError,
        OnUpdateAgentSettingsChanged,
        OnUpdateAgentStateChanged,
        OnHostAudioDeviceChanged,
        OnGuestDebugControlChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 4)
        OnMachineGroupsChanged,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        OnGuestDirectoryRegistered,
        OnGuestDirectoryStateChanged,
        OnGuestDirectoryRead,
        OnClipboardError,
        OnExtPackInstalled,
        OnExtPackUninstalled,
        OnRecordingScreenStateChanged,
#endif
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
        Last,
#else
        End,
#endif
    };

    enum class VFSType
    {
        File = 1,
        Cloud = 2,
        S3 = 3,
        WebDav = 4,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)                 \
    && VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
        OCI = 5,
#endif
    };

    enum class VirtualSystemDescriptionType
    {
        Ignore = 1,
        OS = 2,
        Name = 3,
        Product = 4,
        Vendor = 5,
        Version = 6,
        ProductUrl = 7,
        VendorUrl = 8,
        Description = 9,
        License = 10,
        Miscellaneous = 11,
        CPU = 12,
        Memory = 13,
        HardDiskControllerIDE = 14,
        HardDiskControllerSATA = 15,
        HardDiskControllerSCSI = 16,
        HardDiskControllerSAS = 17,
        HardDiskImage = 18,
        Floppy = 19,
        CDROM = 20,
        NetworkAdapter = 21,
        USBController = 22,
        SoundCard = 23,
        SettingsFile = 24,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
        BaseFolder = 25,
        PrimaryGroup = 26,
        CloudInstanceShape = 27,
        CloudDomain = 28,
        CloudBootDiskSize = 29,
        CloudBucket = 30,
        CloudOCIVCN = 31,
        CloudPublicIP = 32,
        CloudProfileName = 33,
        CloudOCISubnet = 34,
        CloudKeepObject = 35,
        CloudLaunchInstance = 36,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
        CloudInstanceId = 37,
        CloudImageId = 38,
        CloudInstanceState = 39,
        CloudImageState = 40,
        CloudInstanceDisplayName = 41,
        CloudImageDisplayName = 42,
        CloudOCILaunchMode = 43,
        CloudPrivateIP = 44,
        CloudBootVolumeId = 45,
        CloudOCIVCNCompartment = 46,
        CloudOCISubnetCompartment = 47,
        CloudPublicSSHKey = 48,
        BootingFirmware = 49,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 20)
        CloudInitScriptPath = 50,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
        CloudCompartmentId = 51,
        CloudShapeCpus = 52,
        CloudShapeMemory = 53,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 10)
        CloudInstanceMetadata = 54,
        CloudInstanceFreeFormTags = 55,
        CloudImageFreeFormTags = 56,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 38)
        HardDiskControllerVirtioSCSI = 60,
#endif
#if (VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 50)               \
        && VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0))          \
    || VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 14)
        HardDiskControllerNVMe = 61,
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 2, 0)
        NVRAM = 0x8000,
#endif
    };

    enum class VirtualSystemDescriptionValueType
    {
        Reference = 1,
        Original = 2,
        Auto = 3,
        ExtraConfig = 4,
    };

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    enum class VMExecutionEngine
    {
        NotSet = 0,
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
        RawMode = 1,
#elif VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
        Emulated = 1,
#else
        Default = 1,
#endif
        HwVirt = 2,
        NativeApi = 3,
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
        Interpreter = 4,
        Recompiler = 5,
#endif
    };
#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
    enum class VMProcPriority
    {
        Invalid = 0,
        Default = 1,
        Flat = 2,
        Low = 3,
        Normal = 5,
        High = 6,
    };
#endif
}

// Forward Declarations for interface classes
#if defined(VBOX_XPCOM)
#   define VBox_FORWARD_DECL_IFC(ifc) \
        class ifc; \
        namespace VBox { class ifc; }
#elif defined(VBOX_MSCOM)
#   define VBox_FORWARD_DECL_IFC(ifc) \
        struct ifc; \
        namespace VBox { class ifc; }
#else
#   error Unsupported COM configuration
#endif

VBox_FORWARD_DECL_IFC(IAdditionsFacility);
VBox_FORWARD_DECL_IFC(IAdditionsStateChangedEvent);
VBox_FORWARD_DECL_IFC(IAppliance);
VBox_FORWARD_DECL_IFC(IAudioAdapter);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox_FORWARD_DECL_IFC(IAudioAdapterChangedEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IAudioSettings);
#endif
VBox_FORWARD_DECL_IFC(IBandwidthControl);
VBox_FORWARD_DECL_IFC(IBandwidthGroup);
VBox_FORWARD_DECL_IFC(IBandwidthGroupChangedEvent);
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IBIOSSettings);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IBooleanFormValue);
#endif
VBox_FORWARD_DECL_IFC(ICanShowWindowEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
VBox_FORWARD_DECL_IFC(ICertificate);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IChoiceFormValue);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IClipboardErrorEvent);
VBox_FORWARD_DECL_IFC(IClipboardEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IClipboardFileTransferModeChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IClipboardModeChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(ICloudClient);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(ICloudMachine);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(ICloudNetwork);
VBox_FORWARD_DECL_IFC(ICloudNetworkGatewayInfo);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 12)
VBox_FORWARD_DECL_IFC(ICloudNetworkEnvironmentInfo);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(ICloudProfile);
VBox_FORWARD_DECL_IFC(ICloudProvider);
VBox_FORWARD_DECL_IFC(ICloudProviderManager);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(ICloudProfileChangedEvent);
VBox_FORWARD_DECL_IFC(ICloudProfileRegisteredEvent);
VBox_FORWARD_DECL_IFC(ICloudProviderListChangedEvent);
VBox_FORWARD_DECL_IFC(ICloudProviderRegisteredEvent);
VBox_FORWARD_DECL_IFC(ICloudProviderUninstallEvent);
#endif
VBox_FORWARD_DECL_IFC(IConsole);
VBox_FORWARD_DECL_IFC(ICPUChangedEvent);
VBox_FORWARD_DECL_IFC(ICPUExecutionCapChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(ICPUProfile);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(ICursorPositionChangedEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(IDataStream);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IDHCPConfig);
VBox_FORWARD_DECL_IFC(IDHCPGlobalConfig);
VBox_FORWARD_DECL_IFC(IDHCPGroupCondition);
VBox_FORWARD_DECL_IFC(IDHCPGroupConfig);
VBox_FORWARD_DECL_IFC(IDHCPIndividualConfig);
#endif
VBox_FORWARD_DECL_IFC(IDHCPServer);
VBox_FORWARD_DECL_IFC(IDirectory);
VBox_FORWARD_DECL_IFC(IDisplay);
VBox_FORWARD_DECL_IFC(IDisplaySourceBitmap);
VBox_FORWARD_DECL_IFC(IDnDBase);
VBox_FORWARD_DECL_IFC(IDnDModeChangedEvent);
VBox_FORWARD_DECL_IFC(IDnDSource);
VBox_FORWARD_DECL_IFC(IDnDTarget);
VBox_FORWARD_DECL_IFC(IEmulatedUSB);
VBox_FORWARD_DECL_IFC(IEvent);
VBox_FORWARD_DECL_IFC(IEventListener);
VBox_FORWARD_DECL_IFC(IEventSource);
VBox_FORWARD_DECL_IFC(IEventSourceChangedEvent);
VBox_FORWARD_DECL_IFC(IExtPack);
VBox_FORWARD_DECL_IFC(IExtPackBase);
VBox_FORWARD_DECL_IFC(IExtPackFile);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IExtPackInstalledEvent);
#endif
VBox_FORWARD_DECL_IFC(IExtPackManager);
VBox_FORWARD_DECL_IFC(IExtPackPlugIn);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IExtPackUninstalledEvent);
#endif
VBox_FORWARD_DECL_IFC(IExtraDataCanChangeEvent);
VBox_FORWARD_DECL_IFC(IExtraDataChangedEvent);
VBox_FORWARD_DECL_IFC(IFile);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IFirmwareSettings);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IForm);
VBox_FORWARD_DECL_IFC(IFormValue);
#endif
VBox_FORWARD_DECL_IFC(IFramebuffer);
VBox_FORWARD_DECL_IFC(IFramebufferOverlay);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IFsInfo);
#endif
VBox_FORWARD_DECL_IFC(IFsObjInfo);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IGraphicsAdapter);
#endif
VBox_FORWARD_DECL_IFC(IGuest);
VBox_FORWARD_DECL_IFC(IGuestAdditionsStatusChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IGuestDebugControl);
VBox_FORWARD_DECL_IFC(IGuestDebugControlChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IGuestDirectory);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IGuestDirectoryEvent);
VBox_FORWARD_DECL_IFC(IGuestDirectoryReadEvent);
VBox_FORWARD_DECL_IFC(IGuestDirectoryRegisteredEvent);
VBox_FORWARD_DECL_IFC(IGuestDirectoryStateChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IGuestDnDSource);
VBox_FORWARD_DECL_IFC(IGuestDnDTarget);
VBox_FORWARD_DECL_IFC(IGuestFile);
VBox_FORWARD_DECL_IFC(IGuestFileEvent);
VBox_FORWARD_DECL_IFC(IGuestFileIOEvent);
VBox_FORWARD_DECL_IFC(IGuestFileOffsetChangedEvent);
VBox_FORWARD_DECL_IFC(IGuestFileReadEvent);
VBox_FORWARD_DECL_IFC(IGuestFileRegisteredEvent);
VBox_FORWARD_DECL_IFC(IGuestFileSizeChangedEvent);
VBox_FORWARD_DECL_IFC(IGuestFileStateChangedEvent);
VBox_FORWARD_DECL_IFC(IGuestFileWriteEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IGuestFsInfo)
#endif
VBox_FORWARD_DECL_IFC(IGuestFsObjInfo);
VBox_FORWARD_DECL_IFC(IGuestKeyboardEvent);
VBox_FORWARD_DECL_IFC(IGuestMonitorChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IGuestMonitorInfoChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IGuestMouseEvent);
VBox_FORWARD_DECL_IFC(IGuestMultiTouchEvent);
VBox_FORWARD_DECL_IFC(IGuestOSType);
VBox_FORWARD_DECL_IFC(IGuestProcess);
VBox_FORWARD_DECL_IFC(IGuestProcessEvent);
VBox_FORWARD_DECL_IFC(IGuestProcessIOEvent);
VBox_FORWARD_DECL_IFC(IGuestProcessInputNotifyEvent);
VBox_FORWARD_DECL_IFC(IGuestProcessOutputEvent);
VBox_FORWARD_DECL_IFC(IGuestProcessRegisteredEvent);
VBox_FORWARD_DECL_IFC(IGuestProcessStateChangedEvent);
VBox_FORWARD_DECL_IFC(IGuestPropertyChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
VBox_FORWARD_DECL_IFC(IGuestScreenInfo);
#endif
VBox_FORWARD_DECL_IFC(IGuestSession);
VBox_FORWARD_DECL_IFC(IGuestSessionEvent);
VBox_FORWARD_DECL_IFC(IGuestSessionRegisteredEvent);
VBox_FORWARD_DECL_IFC(IGuestSessionStateChangedEvent);
VBox_FORWARD_DECL_IFC(IGuestUserStateChangedEvent);
VBox_FORWARD_DECL_IFC(IHost);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IHostAudioDevice);
VBox_FORWARD_DECL_IFC(IHostAudioDeviceChangedEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IHostDrive);
VBox_FORWARD_DECL_IFC(IHostDrivePartition);
#endif
VBox_FORWARD_DECL_IFC(IHostNameResolutionConfigurationChangeEvent);
VBox_FORWARD_DECL_IFC(IHostNetworkInterface);
VBox_FORWARD_DECL_IFC(IHostPCIDevicePlugEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IHostOnlyNetwork);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)                 \
    && VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IHostUpdate);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IHostUpdateAgent)
#endif
VBox_FORWARD_DECL_IFC(IHostUSBDevice);
VBox_FORWARD_DECL_IFC(IHostUSBDeviceFilter);
VBox_FORWARD_DECL_IFC(IHostVideoInputDevice);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IHostX86)
#endif
VBox_FORWARD_DECL_IFC(IInternalMachineControl);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(IInternalProgressControl);
#endif
VBox_FORWARD_DECL_IFC(IInternalSessionControl);
VBox_FORWARD_DECL_IFC(IKeyboard);
VBox_FORWARD_DECL_IFC(IKeyboardLedsChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(ILanguageChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IMachine);
VBox_FORWARD_DECL_IFC(IMachineDataChangedEvent);
VBox_FORWARD_DECL_IFC(IMachineDebugger);
VBox_FORWARD_DECL_IFC(IMachineEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 4)
VBox_FORWARD_DECL_IFC(IMachineGroupsChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IMachineRegisteredEvent);
VBox_FORWARD_DECL_IFC(IMachineStateChangedEvent);
VBox_FORWARD_DECL_IFC(IMedium);
VBox_FORWARD_DECL_IFC(IMediumAttachment);
VBox_FORWARD_DECL_IFC(IMediumChangedEvent);
VBox_FORWARD_DECL_IFC(IMediumConfigChangedEvent);
VBox_FORWARD_DECL_IFC(IMediumFormat);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(IMediumIO);
#endif
VBox_FORWARD_DECL_IFC(IMediumRegisteredEvent);
VBox_FORWARD_DECL_IFC(IMouse);
VBox_FORWARD_DECL_IFC(IMouseCapabilityChangedEvent);
VBox_FORWARD_DECL_IFC(IMousePointerShape);
VBox_FORWARD_DECL_IFC(IMousePointerShapeChangedEvent);
VBox_FORWARD_DECL_IFC(INATEngine);
VBox_FORWARD_DECL_IFC(INATNetwork);
VBox_FORWARD_DECL_IFC(INATNetworkAlterEvent);
VBox_FORWARD_DECL_IFC(INATNetworkChangedEvent);
VBox_FORWARD_DECL_IFC(INATNetworkCreationDeletionEvent);
VBox_FORWARD_DECL_IFC(INATNetworkPortForwardEvent);
VBox_FORWARD_DECL_IFC(INATNetworkSettingEvent);
VBox_FORWARD_DECL_IFC(INATNetworkStartStopEvent);
VBox_FORWARD_DECL_IFC(INATRedirectEvent);
VBox_FORWARD_DECL_IFC(INetworkAdapter);
VBox_FORWARD_DECL_IFC(INetworkAdapterChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(INvramStore)
#endif
VBox_FORWARD_DECL_IFC(IParallelPort);
VBox_FORWARD_DECL_IFC(IParallelPortChangedEvent);
VBox_FORWARD_DECL_IFC(IPCIAddress);
VBox_FORWARD_DECL_IFC(IPCIDeviceAttachment);
VBox_FORWARD_DECL_IFC(IPerformanceCollector);
VBox_FORWARD_DECL_IFC(IPerformanceMetric);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IPlatform);
VBox_FORWARD_DECL_IFC(IPlatformARM);
VBox_FORWARD_DECL_IFC(IPlatformProperties);
VBox_FORWARD_DECL_IFC(IPlatformX86);
#endif
VBox_FORWARD_DECL_IFC(IProcess);
VBox_FORWARD_DECL_IFC(IProgress);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IProgressCreatedEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox_FORWARD_DECL_IFC(IProgressEvent);
VBox_FORWARD_DECL_IFC(IProgressPercentageChangedEvent);
VBox_FORWARD_DECL_IFC(IProgressTaskCompletedEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IRangedIntegerFormValue);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 14)
VBox_FORWARD_DECL_IFC(IRangedInteger64FormValue);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IRecordingScreenStateChangedEvent);
VBox_FORWARD_DECL_IFC(IRecordingStateChangedEvent);
#elif VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(IRecordingChangedEvent);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(IRecordingScreenSettings);
VBox_FORWARD_DECL_IFC(IRecordingSettings);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 1, 0)
VBox_FORWARD_DECL_IFC(IResourceStore);
#endif
VBox_FORWARD_DECL_IFC(IReusableEvent);
VBox_FORWARD_DECL_IFC(IRuntimeErrorEvent);
VBox_FORWARD_DECL_IFC(ISerialPort);
VBox_FORWARD_DECL_IFC(ISerialPortChangedEvent);
VBox_FORWARD_DECL_IFC(ISession);
VBox_FORWARD_DECL_IFC(ISessionStateChangedEvent);
VBox_FORWARD_DECL_IFC(ISharedFolder);
VBox_FORWARD_DECL_IFC(ISharedFolderChangedEvent);
VBox_FORWARD_DECL_IFC(IShowWindowEvent);
VBox_FORWARD_DECL_IFC(ISnapshot);
VBox_FORWARD_DECL_IFC(ISnapshotChangedEvent);
VBox_FORWARD_DECL_IFC(ISnapshotDeletedEvent);
VBox_FORWARD_DECL_IFC(ISnapshotEvent);
VBox_FORWARD_DECL_IFC(ISnapshotRestoredEvent);
VBox_FORWARD_DECL_IFC(ISnapshotTakenEvent);
VBox_FORWARD_DECL_IFC(IStateChangedEvent);
VBox_FORWARD_DECL_IFC(IStorageController);
VBox_FORWARD_DECL_IFC(IStorageControllerChangedEvent);
VBox_FORWARD_DECL_IFC(IStorageDeviceChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IStringArray);
VBox_FORWARD_DECL_IFC(IStringFormValue);
#endif
VBox_FORWARD_DECL_IFC(ISystemProperties);
VBox_FORWARD_DECL_IFC(IToken);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(ITrustedPlatformModule);
VBox_FORWARD_DECL_IFC(IUefiVariableStore);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox_FORWARD_DECL_IFC(IUnattended);
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox_FORWARD_DECL_IFC(IUpdateAgent);
VBox_FORWARD_DECL_IFC(IUpdateAgentAvailableEvent);
VBox_FORWARD_DECL_IFC(IUpdateAgentErrorEvent);
VBox_FORWARD_DECL_IFC(IUpdateAgentEvent);
VBox_FORWARD_DECL_IFC(IUpdateAgentSettingsChangedEvent);
VBox_FORWARD_DECL_IFC(IUpdateAgentStateChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IUSBController);
VBox_FORWARD_DECL_IFC(IUSBControllerChangedEvent);
VBox_FORWARD_DECL_IFC(IUSBDevice);
VBox_FORWARD_DECL_IFC(IUSBDeviceFilter);
VBox_FORWARD_DECL_IFC(IUSBDeviceFilters);
VBox_FORWARD_DECL_IFC(IUSBDeviceStateChangedEvent);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
VBox_FORWARD_DECL_IFC(IUSBProxyBackend);
#endif
VBox_FORWARD_DECL_IFC(IVBoxSVCAvailabilityChangedEvent);
VBox_FORWARD_DECL_IFC(IVetoEvent);
VBox_FORWARD_DECL_IFC(IVFSExplorer);
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
VBox_FORWARD_DECL_IFC(IVideoCaptureChangedEvent);
#endif
VBox_FORWARD_DECL_IFC(IVirtualBox);
VBox_FORWARD_DECL_IFC(IVirtualBoxClient);
VBox_FORWARD_DECL_IFC(IVirtualBoxErrorInfo);
VBox_FORWARD_DECL_IFC(IVirtualSystemDescription);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 0)
VBox_FORWARD_DECL_IFC(IVirtualSystemDescriptionForm);
#endif
VBox_FORWARD_DECL_IFC(IVRDEServer);
VBox_FORWARD_DECL_IFC(IVRDEServerChangedEvent);
VBox_FORWARD_DECL_IFC(IVRDEServerInfo);
VBox_FORWARD_DECL_IFC(IVRDEServerInfoChangedEvent);

#endif /* _LIBVBOX_VBOXSDK_TYPES_H */
