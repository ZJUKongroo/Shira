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

#include "menuview.h"

using namespace shira::uicomponents;

static const QString MENU_VIEW_CONTENT_OBJECT_NAME("_MenuViewContent");

MenuView::MenuView(QQuickItem *parent)
	: PopupView(parent)
{
	setObjectName("MenuView");
}

int MenuView::viewVerticalMargin() const
{
	return 4;
}

Qt::AlignmentFlag MenuView::cascadeAlign() const
{
	return m_cascadeAlign;
}

int MenuView::contentWidth() const
{
	return m_contentWidth;
}

void MenuView::setContentWidth(int newContentWidth)
{
	if (newContentWidth == m_contentWidth) {
		return;
	}

	m_contentWidth = newContentWidth;
	emit contentWidthChanged();
}

int MenuView::contentHeight() const
{
	return m_contentHeight;
}

void MenuView::setContentHeight(int newContentHeight)
{
	if (newContentHeight == m_contentHeight) {
		return;
	}

	m_contentHeight = newContentHeight;
	emit contentHeightChanged();
}

void MenuView::setCascadeAlign(Qt::AlignmentFlag cascadeAlign)
{
	if (cascadeAlign == m_cascadeAlign) {
		return;
	}

	m_cascadeAlign = cascadeAlign;
	emit cascadeAlignChanged(m_cascadeAlign);
}

void MenuView::componentComplete()
{
	m_contentItem->setObjectName(m_contentItem->objectName() + MENU_VIEW_CONTENT_OBJECT_NAME);

	// PopupView::componentComplete();
}
