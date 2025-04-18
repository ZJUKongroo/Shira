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

#include "guiapp.h"

#include <QtCore/QString>
#include <QtCore/QUrl>

#include "ui/iuiengine.h"

using namespace shira::app;

GuiApp::GuiApp()
{
}

void GuiApp::addModule(shira::modularity::IModuleSetup *module)
{
    m_modules.push_back(module);
}

void GuiApp::perform()
{
    QQmlApplicationEngine *engine = ioc()->resolve<shira::ui::IUiEngine>("app")->qmlAppEngine();

    const QString mainQmlFile = "/Main.qml";
    const QUrl url(QString(appshell_QML_IMPORT) + mainQmlFile);

    engine->load(url);
}
