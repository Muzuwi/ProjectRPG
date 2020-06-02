#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Entity/Actor.hpp"
#include "Entity/Player.hpp"
#include "PlayerUI.hpp"
#include "EnemyUI.hpp"
#include "BattleSystem/QueueUI.hpp"


class BattleEngine {
private:
	std::shared_ptr<Actor> enemy;
	Player& player;
	std::queue<Turn> queue;
	sf::Sprite interface;
	sf::Sprite background;
	int turnCouner;
	PlayerUI playerWindow;
	EnemyUI enemyWindow;
	QueueUI queueWindow;
	bool active;

	sf::Sprite player_sprit, enemy_sprit;
public:
	BattleEngine(Player& yo) : player(yo), enemy(nullptr), queue(), playerWindow(yo), enemyWindow(yo), active(false) {}

	void Init();
	void Draw(sf::RenderTarget&);
	void DrawBackground(sf::RenderTarget&);
	void DrawBattleBack(sf::RenderTarget&);
	void DrawPlayer(sf::RenderTarget&, sf::Vector2f);
	void DrawEnemy(sf::RenderTarget&, sf::Vector2f);
	void DrawAnimation(sf::RenderTarget&);
	void DrawAnimationFrame(sf::RenderTarget&);
	void DrawInterface(sf::RenderTarget&);
	void DrawQueue(sf::RenderTarget&);

	bool InitBattle(std::shared_ptr<Actor>);
	void Enqueue(int);

	void ProcessKey(sf::Event::KeyEvent key);

	bool IsActive() { return active; }
};