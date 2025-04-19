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

#include "mainwindowbridge.h"

#include <QtGui/QWindow>

using namespace shira::ui;

MainWindowBridge::MainWindowBridge(QObject *parent)
    : QObject(parent)
{
}

MainWindowBridge::~MainWindowBridge()
{
    // mainwindow()->deinit();
}

QWindow *MainWindowBridge::qWindow() const
{
    return m_window;
}

QString MainWindowBridge::filePath() const
{
    return m_window ? m_window->filePath() : "";
}

bool MainWindowBridge::fileModified() const
{
    return true;
}

void MainWindowBridge::showOnBack()
{

}

void MainWindowBridge::showOnFront()
{

}

bool MainWindowBridge::isFullScreen() const
{
    return true;
}

void MainWindowBridge::toggleFullScreen()
{

}

QScreen *MainWindowBridge::screen() const
{
    return nullptr;
}

void MainWindowBridge::init()
{

}
