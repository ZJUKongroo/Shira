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

#include "menuitem.h"

using namespace shira::uicomponents;

MenuItem::MenuItem(QObject *parent)
	: QObject(parent)
{
}

QString MenuItem::id() const
{
	return m_id;
}

QString MenuItem::section() const
{
	return m_section;
}

bool MenuItem::selectable() const
{
	return m_selectable;
}

bool MenuItem::selected() const
{
	return m_selected;
}

QList<MenuItem *> MenuItem::subitems() const
{
	return m_subitems;
}

void MenuItem::setId(const QString &id)
{
	if(id == m_id) {
		return;
	}

	m_id = id;
	emit idChanged(m_id);
}

void MenuItem::setSection(const QString &section)
{
	if(section == m_section) {
		return;
	}

	m_section = section;
	emit sectionChanged(m_section);
}

void MenuItem::setSelectable(bool selectable)
{
	if(selectable == m_selectable) {
		return;
	}

	m_selectable = selectable;
	emit selectableChanged(m_selectable);
}

void MenuItem::setSelected(bool selected)
{
	if(selected == m_selected) {
		return;
	}

	m_selected = selected;
	emit selectedChanged(m_selected);
}

void MenuItem::setSubitems(const QList<MenuItem *> &subitems)
{
	if(subitems == m_subitems) {
		return;
	}

	m_subitems = subitems;
	emit subitemsChanged(m_subitems, m_id);
}

bool MenuItem::selectable_property() const
{
	return m_selectable;
}

bool MenuItem::selected_property() const
{
	return m_selected;
}
