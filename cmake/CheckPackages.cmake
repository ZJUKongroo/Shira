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

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Qml Quick)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(qt_components Core Gui Widgets Qml Quick)

foreach(component ${qt_components})
    list(APPEND QT_LIBRARIES ${Qt6${component}_LIBRARIES})
    list(APPEND QT_INCLUDES ${Qt6${component}_INCLUDE_DIRS})
    add_definitions(${Qt6${component}_DEFINITIONS})
endforeach()

include_directories(${QT_INCLUDES})
