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
#include <QtWidgets/QApplication>

#include "global/log.h"
#include "ui/iuiengine.h"

using namespace shira::app;

GuiApp::GuiApp(const shira::modularity::ContextPtr &ctx)
    : shira::BaseApplication(ctx)
{
}

void GuiApp::addModule(shira::modularity::IModuleSetup *module)
{
    m_modules.push_back(module);
}

void GuiApp::perform()
{
    for (shira::modularity::IModuleSetup *m : m_modules) {
        m->registerExports();
    }

    QQmlApplicationEngine *engine = ioc()->resolve<shira::ui::IUiEngine>("app")->qmlAppEngine();

    const QString mainQmlFile = "/Main.qml";
    const QUrl url(QStringLiteral("qrc:/qml") + mainQmlFile);

    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     qApp, [url](QObject *object, const QUrl &objUrl) {
        if (!object && url == objUrl) {
            LOGE() << "failed Qml load\n";
            QCoreApplication::exit(-1);
            return;
        }
    }, Qt::QueuedConnection);

    engine->load(url);
}

void GuiApp::finish()
{

}

void GuiApp::restart()
{

}
