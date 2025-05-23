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

#ifndef GLOBAL_GLOBALMODULE_H
#define GLOBAL_GLOBALMODULE_H

#include "modularity/imodulesetup.h"
#include "internal/baseapplication.h"

namespace shira {

class GlobalModule : public modularity::IModuleSetup
{
public:
    std::string moduleName() const override;

    void registerExports() override;
};

}

#endif // GLOBAL_GLOBALMODULE_H
