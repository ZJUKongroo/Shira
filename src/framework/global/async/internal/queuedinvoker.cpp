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

#include "queuedinvoker.h"

using namespace shira::async;

QueuedInvoker *QueuedInvoker::instance()
{
	static QueuedInvoker i;
	return &i;
}

void QueuedInvoker::invoke(const std::thread::id &callbackTh, const Functor &f, bool isAlwaysQueued)
{
	if (m_onMainThreadInvoke) {
		if (callbackTh == m_mainThreadID) {
			m_onMainThreadInvoke(f, isAlwaysQueued);
		}
	}

	std::lock_guard<std::recursive_mutex> lock(m_mutex);
	m_queues[callbackTh].push(f);
}

void QueuedInvoker::processEvents()
{
	Queue q;
	{
		std::lock_guard<std::recursive_mutex> lock(m_mutex);
		auto n = m_queues.extract(std::this_thread::get_id());
		if (!n.empty()) {
			q = n.mapped();
		}
	}
	while (!q.empty()) {
		const auto& f = q.front();
		if (f) {
			f();
		}
		q.pop();
	}
}

void QueuedInvoker::onMainThreadInvoke(const std::function<void(const std::function<void()> &, bool)> &f)
{
	m_onMainThreadInvoke = f;
	m_mainThreadID = std::this_thread::get_id();
}
