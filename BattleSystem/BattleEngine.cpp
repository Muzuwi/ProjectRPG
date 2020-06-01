#include "BattleSystem/BattleEngine.hpp"
#include <stdlib.h>
#include <time.h> 

void BattleEngine::Init() {
	background = AssetManager::getUI("battle_back").getSprite();
	interface = AssetManager::getUI("windowskin").getSprite();
	playerWindow.Init(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
}

void BattleEngine::Draw(sf::RenderTarget& target) {
	DrawBackground(target);
	DrawBattleBack(target);
	DrawInterface(target);
}

void BattleEngine::DrawBackground(sf::RenderTarget& target) {
	target.clear(sf::Color(255,255,255));
	interface.setTextureRect(sf::Rect(128, 0, 64, 64));
	sf::Vector2f scale = { (float)(target.getSize().x / 64.0), (float)(target.getSize().y / 64.0) };
	interface.setScale(scale);
	interface.setPosition(sf::Vector2f(0, 0));
	target.draw(interface);
}

void BattleEngine::DrawBattleBack(sf::RenderTarget& target) {
	sf::Vector2f size = { 816, 624 };
	sf::Vector2f battleBackPos = { (float)((target.getSize().x - size.x) / 2.0), (float)((target.getSize().y - size.y) / 2.0) };
	background.setPosition(battleBackPos);
	target.draw(background);

	if (target.getSize().x > 1200 and target.getSize().y > 650) {
		interface.setScale(1.0, 1.0);
		//Top - Left Corner
		interface.setTextureRect(sf::IntRect(0, 0, 16, 16));
		interface.setPosition(battleBackPos);
		target.draw(interface);
		//Top Frame
		interface.setTextureRect(sf::IntRect(16, 0, 96, 16));
		interface.setScale((size.x - 32) / 96.0, 1.0);
		interface.setPosition(battleBackPos + sf::Vector2f(16, 0));
		target.draw(interface);
		//Top - Right Corner
		interface.setScale(1.0, 1.0);
		interface.setTextureRect(sf::IntRect(112, 0, 16, 16));
		interface.setPosition(battleBackPos + sf::Vector2f(size.x - 16, 0));
		target.draw(interface);
		//Left Frame
		interface.setTextureRect(sf::IntRect(0, 16, 16, 96));
		interface.setScale(1.0, (size.y - 32) / 96.0);
		interface.setPosition(battleBackPos + sf::Vector2f(0, 16));
		target.draw(interface);
		//Right Frame
		interface.setTextureRect(sf::IntRect(112, 16, 16, 96));
		interface.setPosition(battleBackPos + sf::Vector2f(size.x - 16, 16));
		target.draw(interface);
		//Bottom - Left Corner
		interface.setScale(1.0, 1.0);
		interface.setTextureRect(sf::IntRect(0, 112, 16, 16));
		interface.setPosition(battleBackPos + sf::Vector2f(0, size.y - 16));
		target.draw(interface);
		//Bottom - Right Corner
		interface.setTextureRect(sf::IntRect(112, 112, 16, 16));
		interface.setPosition(battleBackPos + size - sf::Vector2f(16, 16));
		target.draw(interface);
		//Bottom Frame
		interface.setTextureRect(sf::IntRect(16, 112, 96, 16));
		interface.setScale((size.x - 32) / 96.0, 1.0);
		interface.setPosition(battleBackPos + sf::Vector2f(16, size.y - 16));
		target.draw(interface);

		interface.setScale(1.0, 1.0);
	}
}

void BattleEngine::DrawInterface(sf::RenderTarget& target) {
	sf::Vector2f size = { 816, 624 };
	playerWindow.setPosition(sf::Vector2f(8, (target.getSize().y -(size.y * 0.50)) / 2.0));
	playerWindow.setSize(sf::Vector2f(200, size.y * 0.68));
	playerWindow.Draw(target);
}

bool BattleEngine::InitBattle(std::shared_ptr<Actor> hao) {
	if (hao == nullptr) return false;
	enemy = hao;

	turnCouner = 0;
	for (int i = 0; i < 15; i++) Enqueue(++turnCouner);

	return true;
}

void BattleEngine::Enqueue(int turn) {
	int playerAS, ememyAS;
	playerAS = player.getStatistics()["AttackSpeed"];
	ememyAS = enemy->getStatistics()["AttackSpeed"];

	double playerChance = 1.0 * (turn % 2);
	double ASmodifier = playerAS / (double)ememyAS;
	playerChance += (ASmodifier / 2);

	srand(time(NULL));
	double random = (rand() % 100) / 100;
	if (random <= playerChance) {
		queue.push(PLAYER);
		std::cout << "PLAYER" << std::endl;	//TESTING
	}
	else{
		queue.push(ENEMY);
		std::cout << "ENEMY" << std::endl; //TESTING
	}	
}