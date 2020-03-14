#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
private:
	sf::Sprite baseSprite;
public:
	Tile(sf::Texture&);
	~Tile();

	void Draw(int, int, sf::RenderWindow*);
};

