/*
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * Shira
 * Literature Reading
 *
 * Copyright (C) 2025 Zihao Wu <wuzihao051119@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GLOBAL_MODULARITY_IMODULEINTERFACE
#define GLOBAL_MODULARITY_IMODULEINTERFACE

#include "funcinfo.h"

#include <memory>

namespace shira::modularity {

struct IModuleInterface
{
    virtual ~IModuleInterface() = default;
};

struct IModuleExportInterface : public IModuleInterface
{
    virtual ~IModuleExportInterface() = default;
    static constexpr bool isInternal() { return false; }
};

struct IModuleInternalInterface : public IModuleInterface
{
    virtual ~IModuleInternalInterface() = default;
    static constexpr bool isInternal() { return true; }
};

struct IModuleCreator
{
    virtual ~IModuleCreator() = default;
    virtual std::shared_ptr<IModuleInterface> create() = 0;
};

struct IModuleExportCreator : public IModuleCreator
{
    virtual ~IModuleExportCreator() = default;
    static constexpr bool isInternal() { return false; }
};

struct IModuleInternalCreator : public IModuleCreator
{
    virtual ~IModuleInternalCreator() = default;
    static constexpr bool isInternal() { return true; }
};

struct InterfaceInfo
{
    std::string_view id;
    std::string_view module;
    bool internal = false;
    constexpr InterfaceInfo(std::string_view i, std::string_view m, bool intr)
        : id(i), module(m), internal(intr) {}
};

}

#define INTERFACE_ID(id)                                                                \
public:                                                                                 \
    static constexpr shira::modularity::InterfaceInfo interfaceInfo() {                 \
        constexpr shira::modularity::InterfaceInfo info(#id, MODULENAME, isInternal()); \
        return info;                                                                    \
    }                                                                                   \
private:

#define MODULE_EXPORT_INTERFACE shira::modularity::IModuleExportInterface
#define MODULE_EXPORT_CREATOR shira::modularity::IModuleExportCreator

#define MODULE_INTERNAL_INTERFACE shira::modularity::IModuleInternalInterface
#define MODULE_INTERNAL_CREATOR shira::modularity::IModuleInternalCreator

#endif // GLOBAL_MODULARITY_IMODULEINTERFACE
