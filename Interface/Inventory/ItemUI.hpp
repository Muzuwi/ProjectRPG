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
	sf::Text name;
	sf::Text type;
	sf::Text value;
	sf::Text quality;
	sf::Text stats;
	sf::Text description;

	double statW;
	double descW;
	bool active;

	const Item& item;
	std::vector<Button> buttons;
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