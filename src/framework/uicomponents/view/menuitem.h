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

#ifndef UICOMPONENTS_VIEW_MENUITEM_H
#define UICOMPONENTS_VIEW_MENUITEM_H

#include <QtCore/QObject>

namespace shira::uicomponents {

class MenuItem : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString id READ id NOTIFY idChanged)

	Q_PROPERTY(QString section READ section NOTIFY sectionChanged)

	Q_PROPERTY(bool selectable READ selectable_property NOTIFY selectableChanged)
	Q_PROPERTY(bool selected READ selected_property NOTIFY selectedChanged)

	Q_PROPERTY(QList<MenuItem *> subitems READ subitems NOTIFY subitemsChanged)

public:
	MenuItem(QObject *parent = nullptr);

	QString id() const;
	QString section() const;

	bool selectable() const;
	bool selected() const;

	QList<MenuItem *> subitems() const;

public slots:
	void setId(const QString &id);
	void setSection(const QString &section);
	void setSelectable(bool selectable);
	void setSelected(bool selected);
	void setSubitems(const QList<MenuItem *> &subitems);

signals:
	void idChanged(QString id);
	void sectionChanged(QString section);
	void selectableChanged(bool selectable);
	void selectedChanged(bool selected);
	void subitemsChanged(QList<MenuItem *> subitems, const QString &menuId);

private:
	bool selectable_property() const;
	bool selected_property() const;

	QString m_id;
	QString m_section;
	bool m_selectable = false;
	bool m_selected = false;
	QList<MenuItem *> m_subitems;
};

}

#endif // UICOMPONENTS_VIEW_MENUITEM_H
