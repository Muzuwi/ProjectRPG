#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/Actor.hpp"
#include "RenderableObject.hpp"

class Player final : protected Actor, protected RenderableObject {
	unsigned frameCounter;
	bool isMoving;
public:
	Player()
	: Actor(0, 4), frameCounter(0), isMoving(false) { }

	virtual void draw(Vec2u, sf::RenderTarget&) override {};
	virtual void draw(sf::RenderTarget& target) override;
	virtual Vec2u getDimensions() const override;
	virtual void frameTick() override {};

	Vec2f getWorldPosition() const { return worldPosition; }
	Vec2f getSpritePosition() const { return spritePosition; }

	void move(Direction dir) override;
	void go_to(Vec2f f) override;
	void update() override;
protected:
	void onInteract() override;
	void onStep() override;
	bool collisionCheck(Actor &entity) override;
};