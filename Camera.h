#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Camera
{
private:
	sf::Vector2f position;	//Absolute camera's position
	sf::Vector2f target;	//Target position
	sf::Vector2i size;
	float speed;

public:
	Camera(int, int, float);
	~Camera();

	//Instant
	void Move(int, int);
	void MoveCenter(int, int);

	//Scroll
	void GoTo(int, int);
	void GoToCenter(int, int);

	void Update();	//update position

	sf::Vector2i GetPosition() { return sf::Vector2i((int)position.x, (int)position.y); }

	//nearest tile
	sf::Vector2i GetTileOffset(int tileSize) { return sf::Vector2i((int)(position.x) % tileSize, (int)(position.y) % tileSize); }

	//which tiles are visible
	sf::IntRect GetTileBounds(int tileSize);
};

