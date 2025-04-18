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

#include "appfactory.h"

#include "internal/guiapp.h"

#include "appshell/appshellmodule.h"
#include "framework/global/globalmodule.h"
#include "framework/ui/uimodule.h"

using namespace shira::app;

std::shared_ptr<shira::IApplication> AppFactory::newApp() const
{
    return newGuiApp();
}

std::shared_ptr<shira::IApplication> AppFactory::newConsoleApp() const
{
    return nullptr;
}

std::shared_ptr<shira::IApplication> AppFactory::newGuiApp() const
{
    std::shared_ptr<GuiApp> app = std::make_shared<GuiApp>();

    app->addModule(new shira::GlobalModule());
    app->addModule(new shira::appshell::AppShellModule());
    app->addModule(new shira::ui::UiModule());

    return app;
}
