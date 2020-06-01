#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Entity/Actor.hpp"
#include "Entity/Player.hpp"
#include "PlayerUI.hpp"

enum Turn {
	PLAYER = 0,
	ENEMY = 1
};

class BattleEngine {
private:
	std::shared_ptr<Actor> enemy;
	Player& player;
	std::queue<Turn> queue;
	sf::Sprite interface;
	sf::Sprite background;
	int turnCouner;
	PlayerUI playerWindow;

public:
	BattleEngine(Player& yo) : player(yo), enemy(nullptr), queue(), playerWindow(yo) {}

	void Init();
	void Draw(sf::RenderTarget&);
	void DrawBackground(sf::RenderTarget&);
	void DrawBattleBack(sf::RenderTarget&);
	void DrawPlayer(sf::RenderTarget&);
	void DrawEnemy(sf::RenderTarget&);
	void DrawAnimation(sf::RenderTarget&);
	void DrawAnimationFrame(sf::RenderTarget&);
	void DrawInterface(sf::RenderTarget&);
	void DrawQueue(sf::RenderTarget&);

	bool InitBattle(std::shared_ptr<Actor>);
	void Enqueue(int);
};