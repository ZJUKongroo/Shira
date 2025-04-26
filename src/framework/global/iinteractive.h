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

#ifndef IINTERACTIVE_H
#define IINTERACTIVE_H

#include <string>
#include <vector>

#include "modularity/imoduleinterface.h"
#include "types/flags.h"

namespace shira {

class IInteractive : MODULE_EXPORT_INTERFACE
{
	INTERFACE_ID(IInteractive)

public:
	virtual ~IInteractive() = default;

	enum class Button {
		NoButton,
		Ok,
		Continue,
		RestoreDefaults,
		Reset,
		Apply,
		Help,
		Discard,
		Cancel,
		Close,
		Ingore,
		Retry,
		Abort,
		NoToAll,
		No,
		YesToAll,
		Yes,
		Open,
		DontSave,
		SaveAll,
		Save,
		Next,
		Back,
		Select,
		Clear,
		Done,
		CustomButton,
	};

	using Buttons = std::vector<Button>;

	enum ButtonRole {
		AcceptRole,
		RejectRole,
		DestructiveRole,
		ResetRole,
		ApplyRole,
		RetryRole,
		HelpRole,
		ContinueRole,
		BackRole,
		CustomRole,
	};

	struct ButtonData {
		int btn = int(Button::CustomButton);
		std::string text;
		bool accent = false;
		bool leftSide = false;
		ButtonRole role = ButtonRole::CustomRole;

		ButtonData(int btn, const std::string &text)
			: btn(btn), text(text) {}
		ButtonData(Button btn, const std::string &text)
			: btn(int(btn)), text(text) {}
		ButtonData(int btn, const std::string &text, bool accent, bool leftSide = false, ButtonRole role = ButtonRole::CustomRole)
			: btn(btn), text(text), accent(accent), leftSide(leftSide), role(role) {}
		ButtonData(Button btn, const std::string &text, bool accent, bool leftSide = false, ButtonRole role = ButtonRole::CustomRole)
			: btn(int(btn)), text(text), accent(accent), leftSide(leftSide), role(role) {}
	};

	using ButtonDatas = std::vector<ButtonData>;

	enum class TextFormat {
		Auto = 0,
		PlainText,
		RichText,
	};

	struct Text {
		std::string text;
		TextFormat format = TextFormat::Auto;

		Text() = default;
		Text(const char *t)
			: text(t), format(TextFormat::Auto) {}
		Text(const std::string &t, const TextFormat &f = TextFormat::Auto)
			: text(t), format(f) {}
	};

	struct Result
	{
		Result() = default;
		Result(const int &button)
			: m_button(button) {}
		Result(const int &button, bool showAgain)
			: m_button(button), m_showAgain(showAgain) {}

		Button standardButton() const { return static_cast<Button>(m_button); }
		int button() const { return m_button; }

		bool showAgain() const { return m_showAgain; }

	private:
		int m_button = int(Button::NoButton);
		bool m_showAgain = true;
	};

	enum Option {
		NoOptions = 0x0,
		WithIcon = 0x1,
		WithDontShowAgainCheckBox = 0x2,
	};
	DECLARE_FLAGS(Options, Option)

	virtual Result question(const std::string &contentTitle, const std::string &text, const Buttons &buttons,
							const Button &def = Button::NoButton, const Options &options = {},
							const std::string &dialogTitle = "") const = 0;
	
	virtual Result question(const std::string &contentTitle, const Text &text, const ButtonDatas &buttons,
							int defBtn = int(Button::NoButton), const Options &options = {}, const std::string &dialogTitle = "") const = 0;

	virtual ButtonData buttonData(Button b) const = 0;

	virtual Result info(const std::string &contentTitle, const std::string &text, const Buttons &buttons = {},
						int defBtn = int(Button::NoButton), const Options &options = {}, const std::string &dialogTitle = "") const = 0;

	virtual Result info(const std::string &contentTitle, const Text &text, const ButtonDatas &buttons = {},
						int defBtn = int(Button::NoButton), const Options &options = {}, const std::string &dialogTitle = "") const = 0;

	virtual Result warning(const std::string &contentTitle, const std::string &text, const Buttons &buttons = {},
						   int defBtn = int(Button::NoButton), const Options &options = { WithIcon },
						   const std::string &dialogTitle = "") const = 0;

	virtual Result warning(const std::string &contentTitle, const Text &text, const ButtonDatas &buttons = {},
						   int defBtn = int(Button::NoButton), const Options &options = { WithIcon },
						   const std::string &dialogTitle = "") const = 0;

	virtual Result warning(const std::string &contentTitle, const Text &text, const std::string &detailedText,
						   const ButtonDatas &buttons = {}, int defBtn = int(Button::NoButton), const Options &options = { WithIcon },
						   const std::string &dialogTitle = "") const = 0;

	virtual Result error(const std::string &contentTitle, const std::string &text, const Buttons &buttons = {},
						 const Button &def = Button::NoButton, const Options &options = { WithIcon },
						 const std::string &dialogTitle = "") const = 0;

	virtual Result error(const std::string &contentTitle, const Text &text, const ButtonDatas &buttons = {},
						 int defBtn = int(Button::NoButton), const Options &options = { WithIcon },
						 const std::string &dialogTitle = "") const = 0;

	virtual Result error(const std::string &contentTitle, const Text &text, const std::string &detailedText,
						 const ButtonDatas &buttons = {}, int defBtn = int(Button::NoButton), const Options &options = { WithIcon },
						 const std::string &dialogTitle = "") const = 0;

	// virtual Ret showProgress(const std::string &title, Progress *progress) const = 0;
};

// DECLARE_OPERATORS_FOR_FLAGS(IInteractive::Options)

}

#endif // IINTERACTIVE_H
