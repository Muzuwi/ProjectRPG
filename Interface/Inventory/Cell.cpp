#include "Cell.hpp"

Cell::Cell() : item(nullptr), empty(true), Frame() { }
Cell::Cell(const std::shared_ptr<Item>& _item) : item(_item), empty(_item), Frame() { }

void Cell::SelfInit() {
	
}

void Cell::SelfDraw(sf::RenderTarget& target) {
	if (item != nullptr) {
		item->draw(target, position);
	}
	if (item != nullptr && item->getMaxStack() != 1) {
		unsigned counterSize = 10;
		auto offset = Vec2f{ 2.0, 2.0 };

		auto& font = AssetManager::getFont("ConnectionSerif");
		std::string count = std::to_string(item->getStack());

		sf::Text itemCount;
		itemCount.setFont(font);
		itemCount.setString(count);
		itemCount.setFillColor(sf::Color::White);
		itemCount.setOutlineColor(sf::Color::Black);
		itemCount.setOutlineThickness(1.2);
		itemCount.setCharacterSize(counterSize);

		auto endPos = itemCount.findCharacterPos(count.size());
		Vec2f textPos = position + size - Vec2f{ endPos.x,(float)counterSize } -offset;
		itemCount.setPosition(textPos);

		target.draw(itemCount);
	}
}