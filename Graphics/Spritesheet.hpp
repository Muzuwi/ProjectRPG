#pragma once
#include "Types.hpp"


/*
 *      Spritesheet - reprezentacja zbioru tekstur
 *  Każdy spritesheet posiada wewnętrznie teksture (całą zawartość jakiegoś pliku graficznego) oraz rozmiar sprite'a
 *  Na podstawie rozmiaru sprite'a tekstura dzielona jest na "animacje" i "ramki". Patrząc graficzne, "animacje"
 *  idą wierszami, a "ramki" kolumnami.
 */

class Spritesheet {
	sf::Texture m_texture;
	Vec2u m_sprite_size;

	unsigned m_animations;
	unsigned m_frames;
public:
	Spritesheet() {}
	Spritesheet(sf::Texture&& texture, Vec2u defaultDimensions);

	sf::Sprite getSprite(unsigned index=0) const;
	sf::Sprite getSprite(unsigned animation, unsigned frame) const;
	sf::IntRect getTextureCoordinates(unsigned animation, unsigned frame) const;
	sf::IntRect getTextureCoordinates(unsigned index) const;
	Vec2u getSpriteSize() const { return m_sprite_size; }
	const sf::Texture& getTexture() const { return m_texture; }
};