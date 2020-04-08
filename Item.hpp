#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"

class Item {
protected:
	string name;
	string type;
	string value;
	string quality;
	int statLines, descLines;
	vector<string> stats;
	vector<string> description;
	sf::Sprite sprite;
public:
	Item(string, string, string, string, vector<string>, vector<string>);
	void Init(string);
	void Draw(sf::Vector2f, sf::RenderWindow&);

	friend class ItemUI;
};