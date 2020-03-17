#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "Entity/WorldEntity.hpp"
#include "RenderableObject.hpp"

class Player : protected WorldEntity, protected RenderableObject {
public:
	Player()
	: WorldEntity(0,{}) { }

	virtual void draw(Vec2u, sf::RenderTarget&) override {};
	virtual void draw(sf::RenderTarget& target) override;
	virtual Vec2u getDimensions() const override;
	virtual void frameTick() override {};
	void handleKeyboardEvent(bool pressed, sf::Event::KeyEvent& event);

	Vec2f getWorldPosition() const { return worldPosition; }

protected:
	void onInteract() override;
	void update() override;
	void onStep() override;
	bool collisionCheck(WorldEntity &entity) override;
};