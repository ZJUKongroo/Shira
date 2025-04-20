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

set(LINK_LIB
    ${QT_LIBRARIES}
    appshell
    shira::global
    shira::ui
    shira::ui_components
    shira::dock
    shira::actions
)

add_executable(Shira)

target_sources(Shira PRIVATE
    internal/guiapp.cpp
    internal/guiapp.h
    appfactory.cpp
    appfactory.h
    main.cpp
)

target_include_directories(Shira PRIVATE
    ${PROJECT_SOURCE_DIR}/src

    ${SHIRA_FRAMEWORK_DIR}
    ${SHIRA_FRAMEWORK_DIR}/global
)

target_link_libraries(Shira PRIVATE ${LINK_LIB})

install(TARGETS Shira
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    BUNDLE  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
