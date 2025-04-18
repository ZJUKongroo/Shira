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

#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

namespace shira {

static constexpr std::size_t nidx = static_cast<std::size_t>(-1);

template <typename T>
inline bool contains(const std::vector<T> &vec, const T &v)
{
    return std::find(vec.cbegin(), vec.cend(), v) != vec.cend();
}

template <typename T>
inline T value(const std::vector<T> &vec, std::size_t idx)
{
    if (idx < vec.size()) {
        return vec.at(idx);
    }

    if constexpr (std::is_pointer<T>::value) {
        return nullptr;
    } else {
        return T();
    }
}

template <typename T>
inline bool remove(std::vector<T> &vec, const T &v)
{
    std::size_t origSize = vec.size();
    vec.erase(std::remove(vec.begin(), vec.end(), v), vec.end());
    return origSize != vec.size();
}

template <typename T, typename Predicate>
inline bool remove_if(std::vector<T> &vec, Predicate p)
{
    std::size_t origSize = vec.size();
    vec.erase(std::remove_if(vec.begin(), vec.end(), p), vec.end());
    return origSize != vec.size();
}

template <typename T>
inline void removeFirst(std::vector<T> &vec)
{
    vec.erase(vec.begin());
}

template <typename T>
inline T takeAt(std::vector<T> &vec, std::size_t idx)
{
    T v = value(vec, idx);
    vec.erase(vec.begin() + idx);
    return v;
}

template <typename T>
inline T takeFirst(std::vector<T> &vec, std::size_t idx)
{
    return takeAt(vec, 0);
}

template <typename T>
inline T takeLast(std::vector<T> &vec)
{
    return takeAt(vec, vec.size() - 1);
}

template <typename T>
inline void swapItemsAt(std::vector<T> &vec, std::size_t idx1, std::size_t idx2)
{
    T v1 = vec[idx1];
    vec[idx1] = vec[idx2];
    vec[idx2] = v1;
}

template <typename T>
inline bool moveItem(std::vector<T> &vec, std::size_t oldIdx, std::size_t newIdx)
{
    if (oldIdx == nidx || oldIdx == newIdx) {
        return false;
    }

    newIdx = std::min(vec.size() - 1, newIdx);

    if (oldIdx > newIdx) {
        std::rotate(vec.rend() - oldIdx - 1, vec.rend() - oldIdx, vec.rend() - newIdx);
    } else {
        std::rotate(vec.begin() + oldIdx, vec.begin() + oldIdx + 1, vec.begin() + newIdx + 1);
    }

    return true;
}

template <typename T>
std::vector<T> mid(const std::vector<T> &c, std::size_t pos, int alength = -1)
{
    if (c.empty()) {
        return std::vector<T>();
    }

    std::size_t end = 0;
    if (alength < 0) {
        end = c.size();
    } else {
        end = pos + static_cast<std::size_t>(alength);
    }

    if (end > (c.size())) {
        end = c.size();
    }

    if (end == 0) {
        return std::vector<T>();
    }

    if (pos >= end) {
        return std::vector<T>();
    }

    std::vector<T> sub(c.begin() + pos, c.begin() + end);
    return sub;
}

template <typename T>
inline void join(std::vector<T> &l1, const std::vector<T> &l2)
{
    l1.insert(l1.end(), l2.begin(), l2.end());
}

template <typename T>
inline bool contains(const std::list<T> &l, const T &v)
{
    return std::find(l.cbegin(), l.cend(), v) != l.cend();
}

template <typename T>
inline void join(std::list<T> &l1, const std::list<T> &l2)
{
    l1.insert(l1.end(), l2.begin(), l2.end());
}

template <typename T>
inline bool remove(std::list<T> &l, const T &v)
{
    if (!contains(l, v)) {
        return false;
    }
    l.remove(v);
    return true;
}

template <typename T>
inline T takeFirst(std::list<T> &l)
{
    T v = l.front();
    l.pop_front();
    return v;
}

template <typename T>
inline T takeLast(std::list<T> &l)
{
    T v = l.back();
    l.pop_back();
    return v;
}

template <typename T>
inline std::pair<bool, T> take(std::list<T> &l, const T &v)
{
    auto it = std::find(l.begin(), l.end(), v);
    if (it == l.end()) {
        return std::make_pair(false, T());
    }
    std::pair<bool, T> ret = std::make_pair(true, *it);
    l.erase(it);
    return ret;
}

template <typename T>
inline bool contains(const std::set<T> &s, const T &v)
{
    return s.find(v) != s.cend();
}

template <typename T>
inline bool contains(const std::unordered_set<T> &s, const T &v)
{
    return s.find(v) != s.cend();
}

template <typename T, std::size_t size>
inline bool contains(const std::array<T, size> &s, const T &v)
{
    return std::find(s.begin(), s.end(), v) != s.cend();
}

template <typename Container, typename T>
inline std::size_t indexOf(const Container &c, const T &v)
{
    auto it = std::find(c.cbegin(), c.cend(), v);
    if (it != c.cend()) {
        return std::distance(c.cbegin(), it);
    }
    return nidx;
}

template <typename K, typename V>
inline bool contains(const std::map<K, V> &m, const K &k)
{
    return m.find(k) != m.cend();
}

template <typename K, typename V>
inline bool contains(const std::multimap<K, V> &m, const K &k)
{
    return m.find(k) != m.cend();
}

template <typename K, typename V>
inline bool contains(const std::unordered_map<K, V> &m, const K &k)
{
    return m.find(k) != m.cend();
}

}

#endif // CONTAINERS_H
