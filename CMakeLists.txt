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

cmake_minimum_required(VERSION 3.5)
project(libvbox)

include(FeatureSummary)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

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

if(POLICY CMP0115)
    # Old versions of CMake allow you to specify file names without an extension,
    # meaning configured file names which differ in only a ".in" suffix were
    # ambiguous. This shuts up the warning, since we already do the right thing.
    cmake_policy(SET CMP0115 NEW)
endif()

configure_file(
    include/libvbox_vboxsdk_version.h.in
    include/libvbox_vboxsdk_version.h
    @ONLY
)

add_library(vbox SHARED "")

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
        lib/additionsfacility.cpp
        lib/appliance.cpp
        lib/audioadapter.cpp
        lib/audiosettings.cpp
        lib/bandwidthcontrol.cpp
        lib/bandwidthgroup.cpp
        lib/biossettings.cpp
        lib/certificate.cpp
        lib/clipboardevent.cpp
        lib/cloudclient.cpp
        lib/cloudmachine.cpp
        lib/cloudnetwork.cpp
        lib/cloudprofile.cpp
        lib/cloudprofileevent.cpp
        lib/cloudprovider.cpp
        lib/cloudproviderevent.cpp
        lib/cloudprovidermanager.cpp
        lib/comstring.cpp
        lib/console.cpp
        lib/cpuchangedevent.cpp
        lib/cpuprofile.cpp
        lib/cursorpositionchangedevent.cpp
        lib/datastream.cpp
        lib/dhcpconfig.cpp
        lib/dhcpgroupcondition.cpp
        lib/dhcpserver.cpp
        lib/directory.cpp
        lib/display.cpp
        lib/displaysourcebitmap.cpp
        lib/dndbase.cpp
        lib/dndsource.cpp
        lib/dndtarget.cpp
        lib/emulatedusb.cpp
        lib/errorwrap.cpp
        lib/event.cpp
        lib/eventlistener.cpp
        lib/eventsource.cpp
        lib/extpack.cpp
        lib/extpackinstalledevent.cpp
        lib/extpackmanager.cpp
        lib/extpackplugin.cpp
        lib/extradatachangedevent.cpp
        lib/file.cpp
        lib/firmwaresettings.cpp
        lib/form.cpp
        lib/formvalue.cpp
        lib/framebuffer.cpp
        lib/framebufferoverlay.cpp
        lib/fsinfo.cpp
        lib/fsobjinfo.cpp
        lib/graphicsadapter.cpp
        lib/guest.cpp
        lib/guestadditionsstatuschangedevent.cpp
        lib/guestdebugcontrol.cpp
        lib/guestdebugcontrolchangedevent.cpp
        lib/guestdirectoryevent.cpp
        lib/guestfileevent.cpp
        lib/guestfileioevent.cpp
        lib/guestkeyboardevent.cpp
        lib/guestmonitorchangedevent.cpp
        lib/guestmouseevent.cpp
        lib/guestmultitouchevent.cpp
        lib/guestostype.cpp
        lib/guestprocessevent.cpp
        lib/guestprocessioevent.cpp
        lib/guestscreeninfo.cpp
        lib/guestsession.cpp
        lib/guestsessionevent.cpp
        lib/guestuserstatechangedevent.cpp
        lib/host.cpp
        lib/hostaudiodevice.cpp
        lib/hostaudiodevicechangedevent.cpp
        lib/hostdrive.cpp
        lib/hostdrivepartition.cpp
        lib/hostnetworkinterface.cpp
        lib/hostonlynetwork.cpp
        lib/hostpcideviceplugevent.cpp
        lib/hostvideoinputdevice.cpp
        lib/internalmachinecontrol.cpp
        lib/internalprogresscontrol.cpp
        lib/internalsessioncontrol.cpp
        lib/keyboard.cpp
        lib/keyboardledschangedevent.cpp
        lib/languagechangedevent.cpp
        lib/machine.cpp
        lib/machinedebugger.cpp
        lib/machineevent.cpp
        lib/medium.cpp
        lib/mediumattachment.cpp
        lib/mediumevent.cpp
        lib/mediumformat.cpp
        lib/mediumio.cpp
        lib/modechangedevent.cpp
        lib/mouse.cpp
        lib/mousecapabilitychangedevent.cpp
        lib/mousepointershape.cpp
        lib/mousepointershapechangedevent.cpp
        lib/natengine.cpp
        lib/natnetwork.cpp
        lib/natnetworkchangedevent.cpp
        lib/natredirectevent.cpp
        lib/networkadapter.cpp
        lib/nvramstore.cpp
        lib/objchangedevent.cpp
        lib/parallelport.cpp
        lib/pciaddress.cpp
        lib/pcideviceattachment.cpp
        lib/performancecollector.cpp
        lib/performancemetric.cpp
        lib/platform.cpp
        lib/platformproperties.cpp
        lib/platformx86.cpp
        lib/process.cpp
        lib/progress.cpp
        lib/progressevent.cpp
        lib/recordingevent.cpp
        lib/recordingscreensettings.cpp
        lib/recordingsettings.cpp
        lib/resourcestore.cpp
        lib/reusableevent.cpp
        lib/runtimeerrorevent.cpp
        lib/serialport.cpp
        lib/session.cpp
        lib/sharedfolder.cpp
        lib/showwindowevent.cpp
        lib/snapshot.cpp
        lib/snapshotevent.cpp
        lib/statechangedevent.cpp
        lib/storagecontroller.cpp
        lib/stringarray.cpp
        lib/systemproperties.cpp
        lib/token.cpp
        lib/trustedplatformmodule.cpp
        lib/uefivariablestore.cpp
        lib/unattended.cpp
        lib/updateagent.cpp
        lib/updateagentavailableevent.cpp
        lib/updateagentevent.cpp
        lib/usbcontroller.cpp
        lib/usbdevice.cpp
        lib/usbdevicefilter.cpp
        lib/usbdevicefilters.cpp
        lib/usbproxybackend.cpp
        lib/vboxwrap.cpp
        lib/vetoevent.cpp
        lib/vfsexplorer.cpp
        lib/virtualbox.cpp
        lib/virtualboxclient.cpp
        lib/virtualboxerrorinfo.cpp
        lib/virtualsystemdescription.cpp
        lib/vrdeserver.cpp
        lib/vrdeserverinfo.cpp
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
