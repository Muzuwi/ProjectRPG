#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics/Spritesheet.hpp"

Spritesheet::Spritesheet(sf::Texture &&texture, Vec2u defaultDimensions) {
	m_texture = texture;
	m_sprite_size = defaultDimensions;
	m_animations = texture.getSize().y / defaultDimensions.y;
	m_frames = texture.getSize().x / defaultDimensions.x;
	std::cout << "Created spritesheet: texture size " << m_sprite_size.x << "x" << m_sprite_size.y << ", "
	          << "animations: " << m_animations << ", frames: " << m_frames << "\n";
}

/*
 *  Zwraca sprite odpowiedno przystosowany, by rysować daną animację i ramkę
 *  ze spritesheet'a. Może byc on bezpośrednio przekazany do funkcji draw w oknie gry.
 */
sf::Sprite Spritesheet::getSprite(unsigned int animation, unsigned int frame) const {
	//  Miejsce, od którego wyznaczamy obszar który będzie rysowany
	auto textureCoords = Vec2u(m_sprite_size.x * frame, m_sprite_size.y * animation);

	sf::Sprite sprite(m_texture);
	sprite.setTextureRect(sf::IntRect(textureCoords.x, textureCoords.y, m_sprite_size.x, m_sprite_size.y));
	return sprite;
}


sf::IntRect Spritesheet::getTextureCoordinates(unsigned animation, unsigned frame) const {
	auto textureCoords = Vec2u(m_sprite_size.x * frame, m_sprite_size.y * animation);
	auto rect = sf::IntRect(textureCoords.x, textureCoords.y, m_sprite_size.x, m_sprite_size.y);

	return rect;
}

sf::IntRect Spritesheet::getTextureCoordinates(unsigned index) const {
	unsigned anim = index / (m_texture.getSize().x / m_sprite_size.x);
	unsigned frame = index % (m_texture.getSize().x / m_sprite_size.x);

	return getTextureCoordinates(anim, frame);
}

sf::Sprite Spritesheet::getSprite(unsigned index) const {
	unsigned anim = index / (m_texture.getSize().x / m_sprite_size.x);
	unsigned frame = index % (m_texture.getSize().x / m_sprite_size.x);

	return getSprite(anim, frame);
}
