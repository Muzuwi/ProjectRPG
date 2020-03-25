#pragma once
#include "Types.hpp"

/*
 *      WorldEntity - klasa reprezentująca obiekt aktywny w świecie gry
 *  Przez obiekt aktywny rozumie się te elementy świata, których pozycja ulega częstym zmianom
 *  Dostępne funkcje wirtualne, dzięki którym (ewentualnie) będzie można implementować
 *  zaawansowane interakcje ze światem gry.
 *  entityType wskazuje na typ obiektu
 */

class Actor {
protected:
	unsigned entityType;
	Vec2u worldPosition;
	Vec2f spritePosition;
	unsigned movementSpeed;
	Direction facing;
public:
	Actor(unsigned type, unsigned moveSpeed)
	: entityType(type), movementSpeed(moveSpeed), facing(Direction::Down) {}

	Vec2u getWorldPosition() const { return worldPosition; }
	Vec2f getSpritePosition() const { return spritePosition; }
	Direction getDirection() const { return facing; }

	virtual void move(Direction dir) = 0;
	virtual void go_to(Vec2f) = 0;

	virtual void onInteract() = 0;
	virtual void onStep() = 0;
	virtual bool collisionCheck(Actor&) = 0;
	virtual void update() = 0;
};