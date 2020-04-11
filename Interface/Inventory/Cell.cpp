#include "Cell.hpp"

Cell::Cell() :  empty(true), Frame() { }

void Cell::SelfInit() {
	
}

void Cell::SelfDraw(sf::RenderTarget& target) {
	
}

void Cell::setItem(Item toSet) {
	item = toSet;
	empty = false;
}