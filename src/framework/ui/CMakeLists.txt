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

declare_module(shira_ui)

set(MODULE_ALIAS shira::ui)

set(MODULE_QML_IMPORT ${CMAKE_CURRENT_LIST_DIR}/qml)

set(MODULE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/uiengine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/uiengine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/abstractnavigation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/abstractnavigation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/navigationsection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/navigationsection.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/navigationpanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/navigationpanel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/navigationcontrol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/navigationcontrol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/mainwindowbridge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/mainwindowbridge.h
    ${CMAKE_CURRENT_SOURCE_DIR}/uimodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/uimodule.h
    ${CMAKE_CURRENT_SOURCE_DIR}/uiaction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/iuiengine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inavigation.h
)

set(MODULE_LINK shira::global)

setup_module()
