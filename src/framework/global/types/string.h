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

#ifndef TYPES_STRING_H
#define TYPES_STRING_H

#include "containers.h"
#include "types/bytearray.h"

#include <cstring>
#include <sstream>
#include <regex>
#include <memory>
#include <string>

#include <QtCore/QString>

namespace shira {

enum CaseSensitivity {
    CaseInsensitive = 0,
    CaseSensitive = 1,
};

enum SplitBehavior {
    KeepEmptyParts = 0,
    SkipEmptyParts = 1,
};

class AsciiChar
{
public:
    constexpr AsciiChar() = default;
    constexpr explicit AsciiChar(char c)
        : m_ch(c) {}

    constexpr char ascii() const noexcept { return m_ch; }
    constexpr char16_t unicode() const noexcept { return char16_t(m_ch); }
    inline char toLower() const { return toLower(m_ch); }
    inline char toUpper() const { return toUpper(m_ch); }

    static char toLower(char ch);
    static char toUpper(char ch);

private:
    char m_ch = 0;
};

class Char
{
public:
    enum SpecialCharacter {
        Null = 0x0000,
        Tabulation = 0x0009,
        LineFeed = 0x000a,
        FormFeed = 0x000c,
        CarriageReturn = 0x000d,
        Space = 0x0020,
        Nbsp = 0x00a0,
        SoftHyphen = 0x00ad,
        ReplacementCharacter = 0xfffd,
        ObjectReplacementCharacter = 0xfffc,
        ByteOrderMark = 0xfeff,
        ByteOrderSwapped = 0xfffe,
        ParagraphSeparator = 0x2029,
        LineSeparator = 0x2028,
        LastValidCodePoint = 0x10ffff,
    };

    constexpr Char() = default;
    constexpr Char(char16_t c)
        : m_ch(c) {}
    Char(AsciiChar c)
        : m_ch(c.unicode()) {}

    constexpr bool operator==(Char c) const { return m_ch == c.m_ch; }
    constexpr bool operator!=(Char c) const { return !operator==(c); }
    constexpr bool operator==(char16_t c) const { return m_ch == c; }
    constexpr bool operator!=(char16_t c) const { return !operator==(c); }
    constexpr bool operator==(AsciiChar c) const { return m_ch == c.unicode(); }
    constexpr bool operator!=(AsciiChar c) const { return !operator==(c); }

    constexpr bool operator>(Char c) const { return m_ch > c.m_ch; }
    constexpr bool operator>(char16_t c) const { return m_ch > c; }
    constexpr bool operator<(Char c) const { return m_ch < c.m_ch; }
    constexpr bool operator<(char16_t c) const { return m_ch < c; }

    constexpr bool operator>=(Char c) const { return m_ch >= c.m_ch; }
    constexpr bool operator>=(char16_t c) const { return m_ch >= c; }
    constexpr bool operator<=(Char c) const { return m_ch <= c.m_ch; }
    constexpr bool operator<=(char16_t c) const { return m_ch <= c; }

    constexpr char16_t unicode() const { return m_ch; }

    inline bool isNull() const { return m_ch == 0; }

    constexpr bool isAscii() const { return isAscii(m_ch); }
    static constexpr bool isAscii(char16_t c) { return c <= 0x7f; }
    inline char toAscii(bool *ok = nullptr) const { return toAscii(m_ch, ok); }
    static char toAscii(char16_t c, bool *ok = nullptr);
    static inline Char fromAscii(char c) { return static_cast<char16_t>(c); }

    inline bool isLower() const { return toLower() == m_ch; }
    inline Char toLower() const { return toLower(m_ch); }
    static char16_t toLower(char16_t ch);
    inline bool isUpper() const { return toUpper() == m_ch; }
    inline Char toUpper() const { return toUpper(m_ch); }
    static char16_t toUpper(char16_t ch);

private:
    char16_t m_ch = 0;
};

class String
{
public:
    String();
    String(const char16_t *str);
    String(const Char &ch);
    String(const Char *unicode, std::size_t size = nidx);

#ifndef NO_QT_SUPPORT
    String(const QString &str) { *this = fromQString(str); }
    operator QString() const {
        return this->toQString();
    }

    String &operator=(const QString &str) { *this = fromQString(str); return *this; }
    static String fromQString(const QString &str);
	QString toQString() const;

	inline bool operator==(const QString &s) const { return toQString() == s; }
	inline bool operator!=(const QString &s) const { return !operator==(s); }
#endif

    String &operator=(const char16_t *str);
    void reserve(std::size_t i);

    inline bool operator==(const String &s) const { return constStr() == s.constStr(); }
    inline bool operator!=(const String &s) const { return !operator==(s); }

    inline bool operator==(const char16_t *s) const { return constStr() == s; }
    inline bool operator!=(const char16_t *s) const { return !operator==(s); }
    bool operator==(const char *s) const;
    inline bool operator!=(const char *s) const { return !operator==(s); }
    inline bool operator<(const String &s) const { return constStr() < s.constStr(); }
    inline bool operator>(const String &s) const { return constStr() > s.constStr(); }
    inline bool operator<=(const String &s) const { return constStr() <= s.constStr(); }
    inline bool operator>=(const String &s) const { return constStr() >= s.constStr(); }

    inline String &operator+=(const String &s) { return append(s); }
    inline String &operator+=(const char16_t *s);
    inline String &operator+=(char16_t s) { return append(s); }

    inline String operator+(const String &s) const { String t(*this); t += s; return t; }
    inline String operator+(const char16_t *s) const { String t(*this); t += s; return t; }
    inline String operator+(char16_t s) const { String t(*this); t += s; return t; }

    char16_t operator[](std::size_t i) const;
    char16_t &operator[](std::size_t i);

    String &append(Char ch);
    String &append(const String &s);
    String &prepend(Char ch);
    String &prepend(const String &s);

	static String fromUtf8(const char *str);
	static String fromUtf8(const ByteArray &data);
	ByteArray toUtf8() const;

    static String fromAscii(const char *str, std::size_t size = nidx);
    ByteArray toAscii(bool *ok = nullptr) const;

    std::string toStdString() const;
    static String fromStdString(const std::string &str);

    std::wstring toStdWString() const;
    static const String fromStdWString(const std::wstring &str);

    std::size_t size() const;
    bool empty() const;
    inline bool isEmpty() const { return empty(); }
    void clear();
    Char at(std::size_t i) const;
    Char front() const { return at(0); }
    Char back() const { return at(size() - 1); }
    bool contains(const Char &ch) const;
    bool contains(const String &str, CaseSensitivity cs = CaseSensitive) const;
    bool contains(const std::wregex &re) const;
    int count(const Char &ch) const;
    int count(const String &str) const;
    std::size_t indexOf(const Char &ch, std::size_t from = 0) const;
    std::size_t indexOf(const String &str, std::size_t from = 0) const;
    std::size_t indexOf(const char16_t *str, std::size_t from = 0) const;
    std::size_t lastIndexOf(const Char &ch, std::size_t from = nidx) const;

    String mid(std::size_t pos, std::size_t count = nidx) const;
    String left(std::size_t i) const;
    String right(std::size_t i) const;

    String arg(const String &val) const;
    String arg(const String &val1, const String &val2) const;
    String arg(const String &val1, const String &val2, const String &val3) const;
    String arg(const String &val1, const String &val2, const String &val3, const String &val4) const;
    String arg(const String &val1, const String &val2, const String &val3, const String &val4, const String &val5) const;

    String arg(int val) const { return arg(number(val)); }
    String arg(int val1, int val2) const { return arg(number(val1), number(val2)); }
    String arg(int val1, int val2, int val3) { return arg(number(val1), number(val2), number(val3)); }

    static String number(int n, int base = 10);

private:
    struct Mutator;
    const std::u16string &constStr() const;
    Mutator mutStr(bool do_detach = true);
    void detach();
    void doArgs(std::u16string &out, const std::vector<std::u16string_view> &args) const;

    std::shared_ptr<std::u16string> m_data;
};

class StringList : public std::vector<String>
{
public:
    StringList() = default;
    StringList(std::initializer_list<String> l)
        : std::vector<String>(l) {}

    StringList &operator<<(const String &s) { return append(s); }
    StringList &append(const String &s) { push_back(s); return *this; }

    StringList &operator<<(const StringList &l) { return append(l); }
    StringList &append(const StringList &l);

    std::size_t indexOf(const String &s) const { return shira::indexOf(*this, s); }
    bool contains(const String &s) const { return shira::contains(*this, s); }
    StringList filter(const String &str) const;
    String join(const String &sep) const;

    void insert(std::size_t idx, const String &str);
    void insert(const_iterator it, const String &str);
    void replace(std::size_t idx, const String &str);
    bool removeAll(const String &str);
    void removeAt(std::size_t i);
};

class UtfCodec
{
public:
    enum class Encoding {
        Unknown,
        UTF_8,
        UTF_16LE,
        UTF_16BE,
    };

    static void utf8to16(std::string_view src, std::u16string &dst);
    static void utf16to8(std::u16string_view src, std::string &dst);
};

}

#endif // TYPES_STRING_H
