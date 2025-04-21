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

declare_module(shira_ui_components)

set(MODULE_ALIAS shira::ui_components)

set(MODULE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/view/abstractmenumodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/abstractmenumodel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/menuitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/menuitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/popupview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/popupview.h
    ${CMAKE_CURRENT_SOURCE_DIR}/uicomponentsmodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/uicomponentsmodule.h
)

set(MODULE_LINK shira::global)

setup_module()
