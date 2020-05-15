#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Entity/Player.hpp"

class Hud {
private:
	const sf::Font& font;
	sf::Sprite hp, mp, base, back, exp;
	sf::Vector2f position;
	Player& player;
public:
	Hud(Player& entity, sf::Vector2f offset) : player(entity), position(offset), font(AssetManager::getFont("ConnectionSerif")) {};
	void Init();
	void Draw(sf::RenderTarget&);
	sf::Text ParseStatistic(std::string, int, std::string, int, std::string, int);
	sf::Text ParseStatistic(std::string, int, std::string, int);
	void DrawLine(sf::RenderTarget&, sf::Vector2f, sf::Text);
	void SetTransparency(unsigned int);
};