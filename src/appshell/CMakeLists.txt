# SPDX-License-Identifier: GPL-3.0-only
#
# Shira
# Literature Reading
#
# Copyright (C) 2025 Zihao Wu <wuzihao051119@outlook.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

declare_module(appshell)

set(MODULE_QRC appshell.qrc)

set(MODULE_QML_IMPORT ${CMAKE_CURRENT_LIST_DIR}/qml)

set(MODULE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/framelesswindowcontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/framelesswindowcontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/framelesswindowmodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/framelesswindowmodel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/mainwindowtitleprovider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/mainwindowtitleprovider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/appshellmodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/appshellmodule.h
)

if(OS_IS_WIN)
    set(MODULE_SRC ${MODULE_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/platform/win/winframelesswindowcontroller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/platform/win/winframelesswindowcontroller.h
    )
endif()

set(MODULE_LINK shira::global)

setup_module()
