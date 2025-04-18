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

#include "bytearray.h"

#include <cassert>

using namespace shira;

ByteArray::ByteArray()
{
    m_data = std::make_shared<Data>();
    m_data->resize(1);
    m_data->operator[](0) = 0;
}

std::uint8_t *ByteArray::data()
{
    detach();
    return m_data->data();
}

const std::uint8_t *ByteArray::constData() const
{
    if (m_raw.data) {
        return m_raw.data;
    }

    return m_data->data();
}

const char *ByteArray::constChar() const
{
    return reinterpret_cast<const char *>(constData());
}

std::size_t ByteArray::size() const
{
    if (m_raw.data) {
        return m_raw.size;
    }

    return m_data->empty() ? 0 : (m_data->size() - 1);
}

void ByteArray::detach()
{
    if (!m_data) {
        return;
    }

    if (m_raw.data) {
        m_data->resize(m_raw.size + 1);
        m_data->operator[](m_raw.size) = 0;
        std::memcpy(m_data->data(), m_raw.data, m_raw.size);
        m_raw.data = nullptr;
        return;
    }

    if (m_data.use_count() == 1) {
        return;
    }

    m_data = std::make_shared<Data>(*m_data);
}

bool ByteArray::empty() const
{
    return size() == 0;
}

void ByteArray::reserve(std::size_t nsize)
{
    if (nsize + 1 <= m_data->capacity()) {
        return;
    }

    detach();
    m_data->reserve(nsize + 1);
}

void ByteArray::resize(std::size_t nsize)
{
    if (nsize == size()) {
        return;
    }

    detach();
    m_data->resize(nsize + 1);
    m_data->operator[](nsize) = 0;
}

void ByteArray::truncate(std::size_t pos)
{
    if (pos >= size()) {
        return;
    }
    resize(pos);
}

void ByteArray::clear()
{
    resize(0);
}

std::uint8_t ByteArray::at(std::size_t pos) const
{
    assert(pos < size());
    if (pos < size()) {
        return constData()[pos];
    }
    return 0;
}

std::uint8_t ByteArray::operator[](std::size_t pos) const
{
    return at(pos);
}

std::uint8_t &ByteArray::operator[](std::size_t pos)
{
    detach();

    assert(pos < size());
    if (pos < size()) {
        return m_data->operator[](pos);
    }

    static std::uint8_t dummy;
    return dummy;
}
