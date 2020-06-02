#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/Actor.hpp"
#include "Graphics/RenderableObject.hpp"
#include "Entity/PlayerInventory.hpp"

class Player final : public Actor, protected RenderableObject {
	friend class Script;
	static Player* instance;

	std::string name;
	std::map<std::string, int> player_info;

	PlayerInventory inventory;
public:
	Player();

	void draw(sf::RenderTarget& target) const override;
	std::string getName() const { return name; }
	std::map<std::string, int>& getStatistics() { return statistics; }
	std::map<std::string, int>& getPlayerInfo() { return player_info; }
	Vec2u getDimensions() const override;
	void GainEXP(int);
	void setPosition(Vec2u worldPos);
	void GainGold(int);

	PlayerInventory& getInventory() { return inventory; }
protected:
	void onInteract(Direction dir) override {};
	void onStep() override {};
	void onMove(Direction) override {}
	void onUpdate() override {}
	void Lvlup();
	void setDefaultStatistics();

	friend class WorldManager;
};