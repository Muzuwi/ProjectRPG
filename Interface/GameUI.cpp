#include "GameUI.hpp"

GameUI::GameUI() { }

void GameUI::Init() {
	current = NONE;

	settings.Init();
	stats.Init();
	eq.Init();
	hud.Init();
}

void GameUI::DrawGUI(sf::RenderTarget& target, const int& HP, const int& MP, const int& maxHP, const int& maxMP) {
	if (current != NONE) {
		if (current == SETTINGS) settings.draw(target);
		else if (current == STATS) stats.draw(target);
		else if (current == EQ) eq.draw(target);
	}
	
	hud.draw(target, HP, MP, maxHP, maxMP);
}

void GameUI::ProcessKey(sf::Event::KeyEvent key) {
	switch (current)
	{
	case NONE:
		SetScene(key);
		break;
	case EQ:
		if (IsSceneKey(key)) SetScene(key);
		break;
	case STATS:
		if (IsSceneKey(key)) SetScene(key);
		break;
	case SETTINGS:
		if (IsSceneKey(key)) SetScene(key);
		settings.ProcessKey(key);
		break;
	default:
		break;
	}
}

bool GameUI::IsSceneKey(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::I ||
		key.code == sf::Keyboard::C ||
		key.code == sf::Keyboard::Escape
		) return true;	//If key should switch scene
	return false;		//If not
}

void GameUI::SetScene(sf::Event::KeyEvent key) {
	switch (key.code) {
	case sf::Keyboard::Escape:
		if (current == SETTINGS) current = NONE;
		else current = SETTINGS;
		break;
	case sf::Keyboard::I:
		if (current == EQ) current = NONE;
		else current = EQ;
		break;
	case sf::Keyboard::C:
		if (current == STATS) current = NONE;
		else current = STATS;
		break;
	}
}