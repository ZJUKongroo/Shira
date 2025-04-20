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

#include "abstractinvoker.h"

using namespace shira::async;

AbstractInvoker::AbstractInvoker()
{

}

AbstractInvoker::~AbstractInvoker()
{
	// std::_Tidy_deallocate_guard<std::mutex> lock()
}

void AbstractInvoker::invoke(int type)
{
	invoke(type, NotifyData());
}

void AbstractInvoker::invoke(int type, const NotifyData &data)
{
	auto it = m_callbacks.find(type);
	if (it == m_callbacks.end()) {
		return;
	}

	std::thread::id threadID = std::this_thread::get_id();

	CallBacks callbacks = it->second;

	for (const CallBack &c : callbacks) {
		if (!it->second.containsReceiver(c.receiver)) {

		}
	}
}

int AbstractInvoker::CallBacks::receiverIndexOf(Asyncable* receiver) const
{
	for (std::size_t i = 0; i < size(); ++i) {
		if (at(i).receiver == receiver) {
			return int(i);
		}
	}
	return -1;
}

bool AbstractInvoker::CallBacks::containsReceiver(Asyncable* receiver) const
{
	return receiverIndexOf(receiver) > -1;
}

void AbstractInvoker::disconnectAsync(Asyncable *receiver)
{
	std::vector<int> types;
	for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
		for (CallBack &c : it->second) {
			if (c.receiver == receiver) {
				types.push_back(c.type);
			}
		}
	}

	for (int type : types) {
		removeCallBack(type, receiver);
	}
}

void AbstractInvoker::addCallBack(int type, Asyncable *receiver, void *call, Asyncable::AsyncMode mode)
{
	const CallBacks &callbacks = m_callbacks[type];
	if (callbacks.containsReceiver(receiver)) {
		switch (mode) {
		case Asyncable::AsyncMode::AsyncSetOnce:
			deleteCall(type, call);
			return;
		case Asyncable::AsyncMode::AsyncSetRepeat:
			removeCallBack(type, receiver);
			break;
		}
	}

	CallBack c(std::this_thread::get_id(), type, receiver, call);
	m_callbacks[type].push_back(c);

	if (c.receiver) {
		c.receiver->connectAsync(this);
	}
}

void AbstractInvoker::removeCallBack(int type, Asyncable* receiver)
{
	auto it = m_callbacks.find(type);
	if (it == m_callbacks.end()) {
		return;
	}

	CallBacks &callbacks = it->second;
	int index = callbacks.receiverIndexOf(receiver);
	if (index < 0) {
		return;
	}

	CallBack c = callbacks.at(index);
	if (c.receiver) {
		c.receiver->disconnectAsync(this);
	}
	callbacks.erase(callbacks.begin() + index);

	{

	}

	deleteCall(type, c.call);
}

void AbstractInvoker::removeAllCallBacks()
{
	for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
		for (CallBack &c : it->second) {
			if (c.receiver) {
				c.receiver->disconnectAsync(this);
			}

			deleteCall(c.type, c.call);
		}
	}
	m_callbacks.clear();
}

bool AbstractInvoker::containsReceiver(Asyncable* receiver) const
{
	for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
		for (const CallBack &c : it->second) {
			if (c.receiver == receiver) {
				return true;
			}
		}
	}

	return false;
}
