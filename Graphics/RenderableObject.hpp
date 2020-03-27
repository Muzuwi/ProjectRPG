#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Types.hpp"

class RenderableObject {
public:
	/*
     *  Encje których ilość w grze jest zdecydowanie mniejsza z reguły będą świadome własnych pozycji, dzięki czemu
     *  nie potrzeba przekazywać pozycji do ich funkcji renderowania
	 */
	virtual void draw(sf::RenderTarget& target) const = 0;

	virtual Vec2u getDimensions() const = 0;
	virtual void frameTick() = 0;
};