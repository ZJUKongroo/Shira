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

#ifndef VIEW_MAINWINDOWTITLEPROVIDER_H
#define VIEW_MAINWINDOWTITLEPROVIDER_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "modularity/ioc.h"

namespace shira::appshell {

class MainWindowTitleProvider : public QObject, public shira::modularity::Injectable
{
	Q_OBJECT

	Q_PROPERTY(QString title READ title NOTIFY titleChanged)
	Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged)
	Q_PROPERTY(bool fileModified READ fileModified NOTIFY fileModifiedChanged)

public:
	MainWindowTitleProvider(QObject *parent = nullptr);

	Q_INVOKABLE void load();

	QString title() const;
	QString filePath() const;
	bool fileModified() const;

signals:
	void titleChanged(QString title);
	void filePathChanged(QString filePath);
	void fileModifiedChanged(bool fileModified);

private:
	void update();

	void setTitle(const QString &title);
	void setFilePath(const QString &filePath);
	void setFileModified(bool fileModified);

	QString m_title;
	QString m_filePath;
	bool m_fileModified;
};

}

#endif // VIEW_MAINWINDOWTITLEPROVIDER_H
