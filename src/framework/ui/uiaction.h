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

#ifndef UI_UIACTION_H
#define UI_UIACTION_H

#include <string>

#include <QtCore/QVariantMap>

#include "actions/actiontypes.h"

namespace shira::ui {

struct UiContext
{
	UiContext() = default;
	constexpr UiContext(const char *ctx)
		: const_data(ctx) {}

	inline bool operator==(const UiContext &ctx) const
	{
		return std::strcmp(const_data, ctx.const_data) == 0;
	}

	inline bool operator!=(const UiContext &ctx) const
	{
		return !this->operator==(ctx);
	}

	std::string toString() const { return const_data ? std::string(const_data) : std::string(); }

private:
	const char *const_data = nullptr;
};

static constexpr UiContext UiCtxUnknown = "UiCtxUnknown";
static constexpr UiContext UiCtxAny = "UiCtxAny";

static constexpr UiContext UiCtxHomeOpened = "UiCtxHomeOpened";
static constexpr UiContext UiCtxProjectOpened = "UiCtxProjectOpened";
static constexpr UiContext UiCtxProjectFocused = "UiCtxProjectFocused";

static constexpr UiContext UiCtxDialogOpened = "UiCtxDialogOpened";

enum class Checkable {
	No = 0,
	Yes,
};

struct UiAction
{
	shira::actions::ActionCode code;
	UiContext uiCtx = uiCtxAny;
	std::string scCtx = "any";
	Checkable checkable = Checkable::No;

	UiAction() = default;
	UiAction(const shira::actions::ActionCode &code, UiContext ctx, std::string scCtx, Checkable checkable = Checkable::No)
		: code(code), uiCtx(ctx), scCtx(scCtx), checkable(checkable) {}

	bool isValid() const
	{
		return !code.empty();
	}
};

struct UiActionState
{
	bool enabled = false;
	bool checked = false;

	inline bool operator==(const UiActionState &st) const
	{
		return st.enabled == enabled && st.checked == checked;
	}

	inline bool operator!=(const UiActionState &st) const
	{
		return !this->operator==(st);
	}

	static UiActionState make_disabled(bool checked = false)
	{
		return UiActionState { false, checked };
	}

	static UiActionState make_enabled(bool checked = false)
	{
		return UiActionState { true, checked };
	}

	QVariantMap toMap() const
	{
		return {
			{ "enabled", enabled },
			{ "checked", checked }
		};
	}
};

}

#endif // UI_UIACTION_H
