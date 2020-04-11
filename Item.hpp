#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include <string>



class Item {
protected:
	std::string name;
	std::string type;
	std::string value;
	std::string quality;
	std::string stats;
	std::string description;

	sf::Sprite sprite;
public:
	Item(std::string, std::string, std::string, std::string, std::string, std::string);
	Item() {}
	void Init(std::string);
	void Draw(sf::Vector2f, sf::RenderTarget&);

	friend class ItemUI;
};
