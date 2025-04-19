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

#ifndef GLOBAL_MODULARITY_IMODULESETUP_H
#define GLOBAL_MODULARITY_IMODULESETUP_H

#include <string>

#include "ioc.h"
#include "iapplication.h"

namespace shira::modularity {

class IModuleSetup
{
public:
    virtual ~IModuleSetup() {};

    virtual std::string moduleName() const = 0;

    virtual void registerExports() {}
    virtual void resolveImports() {}

    virtual void registerResources() {}
    virtual void registerUiTypes() {}

    virtual void onPreInit() {}
    virtual void onInit() {}
    virtual void onAllInited() {}
    virtual void onDelayedInit() {}
    virtual void onDeInit() {}
    virtual void onDestroy() {}

    virtual void onStartApp() {}

    void setApplication(std::shared_ptr<IApplication> app)
    {
        m_application = app;
    }

    std::shared_ptr<IApplication> application() const { return m_application; }

    const ContextPtr iocContext() const { return m_application ? m_application->iocContext() : globalCtx(); }
    ModulesIoC *ioc() const { return m_application ? m_application->ioc() : globalIoc(); }

protected:
    std::shared_ptr<IApplication> m_application;
};

}

#endif // GLOBAL_MODULARITY_IMODULESETUP_H
