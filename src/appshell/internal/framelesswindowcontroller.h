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

#ifndef INTERNAL_FRAMELESSWINDOWCONTROLLER_H
#define INTERNAL_FRAMELESSWINDOWCONTROLLER_H

#include <QtCore/QRect>
#include <QtCore/QAbstractNativeEventFilter>

namespace shira::appshell {

class FramelessWindowController : public QAbstractNativeEventFilter
{
public:
    virtual void init();

    QRect windowTitleBarMoveArea() const;
    void setWindowTitleBarMoveArea(const QRect &area);

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    QRect m_windowTitleBarMoveArea;
};

}

#endif // INTERNAL_FRAMELESSWINDOWCONTROLLER_H
