#include "Tile.h"

Tile::Tile(sf::Texture& image) {
	baseSprite.setTexture(image);
}

Tile::~Tile() {

}

void Tile::Draw(int x, int y, sf::RenderWindow* window) {
	baseSprite.setPosition(x, y);
	window->draw(baseSprite);
}