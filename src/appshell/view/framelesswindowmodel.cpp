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

#include "framelesswindowmodel.h"

#ifdef Q_OS_WIN
#  include "internal/platform/win/winframelesswindowcontroller.h"
#else
#  include "internal/framelesswindowcontroller.h"
#endif


using namespace shira::appshell;

FramelessWindowModel::FramelessWindowModel(QObject *parent)
{
    m_controller = new FramelessWindowController();
}

FramelessWindowModel::~FramelessWindowModel()
{
    delete m_controller;
}

void FramelessWindowModel::init()
{
    m_controller->init();
}

QRect FramelessWindowModel::titleBarMoveArea() const
{
    return m_controller->windowTitleBarMoveArea();
}

void FramelessWindowModel::setTitleBarMoveArea(const QRect &area)
{
    if (titleBarMoveArea() == area) {
        return;
    }

    m_controller->setWindowTitleBarMoveArea(area);
    emit titleBarMoveAreaChanged(area);
}
