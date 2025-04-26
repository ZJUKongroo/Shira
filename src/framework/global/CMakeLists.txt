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

declare_module(shira_global)

set(MODULE_ALIAS shira::global)

set(MODULE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/types/bytearray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types/bytearray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types/string.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types/string.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types/translatablestring.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types/flags.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types/version.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types/version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/funcinfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/imodulesetup.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/imoduleinterface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/modulesioc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/ioc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/modularity/ioc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/async/internal/abstractinvoker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/async/internal/abstractinvoker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/async/internal/asyncimpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/async/internal/asyncimpl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/async/internal/queuedinvoker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/async/internal/queuedinvoker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/async/asyncable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/baseapplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/baseapplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/interactive.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/interactive.h
    ${CMAKE_CURRENT_SOURCE_DIR}/containers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/translation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/translation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/log.h
    ${CMAKE_CURRENT_SOURCE_DIR}/globalmodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/globalmodule.h
    ${CMAKE_CURRENT_SOURCE_DIR}/iapplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/iinteractive.h
)

setup_module()
