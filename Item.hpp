#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"

class Item {
protected:
	string name;
	string type;
	string value;
	string quality;
	string stats;
	string description;

	sf::Sprite sprite;
public:
	Item(string, string, string, string, string, string);
	Item() {}
	void Init(string);
	void Draw(sf::Vector2f, sf::RenderTarget&);

	friend class ItemUI;
};