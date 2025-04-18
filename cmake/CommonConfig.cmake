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

macro(declare_module name)
    set(MODULE ${name})
    unset(MODULE_ALIAS)
    unset(MODULE_SRC)
    unset(MODULE_DEF)
    unset(MODULE_INCLUDE)
    unset(MODULE_LINK)
    unset(MODULE_QML_IMPORT)
endmacro()

macro(add_qml_import_path input_var)
    if (NOT ${${input_var}} STREQUAL "")
        set(QML_IMPORT_PATH "$CACHE{QML_IMPORT_PATH}")
        list(APPEND QML_IMPORT_PATH ${${input_var}})
        list(REMOVE_DUPLICATES QML_IMPORT_PATH)
        set(QML_IMPORT_PATH "${QML_IMPORT_PATH}" CACHE STRING
            "QtCreator extra import paths for QML modules" FORCE)
    endif()
endmacro()

macro(setup_module)
    message(STATUS "Configuring ${MODULE} <${MODULE_ALIAS}>")

    add_library(${MODULE})

    if (MODULE_ALIAS)
        add_library(${MODULE_ALIAS} ALIAS ${MODULE})
    endif()

    add_qml_import_path(MODULE_QML_IMPORT)

    target_sources(${MODULE} PRIVATE ${MODULE_SRC})

    target_compile_definitions(${MODULE} PUBLIC
        ${MODULE_DEF}
        ${MODULE}_QML_IMPORT="${MODULE_QML_IMPORT}"
    )

    target_include_directories(${MODULE} PRIVATE
        ${MODULE_INCLUDE}
        ${PROJECT_SOURCE_DIR}/src

        ${SHIRA_FRAMEWORK_DIR}
        ${SHIRA_FRAMEWORK_DIR}/global
    )

    target_link_libraries(${MODULE} PRIVATE ${MODULE_LINK} ${QT_LIBRARIES})
endmacro()
