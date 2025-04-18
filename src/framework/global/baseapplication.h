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

#ifndef BASEAPPLICATION_H
#define BASEAPPLICATION_H

#include "iapplication.h"

namespace shira {

class BaseApplication : public IApplication
{
public:
    virtual ~BaseApplication() = default;

    virtual String name() const override { return u"Shira"; }
    virtual String title() const override { return u"Shira title"; }

    virtual Version version() const override { return String(u"1.0.0"); }
};

}

#endif // BASEAPPLICATION_H
