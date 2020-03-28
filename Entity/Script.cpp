#include <fstream>
#include "Entity/NPC.hpp"
#include "Types.hpp"
#include "Script.hpp"

void Script::initBindings() {
	m_lua_state.set_function("log", [this](const std::string& str) {
		std::cout << m_script_name << "/ " << str << "\n";
	});

	m_lua_state.new_usertype<Vec2u>("Vec2u", "x", &Vec2u::x,
	                                               "y", &Vec2u::y);
	m_lua_state.new_usertype<Vec2f>("Vec2f", "x", &Vec2f::x,
			                                       "y", &Vec2f::y);
	m_lua_state.new_usertype<NPC>("NPC", "direction", &NPC::facing,
	                                            "worldPos", &NPC::worldPosition,
	                                            "spritePos", &NPC::spritePosition,
	                                            "moveSpeed", &NPC::movementSpeed);
}

Script::Script(const std::string &scriptName) {
	m_script_name = scriptName;

	std::ifstream file("GameContent/Script/" + scriptName + ".lua");
	if(!file.good()) {
		std::cout << "Error loading Lua script from file!\n";
		std::cout << "Tried loading from path " << "GameContent/Script/"+scriptName+".lua" << "\n";
		file.close();
		return;
	}
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	m_lua_state.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);
	m_lua_state.script(script);

	this->initBindings();
}
