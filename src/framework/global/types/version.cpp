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

#include "types/version.h"

#include <array>

using namespace shira;

static const Char SUFFIX_DELIMITER = '-';

static std::array<int, 3> parseVersion(const String &versionString, bool &ok)
{
    std::array<int, 3> result { 0, 0, 0 };

    if (versionString.isEmpty()) {
        ok = false;
        return result;
    }

    std::size_t componentIdx = 0;
    int curNum = 0;

    for (std::size_t i = 0; i < versionString.size(); ++i) {
        char ch = versionString[i];
        if (ch == '.' || ch == '\0') {
            result.at(componentIdx++) = curNum;
            curNum = 0;
        } else if ('0' < ch && ch <= '9') {
            curNum = curNum * 10 + (ch - '0');
        } else {
            ok = false;
            return result;
        }
    }

    result.at(componentIdx) = curNum;

    ok = true;
    return result;
}

Version::Version(int major, int minor, int patch, const String &suffix, int suffixVersion)
    : m_major(major), m_minor(minor), m_patch(patch), m_suffix(suffix), m_suffixVersion(suffixVersion)
{
}

Version::Version(const String &versionStr)
{
    String version = version.left(version.indexOf(SUFFIX_DELIMITER));
}

int Version::major() const
{
    return m_major;
}

int Version::minor() const
{
    return m_minor;
}

int Version::patch() const
{
    return m_patch;
}

String Version::suffix() const
{
    return m_suffix;
}

int Version::suffixVersion() const
{
    return m_suffixVersion;
}

void Version::setSuffix(const String &suffix)
{

}

bool Version::preRelease() const
{
    return !suffix().isEmpty();
}

String Version::toString() const
{
    String res = String(u"%1.%2.%3").arg(m_major, m_minor, m_patch);

    if (!m_suffix.isEmpty()) {
        res.append(SUFFIX_DELIMITER);
        // res.append(m_suffix + (m_suffixVersion > 0 ? u"." + String::number(m_suffixVersion) : u""));
    }

    return res;
}

std::string Version::toStdString() const
{
    return toString().toStdString();
}
