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

#ifndef UICOMPONENTS_VIEW_ICONVIEW_H
#define UICOMPONENTS_VIEW_ICONVIEW_H

#include <QtGui/QIcon>

#include "quickpaintedview.h"

namespace shira::uicomponents {

class IconView : public QuickPaintedView
{
	Q_OBJECT

public:
	IconView(QQuickItem *parent = nullptr);

	QVariant icon() const;
	QColor backgroundColor() const;

public slots:
	void setIcon(QVariant val);
	void setBackgroundColor(const QColor &color);

signals:
	void iconChanged(const QVariant &icon);
	void backgroundColorChanged(const QColor &color);

private:
	void paint(QPainter *) override;

	QColor m_color;
	QColor m_backgroundColor;
	QIcon m_icon;
};

}

#endif // UICOMPONENTS_VIEW_ICONVIEW_H
