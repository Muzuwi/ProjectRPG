#pragma once
#include "Types.hpp"

class Spritesheet {
	sf::Texture m_texture;
	Vec2u m_sprite_size;

	unsigned m_animations;
	unsigned m_frames;
public:
	Spritesheet() {}
	Spritesheet(sf::Texture&& texture, Vec2u defaultDimensions);

	sf::Sprite getSprite(unsigned animation = 0, unsigned frame = 0) const;
	const sf::Texture& getTexture() const { return m_texture; }
};