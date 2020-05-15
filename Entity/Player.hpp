#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/Actor.hpp"
#include "Graphics/RenderableObject.hpp"
#include "Entity/PlayerInventory.hpp"

class Player final : public Actor, protected RenderableObject {
	std::string name;
	std::map<std::string, int> statistics;
	std::map<std::string, int> player_info;

	PlayerInventory inventory;
public:
	Player()
	: Actor(0, 7), name("Andrzej") {
		setDefaultStatistics();
	}

	void draw(sf::RenderTarget& target) const override;
	std::string getName() const { return name; }
	std::map<std::string, int>& getStatistics() { return statistics; }
	std::map<std::string, int>& getPlayerInfo() { return player_info; }
	Vec2u getDimensions() const override;

	PlayerInventory& getInventory() { return inventory; }
protected:
	void onInteract(Direction dir) override {};
	void onStep() override {};
	void onMove(Direction) override {}
	void onUpdate() override {}
	void setDefaultStatistics();

	friend class WorldManager;
};