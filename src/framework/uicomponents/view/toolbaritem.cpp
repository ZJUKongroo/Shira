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

#include "toolbaritem.h"

using namespace shira::uicomponents;

ToolBarItem::ToolBarItem(QObject *parent)
	: QObject(parent)
{
}

ToolBarItem::ToolBarItem(const shira::ui::UiAction &action, ToolBarItemType::Type type, QObject *parent)
	: QObject(parent)
{
	m_id = QString::fromStdString(action.code);
	m_action = action;
	m_type = type;
}

void ToolBarItem::activate()
{
	
}

void ToolBarItem::handleMenuItem(const QString &menuId)
{
	for (const MenuItem *menuItem : m_menuItems) {
		if (menuItem->id() == menuId) {

		}
	}
}

QString ToolBarItem::id() const
{
	return m_id;
}

QString ToolBarItem::translatedTitle() const
{
	return QString();
}

bool ToolBarItem::selected() const
{
	return m_selected;
}

ToolBarItemType::Type ToolBarItem::type() const
{
	return m_type;
}

QList<MenuItem *> ToolBarItem::menuItems() const
{
	return m_menuItems;
}

bool ToolBarItem::isMenuSecondary() const
{
	return m_isMenuSecondary;
}

void ToolBarItem::setIsMenuSecondary(bool secondary)
{
	if (secondary == m_isMenuSecondary) {
		return;
	}

	m_isMenuSecondary = secondary;
	emit isMenuSecondaryChanged(m_isMenuSecondary);
}

shira::ui::UiAction ToolBarItem::action() const
{
	return m_action;
}

shira::ui::UiActionState ToolBarItem::state() const
{
	return m_state;
}

shira::actions::ActionData ToolBarItem::args() const
{
	return m_args;
}

bool ToolBarItem::isValid() const
{
	return !m_id.isEmpty();
}

QString ToolBarItem::shortcutsTitle() const
{
	return QString();
}

bool ToolBarItem::showTitle() const
{
	return m_showTitle;
}

void ToolBarItem::setShowTitle(bool show)
{
	if (show == m_showTitle) {
		return;
	}

	m_showTitle = show;
	emit showTitleChanged();
}

bool ToolBarItem::isTransparent() const
{
	return m_isTransparent;
}

void ToolBarItem::setIsTransparent(bool isTransparent)
{
	if (isTransparent == m_isTransparent) {
		return;
	}

	m_isTransparent = isTransparent;
	emit isTransparentChanged();
}

bool ToolBarItem::isTitleBold() const
{
	return m_isTitleBold;
}

void ToolBarItem::setIsTitleBold(bool newIsTitleBold)
{
	if (newIsTitleBold == m_isTitleBold) {
		return;
	}

	m_isTitleBold = newIsTitleBold;
	emit isTitleBoldChanged();
}

void ToolBarItem::setId(const QString &id)
{
	if (id == m_id) {
		return;
	}

	m_id = id;
	emit idChanged(m_id);
}

void ToolBarItem::setTitle(const QString &title)
{
	// if (title == m_action.title) {
	//	   return;
	// }

	// m_action.title = title;
	emit titleChanged(title);
}

void ToolBarItem::setState(const shira::ui::UiActionState &state)
{
	if (state == m_state) {
		return;
	}

	m_state = state;
	emit stateChanged();
}

void ToolBarItem::setSelected(bool selected)
{
	if (selected == m_selected) {
		return;
	}

	m_selected = selected;
	emit selectedChanged(m_selected);
}

void ToolBarItem::setType(shira::uicomponents::ToolBarItemType::Type type)
{
	if (type == m_type) {
		return;
	}

	m_type = type;
	typeChanged(m_type);
}

void ToolBarItem::setMenuItems(const QList<shira::uicomponents::MenuItem *> &menuItems)
{
	if (menuItems == m_menuItems) {
		return;
	}

	m_menuItems = menuItems;
	emit menuItemsChanged(m_menuItems, m_id);
}

void ToolBarItem::setAction(const shira::ui::UiAction &action)
{
	if (action == m_action) {
		return;
	}

	m_action = action;
	emit actionChanged();
}

void ToolBarItem::setArgs(const shira::actions::ActionData &args)
{
	m_args = args;
}

QString ToolBarItem::code_property() const
{
	return QString::fromStdString(m_action.code);
}

QString ToolBarItem::description_property() const
{
	return QString();
}

int ToolBarItem::icon_property() const
{
	return 0;
}

bool ToolBarItem::enabled_property() const
{
	return m_state.enabled;
}

bool ToolBarItem::checkable_property() const
{
	return m_action.checkable == shira::ui::Checkable::Yes;
}

bool ToolBarItem::checked_property() const
{
	return m_state.checked;
}

bool ToolBarItem::selected_property() const
{
	return m_selected;
}

int ToolBarItem::type_property() const
{
	return static_cast<int>(m_type);
}
