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

#ifndef GLOBAL_ASYNC_INTERNAL_ASYNCIMPL_H
#define GLOBAL_ASYNC_INTERNAL_ASYNCIMPL_H

#include <map>
#include <mutex>

#include "async/asyncable.h"

namespace shira::async {

class AsyncImpl : public Asyncable::IConnectable
{
public:
	static AsyncImpl *instance();

	struct IFunction {
		virtual ~IFunction() {};
		virtual void call() = 0;
	};

	template <typename F>
	struct Functor : public IFunction {
		F functor;
		Functor(const F fn)
			: functor(fn) {}
		void call() { functor(); }
	};

	template <typename F, typename Arg1>
	struct FunctorArg1 : public IFunction {
		F functor;
		Arg1 arg1;
		FunctorArg1(const F fn, Arg1 a1)
			: functor(fn), arg1(a1) {}
		void call() { functor(arg1); }
	};

	void call(Asyncable *caller, IFunction *f, const std::thread::id &th = std::this_thread::get_id());
	void disconnectAsync(Asyncable *caller);

private:
	AsyncImpl() = default;

	void onCall(std::uint64_t key);

	struct Call {
		Asyncable *caller = nullptr;
		IFunction *f = nullptr;
		Call() = default;
		Call(Asyncable *c, IFunction *_f)
			: caller(c), f(_f) {}
	};

	std::mutex m_mutex;
	std::map<std::uint64_t, Call> m_calls;
};

}

#endif // GLOBAL_ASYNC_INTERNAL_ASYNCIMPL_H
