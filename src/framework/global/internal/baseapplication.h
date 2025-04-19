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

#ifndef INTERNAL_BASEAPPLICATION_H
#define INTERNAL_BASEAPPLICATION_H

#include "iapplication.h"
#include "modularity/ioc.h"
#include "modularity/context.h"
#include "modularity/modulesioc.h"

namespace shira {

class BaseApplication : public IApplication
{
public:
    BaseApplication(const modularity::ContextPtr &ctx);

    static String appName();
    static String appTitle();
    static Version appVersion();

    String name() const override { return appName(); }
    String title() const override { return appTitle(); }
    Version version() const override { return appVersion(); }

    void restart() override;

    const modularity::ContextPtr iocContext() const override;
    modularity::ModulesIoC *ioc() const override;

private:
    modularity::ContextPtr m_iocContext;
};

}

#endif // INTERNAL_BASEAPPLICATION_H
