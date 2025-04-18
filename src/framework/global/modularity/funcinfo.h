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

#ifndef GLOBAL_MODULARITY_FUNCINFO_H
#define GLOBAL_MODULARITY_FUNCINFO_H

#include <string_view>

#ifndef FUNC_SIG
#  if defined(_MSC_VER)
#    define FUNC_SIG __FUNCSIG__
#  else
#    define FUNC_SIG __PRETTY_FUNCTION__
#  endif
#endif

#define FUNCNAME shira::modularity::funcNameBySig(FUNC_SIG)
#define CLASSNAME shira::modularity::classNameBySig(FUNC_SIG)
#define CLASSFUNC shira::modularity::classFuncBySig(FUNC_SIG)
#define MODULENAME shira::modularity::moduleNameBySig(FUNC_SIG)

namespace shira::modularity {

constexpr std::string_view funcNameBySig(const std::string_view &sig)
{
    return std::string_view();
}

constexpr std::string_view classNameBySig(const std::string_view &sig)
{
    return std::string_view();
}

constexpr std::string_view classFuncBySig(const std::string_view &sig)
{
    return std::string_view();
}

constexpr std::string_view moduleNameBySig(const std::string_view &sig)
{
    return std::string_view();
}

}

#endif // GLOBAL_MODULARITY_FUNCINFO_H
