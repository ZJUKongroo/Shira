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

#ifndef UI_VIEW_MAINWINDOWBRIDGE_H
#define UI_VIEW_MAINWINDOWBRIDGE_H

#include <QtCore/QObject>
#include <QtCore/QString>

class QWindow;
class QScreen;

namespace shira::ui {

class MainWindowBridge : public QObject
{
    Q_OBJECT

public:
    explicit MainWindowBridge(QObject *parent = nullptr);
    ~MainWindowBridge();

    QWindow *qWindow() const;

    QString filePath() const;
    virtual bool fileModified() const;

    void showOnBack();
    void showOnFront();

    bool isFullScreen() const;
    void toggleFullScreen();

    QScreen *screen() const;

signals:
    void WindowChanged();
    void filePathChanged();
    void fileModifiedChanged();

protected:
    virtual void init();

    QWindow *m_window = nullptr;

private:
    bool m_isFullScreen = false;
};

}

#endif // UI_VIEW_MAINWINDOWBRIDGE_H
