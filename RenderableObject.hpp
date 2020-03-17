#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Types.hpp"

class RenderableObject {
public:
	/*
     *  Dla oszczędności pamięciowej, obiekty które będą rysowane w dużych ilościach, t.j. kafelki mapy
     *  nie posiadają wiedzy o swojej pozycji i konieczne jest przekazanie im ich pozycji.
	 */
	virtual void draw(Vec2u position, sf::RenderTarget& target) = 0;

	/*
     *  Encje których ilość w grze jest zdecydowanie mniejsza z reguły będą świadome własnych pozycji, dzięki czemu
     *  nie potrzeba przekazywać pozycji do ich funkcji renderowania
	 */
	virtual void draw(sf::RenderTarget& target) = 0;

	virtual Vec2u getDimensions() const = 0;
	virtual void frameTick() = 0;
};