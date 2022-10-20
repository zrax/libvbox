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
COM_WRAP_IFC(ICloudClient)

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
std::vector<VBox::COMPtr<VBox::ICloudMachine>> VBox::ICloudClient::cloudMachineList() const
{
    std::vector<COMPtr<ICloudMachine>> result;
    COM_GetArray_Wrap(get_IFC(), CloudMachineList, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::ICloudMachine>> VBox::ICloudClient::cloudMachineStubList() const
{
    std::vector<COMPtr<ICloudMachine>> result;
    COM_GetArray_Wrap(get_IFC(), CloudMachineStubList, result);
    return result;
}
#endif

#if VirtualBoxSDK_VERSION < VBox_MAKE_VERSION(6, 1, 0)
std::u16string VBox::ICloudClient::getExportLaunchParameters() const
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->GetExportLaunchParameters(&pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

void VBox::ICloudClient::exportLaunchVM(
        const COMPtr<IVirtualSystemDescription> &description,
        const COMPtr<IProgress> &progress, const COMPtr<IVirtualBox> &virtualBox)
{
    auto rc = get_IFC()->ExportLaunchVM(description->get_IFC(), progress->get_IFC(),
                virtualBox->get_IFC());
    COM_ERROR_CHECK(rc);
}
#else
VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getExportDescriptionForm(
        const COMPtr<IVirtualSystemDescription> &description,
        COMPtr<IVirtualSystemDescriptionForm> *form)
{
    ::IProgress *cResult = nullptr;
    ::IVirtualSystemDescriptionForm *cForm = nullptr;

    auto rc = get_IFC()->GetExportDescriptionForm(description->get_IFC(),
                &cForm, &cResult);
    COM_ERROR_CHECK(rc);

    if (form)
        *form = COMPtr<IVirtualSystemDescriptionForm>::wrap(cForm);
    else if (cForm)
        cForm->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::ICloudClient::exportVM(const COMPtr<IVirtualSystemDescription> &description,
        const COMPtr<IProgress> &progress)
{
    auto rc = get_IFC()->ExportVM(description->get_IFC(), progress->get_IFC());
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getLaunchDescriptionForm(
        const COMPtr<IVirtualSystemDescription> &description,
        COMPtr<IVirtualSystemDescriptionForm> *form)
{
    ::IProgress *cResult = nullptr;
    ::IVirtualSystemDescriptionForm *cForm = nullptr;

    auto rc = get_IFC()->GetLaunchDescriptionForm(description->get_IFC(),
                &cForm, &cResult);
    COM_ERROR_CHECK(rc);

    if (form)
        *form = COMPtr<IVirtualSystemDescriptionForm>::wrap(cForm);
    else if (cForm)
        cForm->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::launchVM(
        const COMPtr<IVirtualSystemDescription> &description)
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->LaunchVM(description->get_IFC(), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getImportDescriptionForm(
        const COMPtr<IVirtualSystemDescription> &description,
        COMPtr<IVirtualSystemDescriptionForm> *form)
{
    ::IProgress *cResult = nullptr;
    ::IVirtualSystemDescriptionForm *cForm = nullptr;

    auto rc = get_IFC()->GetImportDescriptionForm(description->get_IFC(),
                &cForm, &cResult);
    COM_ERROR_CHECK(rc);

    if (form)
        *form = COMPtr<IVirtualSystemDescriptionForm>::wrap(cForm);
    else if (cForm)
        cForm->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::ICloudClient::importInstance(
        const COMPtr<IVirtualSystemDescription> &description,
        const COMPtr<IProgress> &progress)
{
    auto rc = get_IFC()->ImportInstance(description->get_IFC(), progress->get_IFC());
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::ICloudMachine> VBox::ICloudClient::getCloudMachine(
        const std::u16string &id)
{
    ::ICloudMachine *cResult = nullptr;
    COM_StringProxy pId(id);

    auto rc = get_IFC()->GetCloudMachine(pId.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<ICloudMachine>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::readCloudMachineList()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->ReadCloudMachineList(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::readCloudMachineStubList()
{
    ::IProgress *cResult = nullptr;

    auto rc = get_IFC()->ReadCloudMachineStubList(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::addCloudMachine(
        const std::u16string &instanceId, COMPtr<ICloudMachine> *machine)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pInstanceId(instanceId);
    ::ICloudMachine *cMachine = nullptr;

    auto rc = get_IFC()->AddCloudMachine(pInstanceId.m_text, &cMachine, &cResult);
    COM_ERROR_CHECK(rc);

    if (machine)
        *machine = COMPtr<ICloudMachine>::wrap(cMachine);
    else if (cMachine)
        cMachine->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::createCloudMachine(
        const COMPtr<IVirtualSystemDescription> &description,
        COMPtr<ICloudMachine> *machine)
{
    ::IProgress *cResult = nullptr;
    ::ICloudMachine *cMachine = nullptr;

    auto rc = get_IFC()->CreateCloudMachine(description->get_IFC(), &cMachine, &cResult);
    COM_ERROR_CHECK(rc);

    if (machine)
        *machine = COMPtr<ICloudMachine>::wrap(cMachine);
    else if (cMachine)
        cMachine->Release();
    return COMPtr<IProgress>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::listInstances(
        const std::vector<CloudMachineState> &machineState,
        COMPtr<IStringArray> *returnNames, COMPtr<IStringArray> *returnIds) const
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::CloudMachineState)> pMachineState(machineState);
    ::IStringArray *cReturnNames = nullptr;
    ::IStringArray *cReturnIds = nullptr;

    auto rc = get_IFC()->ListInstances(COM_ArrayParameter(pMachineState),
                &cReturnNames, &cReturnIds, &cResult);
    COM_ERROR_CHECK(rc);

    if (returnNames)
        *returnNames = COMPtr<IStringArray>::wrap(cReturnNames);
    else if (cReturnNames)
        cReturnNames->Release();
    if (returnIds)
        *returnIds = COMPtr<IStringArray>::wrap(cReturnIds);
    else if (cReturnIds)
        cReturnIds->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::listSourceInstances(
        COMPtr<IStringArray> *returnNames, COMPtr<IStringArray> *returnIds) const
{
    ::IProgress *cResult = nullptr;
    ::IStringArray *cReturnNames = nullptr;
    ::IStringArray *cReturnIds = nullptr;

    auto rc = get_IFC()->ListSourceInstances(&cReturnNames, &cReturnIds, &cResult);
    COM_ERROR_CHECK(rc);

    if (returnNames)
        *returnNames = COMPtr<IStringArray>::wrap(cReturnNames);
    else if (cReturnNames)
        cReturnNames->Release();
    if (returnIds)
        *returnIds = COMPtr<IStringArray>::wrap(cReturnIds);
    else if (cReturnIds)
        cReturnIds->Release();
    return COMPtr<IProgress>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::listImages(
        const std::vector<CloudImageState> &imageState,
        COMPtr<IStringArray> *returnNames, COMPtr<IStringArray> *returnIds) const
{
    ::IProgress *cResult = nullptr;
    COM_ArrayProxy<COM_Enum(::CloudImageState)> pImageState(imageState);
    ::IStringArray *cReturnNames = nullptr;
    ::IStringArray *cReturnIds = nullptr;

    auto rc = get_IFC()->ListImages(COM_ArrayParameter(pImageState),
                &cReturnNames, &cReturnIds, &cResult);
    COM_ERROR_CHECK(rc);

    if (returnNames)
        *returnNames = COMPtr<IStringArray>::wrap(cReturnNames);
    else if (cReturnNames)
        cReturnNames->Release();
    if (returnIds)
        *returnIds = COMPtr<IStringArray>::wrap(cReturnIds);
    else if (cReturnIds)
        cReturnIds->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::listBootVolumes(
        COMPtr<IStringArray> *returnNames, COMPtr<IStringArray> *returnIds) const
{
    ::IProgress *cResult = nullptr;
    ::IStringArray *cReturnNames = nullptr;
    ::IStringArray *cReturnIds = nullptr;

    auto rc = get_IFC()->ListBootVolumes(&cReturnNames, &cReturnIds, &cResult);
    COM_ERROR_CHECK(rc);

    if (returnNames)
        *returnNames = COMPtr<IStringArray>::wrap(cReturnNames);
    else if (cReturnNames)
        cReturnNames->Release();
    if (returnIds)
        *returnIds = COMPtr<IStringArray>::wrap(cReturnIds);
    else if (cReturnIds)
        cReturnIds->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::listSourceBootVolumes(
        COMPtr<IStringArray> *returnNames, COMPtr<IStringArray> *returnIds) const
{
    ::IProgress *cResult = nullptr;
    ::IStringArray *cReturnNames = nullptr;
    ::IStringArray *cReturnIds = nullptr;

    auto rc = get_IFC()->ListSourceBootVolumes(&cReturnNames, &cReturnIds, &cResult);
    COM_ERROR_CHECK(rc);

    if (returnNames)
        *returnNames = COMPtr<IStringArray>::wrap(cReturnNames);
    else if (cReturnNames)
        cReturnNames->Release();
    if (returnIds)
        *returnIds = COMPtr<IStringArray>::wrap(cReturnIds);
    else if (cReturnIds)
        cReturnIds->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::listVnicAttachments(
        const std::vector<std::u16string> &parameters,
        COMPtr<IStringArray> *returnVnicAttachmentIds,
        COMPtr<IStringArray> *returnVnicIds) const
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pParameters(parameters);
    ::IStringArray *cReturnVnicAttachmentIds = nullptr;
    ::IStringArray *cReturnVnicIds = nullptr;

    auto rc = get_IFC()->ListVnicAttachments(COM_ArrayParameter(pParameters),
                &cReturnVnicAttachmentIds, &cReturnVnicIds, &cResult);
    COM_ERROR_CHECK(rc);

    if (returnVnicAttachmentIds)
        *returnVnicAttachmentIds = COMPtr<IStringArray>::wrap(cReturnVnicAttachmentIds);
    else if (cReturnVnicAttachmentIds)
        cReturnVnicAttachmentIds->Release();
    if (returnVnicIds)
        *returnVnicIds = COMPtr<IStringArray>::wrap(cReturnVnicIds);
    else if (cReturnVnicIds)
        cReturnVnicIds->Release();
    return COMPtr<IProgress>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getInstanceInfo(
        const std::u16string &uid,
        const COMPtr<IVirtualSystemDescription> &description) const
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);

    auto rc = get_IFC()->GetInstanceInfo(pUid.m_text, description->get_IFC(),
                &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::startInstance(
        const std::u16string &uid)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);

    auto rc = get_IFC()->StartInstance(pUid.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::pauseInstance(
        const std::u16string &uid)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);

    auto rc = get_IFC()->PauseInstance(pUid.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::terminateInstance(
        const std::u16string &uid)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);

    auto rc = get_IFC()->TerminateInstance(pUid.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::createImage(
        std::vector<std::u16string> &parameters)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pParameters(parameters);

    auto rc = get_IFC()->CreateImage(COM_ArrayParameter(pParameters), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::exportImage(
        const COMPtr<IMedium> &image, const std::vector<std::u16string> &parameters)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pParameters(parameters);

    auto rc = get_IFC()->ExportImage(image->get_IFC(), COM_ArrayParameter(pParameters),
                &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::importImage(
        const std::u16string &uid, const std::vector<std::u16string> &parameters)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);
    COM_StringArrayProxy pParameters(parameters);

    auto rc = get_IFC()->ImportImage(pUid.m_text, COM_ArrayParameter(pParameters),
                &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::deleteImage(const std::u16string &uid)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);

    auto rc = get_IFC()->DeleteImage(pUid.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getImageInfo(
        const std::u16string &uid, COMPtr<IStringArray> *infoArray) const
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);
    ::IStringArray *cInfoArray = nullptr;

    auto rc = get_IFC()->GetImageInfo(pUid.m_text, &cInfoArray, &cResult);
    COM_ERROR_CHECK(rc);

    if (infoArray)
        *infoArray = COMPtr<IStringArray>::wrap(cInfoArray);
    else if (cInfoArray)
        cInfoArray->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::startCloudNetworkGateway(
        const COMPtr<ICloudNetwork> &network, const std::u16string &sshPublicKey,
        COMPtr<ICloudNetworkGatewayInfo> *gatewayInfo)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSshPublicKey(sshPublicKey);
    ::ICloudNetworkGatewayInfo *cGatewayInfo = nullptr;

    auto rc = get_IFC()->StartCloudNetworkGateway(network->get_IFC(),
                pSshPublicKey.m_text, &cGatewayInfo, &cResult);
    COM_ERROR_CHECK(rc);

    if (gatewayInfo)
        *gatewayInfo = COMPtr<ICloudNetworkGatewayInfo>::wrap(cGatewayInfo);
    else if (cGatewayInfo)
        cGatewayInfo->Release();
    return COMPtr<IProgress>::wrap(cResult);
}
#endif

#endif

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 1, 12)
VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::setupCloudNetworkEnvironment(
        const std::u16string& tunnelNetworkName,
        const std::u16string& tunnelNetworkRange,
        const std::u16string& gatewayOsName, const std::u16string& gatewayOsVersion,
        const std::u16string& gatewayShape,
        COMPtr<ICloudNetworkEnvironmentInfo> *networkEnvironmentInfo)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pTunnelNetworkName(tunnelNetworkName);
    COM_StringProxy pTunnelNetworkRange(tunnelNetworkRange);
    COM_StringProxy pGatewayOsName(gatewayOsName);
    COM_StringProxy pGatewayOsVersion(gatewayOsVersion);
    COM_StringProxy pGatewayShape(gatewayShape);
    ::ICloudNetworkEnvironmentInfo *cNetworkEnvironmentInfo = nullptr;

    auto rc = get_IFC()->SetupCloudNetworkEnvironment(pTunnelNetworkName.m_text,
                pTunnelNetworkRange.m_text, pGatewayOsName.m_text,
                pGatewayOsVersion.m_text, pGatewayShape.m_text,
                &cNetworkEnvironmentInfo, &cResult);
    COM_ERROR_CHECK(rc);

    if (networkEnvironmentInfo)
        *networkEnvironmentInfo = COMPtr<ICloudNetworkEnvironmentInfo>::wrap(cNetworkEnvironmentInfo);
    else if (cNetworkEnvironmentInfo)
        cNetworkEnvironmentInfo->Release();
    return COMPtr<IProgress>::wrap(cResult);
}
#endif


#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getVnicInfo(
        const std::u16string &uid, COMPtr<IStringArray> *infoArray) const
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pUid(uid);
    ::IStringArray *cInfoArray = nullptr;

    auto rc = get_IFC()->GetVnicInfo(pUid.m_text, &cInfoArray, &cResult);
    COM_ERROR_CHECK(rc);

    if (infoArray)
        *infoArray = COMPtr<IStringArray>::wrap(cInfoArray);
    else if (cInfoArray)
        cInfoArray->Release();
    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::ICloudClient::getSubnetSelectionForm(
        const COMPtr<IVirtualSystemDescription> &description,
        COMPtr<IVirtualSystemDescriptionForm> *form)
{
    ::IProgress *cResult = nullptr;
    ::IVirtualSystemDescriptionForm *cForm = nullptr;

    auto rc = get_IFC()->GetSubnetSelectionForm(description->get_IFC(), &cForm, &cResult);
    COM_ERROR_CHECK(rc);

    if (form)
        *form = COMPtr<IVirtualSystemDescriptionForm>::wrap(cForm);
    else if (cForm)
        cForm->Release();
    return COMPtr<IProgress>::wrap(cResult);

}
#endif
