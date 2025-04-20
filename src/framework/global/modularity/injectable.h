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

#ifndef INJECTABLE_H
#define INJECTABLE_H

#include <functional>

namespace shira::modularity {

class Injectable
{
public:
	virtual ~Injectable() = default;

	using GetContext = std::function<ContextPtr()>;

	Injectable(const ContextPtr &ctx = nullptr)
		: m_ctx(ctx) {}

	Injectable(const Injectable *inj)
		: m_inj(inj) {}

	Injectable(const GetContext &getCtx)
		: m_getCtx(getCtx) {}

	Injectable(const Injectable &i) = default;

	Injectable &operator=(const Injectable &i) = default;

	const ContextPtr &iocContext() const
	{
		if(m_ctx) {
			return m_ctx;
		}

		if(m_inj) {
			m_ctx = m_inj->iocContext();
		}

		if(m_getCtx) {
			m_ctx = m_getCtx();
		}

		return m_ctx;
	}

private:
	mutable ContextPtr m_ctx;
	const Injectable *m_inj = nullptr;
	GetContext m_getCtx;
};

}

#endif // INJECTABLE_H
