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

#include "mainwindow.h"

#include "global/log.h"
#include "view/mainwindowbridge.h"

using namespace shira::ui;

void MainWindow::init(MainWindowBridge *bridge)
{
    IF_ASSERT_FAILED(!m_bridge) {
        LOGW() << "MainWindowBridge is already set. Refusing to set it again.";
        return;
    }

    m_bridge = bridge;
}

void MainWindow::deinit()
{
    m_bridge = nullptr;
}

QWindow *MainWindow::qWindow() const
{
    return m_bridge ? m_bridge->qWindow() : nullptr;
}

void MainWindow::requestShowOnBack()
{
    if (!m_bridge) {
        return;
    }

    m_bridge->showOnBack();
}

void MainWindow::requestShowOnFront()
{
    if (!m_bridge) {
        return;
    }

    m_bridge->showOnFront();
}

bool MainWindow::isFullScreen() const
{
    return m_bridge ? m_bridge->isFullScreen() : false;
}

void MainWindow::toggleFullScreen()
{
    if (!m_bridge) {
        return;
    }

    m_bridge->toggleFullScreen();
}

QScreen *MainWindow::screen() const
{
    return m_bridge ? m_bridge->screen() : nullptr;
}
