#pragma once
#include "Types.hpp"
#include "Tools/json.hpp"


struct NPCData {
	Vec2u worldPosition;
	unsigned movementSpeed;
	std::string scriptName;
	std::string spritesheetName;
};

using json = nlohmann::json;

void to_json(json& j, const NPCData& npc);
void from_json(const json& j, NPCData& npc);

namespace sf {
	void to_json(json& j, const Vec2u& vec);
	void from_json(const json& j, Vec2u& vec);

	void to_json(json& j, const Vec2f& vec);
	void from_json(const json& j, Vec2f& vec);
}

