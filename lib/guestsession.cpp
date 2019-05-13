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

const void *VBox::IGuestSession::get_IID()
{
    return reinterpret_cast<const void *>(&IID_IGuestSession);
}

VBox::COMString VBox::IGuestSession::user() const
{
    COMString result;
    COM_GetString(get_IFC(), User, result);
    return result;
}

VBox::COMString VBox::IGuestSession::domain() const
{
    COMString result;
    COM_GetString(get_IFC(), Domain, result);
    return result;
}

VBox::COMString VBox::IGuestSession::name() const
{
    COMString result;
    COM_GetString(get_IFC(), Name, result);
    return result;
}

uint32_t VBox::IGuestSession::id() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Id, result);
    return static_cast<uint32_t>(result);
}

uint32_t VBox::IGuestSession::timeout() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), Timeout, result);
    return static_cast<uint32_t>(result);
}

void VBox::IGuestSession::set_timeout(uint32_t value)
{
    COM_SetValue(get_IFC(), Timeout, value);
}

uint32_t VBox::IGuestSession::protocolVersion() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), ProtocolVersion, result);
    return static_cast<uint32_t>(result);
}

VBox::GuestSessionStatus VBox::IGuestSession::status() const
{
    COM_Enum(::GuestSessionStatus) result;
    COM_GetValue(get_IFC(), Status, result);
    return static_cast<GuestSessionStatus>(result);
}

std::vector<VBox::COMString> VBox::IGuestSession::environmentChanges() const
{
    std::vector<COMString> result;
    COM_GetStringArray(get_IFC(), EnvironmentChanges, result);
    return result;
}

void VBox::IGuestSession::set_environmentChanges(const std::vector<COMString> &value)
{
    COM_SetStringArray(get_IFC(), EnvironmentChanges, value);
}

std::vector<VBox::COMString> VBox::IGuestSession::environmentBase() const
{
    std::vector<COMString> result;
    COM_GetStringArray(get_IFC(), EnvironmentBase, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IGuestProcess>> VBox::IGuestSession::processes() const
{
    std::vector<COMPtr<IGuestProcess>> result;
    COM_GetArray_Wrap(get_IFC(), Processes, result);
    return result;
}

VBox::PathStyle VBox::IGuestSession::pathStyle() const
{
    COM_Enum(::PathStyle) result;
    COM_GetValue(get_IFC(), PathStyle, result);
    return static_cast<PathStyle>(result);
}

VBox::COMString VBox::IGuestSession::currentDirectory() const
{
    COMString result;
    COM_GetString(get_IFC(), CurrentDirectory, result);
    return result;
}

void VBox::IGuestSession::set_currentDirectory(const COMString &value)
{
    COM_SetString(get_IFC(), CurrentDirectory, value);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMString VBox::IGuestSession::userHome() const
{
    COMString result;
    COM_GetString(get_IFC(), UserHome, result);
    return result;
}

VBox::COMString VBox::IGuestSession::userDocuments() const
{
    COMString result;
    COM_GetString(get_IFC(), UserDocuments, result);
    return result;
}
#endif

std::vector<VBox::COMPtr<VBox::IGuestDirectory>> VBox::IGuestSession::directories() const
{
    std::vector<COMPtr<IGuestDirectory>> result;
    COM_GetArray_Wrap(get_IFC(), Directories, result);
    return result;
}

std::vector<VBox::COMPtr<VBox::IGuestFile>> VBox::IGuestSession::files() const
{
    std::vector<COMPtr<IGuestFile>> result;
    COM_GetArray_Wrap(get_IFC(), Files, result);
    return result;
}

VBox::COMPtr<VBox::IEventSource> VBox::IGuestSession::eventSource() const
{
    COMPtr<IEventSource> result;
    COM_GetValue_Wrap(get_IFC(), EventSource, result);
    return result;
}

void VBox::IGuestSession::close()
{
    auto rc = get_IFC()->Close();
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::copyFromGuest(
        const std::vector<COMString> &sources, const std::vector<COMString> &filters,
        const std::vector<COMString> &flags, const COMString &destination)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pSources(sources);
    COM_StringArrayProxy pFilters(filters);
    COM_StringArrayProxy pFlags(flags);
    COM_StringProxy pDestination(destination);

    auto rc = get_IFC()->CopyFromGuest(COM_ArrayParameter(pSources),
                COM_ArrayParameter(pFilters), COM_ArrayParameter(pFlags),
                pDestination.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::copyToGuest(
        const std::vector<COMString> &sources, const std::vector<COMString> &filters,
        const std::vector<COMString> &flags, const COMString &destination)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pSources(sources);
    COM_StringArrayProxy pFilters(filters);
    COM_StringArrayProxy pFlags(flags);
    COM_StringProxy pDestination(destination);

    auto rc = get_IFC()->CopyToGuest(COM_ArrayParameter(pSources),
                COM_ArrayParameter(pFilters), COM_ArrayParameter(pFlags),
                pDestination.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::directoryCopy(
        const COMString &source, const COMString &destination,
        const std::vector<DirectoryCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_ArrayProxy<COM_Enum(::DirectoryCopyFlag)> pFlags(flags);
#else
    COM_ArrayProxy<COM_Enum(::DirectoryCopyFlags)> pFlags(flags);
#endif

    auto rc = get_IFC()->DirectoryCopy(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::directoryCopyFromGuest(
        const COMString &source, const COMString &destination,
        const std::vector<DirectoryCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_ArrayProxy<COM_Enum(::DirectoryCopyFlag)> pFlags(flags);
#else
    COM_ArrayProxy<COM_Enum(::DirectoryCopyFlags)> pFlags(flags);
#endif

    auto rc = get_IFC()->DirectoryCopyFromGuest(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::directoryCopyToGuest(
        const COMString &source, const COMString &destination,
        const std::vector<DirectoryCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_ArrayProxy<COM_Enum(::DirectoryCopyFlag)> pFlags(flags);
#else
    COM_ArrayProxy<COM_Enum(::DirectoryCopyFlags)> pFlags(flags);
#endif

    auto rc = get_IFC()->DirectoryCopyToGuest(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IGuestSession::directoryCreate(const COMString &path, uint32_t mode,
        const std::vector<DirectoryCreateFlag> &flags)
{
    COM_StringProxy pPath(path);
    COM_ArrayProxy<COM_Enum(::DirectoryCreateFlag)> pFlags(flags);

    auto rc = get_IFC()->DirectoryCreate(pPath.m_text, mode,
                COM_ArrayParameter(pFlags));
    COM_ERROR_CHECK(rc);
}

VBox::COMString VBox::IGuestSession::directoryCreateTemp(
        const COMString &templateName, uint32_t mode, const COMString &path,
        bool secure)
{
    COM_StringProxy pResult;
    COM_StringProxy pTemplateName(templateName);
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->DirectoryCreateTemp(pTemplateName.m_text, mode,
                pPath.m_text, secure, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

bool VBox::IGuestSession::directoryExists(const COMString &path, bool followSymlinks)
{
    COM_Bool cResult;
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->DirectoryExists(pPath.m_text, followSymlinks, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMPtr<VBox::IGuestDirectory> VBox::IGuestSession::directoryOpen(
        const COMString &path, const COMString &filter,
        const std::vector<DirectoryOpenFlag> &flags)
{
    ::IGuestDirectory *cResult = nullptr;
    COM_StringProxy pPath(path);
    COM_StringProxy pFilter(filter);
    COM_ArrayProxy<COM_Enum(::DirectoryOpenFlag)> pFlags(flags);

    auto rc = get_IFC()->DirectoryOpen(pPath.m_text, pFilter.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestDirectory>::wrap(cResult);
}

void VBox::IGuestSession::directoryRemove(const COMString &path)
{
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->DirectoryRemove(pPath.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::directoryRemoveRecursive(
        const COMString &path, const std::vector<DirectoryRemoveRecFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pPath(path);
    COM_ArrayProxy<COM_Enum(::DirectoryRemoveRecFlag)> pFlags(flags);

    auto rc = get_IFC()->DirectoryRemoveRecursive(pPath.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

void VBox::IGuestSession::environmentScheduleSet(const COMString &name,
        const COMString &value)
{
    COM_StringProxy pName(name);
    COM_StringProxy pValue(value);

    auto rc = get_IFC()->EnvironmentScheduleSet(pName.m_text, pValue.m_text);
    COM_ERROR_CHECK(rc);
}

void VBox::IGuestSession::environmentScheduleUnset(const COMString &name)
{
    COM_StringProxy pName(name);

    auto rc = get_IFC()->EnvironmentScheduleUnset(pName.m_text);
    COM_ERROR_CHECK(rc);
}

VBox::COMString VBox::IGuestSession::environmentGetBaseVariable(
        const COMString &name)
{
    COM_StringProxy pResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->EnvironmentGetBaseVariable(pName.m_text, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

bool VBox::IGuestSession::environmentDoesBaseVariableExist(const COMString &name)
{
    COM_Bool cResult;
    COM_StringProxy pName(name);

    auto rc = get_IFC()->EnvironmentDoesBaseVariableExist(pName.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fileCopy(const COMString &source,
        const COMString &destination, const std::vector<FileCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
    COM_ArrayProxy<COM_Enum(::FileCopyFlag)> pFlags(flags);

    auto rc = get_IFC()->FileCopy(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fileCopyFromGuest(
        const COMString &source, const COMString &destination,
        const std::vector<FileCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
    COM_ArrayProxy<COM_Enum(::FileCopyFlag)> pFlags(flags);

    auto rc = get_IFC()->FileCopyFromGuest(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fileCopyToGuest(
        const COMString &source, const COMString &destination,
        const std::vector<FileCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
    COM_ArrayProxy<COM_Enum(::FileCopyFlag)> pFlags(flags);

    auto rc = get_IFC()->FileCopyToGuest(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IGuestFile> VBox::IGuestSession::fileCreateTemp(
        const COMString &templateName, uint32_t mode, const COMString &path,
        bool secure)
{
    ::IGuestFile *cResult = nullptr;
    COM_StringProxy pTemplateName(templateName);
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->FileCreateTemp(pTemplateName.m_text, mode, pPath.m_text,
                secure, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestFile>::wrap(cResult);
}

bool VBox::IGuestSession::fileExists(const COMString &path, bool followSymlinks)
{
    COM_Bool cResult;
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->FileExists(pPath.m_text, followSymlinks, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMPtr<VBox::IGuestFile> VBox::IGuestSession::fileOpen(
        const COMString &path, FileAccessMode accessMode,
        FileOpenAction openAction, uint32_t creationMode)
{
    ::IGuestFile *cResult = nullptr;
    COM_StringProxy pPath(path);
    auto cAccessMode = static_cast<COM_Enum(::FileAccessMode)>(accessMode);
    auto cOpenAction = static_cast<COM_Enum(::FileOpenAction)>(openAction);

    auto rc = get_IFC()->FileOpen(pPath.m_text, cAccessMode, cOpenAction,
                creationMode, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestFile>::wrap(cResult);
}

VBox::COMPtr<VBox::IGuestFile> VBox::IGuestSession::fileOpenEx(const COMString &path,
        FileAccessMode accessMode, FileOpenAction openAction,
        FileSharingMode sharingMode, uint32_t creationMode,
        const std::vector<FileOpenExFlag> &flags)
{
    ::IGuestFile *cResult = nullptr;
    COM_StringProxy pPath(path);
    auto cAccessMode = static_cast<COM_Enum(::FileAccessMode)>(accessMode);
    auto cOpenAction = static_cast<COM_Enum(::FileOpenAction)>(openAction);
    auto cSharingMode = static_cast<COM_Enum(::FileSharingMode)>(sharingMode);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_ArrayProxy<COM_Enum(::FileOpenExFlag)> pFlags(flags);
#else
    COM_ArrayProxy<COM_Enum(::FileOpenExFlags)> pFlags(flags);
#endif

    auto rc = get_IFC()->FileOpenEx(pPath.m_text, cAccessMode, cOpenAction,
                cSharingMode, creationMode, COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestFile>::wrap(cResult);
}

int64_t VBox::IGuestSession::fileQuerySize(const COMString &path,
        bool followSymlinks)
{
    COM_Long64 cResult;
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->FileQuerySize(pPath.m_text, followSymlinks, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<int64_t>(cResult);
}

bool VBox::IGuestSession::fsObjExists(const COMString &path, bool followSymlinks)
{
    COM_Bool cResult;
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->FsObjExists(pPath.m_text, followSymlinks, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMPtr<VBox::IGuestFsObjInfo> VBox::IGuestSession::fsObjQueryInfo(
        const COMString &path, bool followSymlinks)
{
    ::IGuestFsObjInfo *cResult = nullptr;
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->FsObjQueryInfo(pPath.m_text, followSymlinks, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestFsObjInfo>::wrap(cResult);
}

void VBox::IGuestSession::fsObjRemove(const COMString &path)
{
    COM_StringProxy pPath(path);

    auto rc = get_IFC()->FsObjRemove(pPath.m_text);
    COM_ERROR_CHECK(rc);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fsObjRemoveArray(
        const std::vector<COMString> &path)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pPath(path);

    auto rc = get_IFC()->FsObjRemoveArray(COM_ArrayParameter(pPath), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif

void VBox::IGuestSession::fsObjRename(const COMString &oldPath,
        const COMString &newPath, const std::vector<FsObjRenameFlag> &flags)
{
    COM_StringProxy pOldPath(oldPath);
    COM_StringProxy pNewPath(newPath);
    COM_ArrayProxy<COM_Enum(::FsObjRenameFlag)> pFlags(flags);

    auto rc = get_IFC()->FsObjRename(pOldPath.m_text, pNewPath.m_text,
                COM_ArrayParameter(pFlags));
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fsObjMove(
        const COMString &source, const COMString &destination,
        const std::vector<FsObjMoveFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringProxy pSource(source);
    COM_StringProxy pDestination(destination);
#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
    COM_ArrayProxy<COM_Enum(::FsObjMoveFlag)> pFlags(flags);
#else
    COM_ArrayProxy<COM_Enum(::FsObjMoveFlags)> pFlags(flags);
#endif

    auto rc = get_IFC()->FsObjMove(pSource.m_text, pDestination.m_text,
                COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(6, 0, 0)
VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fsObjMoveArray(
        const std::vector<COMString> &source, const COMString &destination,
        const std::vector<FsObjMoveFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pSource(source);
    COM_StringProxy pDestination(destination);
    COM_ArrayProxy<COM_Enum(::FsObjMoveFlag)> pFlags(flags);

    auto rc = get_IFC()->FsObjMoveArray(COM_ArrayParameter(pSource),
                pDestination.m_text, COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}

VBox::COMPtr<VBox::IProgress> VBox::IGuestSession::fsObjCopyArray(
        const std::vector<COMString> &source, const COMString &destination,
        const std::vector<FileCopyFlag> &flags)
{
    ::IProgress *cResult = nullptr;
    COM_StringArrayProxy pSource(source);
    COM_StringProxy pDestination(destination);
    COM_ArrayProxy<COM_Enum(::FileCopyFlag)> pFlags(flags);

    auto rc = get_IFC()->FsObjCopyArray(COM_ArrayParameter(pSource),
                pDestination.m_text, COM_ArrayParameter(pFlags), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IProgress>::wrap(cResult);
}
#endif

void VBox::IGuestSession::fsObjSetACL(const COMString &path, bool followSymlinks,
        const COMString &acl, uint32_t mode)
{
    COM_StringProxy pPath(path);
    COM_StringProxy pAcl(acl);

    auto rc = get_IFC()->FsObjSetACL(pPath.m_text, followSymlinks, pAcl.m_text, mode);
    COM_ERROR_CHECK(rc);
}

VBox::COMPtr<VBox::IGuestProcess> VBox::IGuestSession::processCreate(
        const COMString &executable, const std::vector<COMString> &arguments,
        const std::vector<COMString> &environmentChanges,
        const std::vector<ProcessCreateFlag> &flags, uint32_t timeoutMS)
{
    ::IGuestProcess *cResult = nullptr;
    COM_StringProxy pExecutable(executable);
    COM_StringArrayProxy pArguments(arguments);
    COM_StringArrayProxy pEnvironmentChanges(environmentChanges);
    COM_ArrayProxy<COM_Enum(::ProcessCreateFlag)> pFlags(flags);

    auto rc = get_IFC()->ProcessCreate(pExecutable.m_text, COM_ArrayParameter(pArguments),
                COM_ArrayParameter(pEnvironmentChanges), COM_ArrayParameter(pFlags),
                timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestProcess>::wrap(cResult);
}

VBox::COMPtr<VBox::IGuestProcess> VBox::IGuestSession::processCreateEx(
        const COMString &executable, const std::vector<COMString> &arguments,
        const std::vector<COMString> &environmentChanges,
        const std::vector<ProcessCreateFlag> &flags, uint32_t timeoutMS,
        ProcessPriority priority, const std::vector<int32_t> &affinity)
{
    ::IGuestProcess *cResult = nullptr;
    COM_StringProxy pExecutable(executable);
    COM_StringArrayProxy pArguments(arguments);
    COM_StringArrayProxy pEnvironmentChanges(environmentChanges);
    COM_ArrayProxy<COM_Enum(::ProcessCreateFlag)> pFlags(flags);
    auto cPriority = static_cast<COM_Enum(::ProcessPriority)>(priority);
    COM_ArrayProxy<COM_Long> pAffinity(affinity);

    auto rc = get_IFC()->ProcessCreateEx(pExecutable.m_text,
                COM_ArrayParameter(pArguments), COM_ArrayParameter(pEnvironmentChanges),
                COM_ArrayParameter(pFlags), timeoutMS, cPriority,
                COM_ArrayParameter(pAffinity), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestProcess>::wrap(cResult);
}

VBox::COMPtr<VBox::IGuestProcess> VBox::IGuestSession::processGet(uint32_t pid)
{
    ::IGuestProcess *cResult = nullptr;

    auto rc = get_IFC()->ProcessGet(pid, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IGuestProcess>::wrap(cResult);
}

void VBox::IGuestSession::symlinkCreate(const COMString &symlink,
        const COMString &target, SymlinkType type)
{
    COM_StringProxy pSymlink(symlink);
    COM_StringProxy pTarget(target);
    auto cType = static_cast<COM_Enum(::SymlinkType)>(type);

    auto rc = get_IFC()->SymlinkCreate(pSymlink.m_text, pTarget.m_text, cType);
    COM_ERROR_CHECK(rc);
}

bool VBox::IGuestSession::symlinkExists(const COMString &symlink)
{
    COM_Bool cResult;
    COM_StringProxy pSymlink(symlink);

    auto rc = get_IFC()->SymlinkExists(pSymlink.m_text, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMString VBox::IGuestSession::symlinkRead(const COMString &symlink,
        const std::vector<SymlinkReadFlag> &flags)
{
    COM_StringProxy pResult;
    COM_StringProxy pSymlink(symlink);
    COM_ArrayProxy<COM_Enum(::SymlinkReadFlag)> pFlags(flags);

    auto rc = get_IFC()->SymlinkRead(pSymlink.m_text, COM_ArrayParameter(pFlags),
                &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}

VBox::GuestSessionWaitResult VBox::IGuestSession::waitFor(uint32_t waitFor,
        uint32_t timeoutMS)
{
    COM_Enum(::GuestSessionWaitResult) cResult;

    auto rc = get_IFC()->WaitFor(waitFor, timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<GuestSessionWaitResult>(cResult);
}

VBox::GuestSessionWaitResult VBox::IGuestSession::waitForArray(
        const std::vector<GuestSessionWaitForFlag> &waitFor, uint32_t timeoutMS)
{
    COM_Enum(::GuestSessionWaitResult) cResult;
    COM_ArrayProxy<COM_Enum(::GuestSessionWaitForFlag)> pWaitFor(waitFor);

    auto rc = get_IFC()->WaitForArray(COM_ArrayParameter(pWaitFor), timeoutMS, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<GuestSessionWaitResult>(cResult);
}
