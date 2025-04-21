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

#ifndef UICOMPONENTS_VIEW_POPUPVIEW_H
#define UICOMPONENTS_VIEW_POPUPVIEW_H

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>
#include <QtQuick/QQuickItem>

#include "modularity/ioc.h"

namespace shira::uicomponents {

class PopupView : public QObject, public QQmlParserStatus, public shira::modularity::Injectable
{
	Q_OBJECT

	Q_INTERFACES(QQmlParserStatus)

public:
	explicit PopupView(QQuickItem *parent = nullptr);
	~PopupView() override;

	enum class OpenPolicy {
		Default = 0x00000000,
		NoActivateFocus = 0x00000001,
		OpenOnContentReady = 0x00000002,
	};
	Q_DECLARE_FLAGS(OpenPolicies, OpenPolicy)
	Q_FLAG(OpenPolicies)

	enum class ClosePolicy {
		NoAutoClose = 0x00000000,
		CloseOnPressOutsideParent = 0x00000001,
	};
	Q_DECLARE_FLAGS(ClosePolicies, ClosePolicy)
	Q_FLAG(ClosePolicies)

	enum class FocusPolicy {
		TabFocus = 0x00000001,
		ClickFocus = 0x00000002,
		DefaultFocus = FocusPolicy::TabFocus | FocusPolicy::ClickFocus,
		NoFocus = 0,
	};
	Q_DECLARE_FLAGS(FocusPolicies, FocusPolicy)
	Q_FLAG(FocusPolicies)

	enum class Placement {
		Default,
		PreferBelow,
		PreferAbove,
	};
	Q_ENUM(Placement)

	QQuickItem *parentItem() const;

	QQuickItem *contentItem() const;
	int contentWidth() const;
	int contentHeight() const;

	QWindow *window() const;

	qreal localX() const;
	qreal localY() const;
	QRect geometry() const;

	void init();

	OpenPolicies openPolicies() const;
	ClosePolicies closePolicies() const;
	Placement placement() const;

	FocusPolicies focusPolicies() const;

	QString title() const;
	bool resizable() const;

public slots:
	void setParentItem(QQuickItem *parent);
	void setEngine(QQmlEngine *engine);
	void setContentItem(QQuickItem *content);
	void setContentWidth(int contentWidth);
	void setContentHeight(int contentHeight);
	void setLocalX(qreal x);
	void setLocalY(qreal y);
	void setOpenPolicies(OpenPolicies openPolicies);
	void setClosePolicies(ClosePolicies closePolicies);
	void setPlacement(Placement newPlacement);
	void setTitle(QString title);
	void setResizable(bool resizable);

	void setAnchorItem(QQuickItem *anchorItem);

	void setFocusPolicies(const FocusPolicies &focusPolicies);

signals:
	void parentItemChanged(QQuickItem *parent);
	void contentItemChanged(QQuickItem *content);
	void contentWidthChanged(int contentWidth);
	void contentHeightChanged(int contentHeight);
	void localPosChanged(QPointF localPos);
	void openPoliciesChanged(OpenPolicies openPolicies);
	void closePoliciesChanged(ClosePolicies closePolicies);
	void placementChanged(Placement newPlacement);
	void titleChanged(QString title);
	void resizableChanged(bool resizable);
	void anchorItemChanged(QQuickItem *anchorItem);
	void focusPoliciesChanged(FocusPolicies focusPolicies);

protected:
	QQuickItem *m_contentItem = nullptr;
	int m_contentWidth = 0;
	int m_contentHeight = 0;

	QQuickItem *m_anchor = nullptr;

	QPointF m_localPos;
	QPointF m_globalPos;

	OpenPolicies m_openPolicies = { OpenPolicy::Default };
	ClosePolicies m_closePolicies = { ClosePolicy::CloseOnPressOutsideParent };
	FocusPolicies m_focusPolicies = { FocusPolicy::DefaultFocus };

	Placement m_placement = { Placement::Default };

	QString m_title;

	bool m_resizable;
};

}

#endif // UICOMPONENTS_VIEW_POPUPVIEW_H
