#include "Cell.hpp"

Cell::Cell() : item(nullptr), empty(true), Frame() { }
Cell::Cell(const std::shared_ptr<Item>& _item) : item(_item), empty(_item), Frame() { }

void Cell::SelfInit() {
	
}

void Cell::SelfDraw(sf::RenderTarget& target) {
	
}