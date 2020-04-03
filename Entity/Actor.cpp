#include "World/Tile.hpp"
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

	this->onMove(dir);

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

	this->onUpdate();
}

/*
 *  Dodaje do kolejki ruchow prosbe o przesuniecie aktora w dany kierunek
 */
void Actor::enqueueMove(Direction dir) {
	movementQueue.push(dir);
}

/*
 *  Czy kolejka ruchów aktora jest pusta?
 */
bool Actor::wantsToMove() const {
	return movementQueue.size() != 0;
}

/*
 *  Zwraca pierwszy ruch z kolejki aktora
 */
Direction Actor::popMovement() {
	Direction ret = movementQueue.front();
	movementQueue.pop();
	return ret;
}

/*
 *  Funkcja pomocnicza do zamiany kierunków na przeciwne
 */
Direction Actor::flipDirection(Direction dir) {
	if(dir == Direction::Down)
		return Direction::Up;
	else if(dir == Direction::Up)
		return Direction::Down;
	else if(dir == Direction::Left)
		return Direction::Right;
	else
		return Direction::Left;
}
