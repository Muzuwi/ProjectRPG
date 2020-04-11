#include "GameUI.hpp"

GameUI::GameUI(Player& _player)
: player(_player), eq(_player.getInventory()) {
	current = NONE;
}

void GameUI::Init() {
	settings.Init(sf::Vector2f(250, 100), sf::Vector2f(300, 400));
	stats.Init(sf::Vector2f(0, 0), sf::Vector2f(300, 600));
	eq.Init(sf::Vector2f(500, 0), sf::Vector2f(300, 600));
	hud.Init();
}

void GameUI::DrawGUI(sf::RenderTarget& target, const int& HP, const int& MP, const int& maxHP, const int& maxMP) {
	if (current != NONE) {
		if (current == SETTINGS) settings.Draw(target);
		else if (current == STATS) stats.Draw(target);
		else if (current == EQ) eq.Draw(target);
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
		eq.ProcessKey(key);
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

bool GameUI::IsActive() {
	if (current == NONE) return false;
	return true;
}