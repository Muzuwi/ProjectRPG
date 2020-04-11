#include "SettUI.hpp"

SettUI::SettUI() { }

void SettUI::SelfInit(){
	SetButtons();
}

void SettUI::DrawSelf(sf::RenderTarget& target) {
	title.setFont(font);
	title.setString("Settings");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(350.f, 115.f));
	target.draw(title);

	DrawButtons(target);
}

void SettUI::SetButtons() {
	focus = 0;

	//Creating Buttons
	sf::Vector2f size(150,30);
	Button b0("Audio");
	Button b1("Video");
	Button b2("Credits");
	Button b3("Main Menu");
	Button b4("Exit Game");

	//Remembering buttons
	buttons.push_back(b0);
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);
	buttons.push_back(b4);

	//Initializing
	sf::Vector2f position(330, 190);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Init(position, size);
		position += sf::Vector2f(0, 40);
	}
	buttons[focus].SetFocus();
}

void SettUI::DrawButtons(sf::RenderTarget& target) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Draw(target);
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
	//Obsługa Przycisków
	if (focus == 0) std::cout << "* Audio Settings *" << std::endl; //Audio subwindow
	if (focus == 1) std::cout << "* Video Settings *" << std::endl; //Music subwindow
	if (focus == 2) std::cout << "* Credits: *" << std::endl << "-> Lukasz Kedziora" << std::endl << "-> Maciej Tomaszewski" << std::endl; //Credits scene
	if (focus == 3) std::cout << "* Someday you will go to Main Menu *" << std::endl; //Main menu
	if (focus == 4) std::cout << "* Someday I will close window *" << std::endl; //Close window
}

void SettUI::ProcessKey(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::W) Update(-1);
	else if (key.code == sf::Keyboard::S) Update(1);
	else if (key.code == sf::Keyboard::Space) Call();
}