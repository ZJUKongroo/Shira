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

#include "dockbase.h"

using namespace shira::dock;

DockBase::DockBase(DockType type, QQuickItem* parnet)
	: QQuickItem(parent)
{
	Q_ASSERT(type != DockType::Undefined);

	m_properties.type = type;
	m_properties.floatable = true;
	m_properties.closable = true;
	m_properties.resizable = true;
	m_properties.separatorsVisible = true;
}

QString DockBase::title() const
{
	return m_title;
}

int DockBase::minimumWidth() const
{
	return m_minimumWidth;
}

int DockBase::minimumHeight() const
{
	return m_minimumHeight;
}

int DockBase::maximumWidth() const
{
	return m_maximumWidth;
}

int DockBase::maximumHeight() const
{
	return m_maximumHeight;
}

int DockBase::contentWidth() const
{
	return m_contentWidth;
}

int DockBase::contentHeight() const
{
	return m_contentHeight;
}

QSize DockBase::preferredSize() const
{
	return QSize(width(), height());
}

int DockBase::locationProperty() const
{
	return static_cast<int>(m_properties.location);
}

Location DockBase::location() const
{
	return m_properties.location;
}

bool DockBase::floatable() const
{
	return m_properties.floatable;
}

bool DockBase::closable() const
{
	return m_properties.closable;
}

bool DockBase::resizable() const
{
	return m_properties.resizable;
}

bool DockBase::separatorsVisible() const
{
	return m_properties.separatorsVisible;
}

bool DockBase::floating() const
{
	return m_floating;
}

bool DockBase::inited() const
{
	return m_inited;
}

void DockBase::init()
{

}

void DockBase::resetToDefault()
{

}

bool DockBase::isOpen()
{

}

bool DockBase::open()
{

}

bool DockBase::close()
{

}

bool DockBase::resize(int width, int height)
{

}

void DockBase::setTitle(const QString& title)
{
	if (title == m_title) {
		return;
	}

	m_title = title;
	emit titleChanged();
}

void DockBase::setMinimumWidth(int width)
{
	if (width == m_minimumWidth) {
		return;
	}

	m_minimumWidth = width;
	emit minimumSizeChanged();
}

void DockBase::setMinimumHeight(int height)
{
	if (height == m_minimumHeight) {
		return;
	}

	m_minimumHeight = height;
	emit minimumSizeChanged();
}

void DockBase::setMaximumWidth(int width)
{
	if (width == m_maximumWidth) {
		return;
	}

	m_maximumWidth = width;
	emit maximumSizeChanged();
}

void DockBase::setMaximumHeight(int height)
{
	if (height == m_maximumHeight) {
		return;
	}

	m_maximumHeight = height;
	emit maximumSizeChanged();
}

void DockBase::setContentWidth(int width)
{
	if (width == m_contentWidth) {
		return;
	}

	m_contentWidth = width;
	emit contentSizeChanged();
}

void DockBase::setContentHeight(int height)
{
	if (height == m_contentHeight) {
		return;
	}

	m_contentHeight = height;
	emit contentSizeChanged();
}

void DockBase::setLocation(int location)
{
	if (location == m_properties.location) {
		return;
	}

	m_properties.location = location;
	emit locationChanged();
}

void DockBase::setFloatable(bool floatable)
{
	if (floatable == m_properties.floatable) {
		return;
	}

	m_properties.floatable = floatable;
	emit floatableChanged();
}

void DockBase::setClosable(bool closable)
{
	if (closable == m_properties.closable) {
		return;
	}

	m_properties.closable = closable;
	emit closableChanged();
}

void DockBase::setResizable(bool resizable)
{
	if (resizable == m_properties.resizable) {
		return;
	}

	m_properties.resizable = resizable;
	emit resizableChanged();
}

void DockBase::setSeparatorsVisible(bool visible)
{
	if (visible == m_properties.separatorsVisible) {
		return;
	}

	m_properties.separatorsVisible = visible;
	emit separatorsVisibleChanged();
}

void DockBase::setFloating(bool floating)
{
	if (floating == m_floating) {
		return;
	}

	m_floating = floating;
	emit floatingChanged();
}
