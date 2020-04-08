#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Window.hpp"
#include "Interface/Frame.hpp"
#include "Interface/Cell.hpp"
#include "Item.hpp"

class ItemUI : public Window {
protected:
	//Item Symulation
	sf::Text name;
	sf::Text type;
	sf::Text value;
	sf::Text quality;
	sf::Text stats;
	sf::Text description;
	sf::Font font;

	Item item;
public:
	ItemUI(Item);
	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
};