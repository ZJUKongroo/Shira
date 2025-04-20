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

#ifndef DOCK_INTERNAL_DOCKBASE_H
#define DOCK_INTERNAL_DOCKBASE_H

#include <QtQuick/QQuickItem>
#include <QtCore/QString>

#include "docktypes.h"

namespace shira::dock {

class DockBase : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

    Q_PROPERTY(int minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumSizeChanged)
    Q_PROPERTY(int minimumHeight READ minimumHeight WRITE setMinimumHeight NOTIFY minimumSizeChanged)
    Q_PROPERTY(int maximumWidth READ maximumWidth WRITE setMaximumWidth NOTIFY maximumSizeChanged)
    Q_PROPERTY(int maximumHeight READ maximumHeight WRITE setMaximumHeight NOTIFY maximumSizeChanged)
    Q_PROPERTY(int contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentSizeChanged)
    Q_PROPERTY(int contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentSizeChanged)

    Q_PROPERTY(int location READ locationProperty WRITE setLocation NOTIFY locationChanged)

    Q_PROPERTY(bool floatable READ floatable WRITE setFloatable NOTIFY floatableChanged)
    Q_PROPERTY(bool closable READ closable WRITE setClosable NOTIFY closableChanged)
    Q_PROPERTY(bool resizable READ resizable WRITE setResizable NOTIFY resizableChanged)
    Q_PROPERTY(bool separatorsVisible READ separatorsVisible WRITE setSeparatorsVisible NOTIFY separatorsVisibleChanged)

    Q_PROPERTY(bool floating READ floating NOTIFY floatingChanged)

    Q_PROPERTY(bool inited READ inited NOTIFY initedChanged)

public:
    DockBase(DockType type, QQuickItem *parent = nullptr);

    QString title() const;

    int minimumWidth() const;
    int minimumHeight() const;
    int maximumWidth() const;
    int maximumHeight() const;
    int contentWidth() const;
    int contentHeight() const;
    QSize preferredSize() const;

    int locationProperty() const;
    Location location() const;

    bool floatable() const;
    bool closable() const;
    bool resizable() const;
    bool separatorsVisible() const;

    bool floating() const;

    bool inited() const;

    virtual void init();
    virtual void resetToDefault();

    Q_INVOKABLE bool isOpen();
    Q_INVOKABLE bool open();
    Q_INVOKABLE bool close();
    Q_INVOKABLE bool resize(int width, int height);

public slots:
    void setTitle(const QString &title);

    void setMinimumWidth(int width);
    void setMinimumHeight(int height);
    void setMaximumWidth(int width);
    void setMaximumHeight(int height);
    void setContentWidth(int width);
    void setContentHeight(int height);

    void setLocation(int location);

    void setFloatable(bool floatable);
    void setClosable(bool closable);
    void setResizable(bool resizable);
    void setSeparatorsVisible(bool visible);

    void setFloating(bool floating);

signals:
    void titleChanged();

    void minimumSizeChanged();
    void maximumSizeChanged();
    void contentSizeChanged();

    void locationChanged();

    void floatableChanged();
    void closableChanged();
    void resizableChanged();
    void separatorsVisibleChanged();

    void floatingChanged();

    void initedChanged();

private:
    QString m_title;

    int m_minimumWidth = 0;
    int m_minimumHeight = 0;
    int m_maximumWidth = 0;
    int m_maximumHeight = 0;
    int m_contentWidth = 0;
    int m_contentHeight = 0;

    DockProperties m_properties;

    bool m_defaultVisibility = false;

    bool m_floating = false;
    bool m_inited = false;
};

}

#endif // DOCK_INTERNAL_DOCKBASE_H
