#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Entity/Actor.hpp"
#include "Entity/Player.hpp"
#include "PlayerUI.hpp"
#include "EnemyUI.hpp"
#include "BattleSystem/QueueUI.hpp"
#include <random> 

enum Action {
	NOTYET = 0,
	QUICK = 1,
	HEAVY = 2,
	DEFEND = 3,
	ITEM = 4,
	FLEE = 5
};

class BattleEngine {
private:
	Actor* enemy;
	Player& player;
	std::queue<Turn> queue;
	sf::Sprite interface;
	sf::Sprite background;
	int turnCouner;
	PlayerUI playerWindow;
	EnemyUI enemyWindow;
	QueueUI queueWindow;
	bool active;
	int focus;			//current focus
	std::vector<OptionWindow> buttons;
	sf::Sprite player_sprit, enemy_sprit;
	std::mt19937 mt;
	Action current;
public:
	BattleEngine(Player& yo) : player(yo), enemy(nullptr), queue(), playerWindow(yo), enemyWindow(nullptr), active(false){
		std::random_device rd;
		mt = std::mt19937(rd());
	}

	void Init();
	void Draw(sf::RenderTarget&);
	void DrawBackground(sf::RenderTarget&);
	void DrawBattleBack(sf::RenderTarget&);
	void DrawPlayer(sf::RenderTarget&, sf::Vector2f);
	void DrawEnemy(sf::RenderTarget&, sf::Vector2f);
	//void DrawAnimation(sf::RenderTarget&);
	//void DrawAnimationFrame(sf::RenderTarget&);
	void DrawInterface(sf::RenderTarget&);
	void DrawButtons(sf::RenderTarget&, sf::Vector2f);
	void ProcessTurn();
	void BattleLoop();
	void PlayerTurn(Action);
	void EnemyTurn();
	void QuickAtack(Actor&, Actor&);
	void Defeat();
	void Victory();
	void EndBattle();

	bool InitBattle(Actor*);
	void Enqueue();

	void ProcessKey(sf::Event::KeyEvent);
	void Call();
	void Update(int);

	bool IsActive() { return active; }
};