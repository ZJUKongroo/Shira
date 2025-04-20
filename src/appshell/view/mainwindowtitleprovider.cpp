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

#include "mainwindowtitleprovider.h"

#include "modularity/ioc.h"

using namespace shira::appshell;

MainWindowTitleProvider::MainWindowTitleProvider(QObject *parent)
	: QObject(parent), Injectable(shira::modularity::iocCtxForQmlObject(this))
{
}

void MainWindowTitleProvider::load()
{
	update();
}

QString MainWindowTitleProvider::title() const
{
	return m_title;
}

QString MainWindowTitleProvider::filePath() const
{
	return m_filePath;
}

bool MainWindowTitleProvider::fileModified() const
{
	return m_fileModified;
}

void MainWindowTitleProvider::update()
{
	setTitle("This is a test!");
	setFilePath("");
	setFileModified(false);
}

void MainWindowTitleProvider::setTitle(const QString &title)
{
	if (title == m_title) {
		return;
	}

	m_title = title;
	emit titleChanged(m_title);
}

void MainWindowTitleProvider::setFilePath(const QString &filePath)
{
	if (filePath == m_filePath) {
		return;
	}
	
	m_filePath = filePath;
	emit filePathChanged(m_filePath);
}

void MainWindowTitleProvider::setFileModified(bool fileModified)
{
	if (fileModified == m_fileModified) {
		return;
	}

	m_fileModified = fileModified;
	emit fileModifiedChanged(m_fileModified);
}
