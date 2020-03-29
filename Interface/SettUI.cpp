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
	Button b0("sett_button", "Audio", 330, 190);
	Button b1("sett_button", "Video", 330, 230);
	Button b2("sett_button", "Credits", 330, 270);
	Button b3("sett_button", "Main Menu", 330, 310);
	Button b4("sett_button", "Exit Game", 330, 350);
	buttons.push_back(b0);
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);
	buttons.push_back(b4);
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

void SettUI::Update(int change) {
	buttons[focus].RemoveFocus();
	focus = focus + change;
	if (focus < 0) focus = buttons.size() + focus;
	else focus = focus % buttons.size();
	buttons[focus].SetFocus();
}

void SettUI::Call() {
	//Obs³uga Przycisków
	if (focus == 0) cout << "* Audio Settings *" << endl; //Audio subwindow
	if (focus == 1) cout << "* Video Settings *" << endl; //Music subwindow
	if (focus == 2) cout << "* Credits: *" << endl << "-> Lukasz Kedziora" << endl << "-> Maciej Tomaszewski" << endl; //Credits scene
	if (focus == 3) cout << "* Someday you will go to Main Menu *" << endl; //Main menu
	if (focus == 4) cout << "* Someday I will close window *" << endl; //Close window
}