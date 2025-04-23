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

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <string>

#ifndef NO_QT_SUPPORT
class QString;
#endif

#include "types/string.h"

namespace shira {

std::string trc(const char *context, const char *key, const char *disambiguation = nullptr, int n = -1);

String mtrc(const char *context, const char *key, const char *disambiguation = nullptr, int n = -1);
String mtrc(const char *context, const String &key, const char *disambiguation = nullptr, int n = -1);
String mtrc(const char *context, const String &key, const String &disambiguation, int n = -1);

#ifndef NO_QT_SUPPORT
QString qtrc(const char *context, const char *key, const char *disambiguation = nullptr, int n = -1);
QString qtrc(const char *context, const String &key, const char *disambiguation = nullptr, int n = -1);
QString qtrc(const char *context, const String &key, const String &disambiguation, int n = -1);
#endif

}

#endif // TRANSLATION_H
