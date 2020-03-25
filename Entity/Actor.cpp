#include "Tile.hpp"
#include "Entity/Actor.hpp"

void Actor::move(Direction dir) {
	if(isMoving) return;

	switch(dir) {
		case Direction::Up:     --this->worldPosition.y; isMoving = true;  break;
		case Direction::Down:   ++this->worldPosition.y; isMoving = true;  break;
		case Direction::Left:   --this->worldPosition.x; isMoving = true;  break;
		case Direction::Right:  ++this->worldPosition.x; isMoving = true;  break;
		default: break;
	}

	facing = dir;
}

void Actor::update() {
	++frameCounter;

	if(isMoving) {
		auto targetPosition = worldPosition * Tile::dimensions();

		if(targetPosition.x != spritePosition.x) {
			if(targetPosition.x > spritePosition.x) {
				spritePosition.x += (double)movementSpeed;
				if(spritePosition.x >= targetPosition.x) {
					spritePosition.x = targetPosition.x;
					isMoving = false;
				}
			} else {
				spritePosition.x -= (double)movementSpeed;
				if(spritePosition.x <= targetPosition.x) {
					spritePosition.x = targetPosition.x;
					isMoving = false;
				}
			}
		} else if(targetPosition.y != spritePosition.y) {
			if(targetPosition.y > spritePosition.y) {
				spritePosition.y += (double)movementSpeed;
				if(spritePosition.y >= targetPosition.y) {
					spritePosition.y = targetPosition.y;
					isMoving = false;
				}
			} else {
				spritePosition.y -= (double)movementSpeed;
				if(spritePosition.y <= targetPosition.y) {
					spritePosition.y = targetPosition.y;
					isMoving = false;
				}
			}

		}

	}
}
