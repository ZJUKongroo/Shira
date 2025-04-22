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

#ifndef UICOMPONENTS_VIEW_MENUVIEW_H
#define UICOMPONENTS_VIEW_MENUVIEW_H

#include "popupview.h"

namespace shira::uicomponents {

class MenuView : public PopupView
{
	Q_OBJECT

	Q_INTERFACES(QQmlParserStatus)

	Q_PROPERTY(int contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged)
	Q_PROPERTY(int contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentHeightChanged)

	Q_PROPERTY(Qt::AlignmentFlag cascadeAlign READ cascadeAlign WRITE setCascadeAlign NOTIFY cascadeAlignChanged)

public:
	explicit MenuView(QQuickItem *parent = nullptr);
	~MenuView() override = default;

	Q_INVOKABLE int viewVerticalMargin() const;

	Qt::AlignmentFlag cascadeAlign() const;

	int contentWidth() const;
	void setContentWidth(int newContentWidth);

	int contentHeight() const;
	void setContentHeight(int newContentHeight);

public slots:
	void setCascadeAlign(Qt::AlignmentFlag cascadeAlign);

signals:
	void cascadeAlignChanged(Qt::AlignmentFlag cascadeAlign);

	void contentWidthChanged();
	void contentHeightChanged();

private:
	void componentComplete() override;

	// void updateGeometry() override;
	// void updateContentPosition() override;

	// QRect viewGeometry() const override;

	// Qt::AlignmentFlag parentCascadeAlign(const QQuickItem *parent) const;

	// QQuickItem *parentMenuConentItem() const;

	Qt::AlignmentFlag m_cascadeAlign = Qt::AlignmentFlag::AlignRight;

	int m_contentWidth = -1;
	int m_contentHeight = -1;
};

}

#endif // UICOMPONENTS_VIEW_MENUVIEW_H
