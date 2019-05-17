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

COM_WRAP_IFC(INetworkAdapterChangedEvent)
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
COM_WRAP_IFC(IAudioAdapterChangedEvent)
#endif
COM_WRAP_IFC(ISerialPortChangedEvent)
COM_WRAP_IFC(IParallelPortChangedEvent)
COM_WRAP_IFC(IStorageControllerChangedEvent)
COM_WRAP_IFC(IMediumChangedEvent)
COM_WRAP_IFC(IVRDEServerChangedEvent)
COM_WRAP_IFC(IVRDEServerInfoChangedEvent)
#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 0, 0)
COM_WRAP_IFC(IVideoCaptureChangedEvent)
#endif
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
COM_WRAP_IFC(IRecordingChangedEvent)
#endif
COM_WRAP_IFC(IUSBControllerChangedEvent)
COM_WRAP_IFC(ISharedFolderChangedEvent)
COM_WRAP_IFC(IEventSourceChangedEvent)
COM_WRAP_IFC(IBandwidthGroupChangedEvent)
COM_WRAP_IFC(IStorageDeviceChangedEvent)
COM_WRAP_IFC(IHostNameResolutionConfigurationChangeEvent)

VBox::COMPtr<VBox::INetworkAdapter>
VBox::INetworkAdapterChangedEvent::networkAdapter() const
{
    COMPtr<INetworkAdapter> result;
    COM_GetValue_Wrap(get_IFC(), NetworkAdapter, result);
    return result;
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 2, 0)
VBox::COMPtr<VBox::IAudioAdapter>
VBox::IAudioAdapterChangedEvent::audioAdapter() const
{
    COMPtr<IAudioAdapter> result;
    COM_GetValue_Wrap(get_IFC(), AudioAdapter, result);
    return result;
}
#endif

VBox::COMPtr<VBox::ISerialPort> VBox::ISerialPortChangedEvent::serialPort() const
{
    COMPtr<ISerialPort> result;
    COM_GetValue_Wrap(get_IFC(), SerialPort, result);
    return result;
}

VBox::COMPtr<VBox::IParallelPort>
VBox::IParallelPortChangedEvent::parallelPort() const
{
    COMPtr<IParallelPort> result;
    COM_GetValue_Wrap(get_IFC(), ParallelPort, result);
    return result;
}

VBox::COMPtr<VBox::IMediumAttachment>
VBox::IMediumChangedEvent::mediumAttachment() const
{
    COMPtr<IMediumAttachment> result;
    COM_GetValue_Wrap(get_IFC(), MediumAttachment, result);
    return result;
}

VBox::Scope VBox::ISharedFolderChangedEvent::scope() const
{
    COM_Enum(::Scope) result;
    COM_GetValue(get_IFC(), Scope, result);
    return static_cast<Scope>(result);
}

VBox::COMPtr<VBox::IEventListener> VBox::IEventSourceChangedEvent::listener() const
{
    COMPtr<IEventListener> result;
    COM_GetValue_Wrap(get_IFC(), Listener, result);
    return result;
}

bool VBox::IEventSourceChangedEvent::add() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Add, result);
    return result;
}

VBox::COMPtr<VBox::IBandwidthGroup>
VBox::IBandwidthGroupChangedEvent::bandwidthGroup() const
{
    COMPtr<IBandwidthGroup> result;
    COM_GetValue_Wrap(get_IFC(), BandwidthGroup, result);
    return result;
}

VBox::COMPtr<VBox::IMediumAttachment>
VBox::IStorageDeviceChangedEvent::storageDevice() const
{
    COMPtr<IMediumAttachment> result;
    COM_GetValue_Wrap(get_IFC(), StorageDevice, result);
    return result;
}

bool VBox::IStorageDeviceChangedEvent::removed() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Removed, result);
    return result;
}

bool VBox::IStorageDeviceChangedEvent::silent() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Silent, result);
    return result;
}
