#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Entity/Player.hpp"

class Hud {
private:
	const sf::Font& font;
	sf::Sprite hp, mp, base, exp;
	sf::Vector2f position, size;
	Player& player;

	//Static values to dynamic calculate
	sf::Vector2f exp_size, bars_size, main_section_size;
public:
	Hud(Player& entity, sf::Vector2f offset) : player(entity), position(offset), font(AssetManager::getFont("VCR_OSD_MONO")) {};

	void Init();
	void Draw(sf::RenderTarget&);
	void DrawLine(sf::RenderTarget&, sf::Vector2f, sf::Text);

	sf::Text ParseStatistic(std::string, int, std::string, int, std::string, int);
	sf::Text ParseStatistic(std::string, int, std::string, int);

	sf::Vector2f getTextSize(sf::Text);
	sf::Vector2f getOffset(sf::Text, sf::Vector2f, sf::Vector2f = sf::Vector2f(0,0));
};