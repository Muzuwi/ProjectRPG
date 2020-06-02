#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Interface/Components/Window.hpp"
#include "Interface/Components/Button.hpp"
#include "Interface/OptionWindow.hpp"
#include "Entity/Player.hpp"

class EnemyUI: public Window {
protected:
	const sf::Font& font;

	//Static Titles
	sf::Text title;

	//Icons
	sf::Sprite stat_icons;

	//PLAYER
	Actor* enemy;								//Player

	//Self Operation
	void DrawSelf(sf::RenderTarget&)override;
	void SelfInit();
public:
	EnemyUI() : enemy(nullptr), font(AssetManager::getFont("VCR_OSD_MONO")) {}
	EnemyUI(Actor*);
	//Set Enemy
	void SetEnemy(Actor*);
	//Drawing Functions
	void DrawPlayerInfo(sf::RenderTarget&, sf::Vector2f, int);
	void DrawStatistics(sf::RenderTarget&, sf::Vector2f, int);
	void DrawLine(sf::RenderTarget&, sf::Vector2f, sf::Text, sf::Color = sf::Color::Black);
	void DrawBar(sf::RenderTarget&, sf::Vector2f, int, int, sf::Vector2f, sf::Color = sf::Color::White);
	void DrawIcon(sf::RenderTarget&, sf::Sprite&, int, sf::Vector2f, sf::Vector2f);
	//Parsing Functions
	sf::Text ParseText(int value1, int value2, int = 16, std::string = "", std::string = "", std::string = "");
	sf::Text ParseText(int value, int = 16, std::string = "", std::string = "");
	//Other
	sf::Vector2f getTextSize(sf::Text, std::string);
};

