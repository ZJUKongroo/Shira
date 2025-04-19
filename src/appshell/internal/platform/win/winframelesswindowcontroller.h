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

#ifndef INTERNAL_PLATFORM_WINFRAMELESSWINDOWCONTROLLER_H
#define INTERNAL_PLATFORM_WINFRAMELESSWINDOWCONTROLLER_H

#include "internal/framelesswindowcontroller.h"

#include <Windows.h>

#include <QtGui/QScreen>
#include <QtCore/QEvent>

namespace shira::appshell {

class WinFramelessWindowController : public QObject, public FramelessWindowController
{
public:
    explicit WinFramelessWindowController();

    void init() override;

private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool nativeEventFilter(const QByteArray &eventByte, void *message, qintptr *result) override;

    MONITORINFO m_monitorInfo;
};

}

#endif // INTERNAL_PLATFORM_WINFRAMELESSWINDOWCONTROLLER_H
