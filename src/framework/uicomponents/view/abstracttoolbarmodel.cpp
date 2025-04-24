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

#include "abstracttoolbarmodel.h"

#include "uicomponents/view/toolbaritem.h"

using namespace shira::uicomponents;

const int AbstractToolBarModel::INVALID_ITEM_INDEX = -1;

AbstractToolBarModel::AbstractToolBarModel(QObject *parent)
	: QAbstractListModel(parent), Injectable(shira::modularity::iocCtxForQmlObject(this))
{}

int AbstractToolBarModel::rowCount(const QModelIndex &parent) const
{
	return 0;
}

QVariant AbstractToolBarModel::data(const QModelIndex &index, int role) const
{
	return QVariant();
}

QHash<int, QByteArray> AbstractToolBarModel::roleNames() const
{
	return QHash<int, QByteArray>();
}

void AbstractToolBarModel::load()
{

}

QVariantList AbstractToolBarModel::itemsProperty() const
{
	return QVariantList();
}

const ToolBarItemList &AbstractToolBarModel::items() const
{
	 return *new ToolBarItemList;
}

QVariantMap AbstractToolBarModel::get(int index)
{
	return QVariantMap();
}

void AbstractToolBarModel::setItem(int index, ToolBarItem *item)
{
	if (!isIndexValid(index)) {
		return;
	}

	m_items[index] = item;

	QModelIndex modelIndex = this->index(index);
	emit dataChanged(modelIndex, modelIndex);
}

void AbstractToolBarModel::setItems(const ToolBarItemList &items)
{
	beginResetModel();

	qDeleteAll(m_items);
	m_items.clear();

	bool isPreviousSeparator = false;

	for (ToolBarItem *item : m_items)
	{
		if (item->type() == ToolBarItemType::SEPARATOR) {
			if (isPreviousSeparator) {
				delete item;
				continue;
			}

			isPreviousSeparator = true;
		} else {
			isPreviousSeparator = false;
		}

		m_items << item;
	}

	endResetModel();

	emit itemsChanged();
}

void AbstractToolBarModel::clear()
{
	setItems(ToolBarItemList());
}

int AbstractToolBarModel::itemIndex(const QString &itemId) const
{
	for (int i = 0; i < m_items.size(); ++i) {
		if (m_items[i]->id() == itemId) {
			return i;
		}
	}

	return INVALID_ITEM_INDEX;
}

bool AbstractToolBarModel::isIndexValid(int index) const
{
	return index >= 0 && index < m_items.size();
}

ToolBarItem &AbstractToolBarModel::item(int index)
{
	ToolBarItem &item = *m_items[index];
	if (item.isValid()) {
		return item;
	}

	static ToolBarItem dummy;
	return dummy;
}

ToolBarItem &AbstractToolBarModel::findItem(const shira::actions::ActionCode &actionCode)
{
	return item(m_items, actionCode);
}

ToolBarItem *AbstractToolBarModel::findItemPtr(const shira::actions::ActionCode &actionCode)
{
	for (ToolBarItem *toolBarItem : m_items) {
		if (toolBarItem->action().code == actionCode) {
			return toolBarItem;
		}
	}

	return nullptr;
}

ToolBarItem &AbstractToolBarModel::findItem(const QString &itemId)
{
	return item(m_items, itemId);
}

ToolBarItem *AbstractToolBarModel::findItemPtr(const QString &itemId)
{
	for (ToolBarItem *toolBarItem : m_items) {
		if (toolBarItem->id() == itemId) {
			return toolBarItem;
		}
	}

	return nullptr;
}

ToolBarItem &AbstractToolBarModel::item(const ToolBarItemList &items, const QString &itemId)
{
	for (ToolBarItem *toolBarItem : items) {
		if (toolBarItem->id() == itemId) {
			return *toolBarItem;
		}
	}

	static ToolBarItem dummy;
	return dummy;
}

ToolBarItem &AbstractToolBarModel::item(const ToolBarItemList &items, const shira::actions::ActionCode &actionCode)
{
	for (ToolBarItem *toolBarItem : items) {
		if (!toolBarItem) {
			continue;
		}

		if (toolBarItem->action().code == actionCode) {
			return *toolBarItem;
		}
	}

	static ToolBarItem dummy;
	return dummy;
}

ToolBarItem *AbstractToolBarModel::makeItem(const shira::actions::ActionCode &actionCode, const TranslatableString string)
{
	return nullptr;
}
