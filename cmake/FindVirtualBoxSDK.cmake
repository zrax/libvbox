# This file is part of libvbox
# Copyright (C) 2019  Michael Hansen
#
# libvbox is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# libvbox is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with libvbox; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

set(VirtualBoxSDK_DIR "" CACHE STRING "Path to the VirtualBox SDK")

if(WIN32)

    # Use MSCOM
    find_path(VirtualBoxSDK_INCLUDE_DIR
        NAMES VirtualBox.h
        HINTS "${VirtualBoxSDK_DIR}/bindings/mscom/include"
    )
    find_path(VirtualBoxSDK_IDL_DIR
        NAMES VirtualBox.idl
        HINTS "${VirtualBoxSDK_DIR}/bindings/mscom/idl"
    )
    find_file(VirtualBoxSDK_IID_LIB
        NAMES VirtualBox_i.c
        HINTS "${VirtualBoxSDK_DIR}/bindings/mscom/lib"
    )

    mark_as_advanced(
        VirtualBoxSDK_INCLUDE_DIR
        VirtualBoxSDK_IDL_DIR
        VirtualBoxSDK_IID_LIB
    )

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(VirtualBoxSDK
        REQUIRED_VARS VirtualBoxSDK_INCLUDE_DIR
                      VirtualBoxSDK_IDL_DIR
                      VirtualBoxSDK_IID_LIB
    )

    set(VirtualBoxSDK_RT_PLATFORM RT_OS_WINDOWS)

    if(VirtualBoxSDK_FOUND)
        set(VirtualBoxSDK_COM_FLAVOR MSCOM)
        list(APPEND VirtualBoxSDK_DEFINITIONS ${VirtualBoxSDK_RT_PLATFORM})

        set(VirtualBoxSDK_INCLUDE_DIRS
            "${VirtualBoxSDK_INCLUDE_DIR}"
        )

        if(NOT TARGET VirtualBox::SDK)
            add_library(VirtualBox::SDK INTERFACE IMPORTED)
            set_target_properties(VirtualBox::SDK PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${VirtualBoxSDK_INCLUDE_DIRS}"
                INTERFACE_COMPILE_DEFINITIONS "${VirtualBoxSDK_DEFINITIONS}"
            )
        endif()
    endif()

else()

    # Use XPCOM
    find_path(VirtualBoxSDK_INCLUDE_DIR
        NAMES VirtualBox_XPCOM.h
        HINTS "${VirtualBoxSDK_DIR}/bindings/xpcom/include"
    )
    find_path(VirtualBoxSDK_IDL_DIR
        NAMES VirtualBox_XPCOM.idl
        HINTS "${VirtualBoxSDK_DIR}/bindings/xpcom/idl"
    )
    find_file(VirtualBoxSDK_IID_LIB
        NAMES VirtualBox_i.c
        HINTS "${VirtualBoxSDK_DIR}/bindings/xpcom/lib"
    )

    find_library(VirtualBox_XPCOM_LIB
        NAMES VBoxXPCOM
        HINTS /usr/lib/virtualbox
              /usr/local/lib/virtualbox
              /opt/VirtualBox/lib
    )

    mark_as_advanced(
        VirtualBoxSDK_INCLUDE_DIR
        VirtualBoxSDK_IDL_DIR
        VirtualBoxSDK_IID_LIB
        VirtualBox_XPCOM_LIB
    )

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(VirtualBoxSDK
        REQUIRED_VARS VirtualBoxSDK_INCLUDE_DIR
                      VirtualBoxSDK_IDL_DIR
                      VirtualBoxSDK_IID_LIB
                      VirtualBox_XPCOM_LIB
    )

    find_program(CMAKE_UNAME uname /bin /usr/bin /usr/local/bin)
    mark_as_advanced(CMAKE_UNAME)
    if(CMAKE_UNAME)
        exec_program(${CMAKE_UNAME} ARGS -s OUTPUT_VARIABLE _UNAME_SYSTEM)
        if(_UNAME_SYSTEM STREQUAL "Linux")
            set(VirtualBoxSDK_RT_PLATFORM RT_OS_LINUX)
        elseif(_UNAME_SYSTEM STREQUAL "FreeBSD")
            set(VirtualBoxSDK_RT_PLATFORM RT_OS_FREEBSD)
        elseif(_UNAME_SYSTEM STREQUAL "NetBSD")
            set(VirtualBoxSDK_RT_PLATFORM RT_OS_NETBSD)
        elseif(_UNAME_SYSTEM STREQUAL "OpenBSD")
            set(VirtualBoxSDK_RT_PLATFORM RT_OS_OPENBSD)
        elseif(_UNAME_SYSTEM STREQUAL "SunOS")
            set(VirtualBoxSDK_RT_PLATFORM RT_OS_SOLARIS)
        elseif(_UNAME_SYSTEM STREQUAL "Darwin")
            set(VirtualBoxSDK_RT_PLATFORM RT_OS_DARWIN)
        else()
            message(FATAL_ERROR "Unsupported OS: ${_UNAME_SYSTEM}")
        endif()
    else()
        message(FATAL_ERROR "Could not determine host OS")
    endif()

    if(VirtualBoxSDK_FOUND)
        set(VirtualBoxSDK_COM_FLAVOR XPCOM)
        list(APPEND VirtualBoxSDK_DEFINITIONS ${VirtualBoxSDK_RT_PLATFORM})

        set(VirtualBoxSDK_INCLUDE_DIRS
            "${VirtualBoxSDK_INCLUDE_DIR}"
            "${VirtualBoxSDK_INCLUDE_DIR}/nsprpub"
            "${VirtualBoxSDK_INCLUDE_DIR}/string"
            "${VirtualBoxSDK_INCLUDE_DIR}/xpcom"
            "${VirtualBoxSDK_INCLUDE_DIR}/ipcd"
        )

        try_compile(VBOX_WITH_XPCOM_NAMESPACE_CLEANUP
            "${CMAKE_CURRENT_BINARY_DIR}"
            "${CMAKE_SOURCE_DIR}/cmake/check_nscleanup.cpp"
            CMAKE_FLAGS
                "-DINCLUDE_DIRECTORIES=${VirtualBoxSDK_INCLUDE_DIRS}"
            COMPILE_DEFINITIONS
                "-D${VirtualBoxSDK_RT_PLATFORM}"
                "-DVBOX_WITH_XPCOM_NAMESPACE_CLEANUP"
            LINK_LIBRARIES
                "${VirtualBox_XPCOM_LIB}"
                dl pthread
        )
        if(VBOX_WITH_XPCOM_NAMESPACE_CLEANUP)
            list(APPEND VirtualBoxSDK_DEFINITIONS VBOX_WITH_XPCOM_NAMESPACE_CLEANUP)
        endif()

        if(NOT TARGET VirtualBox::SDK)
            add_library(VirtualBox::SDK INTERFACE IMPORTED)
            set_target_properties(VirtualBox::SDK PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${VirtualBoxSDK_INCLUDE_DIRS}"
                INTERFACE_COMPILE_DEFINITIONS "${VirtualBoxSDK_DEFINITIONS}"
            )
        endif()
        if(NOT TARGET VirtualBox::XPCOM)
            add_library(VirtualBox::XPCOM UNKNOWN IMPORTED)
            set_target_properties(VirtualBox::XPCOM PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES "C;CXX"
                IMPORTED_LINK_INTERFACE_LIBRARIES "dl;pthread"
                IMPORTED_LOCATION "${VirtualBox_XPCOM_LIB}"
            )
        endif()
    endif()

endif()

# This isn't available anywhere in the SDK, and won't necessarily match
# the VirtualBox version.  Therefore, we must ask the user to correctly
# identify the SDK version :(
set(VirtualBoxSDK_VERSION "6.0.10" CACHE STRING "VirtualBox SDK Version")
set(VirtualBoxSDK_VERSION_REGEX "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$")
if(NOT (VirtualBoxSDK_VERSION MATCHES "${VirtualBoxSDK_VERSION_REGEX}"))
    message(FATAL_ERROR "VirtualBoxSDK_VERSION Must be specified as Major.Minor.Patch")
endif()
string(REGEX REPLACE "${VirtualBoxSDK_VERSION_REGEX}" "\\1" VirtualBoxSDK_VERSION_MAJOR "${VirtualBoxSDK_VERSION}")
string(REGEX REPLACE "${VirtualBoxSDK_VERSION_REGEX}" "\\2" VirtualBoxSDK_VERSION_MINOR "${VirtualBoxSDK_VERSION}")
string(REGEX REPLACE "${VirtualBoxSDK_VERSION_REGEX}" "\\3" VirtualBoxSDK_VERSION_PATCH "${VirtualBoxSDK_VERSION}")
