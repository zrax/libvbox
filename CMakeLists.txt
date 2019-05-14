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

cmake_minimum_required(VERSION 3.1)
project(libvbox)

include(FeatureSummary)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(VirtualBoxSDK REQUIRED)
set_package_properties(VirtualBoxSDK PROPERTIES
    URL "https://www.virtualbox.org/wiki/Downloads"
    TYPE REQUIRED
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

configure_file(
    include/libvbox_vboxsdk_version.h.in
    include/libvbox_vboxsdk_version.h
    @ONLY
)

add_library(vbox SHARED lib/vboxwrap.cpp)

if(MSVC)
    # Keep the "libvbox" name even on MSVC
    set_target_properties(vbox PROPERTIES PREFIX "lib")
endif()

target_include_directories(vbox
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_BINARY_DIR}/include"
)

target_compile_definitions(vbox
    PRIVATE
        BUILDING_LIBVBOX
)

target_sources(vbox
    PRIVATE
        include/libvbox.h
        include/libvbox_errors.h
        include/libvbox_interfaces.h
        include/libvbox_vboxsdk_types.h
        include/libvbox_vboxsdk_version.h
        include/libvbox_wrap.h
        lib/libvbox_p.h
        lib/comstring.cpp
        lib/console.cpp
        lib/display.cpp
        lib/errorwrap.cpp
        lib/event.cpp
        lib/eventlistener.cpp
        lib/eventsource.cpp
        lib/guest.cpp
        lib/guestsession.cpp
        lib/host.cpp
        lib/keyboard.cpp
        lib/machine.cpp
        lib/mouse.cpp
        lib/mousepointershape.cpp
        lib/process.cpp
        lib/progress.cpp
        lib/session.cpp
        lib/vetoevent.cpp
        lib/virtualbox.cpp
        lib/virtualboxclient.cpp
        lib/virtualboxerrorinfo.cpp
        ${VirtualBoxSDK_IID_LIB}
)

target_link_libraries(vbox PRIVATE VirtualBox::SDK)
if(WIN32)
    target_link_libraries(vbox PUBLIC Uuid Ole32 OleAut32)
else()
    target_link_libraries(vbox PUBLIC VirtualBox::XPCOM)
endif()

install(TARGETS vbox
    EXPORT vbox-targets
    RUNTIME DESTINATION bin COMPONENT shlib
    LIBRARY DESTINATION lib COMPONENT shlib
)
install(
    FILES
        include/libvbox.h
        include/libvbox_errors.h
        include/libvbox_interfaces.h
        include/libvbox_vboxsdk_types.h
        include/libvbox_wrap.h
        "${CMAKE_CURRENT_BINARY_DIR}/include/libvbox_vboxsdk_version.h"
    DESTINATION include
    COMPONENT devel
)

export(TARGETS vbox
    NAMESPACE libvbox::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/vbox-targets.cmake"
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(libvbox-config-version.cmake
    VERSION 1.0
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        libvbox-config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/libvbox-config-version.cmake"
    DESTINATION lib/cmake/libvbox
    COMPONENT devel
)
install(EXPORT vbox-targets
    DESTINATION lib/cmake/libvbox
    NAMESPACE libvbox::
    COMPONENT devel
)
