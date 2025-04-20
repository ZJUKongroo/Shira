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

#include "asyncimpl.h"

using namespace shira::async;

AsyncImpl *AsyncImpl::instance()
{
	static AsyncImpl a;
	return &a;
}

void AsyncImpl::disconnectAsync(Asyncable *caller)
{
	std::lock_guard locker(m_mutex);

	for (auto it = m_calls.cbegin(), end = m_calls.cend(); it != end; ++it) {
		if (it->second.caller == caller) {
			m_calls.erase(it);
			break;
		}
	}
}

void AsyncImpl::call(Asyncable *caller, IFunction *f, const std::thread::id &th)
{
	if (caller) {
		caller->connectAsync(this);
	}

	std::uint64_t key = reinterpret_cast<std::uint64_t>(f);
	{
		std::lock_guard locker(m_mutex);
		m_calls[key] = Call(caller, f);
	}

	auto functor = [this, key]() { onCall(key); };
	// TO DO!
}

void AsyncImpl::onCall(std::uint64_t key)
{
	Call c;
	{
		std::lock_guard locker(m_mutex);
		auto it = m_calls.find(key);

		if (it == m_calls.end()) {
			return;
		}

		c = it->second;

		m_calls.erase(it);

		if (c.caller) {
			c.caller->disconnectAsync(this);
		}
	}

	c.f->call();
	delete c.f;
}
