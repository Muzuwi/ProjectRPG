#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/Actor.hpp"
#include "Graphics/RenderableObject.hpp"
#include "Entity/PlayerInventory.hpp"

class Player final : public Actor, protected RenderableObject {
	int maxHP = 100;
	int maxMP = 100;

	int HP = 89;
	int	MP = 65;

	PlayerInventory inventory;
public:
	Player()
	: Actor(0, 7) {}

	void draw(sf::RenderTarget& target) const override;

	int getHP() const { return HP; }
	int getMP() const { return MP; }
	int getMaxHP() const { return maxHP; }
	int getMaxMP() const { return maxMP; }
	Vec2u getDimensions() const override;

	PlayerInventory& getInventory() { return inventory; }
protected:
	void onInteract(Direction dir) override {};
	void onStep() override {};
	void onMove(Direction) override {}
	void onUpdate() override {}
};