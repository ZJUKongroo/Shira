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

#include "abstractnavigation.h"

#include "modularity/ioc.h"

using namespace shira::ui;

AbstractNavigation::AbstractNavigation(QObject *parent)
	: QObject(parent), Injectable(shira::modularity::iocCtxForQmlObject(this))
{
}

int AbstractNavigation::order() const
{
	return m_index.order();
}

int AbstractNavigation::column() const
{
	return m_index.column;
}

int AbstractNavigation::row() const
{
	return m_index.row;
}

QString AbstractNavigation::name() const
{
	return m_name;
}

const INavigation::Index &AbstractNavigation::index() const
{
	return m_index;
}

void AbstractNavigation::setIndex(const INavigation::Index &index)
{
	if (m_index == index) {
		return;
	}

	bool _rowChanged = m_index.row != index.row;
	bool _columnChanged = m_index.column != index.column;
	bool _orderChanged = m_index.order() != index.order();

	m_index = index;
	
	if (_rowChanged) {
		emit rowChanged(m_index.row);
	}

	if (_columnChanged) {
		emit columnChanged(m_index.column);
	}
	
	if (_orderChanged) {
		emit orderChanged(m_index.order());
	}
}

bool AbstractNavigation::enabled() const
{
	return m_enabled;
}

bool AbstractNavigation::active() const
{
	return m_active;
}

bool AbstractNavigation::highlight() const
{
	return false;
}

void AbstractNavigation::onEvent(INavigation::EventPtr e)
{

}

QWindow *AbstractNavigation::window() const
{
	return nullptr;
}

QQuickItem *AbstractNavigation::visualItem() const
{
	return nullptr;
}

void AbstractNavigation::classBegin()
{

}

void AbstractNavigation::componentComplete()
{

}

void AbstractNavigation::setName(const QString &name)
{
	if (m_name == name) {
		return;
	}

	m_name = name;
	emit nameChanged(m_name);
}

void AbstractNavigation::setOrder(int order)
{
	if (m_index.order() == order) {
		return;
	}

	m_index.setOrder(order);
	emit orderChanged(m_index.order());
}

void AbstractNavigation::setColumn(int column)
{
	if (m_index.column == column) {
		return;
	}

	m_index.column = column;
	emit columnChanged(m_index.column);
}

void AbstractNavigation::setRow(int row)
{
	if (m_index.row == row) {
		return;
	}

	m_index.row = row;
	emit rowChanged(m_index.row);
}

void AbstractNavigation::setEnabled(bool enabled)
{
	if (m_enabled == enabled) {
		return;
	}

	m_enabled = enabled;
	emit enabledChanged(m_enabled);
}

void AbstractNavigation::setActive(bool active)
{
	if (m_active == active) {
		return;
	}

	m_active = active;
	emit activeChanged(m_active);
}
