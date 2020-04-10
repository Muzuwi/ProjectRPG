#pragma once
#include <string>
#include <vector>

enum DialogType {
	Dialog_Normal,
	Dialog_Choice,
};

enum DialogSkipType {
	Skip_Press,
	Skip_Timeout
};


class Script;

class Dialog {
	DialogType type;
	DialogSkipType skipType;
	unsigned timeout;
	Script* owner;
	std::string text;
	std::vector<std::string> choices;
public:
	explicit Dialog(const std::string& _text, Script* own = nullptr)
		: text(_text), owner(own), type(Dialog_Normal), skipType(Skip_Press) { }

	explicit Dialog(const std::string& _text, unsigned time, Script* own = nullptr)
		: text(_text), owner(own), type(Dialog_Normal), skipType(Skip_Timeout), timeout(time) { }

	explicit Dialog(const std::string& _text, const std::vector<std::string>& choice, Script* own = nullptr)
		: text(_text), owner(own), type(Dialog_Choice), skipType(Skip_Press), choices(choice) { }

	explicit Dialog(const std::string& _text, const std::vector<std::string>& choice, unsigned time, Script* own = nullptr)
		: text(_text), owner(own), type(Dialog_Choice), skipType(Skip_Press), timeout(time), choices(choice) { }

	Script* getOwner() const { return owner; }
	const std::string& getText() const { return text; }
	const std::vector<std::string>& getChoices() const { return choices; }
	DialogType getDialogType() const { return type; }
	DialogSkipType getSkipType() const { return skipType; }
	unsigned getTimeout() const { return timeout; }

};