#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/Actor.hpp"
#include "RenderableObject.hpp"

class Player final : protected Actor, protected RenderableObject {
	int maxHP = 100;
	int maxMP = 100;

	int HP = 89;
	int	MP = 65;

	unsigned frameCounter;
	bool isMoving;
public:
	Player()
			: Actor(0, 100), frameCounter(0), isMoving(false) { }

	virtual void draw(Vec2u, sf::RenderTarget&) override {};
	virtual void draw(sf::RenderTarget& target) override;
	virtual Vec2u getDimensions() const override;
	virtual void frameTick() override {};

	Vec2f getWorldPosition() const { return worldPosition; }
	Vec2f getSpritePosition() const { return spritePosition; }

	void move(Direction dir) override;
	void go_to(Vec2f f) override;
	void update() override;

	int getHP() { return HP; }
	int getMP() { return MP; }
	int getMaxHP() { return maxHP; }
	int getMaxMP() { return maxMP; }
protected:
	void onInteract() override;
	void onStep() override;
	bool collisionCheck(Actor &entity) override;
};