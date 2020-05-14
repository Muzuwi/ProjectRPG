#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/Actor.hpp"
#include "Graphics/RenderableObject.hpp"
#include "Entity/PlayerInventory.hpp"

class Player final : public Actor, protected RenderableObject {
	std::string name;
	int lvl;
	int maxHP = 100;
	int maxMP = 100;

	int HP = 89;
	int	MP = 65;

	std::map<std::string, int> statistics;

	PlayerInventory inventory;
public:
	Player()
	: Actor(0, 7), name("Andrzej"), lvl(1) {
		setDefaultStatistics();
	}

	void draw(sf::RenderTarget& target) const override;

	int getHP() const { return HP; }
	int getMP() const { return MP; }
	int getMaxHP() const { return maxHP; }
	int getMaxMP() const { return maxMP; }
	std::string getName() const { return name; }
	int getLVL () const { return lvl; }
	std::map<std::string, int>& getStatistics() { return statistics; }
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