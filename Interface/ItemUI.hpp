#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Window.hpp"
#include "Interface/Frame.hpp"
#include "Interface/Cell.hpp"
#include "Interface/Button.hpp"
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

	double statW;
	double descW;
	bool active;

	Item item;
	std::vector<Button> buttons;
	unsigned int focus;
public:
	ItemUI(Item);
	ItemUI() : active(false) {}
	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
	void ProcessKey(sf::Event::KeyEvent);
	void SetButtons();
	void Call();
	void DrawButtons(sf::RenderTarget&);
	bool isActive() { return active; }
	void Update(int);
};