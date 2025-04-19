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

#include "types/string.h"

#include "global/log.h"

using namespace shira;

char AsciiChar::toLower(char ch)
{
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

char AsciiChar::toUpper(char ch)
{
    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

char Char::toAscii(char16_t c, bool *ok)
{
    if (isAscii(c)) {
        if (ok) {
            *ok = true;
        }
        return static_cast<char>(c);
    } else {
        if (ok) {
            *ok = false;
        }
        return '?';
    }
}

char16_t Char::toLower(char16_t ch)
{
    return std::tolower(static_cast<unsigned char>(ch));
}

char16_t Char::toUpper(char16_t ch)
{
    return std::toupper(static_cast<unsigned char>(ch));
}

String::String()
{
    m_data = std::make_shared<std::u16string>();
}

String::String(const char16_t *str)
{
    m_data = std::make_shared<std::u16string>(str ? str : u"");
}

String::String(const Char &ch)
{
    m_data = std::make_shared<std::u16string>();
    *m_data.get() += ch.unicode();
}

String::String(const Char *unicode, size_t size)
{
    if (!unicode) {
        m_data = std::make_shared<std::u16string>();
        return;
    }

    static_assert(sizeof(Char) == sizeof(char16_t));
    const char16_t *str = reinterpret_cast<const char16_t *>(unicode);
    if (size == nidx) {
        m_data = std::make_shared<std::u16string>(str);
    } else {
        m_data = std::make_shared<std::u16string>(str, size);
    }
}

struct String::Mutator
{
    std::u16string &s;
    String *self = nullptr;

    Mutator(std::u16string &s, String *self)
        : s(s), self(self) {}
    ~Mutator() {}

    operator std::u16string &() {
        return s;
    }

    void reserve(std::size_t n) { s.reserve(n); }
    void resize(std::size_t n) { s.resize(n); }
    void clear() { s.clear(); }
    void push_pack(char16_t c) { s.push_back(c); }
    void insert(std::size_t p, const std::u16string &v) { s.insert(p, v); }
    void erase(std::size_t p, std::size_t n) { s.erase(p, n); }

    std::u16string &operator=(const std::u16string &v) { return s.operator=(v); }
    std::u16string &operator=(const char16_t *v) { return s.operator=(v); }
    std::u16string &operator=(const char16_t v) { return s.operator=(v); }

    std::u16string &operator+=(const std::u16string &v) { return s.operator+=(v); }
    std::u16string &operator+=(const char16_t *v) { return s.operator+=(v); }
    std::u16string &operator+=(const char16_t v) { return s.operator+=(v); }
    char16_t &operator[](std::size_t i) { return s.operator[](i); }
};

String::Mutator String::mutStr(bool do_detach)
{
    if (do_detach) {
        detach();
    }
    return Mutator(*m_data.get(), this);
}

const std::u16string &String::constStr() const
{
    return *m_data.get();
}

void String::reserve(std::size_t i)
{
    mutStr().reserve(i);
}

bool String::operator==(const char *s) const
{
    if (!s) {
        return s;
    }

    std::string_view v(s);
    if (size() != v.size()) {
        return false;
    }

    for (std::size_t i = 0; i < v.size(); ++i) {
        IF_ASSERT_FAILED(Char::isAscii(v.at(i))) {
        }
        if (at(i).toAscii() != v.at(i)) {
            return false;
        }
    }
    return true;
}

void String::detach()
{
    if (!m_data) {
        return;
    }

    if (m_data.use_count() == 1) {
        return;
    }

    m_data = std::make_shared<std::u16string>(*m_data);
}

String &String::operator=(const char16_t *str)
{
    mutStr() = str;
    return *this;
}

String &String::operator+=(const char16_t *s)
{
    mutStr() += s;
    return *this;
}

char16_t String::operator[](std::size_t i) const
{
    return constStr()[i];
}

char16_t &String::operator[](std::size_t i)
{
    return mutStr()[i];
}

String &String::append(Char ch)
{
    mutStr() += ch.unicode();
    return *this;
}

String &String::append(const String &s)
{
    mutStr() += s.constStr();
    return *this;
}

String &String::prepend(Char ch)
{
    mutStr() = ch.unicode() + constStr();
    return *this;
}

String &String::prepend(const String &s)
{
    mutStr() = s.constStr() + constStr();
    return *this;
}

String String::fromAscii(const char *str, std::size_t size)
{
    if (!str) {
        return String();
    }

    size = (size == nidx) ? std::strlen(str) : size;
    String s;
    std::u16string &data = s.mutStr();
    data.resize(size);
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = Char::fromAscii(str[i]).unicode();
    }
    return s;
}

ByteArray String::toAscii(bool *ok) const
{
    ByteArray ba;
    ba.resize(size());

    if (ok) {
        *ok = true;
    }

    for (std::size_t i = 0; i < size(); ++i) {
        bool cok = false;
        char ch = Char::toAscii(constStr().at(i), &cok);
        if (!cok && ok) {
            *ok = false;
        }
        ba[i] = static_cast<std::uint8_t>(ch);
    }
    return ba;
}

String String::fromStdString(const std::string &str)
{
    String s;
    UtfCodec::utf8to16(std::string_view(str), s.mutStr());
    return s;
}

std::string String::toStdString() const
{
    std::string s;
    UtfCodec::utf16to8(std::u16string_view(constStr()), s);
    return s;
}

std::wstring String::toStdWString() const
{
    const std::u16string &u16 = constStr();
    std::wstring ws;
    ws.resize(u16.size());

    static_assert(sizeof(wchar_t) >= sizeof(char16_t));

    for (std::size_t i = 0; i < ws.size(); ++i) {
        ws[i] = static_cast<wchar_t>(u16.at(i));
    }

    return ws;
}

const String String::fromStdWString(const std::wstring &str)
{
    String s;
    s.mutStr().resize(str.size());

    static_assert(sizeof(wchar_t) >= sizeof(char16_t));

    for (std::size_t i = 0; i < str.size(); ++i) {
        s[i] = static_cast<char16_t>(str.at(i));
    }

    return s;
}

std::size_t String::size() const
{
    return constStr().size();
}

bool String::empty() const
{
    return constStr().empty();
}

void String::clear()
{
    mutStr().clear();
}

Char String::at(std::size_t i) const
{
    IF_ASSERT_FAILED(i < size()) {
        return Char();
    }
    return Char(constStr().at(i));
}

bool String::contains(const Char &ch) const
{
    return constStr().find(ch.unicode()) != std::u16string::npos;
}

bool String::contains(const String &str, CaseSensitivity cs) const
{
    if (cs == CaseSensitivity::CaseInsensitive) {
        return constStr().find(str.constStr()) != std::u16string::npos;
    } else {
        std::u16string self = constStr();
        std::transform(self.begin(), self.end(), self.begin(), [](char16_t c) { return Char::toLower(c); });
        std::u16string other = constStr();
        std::transform(other.begin(), other.end(), other.begin(), [](char16_t c) { return Char::toLower(c); });
        return self.find(other) != std::u16string::npos;
    }
}

bool String::contains(const std::wregex &re) const
{
    std::wstring ws = toStdWString();

    auto words_begin = std::wsregex_iterator(ws.begin(), ws.end(), re);
    if (words_begin != std::wsregex_iterator()) {
        return true;
    }
    return false;
}

int String::count(const Char &ch) const
{
    int count = 0;
    for (std::size_t i = 0; i < constStr().size(); ++i) {
        if (constStr().at(i) == ch.unicode()) {
            ++count;
        }
    }
    return count;
}

int String::count(const String &str) const
{
    int count = 0;
    std::string::size_type pos = 0;
    std::u16string otherStr = str.constStr();
    while ((pos = constStr().find(otherStr, pos)) != std::string::npos) {
        ++count;
        pos += str.size();
    }
    return count;
}

std::size_t String::indexOf(const Char &ch, std::size_t from) const
{
    for (std::size_t i = from; i < constStr().size(); ++i) {
        if (constStr().at(i) == ch.unicode()) {
            return i;
        }
    }
    return nidx;
}

std::size_t String::indexOf(const String &str, std::size_t from) const
{
    return constStr().find(str.constStr(), from);
}

std::size_t String::indexOf(const char16_t *str, std::size_t from) const
{
    return constStr().find(str, from);
}

std::size_t String::lastIndexOf(const Char &ch, std::size_t from) const
{
    from = std::min(from, constStr().size() - 1);

    for (int i = static_cast<int>(from); i >= 0; --i) {
        if (constStr().at(i) == ch.unicode()) {
            return i;
        }
    }
    return nidx;
}

void String::doArgs(std::u16string &out, const std::vector<std::u16string_view> &args) const
{
    struct Part {
        std::u16string_view substr;
        std::size_t argIdxToInsertAfter = nidx;
    };

    const std::u16string &str = constStr();
    const std::u16string_view view(str);
    std::vector<Part> parts;

    // TO DO!
}

String String::arg(const String &val) const
{
    String s;
    doArgs(s.mutStr(), { std::u16string_view(val.constStr()) });
    return s;
}

String String::arg(const String &val1, const String &val2) const
{
    String s;
    doArgs(s.mutStr(), { std::u16string_view(val1.constStr()),
                         std::u16string_view(val2.constStr()) });
    return s;
}

String String::arg(const String &val1, const String &val2, const String &val3) const
{
    String s;
    doArgs(s.mutStr(), { std::u16string_view(val1.constStr()),
                         std::u16string_view(val2.constStr()),
                         std::u16string_view(val3.constStr()) });
    return s;
}

String String::arg(const String &val1, const String &val2, const String &val3, const String &val4) const
{
    String s;
    doArgs(s.mutStr(), { std::u16string_view(val1.constStr()),
                         std::u16string_view(val2.constStr()),
                         std::u16string_view(val3.constStr()),
                         std::u16string_view(val4.constStr()) });
    return s;
}

String String::arg(const String &val1, const String &val2, const String &val3, const String &val4, const String &val5) const
{
    String s;
    doArgs(s.mutStr(), { std::u16string_view(val1.constStr()),
                         std::u16string_view(val2.constStr()),
                         std::u16string_view(val3.constStr()),
                         std::u16string_view(val4.constStr()),
                         std::u16string_view(val5.constStr()) });
    return s;
}

String String::mid(std::size_t pos, std::size_t count) const
{
    String s;
    if (pos > size()) {
        return s;
    }
    s.mutStr() = constStr().substr(pos, count);
    return s;
}

String String::left(std::size_t n) const
{
    return mid(0, n);
}

String String::right(std::size_t n) const
{
    return mid(size() - n);
}

String String::number(int n, int base)
{
    std::stringstream stream;
    if (base == 16) {
        stream << std::hex;
    }

    stream << n;
    std::string s = stream.str();
    return fromAscii(s.c_str(), s.size());
}

StringList &StringList::append(const StringList &l)
{
    for (const String &s : l) {
        push_back(s);
    }
    return *this;
}

StringList StringList::filter(const String &str) const
{
    StringList result;
    for (const String &s : *this) {
        if (s.contains(str)) {
            result << s;
        }
    }
    return result;
}

String StringList::join(const String &sep) const
{
    String res;
    for (std::size_t i = 0; i < size(); ++i) {
        if (i) {
            res += sep;
        }
        res += at(i);
    }
    return res;
}

void StringList::insert(std::size_t idx, const String &str)
{
    std::vector<String>::insert(begin() + idx, str);
}

void StringList::insert(const_iterator it, const String &str)
{
    std::vector<String>::insert(it, str);
}

void StringList::replace(std::size_t idx, const String &str)
{
    this->operator[](idx) = str;
}

bool StringList::removeAll(const String &str)
{
    std::size_t origSize = size();
    erase(std::remove(begin(), end(), str), end());
    return origSize != size();
}

void StringList::removeAt(std::size_t i)
{
    erase(begin() + i);
}

void UtfCodec::utf8to16(std::string_view src, std::u16string &dst)
{
    try {
        // TO DO!
    } catch (const std::exception &e) {
        LOGE() << e.what();
    }
}

void UtfCodec::utf16to8(std::u16string_view src, std::string &dst)
{
    try {
        // TO DO!
    } catch (const std::exception &e) {
        LOGE() << e.what();
    }
}
