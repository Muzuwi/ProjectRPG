#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Components/Window.hpp"
#include "Interface/Components/Frame.hpp"
#include "Interface/Inventory/Cell.hpp"
#include "Interface/Components/Button.hpp"
#include "World/Item.hpp"

class ItemUI : public Window {
protected:
	const sf::Font& font;

	//Content to display
	sf::Text name;
	sf::Text type;
	sf::Text value;
	sf::Text quality;
	sf::Text stats;
	sf::Text description;

	//Dynamic Height of Statistics and Description
	double statW;
	double descW;

	//IsActive Flag
	bool active;

	//Source of Content
	const Item& item;

	//Managing Buttons
	std::vector<Button> buttons;

	//Index of current focus
	unsigned int focus;
public:
	ItemUI(const Item&);

	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
	void ProcessKey(sf::Event::KeyEvent);
	void SetButtons();
	void Call();
	void DrawButtons(sf::RenderTarget&);
	bool isActive() { return active; }
	void Update(int);
};