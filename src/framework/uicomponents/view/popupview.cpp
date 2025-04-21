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

#include "popupview.h"

using namespace shira::uicomponents;

PopupView::PopupView(QQuickItem *parent)
	: QObject(parent), Injectable(shira::modularity::iocCtxForQmlObject(this))
{

}

PopupView::~PopupView()
{

}

QQuickItem *PopupView::parentItem() const
{
	if (!parent()) {
		return nullptr;
	}

	return qobject_cast<QQuickItem *>(parent());
}

QQuickItem *PopupView::contentItem() const
{
	return m_contentItem;
}

int PopupView::contentWidth() const
{
	return m_contentWidth;
}

int PopupView::contentHeight() const
{
	return m_contentHeight;
}

QWindow *PopupView::window() const
{
	return nullptr;
}

qreal PopupView::localX() const
{
	return m_localPos.x();
}

qreal PopupView::localY() const
{
	return m_localPos.y();
}

QRect PopupView::geometry() const
{
	return QRect();
}

void PopupView::init()
{

}

PopupView::OpenPolicies PopupView::openPolicies() const
{
	return m_openPolicies;
}

PopupView::ClosePolicies PopupView::closePolicies() const
{
	return m_closePolicies;
}

PopupView::Placement PopupView::placement() const
{
	return m_placement;
}

PopupView::FocusPolicies PopupView::focusPolicies() const
{
	return m_focusPolicies;
}

QString PopupView::title() const
{
	return m_title;
}

bool PopupView::resizable() const
{
	return m_resizable;
}

void PopupView::setParentItem(QQuickItem *parent)
{
	if (parent == parentItem()) {
		return;
	}

	setParent(parent);
	emit parentItemChanged(parentItem());
}

void PopupView::setEngine(QQmlEngine *engine)
{

}

void PopupView::setContentItem(QQuickItem *content)
{
	if (content == m_contentItem) {
		return;
	}

	m_contentItem = content;
	emit contentItemChanged(m_contentItem);
}

void PopupView::setContentWidth(int contentWidth)
{
	if (contentWidth == m_contentWidth) {
		return;
	}

	m_contentWidth = contentWidth;
	emit contentWidthChanged(m_contentWidth);
}

void PopupView::setContentHeight(int contentHeight)
{
	if (contentHeight == m_contentHeight) {
		return;
	}

	m_contentHeight = contentHeight;
	emit contentHeightChanged(m_contentHeight);
}

void PopupView::setLocalX(qreal x)
{
	if (x == localX()) {
		return;
	}

	m_localPos.setX(x);
	emit localPosChanged(m_localPos);
}

void PopupView::setLocalY(qreal y)
{
	if (y == localY()) {
		return;
	}

	m_localPos.setY(y);
	emit localPosChanged(m_localPos);
}

void PopupView::setOpenPolicies(OpenPolicies openPolicies)
{
	if (openPolicies == m_openPolicies) {
		return;
	}

	m_openPolicies = openPolicies;
	emit openPoliciesChanged(m_openPolicies);
}

void PopupView::setClosePolicies(ClosePolicies closePolicies)
{
	if (closePolicies == m_closePolicies) {
		return;
	}

	m_closePolicies = closePolicies;
	emit closePoliciesChanged(m_closePolicies);
}

void PopupView::setPlacement(Placement newPlacement)
{
	if (newPlacement == m_placement) {
		return;
	}

	m_placement = newPlacement;
	emit placementChanged(m_placement);
}

void PopupView::setTitle(QString title)
{
	if (title == m_title) {
		return;
	}

	m_title = title;
	emit titleChanged(m_title);
}

void PopupView::setResizable(bool resizable)
{
	if (resizable == m_resizable) {
		return;
	}

	m_resizable = resizable;
	emit resizableChanged(m_resizable);
}

void PopupView::setAnchorItem(QQuickItem *anchorItem)
{
	if (anchorItem == m_anchor) {
		return;
	}

	m_anchor = anchorItem;
	emit anchorItemChanged(m_anchor);
}

void PopupView::setFocusPolicies(const FocusPolicies &focusPolicies)
{
	if (focusPolicies == m_focusPolicies) {
		return;
	}

	m_focusPolicies = focusPolicies;
	emit focusPoliciesChanged(m_focusPolicies);
}
