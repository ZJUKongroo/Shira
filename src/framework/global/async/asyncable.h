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

#ifndef GLOBAL_ASYNC_ASYNCABLE_H
#define GLOBAL_ASYNC_ASYNCABLE_H

#include <set>

namespace shira::async {

class Asyncable
{
public:
	enum class AsyncMode {
		AsyncSetOnce = 0,
		AsyncSetRepeat,
	};

	virtual ~Asyncable()
	{
		disconnectAll();
	}

	struct IConnectable {
		virtual ~IConnectable() {}
		virtual void disconnectAsync(Asyncable *a) = 0;
	};

	bool isConnectedAsync() const { return !m_connects.empty(); }

	void connectAsync(IConnectable *c)
	{
		if (c && m_connects.count(c) == 0) {
			m_connects.insert(c);
		}
	}

	void disconnectAsync(IConnectable *c)
	{
		m_connects.erase(c);
	}

	void disconnectAll()
	{
		auto copy = m_connects;
		for (IConnectable *c : copy) {
			c->disconnectAsync(this);
		}

		m_connects.clear();
	}

private:
	std::set<IConnectable *> m_connects;
};

}

#endif // GLOBAL_ASYNC_ASYNCABLE_H
