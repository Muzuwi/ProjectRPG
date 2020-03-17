#pragma once
#include "Types.hpp"

/*
 *      WorldEntity - klasa reprezentująca obiekt aktywny w świecie gry
 *  Przez obiekt aktywny rozumie się te elementy świata, których pozycja ulega częstym zmianom
 *  Dostępne funkcje wirtualne, dzięki którym (ewentualnie) będzie można implementować
 *  zaawansowane interakcje ze światem gry.
 *  entityType wskazuje na typ obiektu
 */

class WorldEntity {
protected:
	unsigned entityType;
	Vec2f worldPosition;
public:
	WorldEntity(unsigned type, Vec2f position) : entityType(type), worldPosition(position) {}

	Vec2f getWorldPosition() const { return worldPosition; }

	virtual void onInteract() = 0;
	virtual void onStep() = 0;
	virtual bool collisionCheck(WorldEntity&) = 0;
	virtual void update() = 0;
};