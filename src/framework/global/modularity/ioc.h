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

#ifndef GLOBAL_MODULARITY_IOC_H
#define GLOBAL_MODULARITY_IOC_H

#include <map>
#include <mutex>

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include "context.h"
#include "modulesioc.h"
#include "injectable.h"

namespace shira::modularity {

static std::map<IoCID, ModulesIoC *> s_map;

ModulesIoC *_ioc(const ContextPtr &ctx = nullptr);
void removeIoC(const ContextPtr &ctx = nullptr);

inline ModulesIoC *globalIoc()
{
    return _ioc(nullptr);
}

inline ContextPtr globalCtx()
{
    static ContextPtr ctx = std::make_shared<Context>();
    return ctx;
}

struct StaticMutex
{
    static std::recursive_mutex mutex;
};

template <typename I>
class Inject
{
public:
    Inject(const ContextPtr &ctx = nullptr)
        : m_ctx(ctx) {}

    Inject(const Injectable *o)
        : m_inj(o) {}

	const ContextPtr &iocContext() const
	{
		if (m_ctx) {
			return m_ctx;
		}

		if (m_inj) {
			return m_inj->iocContext();
		}

		return m_ctx;
	}

	const std::shared_ptr<I> &get() const
	{
		if (!m_i) {
			const std::lock_guard<std::recursive_mutex> lock(StaticMutex::mutex);
			if (!m_i) {
				static std::string_view module = "";
				m_i = _ioc(iocContext())->template resolve<I>(module);
			}
		}
		return m_i;
	}

	void set(std::shared_ptr<I> impl)
	{
		m_i = impl;
	}

	const std::shared_ptr<I> &operator()() const
	{
		return get();
	}

private:
	const ContextPtr m_ctx;
	const Injectable *m_inj = nullptr;
	mutable std::shared_ptr<I> m_i = nullptr;
};

template <typename I>
class GlobalInject : public Inject<I>
{
public:
	GlobalInject()
		: Inject<I>(ContextPtr()) {}
};

struct QmlIoCContext : public QObject
{
	Q_OBJECT

public:
	QmlIoCContext(QObject *p)
		: QObject(p) {}

	ContextPtr ctx;
};

Injectable::GetContext iocCtxForQmlObject(const QObject *o);
ContextPtr iocCtxForQmlEngine(const QQmlEngine *e);
ContextPtr iocCtxForQWidget(const QWidget *o);

}

#endif // GLOBAL_MODULARITY_IOC_H
