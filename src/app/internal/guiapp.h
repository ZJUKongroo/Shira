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

#ifndef GUIAPP_H
#define GUIAPP_H

#include <vector>

#include "internal/baseapplication.h"
#include "modularity/modulesioc.h"
#include "modularity/imodulesetup.h"

namespace shira::app {

class GuiApp : public shira::BaseApplication
{
public:
    GuiApp(const shira::modularity::ContextPtr &ctx);

    void addModule(shira::modularity::IModuleSetup *module);

    void perform() override;
    void finish() override;
    void restart() override;

private:
    std::vector<shira::modularity::IModuleSetup *> m_modules;
};

}

#endif // GUIAPP_H
