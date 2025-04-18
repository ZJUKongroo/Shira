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

#ifndef GLOBAL_MODULARITY_MODULESIOC_H
#define GLOBAL_MODULARITY_MODULESIOC_H

#include <map>
#include <string>
#include <cassert>
#include <iostream>

#include "imoduleinterface.h"

namespace shira::modularity {

class ModulesIoC
{
public:
    ModulesIoC() = default;

    template <typename I>
    void registerExportCreator(const std::string &module, IModuleCreator *c)
    {
        if (!c) {
            assert(c);
            return;
        }
        registerService(module, I::interfaceInfo(), std::shared_ptr<IModuleInterface>(), c);
    }

    template <typename I>
    void registerExport(const std::string module, I *p)
    {
        if (!p) {
            assert(p);
            return;
        }
        registerExport(module, std::shared_ptr<I>(p));
    }

    template <typename I>
    void registerExportNoDelete(const std::string &module, I *p)
    {
        if (!p) {
            assert(p);
            return;
        }
        registerExport(module, std::shared_ptr<I>(p, [](I *) {}));
    }

    template <typename I>
    void registerExport(const std::string &module, std::shared_ptr<I> p)
    {
        if (!p) {
            assert(p);
            return;
        }
        registerService(module, I::interfaceInfo(), std::static_pointer_cast<IModuleInterface>(p), nullptr);
    }

    template <typename I>
    void registerInternal(const std::string &module, IModuleCreator *c)
    {
        if (!c) {
            assert(c);
            return;
        }
        registerService(module, I::interfaceInfo(), std::shared_ptr<IModuleInterface>(), c);
    }

    template <typename I>
    void registerInternal(const std::string &module, I *p)
    {
        if (!p) {
            assert(p);
            return;
        }
        registerInternal(module, std::shared_ptr<I>(p));
    }

    template <typename I>
    void registerInternalNoDelete(const std::string &module, I *p)
    {
        if (!p) {
            assert(p);
            return;
        }
        registerInternal(module, std::shared_ptr<I>(p, [](I *) {}));
    }

    template <typename I>
    void registerInternal(const std::string &module, std::shared_ptr<I> p)
    {
        if (!p) {
            assert(p);
            return;
        }
        registerService(module, I::interfaceInfo(), std::static_pointer_cast<IModuleInterface>(p), nullptr);
    }

    template <typename I>
    void unregister(const std::string &module)
    {
        unregisterService(I::interfaceInfo());
    }

    template <typename I>
    void unregisterIfRegistered(const std::string &module, std::shared_ptr<I> p)
    {
        if (resolve<I>(module, std::string_view()) == p) {
            unregister<I>(module);
        }
    }

    template <typename I>
    std::shared_ptr<I> resolve(const std::string &module, const std::string_view &callInfo = std::string_view())
    {
        std::shared_ptr<IModuleInterface> p = doResolvePtrByInfo(module, I::interfaceInfo(), callInfo);
#ifndef NDEBUG
        return std::dynamic_pointer_cast<I>(p);
#else
        return std::static_pointer_cast<I>(p);
#endif
    }

    template <typename I>
    std::shared_ptr<I> resolveRequiredImport(const std::string &module)
    {
        std::shared_ptr<IModuleInterface> p = doResolvePtrByInfo(module, I::interfaceInfo(), std::string_view());
        if (!p) {
            std::cerr << "not found implementation for interface: " << I::interfaceInfo().id << std::endl;
            assert(false);
        }
#ifndef NDEBUG
        return std::dynamic_pointer_cast<I>(p);
#else
        return std::static_pointer_cast<I>(p);
#endif
    }

    void reset()
    {
        m_map.clear();
    }

private:
    void unregisterService(const InterfaceInfo &info)
    {
        m_map.erase(info.id);
    }

    void registerService(const std::string &module,
                         const InterfaceInfo &info,
                         std::shared_ptr<IModuleInterface> p,
                         IModuleCreator *c)
    {
        auto foundIt = m_map.find(info.id);
        if (foundIt != m_map.end()) {
            std::cerr << module << ": double register:"
                      << info.id << ", first register in" << m_map[info.id].sourceModule << std::endl;
            assert(false);
            return;
        }

        Service inj;
        inj.sourceModule = module;
        inj.c = c;
        inj.p = p;
        m_map[info.id] = inj;
    }

    std::shared_ptr<IModuleInterface> doResolvePtrByInfo(const std::string_view usageModule,
                                                         const InterfaceInfo &info,
                                                         const std::string_view &callInfo)
    {
        if (info.internal) {
            if (usageModule != info.module) {
                std::cerr << "Assertion failed!! Interface '" << info.id << "' is internal"
                          << ", usage module: '" << usageModule << "'"
                          << ", interface module: '" << info.module << "'"
                          << ", called from: " << (callInfo.empty() ? std::string_view("unknown") : callInfo);

#ifndef NDEBUG
                std::abort();
#endif
            }
        }

        auto it = m_map.find(info.id);
        if (it == m_map.end()) {
            return nullptr;
        }

        Service &inj = it->second;
        if (inj.p) {
            return inj.p;
        }

        if (inj.c) {
            return inj.c->create();
        }

        return nullptr;
    }

    struct Service {
        IModuleCreator *c = nullptr;
        std::string sourceModule;
        std::shared_ptr<IModuleInterface> p;
    };

    std::map<std::string_view, Service> m_map;
};

template <typename T>
struct Creator : MODULE_EXPORT_CREATOR
{
    std::shared_ptr<IModuleInterface> create() { return std::make_shared<T>(); }
};

}

#endif // GLOBAL_MODULARITY_MODULESIOC_H
