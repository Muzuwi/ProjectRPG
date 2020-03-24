#include "GameUI.hpp"

GameUI::GameUI() { }

void GameUI::Init() {
	left = NONE;
	right = NONE;
	hud.Init();
}

void GameUI::DrawGUI(sf::RenderTarget& target, const int& HP, const int& MP, const int& maxHP, const int& maxMP) {
	hud.draw(target, HP, MP, maxHP, maxMP);
}
//Under Construction :)