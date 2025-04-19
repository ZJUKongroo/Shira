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

#ifndef UI_INTERNAL_UIENGINE_H
#define UI_INTERNAL_UIENGINE_H

#include <QtCore/QObject>

#include "ui/iuiengine.h"
#include "modularity/context.h"

namespace shira::ui {

class UiEngine : public QObject, public IUiEngine
{
    Q_OBJECT

public:
    UiEngine(const shira::modularity::ContextPtr &iocCtx);
    ~UiEngine() override;

    QQmlApplicationEngine *qmlAppEngine() const override;
    QQmlEngine *qmlEngine() const override;
    void quit() override;

private:
    QQmlApplicationEngine *m_engine = nullptr;
};

}

#endif // UI_INTERNAL_UIENGINE_H
