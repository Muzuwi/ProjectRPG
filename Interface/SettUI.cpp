#include "SettUI.hpp"

SettUI::SettUI() { }

void SettUI::Init() {
	UI = TextureManager::get()->getSpritesheet("settings").getSprite();
	UI.setPosition(sf::Vector2f(250.f, 100.f));

	font.loadFromFile("GameContent/fonts/arial.ttf");
	title.setFont(font);

	title.setString("Settings");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(355.f, 130.f));

	SetButtons();
}

void SettUI::SetButtons() {
	focus = 0;
	Button b1("sett_button", "Audio", 330, 190);
	Button b2("sett_button", "Video", 330, 230);
	Button b3("sett_button", "Credits", 330, 270);
	Button b4("sett_button", "Main Menu", 330, 310);
	Button b5("sett_button", "Exit Game", 330, 350);
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);
	buttons.push_back(b4);
	buttons.push_back(b5);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Init();
	}
	buttons[focus].SetFocus();
}

void SettUI::draw(sf::RenderTarget& target) {
	target.draw(UI);
	target.draw(title);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].draw(target);
	}
}