#include "GameUI.hpp"

GameUI::GameUI() { }

void GameUI::Init() {
	left = NONE;
	right = NONE;

	stats.Init();
	eq.Init();
	hud.Init();
}

void GameUI::DrawGUI(sf::RenderTarget& target, const int& HP, const int& MP, const int& maxHP, const int& maxMP) {
	if (left != NONE) {
		if (left == STATS) stats.draw(target);
	}

	if (right != NONE) {
		if (right == EQ) eq.draw(target);
	}
	
	hud.draw(target, HP, MP, maxHP, maxMP);
}

void GameUI::SetScene(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::C){
		if (left == NONE) left = STATS;
		else left = NONE;
	}
	if (key.code == sf::Keyboard::I){
		if (right == NONE) right = EQ;
		else right = NONE;
	}
}