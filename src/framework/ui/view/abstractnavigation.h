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

#ifndef UI_VIEW_ABSTRACTNAVIGATION_H
#define UI_VIEW_ABSTRACTNAVIGATION_H

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

#include "modularity/ioc.h"
#include "ui/inavigation.h"

namespace shira::ui {

class AbstractNavigation : public QObject, public QQmlParserStatus, public shira::modularity::Injectable
{
	Q_OBJECT

	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

	Q_PROPERTY(int order READ order WRITE setOrder NOTIFY orderChanged)
	Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
	Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)

	Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
	Q_PROPERTY(bool active READ active NOTIFY activeChanged)
	Q_PROPERTY(bool highlight READ highlight NOTIFY highlightChanged)

	Q_INTERFACES(QQmlParserStatus)

public:
	explicit AbstractNavigation(QObject *parent = nullptr);

	int order() const;
	int column() const;
	int row() const;

	QString name() const;

	const INavigation::Index &index() const;
	void setIndex(const INavigation::Index &index);

	bool enabled() const;

	bool active() const;

	bool highlight() const;

	void onEvent(INavigation::EventPtr e);

	QWindow *window() const;
	QQuickItem *visualItem() const;

	void classBegin() override;
	void componentComplete() override;

public slots:
	void setName(const QString &name);
	void setOrder(int order);
	void setColumn(int column);
	void setRow(int row);
	void setEnabled(bool enabled);
	void setActive(bool active);

signals:
	void nameChanged(QString name);
	void orderChanged(int order);
	void columnChanged(int column);
	void rowChanged(int row);
	void enabledChanged(int enabled);
	void activeChanged(int active);
	void highlightChanged();

	void navigationEvent(QVariant event);

protected:
	QString m_name;
	INavigation::Index m_index;

	bool m_enabled = true;

	bool m_active = false;

	// NavigationEvent *m_event = nullptr;
};

}

#endif // UI_VIEW_ABSTRACTNAVIGATION_H
