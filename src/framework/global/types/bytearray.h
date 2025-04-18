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

#ifndef TYPES_BYTEARRAY_H
#define TYPES_BYTEARRAY_H

#include <vector>
#include <memory>

namespace shira {

class ByteArray
{
public:
    typedef std::uint8_t value_type;

    ByteArray();

    std::uint8_t *data();
    const std::uint8_t *constData() const;
    const char *constChar() const;
    std::size_t size() const;
    bool empty() const;

    std::uint8_t at(std::size_t pos) const;
    std::uint8_t operator[](std::size_t pos) const;
    std::uint8_t &operator[](std::size_t pos);

    void reserve(std::size_t nsize);
    void resize(std::size_t nsize);
    void truncate(std::size_t pos);
    void clear();

private:
    using Data = std::vector<std::uint8_t>;
    struct RawData {
        const std::uint8_t *data = nullptr;
        std::size_t size = 0;
    };

    void detach();

    std::shared_ptr<Data> m_data;
    RawData m_raw;
};

}

#endif // TYPES_BYTEARRAY_H
