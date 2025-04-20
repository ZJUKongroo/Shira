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

#ifndef GLOBAL_ASYNC_INTERNAL_QUEUEDINVOKER_H
#define GLOBAL_ASYNC_INTERNAL_QUEUEDINVOKER_H

#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <functional>

namespace shira::async {

class QueuedInvoker
{
public:
	static QueuedInvoker *instance();

	using Functor = std::function<void()>;

	void invoke(const std::thread::id &th, const Functor &f, bool isAlwaysQueued = false);
	void processEvents();
	void onMainThreadInvoke(const std::function<void(const std::function<void()> &, bool)> &f);

private:
	QueuedInvoker() = default;

	using Queue = std::queue<Functor>;

	std::recursive_mutex m_mutex;
	std::map<std::thread::id, Queue> m_queues;

	std::function<void(const std::function<void()> &, bool)> m_onMainThreadInvoke;
	std::thread::id m_mainThreadID;
};

}

#endif // GLOBAL_ASYNC_INTERNAL_QUEUEDINVOKER_H
