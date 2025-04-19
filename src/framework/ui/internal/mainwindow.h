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

#ifndef UI_INTERNAL_MAINWINDOW_H
#define UI_INTERNAL_MAINWINDOW_H

#include "imainwindow.h"

namespace shira::ui {

class MainWindow : public IMainWindow
{
public:
    MainWindow() = default;

    void init(MainWindowBridge *bridge) override;
    void deinit() override;

    QWindow *qWindow() const override;

    void requestShowOnBack() override;
    void requestShowOnFront() override;

    bool isFullScreen() const override;
    void toggleFullScreen() override;

    QScreen *screen() const override;

private:
    MainWindowBridge *m_bridge = nullptr;
};

}

#endif // UI_INTERNAL_MAINWINDOW_H
