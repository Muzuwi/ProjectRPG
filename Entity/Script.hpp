#pragma once
#include <string>
#include <sol/sol.hpp>

class Script {
	std::string m_script_name;
	sol::state m_lua_state;
	void initBindings();
public:
	Script() { }
	Script(const std::string&);

	template<typename... Args>
	void set(Args&&... args) {
		m_lua_state.set(std::forward<Args>(args)...);
	}

	template<typename... Args>
	void executeFunction(const std::string& name, Args&&... args) {
		static bool errored = false;
		sol::function func = m_lua_state[name];
		try {
			func(std::forward<Args>(args)...);
		} catch(sol::error& err) {
			std::cerr << "An error occured during call to Lua function '"
					  << name << "' in script 'GameContent/Script/" << m_script_name << ".lua'\n";
			throw std::runtime_error("Error in Lua script " + m_script_name);
		}
	}

	template<typename... Args>
	void addFunction(const std::string& name, Args&&... args) {
		m_lua_state.set_function(name, std::forward<Args>(args)...);
	}

};