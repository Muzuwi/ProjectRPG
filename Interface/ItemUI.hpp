#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Window.hpp"

class ItemUI : public Window {
protected:
	//Item Symulation
	sf::Text name;
	sf::Text type;
	sf::Text value;
	sf::Text quality;
	sf::Text stat;
	sf::Text descript;
	sf::Font font;

	string name_ = "Ostrze burzy";
	string type_ = "One-Handed";
	string value_ = "6900";
	string quality_ = "Legendarny";
	int statLines = 3, descLines = 4;
	vector<string> stats;
	vector<string> description;
public:
	ItemUI();
	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
};