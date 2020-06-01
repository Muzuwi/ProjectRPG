#include <fstream>
#include "Sound/SoundEngine.hpp"
#include "Entity/NPC.hpp"
#include "Types.hpp"
#include "Script.hpp"
#include "Interface/DialogEngine.hpp"
#include "Player.hpp"

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
	                                            "moveSpeed", &NPC::movementSpeed,
	                                            "move", &NPC::enqueueMove,
	                                            "moving", &NPC::isMoving,
	                                            "statistics", &NPC::statistics
	                                            );
	m_lua_state.new_usertype<Player>("Player", "giveItem",
			[](Player& player, const std::string& item, unsigned count) -> void {
				if(count == 0 || item.empty()) return;
				const auto& list = AssetManager::getJSON("ItemList");
				if(!list.contains(item)) return;

				player.getInventory().addItem(*std::make_shared<Item>(item, count));
				return;
			});

	m_lua_state.new_usertype<SoundEngine>("SoundEngine",
			"playSound", &SoundEngine::playSound,
			"playMusic", &SoundEngine::playMusic);

	m_lua_state.new_usertype<DialogEngine>("DialogEngine",
			"say", sol::yielding(
					[this](DialogEngine& engine, const std::string& text) {
						Dialog dialog{text, this};
						engine.spawnDialog(dialog);
						this->m_scheduler = CoroutineScheduler::DialogEngine;
					} ),
			"ask", sol::yielding(
					[this](DialogEngine& engine, const std::string& text, sol::table t) {
						std::vector<std::string> selections;
						for(unsigned i = 1; i <= t.size(); i++)
							selections.push_back(t[i].get<std::string>());

						Dialog dialog{text, selections, this};
						engine.spawnDialog(dialog);
						this->m_scheduler = CoroutineScheduler::DialogEngine;
					} ),
			"choice", &DialogEngine::selection );

	m_lua_state.set("sound", SoundEngine::instance);
	m_lua_state.set("dialog", DialogEngine::instance);
	m_lua_state.set("player", Player::instance);
}

Script::Script(const std::string &scriptName) {
	m_script_name = scriptName;
	m_is_yielding = false;
	m_scheduler = CoroutineScheduler::None;

	std::ifstream file("GameContent/Script/" + scriptName + ".lua");
	if(!file.good()) {
		std::cerr << "Error loading Lua script from file!\n";
		std::cerr << "Tried loading from path " << "GameContent/Script/"+scriptName+".lua" << "\n";
		file.close();
		throw std::runtime_error("Script load failed");
	}
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	m_lua_state.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io, sol::lib::math);

	this->initBindings();
	m_lua_state.script(script);
}
