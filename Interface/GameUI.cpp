#include "GameUI.hpp"

GameUI::GameUI(Player& _player)
: player(_player), eq(_player), hud(_player, sf::Vector2f(8,8)), resolution(std::pair(800,600)) {
	current = NONE;
}

void GameUI::Init(std::shared_ptr<sf::RenderWindow> win) {
	settings.Init(sf::Vector2f(250, 100), sf::Vector2f(300, 400));
	settings.SetWindow(win);
	eq.Init(sf::Vector2f(100, 50), sf::Vector2f(600, 450));
	hud.Init();
	credits = AssetManager::getUI("credits").getSprite();
}

void GameUI::DrawGUI(sf::RenderTarget& target) {
	sf::Vector2f cred_pos((target.getView().getSize().x - 400) / 2, 250);
	credits.setPosition(cred_pos);
	settings.setPosition(sf::Vector2f((resolution.first - 300) / 2, (resolution.second - 400) / 2));
	eq.setPosition(sf::Vector2f((resolution.first - 600) / 2, (resolution.second - 450) / 2));

	hud.Draw(target);
	if (current != NONE) {
		if (current == SETTINGS) {
			if (settings.IsCreditsActive()) {
				sf::Vector2f cred_pos((target.getView().getSize().x - 400) / 2, 64);
				credits.setPosition(cred_pos);
				target.draw(credits);
			}
			else settings.Draw(target);
		}
		else if (current == EQ) eq.Draw(target);
	}
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
	}
}

bool GameUI::IsActive() {
	if (current == NONE) return false;
	return true;
}

void GameUI::UpdateResolution(std::pair<unsigned int, unsigned int> new_res) {
	if (new_res != resolution) resolution = new_res;
}