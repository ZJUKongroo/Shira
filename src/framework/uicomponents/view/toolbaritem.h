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

#ifndef UICOMPONENTS_VIEW_TOOLBARITEM_H
#define UICOMPONENTS_VIEW_TOOLBARITEM_H

#include <QtCore/QObject>

#include "modularity/ioc.h"
#include "ui/uiaction.h"
#include "menuitem.h"

namespace shira::uicomponents {

class ToolBarItem : public QObject, public shira::modularity::Injectable
{
	Q_OBJECT

public slots:
	void setId(const QString &id);
	void setTitle(const QString &title);

signals:
	void idChanged(QString id);
	void titleChanged(QString title);

private:
	QString m_id;
	QString m_title;
	shira::ui::UiActionState m_state;
	bool m_selected = false;
	QList<MenuItem *> m_menuItems;
	bool m_isMenuSecondary = false;
	bool m_showTitle = false;
	bool m_isTitleBold = false;

	shira::ui::UiAction m_action;
};

using ToolBarItemList = QList<ToolBarItem *>;

}

#endif // UICOMPONENTS_VIEW_TOOLBARITEM_H
