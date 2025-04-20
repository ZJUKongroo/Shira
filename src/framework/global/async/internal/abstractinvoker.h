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

#ifndef GLOBAL_ASYNC_INTERNAL_ABSTRACTINVOKER_H
#define GLOBAL_ASYNC_INTERNAL_ABSTRACTINVOKER_H

#include <map>
#include <tuple>
#include <vector>
#include <memory>
#include <thread>

#include "async/asyncable.h"

namespace shira::async {

class NotifyData
{
public:
	NotifyData() = default;

	template <typename ...T>
	void setArg(int i, const T & ...val)
	{
		IArg *p = new Arg<T...>(val...);
		m_args.insert(m_args.begin() + i, std::shared_ptr<IArg>(p));
	}

	template <typename T>
	T arg(int i = 0) const
	{
		IArg *p = m_args.at(i).get();
		if (!p) {
			return {};
		}
		Arg<T> *d = reinterpret_cast<Arg<T> *>(p);
		return std::get<0>(d->val);
	}

	template <typename ...T>
	std::tuple<T...> args(int i = 0) const
	{
		IArg *p = m_args.at(i).get();
		if (!p) {
			return {};
		}
		Arg<T...> *d = reinterpret_cast<Arg<T...> *>(p);
		return d->val;
	}

	struct IArg {
		virtual ~IArg() = default;
	};

	template <typename ...T>
	struct Arg : public IArg {
		std::tuple<T...> val;
		Arg(const T & ...v)
			: IArg(), val(v...) {}
	};

private:
	std::vector<std::shared_ptr<IArg>> m_args;
};

class AbstractInvoker : public Asyncable::IConnectable
{
public:
	void disconnectAsync(Asyncable* receiver);

	void invoke(int type);
	void invoke(int type, const NotifyData &data);

protected:
	explicit AbstractInvoker();
	~AbstractInvoker();

	virtual void deleteCall(int type, void *call) = 0;
	virtual void doInvoke(int type, void *call, const NotifyData &data) = 0;

	struct CallBack {
		std::thread::id threadID;
		int type = 0;
		Asyncable *receiver = nullptr;
		void *call = nullptr;
		CallBack() = default;
		CallBack(std::thread::id threadID, int t, Asyncable* cr, void* c)
			: threadID(threadID), type(t), receiver(cr), call(c) {}
	};

	class CallBacks : public std::vector<CallBack>
	{
	public:
		int receiverIndexOf(Asyncable *receiver) const;
		bool containsReceiver(Asyncable *receiver) const;
	};

	void addCallBack(int type, Asyncable *receiver, void *call, Asyncable::AsyncMode mode = Asyncable::AsyncMode::AsyncSetRepeat);
	void removeCallBack(int type, Asyncable *receiver);
	void removeAllCallBacks();

	bool containsReceiver(Asyncable *receiver) const;

	std::map<int, CallBacks> m_callbacks;
};

}

#endif // GLOBAL_ASYNC_INTERNAL_ABSTRACTINVOKER_H
