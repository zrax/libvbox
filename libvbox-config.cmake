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

include("${CMAKE_CURRENT_LIST_DIR}/vbox-targets.cmake")

if(NOT WIN32)
    # There's got to be a better way to do this...
    find_library(VirtualBox_XPCOM_LIB
        NAMES VBoxXPCOM
        HINTS /usr/lib/virtualbox
              /usr/local/lib/virtualbox
              /opt/VirtualBox/lib
    )
    mark_as_advanced(VirtualBox_XPCOM_LIB)

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(VirtualBox_XPCOM
        REQUIRED_VARS VirtualBox_XPCOM_LIB
    )

    if(VirtualBox_XPCOM_FOUND)
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
