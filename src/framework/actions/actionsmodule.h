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

#ifndef ACTIONS_ACTIONSMODULE_H
#define ACTIONS_ACTIONSMODULE_H

#include "modularity/imodulesetup.h"

namespace shira::actions {

class ActionsModule : public shira::modularity::IModuleSetup
{
public:
	std::string moduleName() const override;

	void onInit() override;
};

}

#endif // ACTIONS_ACTIONSMODULE_H
