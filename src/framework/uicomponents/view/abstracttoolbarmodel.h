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

#ifndef UICOMPONENTS_VIEW_ABSTRACTTOOLBARMODEL_H
#define UICOMPONENTS_VIEW_ABSTRACTTOOLBARMODEL_H

#include <QtCore/QAbstractListModel>

#include "modularity/ioc.h"
#include "actions/actiontypes.h"
#include "global/types/translatablestring.h"

namespace shira::uicomponents {

class ToolBarItem;
class MenuItem;
using ToolBarItemList = QList<ToolBarItem *>;

class ToolBarItemType
{
	Q_GADGET

public:
	enum Type
	{
		ACTION,
		SEPARATOR,
		USER_TYPE,
	};
	Q_ENUM(Type)
};

class AbstractToolBarModel : public QAbstractListModel, public shira::modularity::Injectable
{
	Q_OBJECT

	Q_PROPERTY(int length READ rowCount NOTIFY itemsChanged)
	Q_PROPERTY(QVariantList items READ itemsProperty NOTIFY itemsChanged)

public:
	explicit AbstractToolBarModel(QObject *parent = nullptr);

	const shira::actions::ActionCode SEPARATOR_ID = "";

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;

	Q_INVOKABLE virtual void load();
	
	QVariantList itemsProperty() const;
	const ToolBarItemList &items() const;

	Q_INVOKABLE QVariantMap get(int index);

signals:
	void itemsChanged();
	void itemChanged(ToolBarItem *item);

protected:
	enum Roles {
		ItemRole,
		UserRole,
	};

	void setItem(int index, ToolBarItem *item);
	void setItems(const ToolBarItemList &items);
	void clear();

	static const int INVALID_ITEM_INDEX;

	int itemIndex(const QString &itemId) const;

	ToolBarItem &item(int index);

	ToolBarItem &findItem(const shira::actions::ActionCode &actionCode);
	ToolBarItem *findItemPtr(const shira::actions::ActionCode &actionCode);
	ToolBarItem &findItem(const QString &itemId);
	ToolBarItem *findItemPtr(const QString &itemId);

	ToolBarItem *makeItem(const shira::actions::ActionCode &actionCode, const TranslatableString string);

	bool isIndexValid(int index) const;

private:
	ToolBarItem &item(const ToolBarItemList &items, const QString &itemId);
	ToolBarItem &item(const ToolBarItemList &items, const shira::actions::ActionCode &actionCode);

	ToolBarItemList m_items;
};

}

#endif // UICOMPONENTS_VIEW_ABSTRACTTOOLBARMODEL_H
