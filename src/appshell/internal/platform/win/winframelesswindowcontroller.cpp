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

#include "winframelesswindowcontroller.h"

using namespace shira::appshell;

static HWND s_hwnd = 0;

static void updateWindowPosition()
{

}

WinFramelessWindowController::WinFramelessWindowController()
    : FramelessWindowController()
{
    memset(&m_monitorInfo, 0, sizeof(m_monitorInfo));
    m_monitorInfo.cbSize = sizeof(MONITORINFO);

    qApp->installEventFilter(this);
    qApp->installNativeEventFilter(this);
}

void WinFramelessWindowController::init()
{
    // TO DO!
}

bool WinFramelessWindowController::eventFilter(QObject *watched, QEvent *event)
{
    return false;
}

bool WinFramelessWindowController::nativeEventFilter(const QByteArray &eventByte, void *message, qintptr *result)
{
    return false;
}
