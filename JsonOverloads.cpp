#include "Entity/NPC.hpp"
#include "World/Tile.hpp"
#include "World/Map.hpp"
#include "JsonOverloads.hpp"

/*
 *      NPC
 */

void to_json(json &j, const NPCData& npc) {
	j = json {
			{"scriptName", npc.scriptName},
			{"worldPos", npc.worldPosition},
			{"moveSpeed", npc.movementSpeed},
			{"spritesheet", npc.spritesheetName}
	};
}

void from_json(const json &j, NPCData& npc) {
	j.at("scriptName").get_to(npc.scriptName);
	j.at("worldPos").get_to(npc.worldPosition);
	j.at("moveSpeed").get_to(npc.movementSpeed);
	j.at("spritesheet").get_to(npc.spritesheetName);
}

void to_json(json &j, const Tile &tile) {
	j = json {
		tile.getPriority(),
		tile.getCollisionBitmap()
	};
}

void from_json(const json &j, Tile &tile) {
	unsigned bitmap = 0;
	unsigned priority = 0;

	j.at(0).get_to(priority);
	j.at(1).get_to(bitmap);

	tile = Tile(bitmap, priority);
}

void to_json(json& j, const Connection& connection) {
	j = json {
		connection.sourcePos,
		connection.targetMap,
		connection.targetPos
	};
}

void from_json(const json& j, Connection& connection) {
	j.at(0).get_to(connection.sourcePos);
	j.at(1).get_to(connection.targetMap);
	j.at(2).get_to(connection.targetPos);
}

/*
 *      Wektory SFML
 */

void sf::to_json(json& j, const Vec2u& vec) {
	j = json { vec.x,vec.y };
}

void sf::from_json(const json& j, Vec2u& vec) {
	j.at(0).get_to(vec.x);
	j.at(1).get_to(vec.y);
}

void sf::to_json(json& j, const Vec2f& vec) {
	j = json { vec.x,vec.y };
}

void sf::from_json(const json& j, Vec2f& vec) {
	j.at(0).get_to(vec.x);
	j.at(1).get_to(vec.y);
}
