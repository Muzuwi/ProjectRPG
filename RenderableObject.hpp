#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Types.hpp"

class RenderableObject {
public:
	virtual void draw(Vec2u position, sf::RenderTarget& target) = 0;
	virtual Vec2u getDimensions() const = 0;
};