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
    constexpr std::string_view Colon("::");
    constexpr std::string_view ArgBegin("(");
    constexpr std::string_view Space(" ");

    std::size_t endFunc = sig.find_first_of(ArgBegin);
    if (endFunc == std::string_view::npos) {
        return sig;
    }

    std::size_t beginFunc = sig.find_last_of(Colon, endFunc);
    if (beginFunc == std::string_view::npos) {
        beginFunc = sig.find_last_of(Space, endFunc);
    }

    if (beginFunc == std::string_view::npos) {
        beginFunc = 0;
    } else {
        beginFunc += 1;
    }

    return sig.substr(beginFunc, (endFunc - beginFunc));
}

constexpr std::string_view classNameBySig(const std::string_view &sig)
{
    constexpr std::string_view Colon("::");
    constexpr std::string_view ArgBegin("(");
    constexpr std::string_view Space(" ");

    std::size_t endFunc = sig.find_first_of(ArgBegin);
    if (endFunc == std::string_view::npos) {
        return sig;
    }

    std::size_t beginFunc = sig.find_last_of(Colon, endFunc);
    if (beginFunc == std::string_view::npos) {
        return std::string_view();
    }

    std::size_t beginClassColon = sig.find_last_of(Colon, beginFunc - 2);
    std::size_t beginClassSpace = sig.find_last_of(Space, beginFunc - 2);

    std::size_t beginClass = std::string_view::npos;
    if (beginClassColon == std::string_view::npos) {
        beginClass = beginClassSpace;
    } else if (beginClassSpace == std::string_view::npos) {
        beginClass = beginClassColon;
    } else {
        beginClass = std::max(beginClassColon, beginClassSpace);
    }

    if (beginClass == std::string_view::npos) {
        beginClass = 0;
    } else {
        beginClass += 1;
    }

    return sig.substr(beginClass, (beginFunc - 1 - beginClass));
}

constexpr std::string_view classFuncBySig(const std::string_view &sig)
{
    constexpr std::string_view Colon("::");
    constexpr std::string_view ArgBegin("(");
    constexpr std::string_view Space(" ");

    std::size_t endFunc = sig.find_first_of(ArgBegin);
    if (endFunc == std::string_view::npos) {
        return sig;
    }

    std::size_t beginFunc = sig.find_last_of(Colon, endFunc);
    if (beginFunc == std::string_view::npos) {
        return funcNameBySig(sig);
    }

    std::size_t beginClassColon = sig.find_last_of(Colon, beginFunc - 2);
    std::size_t beginClassSpace = sig.find_last_of(Space, beginFunc - 2);

    std::size_t beginClass = std::string_view::npos;
    if (beginClassColon == std::string_view::npos) {
        beginClass = beginClassSpace;
    } else if (beginClassSpace == std::string_view::npos) {
        beginClass = beginClassColon;
    } else {
        beginClass = std::max(beginClassColon, beginClassSpace);
    }

    if (beginClass == std::string_view::npos) {
        beginClass = 0;
    } else {
        beginClass += 1;
    }

    return sig.substr(beginClass, (endFunc - beginClass));
}

constexpr std::string_view moduleNameBySig(const std::string_view &sig)
{
    constexpr std::string_view Colon("::");
    constexpr std::string_view ArgBegin("(");
    constexpr std::string_view Space(" ");

    std::size_t endFunc = sig.find_first_of(ArgBegin);
    if (endFunc == std::string_view::npos) {
        return sig;
    }

    std::size_t beginFunc = sig.find_last_of(Space, endFunc);
    if (beginFunc == std::string_view::npos) {
        return std::string_view();
    }

    std::size_t beginModule = sig.find_first_of(Colon, beginFunc) + 2;
    if (beginModule == std::string_view::npos) {
        return std::string_view();
    }

    std::size_t endModule = sig.find_first_of(Colon, beginModule);
    if (endModule == std::string_view::npos) {
        return std::string_view();
    }

    return sig.substr(beginModule, (endModule - beginModule));
}

}

#endif // GLOBAL_MODULARITY_FUNCINFO_H
