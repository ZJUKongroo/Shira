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

#include "uimodule.h"

#include "internal/mainwindow.h"

using namespace shira::ui;

std::string UiModule::moduleName() const
{
    return "ui";
}

void UiModule::registerExports()
{
    m_uiengine = std::make_shared<UiEngine>(iocContext());

    ioc()->registerExport(moduleName(), m_uiengine);
    ioc()->registerExport(moduleName(), new MainWindow());
}
