#pragma once
#include <string>
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

enum class CoroutineScheduler {
	None,
	DialogEngine,
	ShopEngine,
	BattleEngine
};

enum class CoroutineStatus {
	Finished,
	YieldedToCaller,
	OrphanedCaller
};

class Script {
	std::string m_script_name;
	sol::state m_lua_state;

	bool m_is_yielding;
	std::string m_yielding_coroutine;
	CoroutineScheduler m_scheduler;

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
		if(m_is_yielding) return;

		m_scheduler = CoroutineScheduler::None;
		sol::coroutine func = m_lua_state[name];

		try {
			auto res = func(std::forward<Args>(args)...);
			do {
				if(res.status() == sol::call_status::yielded && m_scheduler == CoroutineScheduler::None) {
					std::cerr << "Error in script '" << m_script_name << "': coroutine yielded but no listener connected, resuming\n";
					res = func(std::forward<Args>(args)...);
				}
			} while(!((res.status() == sol::call_status::yielded && m_scheduler != CoroutineScheduler::None)
			          || res.status() == sol::call_status::ok));

			if(res.status() == sol::call_status::yielded) {
				std::cout << "Script has yielded\n";
				m_is_yielding = true;
				m_yielding_coroutine = name;
			}
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

	CoroutineStatus resumePausedCoroutine() {
		if(!m_is_yielding) return CoroutineStatus::Finished;
		auto old_scheduler = m_scheduler;
		m_scheduler = CoroutineScheduler::None;

		sol::coroutine func = m_lua_state[m_yielding_coroutine];

		auto res = func();
		do {
			if(res.status() == sol::call_status::yielded && m_scheduler == CoroutineScheduler::None) {
				std::cerr << "Error in script '" << m_script_name << "': coroutine yielded but no listener connected, resuming\n";
				res = func();
			}
		} while(!((res.status() == sol::call_status::yielded && m_scheduler != CoroutineScheduler::None)
				|| res.status() == sol::call_status::ok));

		if(res.status() == sol::call_status::yielded && m_scheduler != old_scheduler) {
			std::cout << "Script orphaned it's previous scheduler!\n";
			return CoroutineStatus::OrphanedCaller;
		}

		if(res.status() == sol::call_status::yielded) {
			std::cout << "The coroutine is still yielding\n";
			return CoroutineStatus::YieldedToCaller;
		} else {
			std::cout << "The coroutine has finished, my job here is done\n";
			m_is_yielding = false;
			m_yielding_coroutine = "";
			return CoroutineStatus::Finished;
		}
	}

};