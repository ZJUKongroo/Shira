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

#ifndef UICOMPONENTS_VIEW_DIALOGVIEW_H
#define UICOMPONENTS_VIEW_DIALOGVIEW_H

#include "popupview.h"

#include "modularity/ioc.h"

namespace shira::uicomponents {

class DialogView : public PopupView
{
	Q_OBJECT

	// shira::Inject<IApplication> application;

public:
	explicit DialogView(QQuickItem *parent = nullptr);
	~DialogView() override = default;

	Q_INVOKABLE void exec();
	Q_INVOKABLE void show();
	Q_INVOKABLE void hide();
	Q_INVOKABLE void raise();
	Q_INVOKABLE void accept();
	Q_INVOKABLE void reject(int code = -1);

private:
	// bool isDialog() const override;
	// void beforeOpen() override;
	// void onHidden() override;
	   
	// QScreen *resolveScreen() const override;
	   
	// void updateGeometry() override;
	   
	// QRect viewGeometry() const override;

	QEventLoop m_loop;
};

}

#endif // UICOMPONENTS_VIEW_DIALOGVIEW_H
