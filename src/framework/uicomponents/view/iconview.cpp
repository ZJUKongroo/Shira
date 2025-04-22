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

#include "iconview.h"

#include <QtGui/QPainter>

using namespace shira::uicomponents;

IconView::IconView(QQuickItem *parent)
	: QuickPaintedView(parent)
{
}

QVariant IconView::icon() const
{
	return QVariant::fromValue(m_icon);
}

QColor IconView::backgroundColor() const
{
	return m_backgroundColor;
}

void IconView::setIcon(QVariant val)
{
	if (val.canConvert<QIcon>()) {
		m_icon = val.value<QIcon>();
	} else if (val.canConvert<QColor>()) {
		m_color = val.value<QColor>();
		m_icon = QIcon();
	} else if (val.canConvert<QPixmap>()) {
		m_icon = QIcon(val.value<QPixmap>());
	} else {
		m_icon = QIcon();
		m_color = QColor(Qt::white);
	}

	update();
	emit iconChanged(val);
}

void IconView::setBackgroundColor(const QColor &color)
{
	if (color == m_backgroundColor) {
		return;
	}

	m_backgroundColor = color;
	emit backgroundColorChanged(m_backgroundColor);
}

void IconView::paint(QPainter *p)
{
	if (m_backgroundColor.isValid()) {
		p->fillRect(0, 0, width(), height(), m_backgroundColor);
	}

	if (m_icon.isNull()) {
		p->fillRect(0, 0, width(), height(), m_color);
		return;
	}

	m_icon.paint(p, QRect(0, 0, width(), height()), Qt::AlignCenter);
}
