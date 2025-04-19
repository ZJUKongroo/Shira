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

#ifndef DOCK_DOCKTYPES_H
#define DOCK_DOCKTYPES_H

#include <QtCore/QObject>

namespace shira::dock {

enum class DockType {
    Undefined = -1,
    Panel,
    ToolBar,
    DockingHolder,
    StatusBar,
    Central,
};

class DockLocation
{
    Q_GADGET

public:
    enum Location {
        Undefined,
        Left,
        Right,
        Center,
        Top,
        Bottom,
    };

    Q_ENUM(Location);
};

using Location = DockLocation::Location;

struct DockProperties
{
    DockType type = DockType::Undefined;
    Location location = Location::Undefined;
    bool floatable = false;
    bool closable = false;
    bool resizable = false;
    bool separatorsVisible = false;
    bool selected = false;
    QRect highlightingRect;

    bool isValid() const
    {
        return type != DockType::Undefined;
    }
};

}

#endif // DOCK_DOCKTYPES_H
