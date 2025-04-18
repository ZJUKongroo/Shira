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

#ifndef GLOBAL_IAPPLICATION_H
#define GLOBAL_IAPPLICATION_H

#include "types/string.h"
#include "types/version.h"
#include "modularity/imoduleinterface.h"

namespace shira {

class IApplication : MODULE_EXPORT_INTERFACE
{
    INTERFACE_ID(IApplication)

public:
    virtual ~IApplication() = default;

    enum class RunMode {
        GuiApp,
        ConsoleApp,
    };

    virtual String name() const = 0;
    virtual String title() const = 0;

    virtual Version version() const = 0;
};

}

#endif // GLOBAL_IAPPLICATION_H
