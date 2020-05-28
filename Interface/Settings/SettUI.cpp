#include "SettUI.hpp"
#include "Engine.hpp"

SettUI::SettUI() { }

void SettUI::SelfInit(){
	title = sf::Text("Settings", font, 32);
	title.setFillColor(sf::Color::White);
	title.setPosition(position + sf::Vector2f((size.x - getTextSize(title, "Settings").x) / 2.0, 8));
	SetButtons();
}

void SettUI::DrawSelf(sf::RenderTarget& target) {
	target.draw(title);
	DrawButtons(target);
}

void SettUI::SetButtons() {
	focus = 0;

	//Creating Buttons
	sf::Vector2f size(196,32);
	Button save("Save Game");
	Button load("Load Game");
	Button dummy(""); //Dummy element
	Button cred("Credits");
	Button menu("Main Menu");
	Button exit("Exit Game");

	//Remembering buttons
	buttons.push_back(save);
	buttons.push_back(load);
	buttons.push_back(dummy);
	buttons.push_back(dummy);
	buttons.push_back(cred);
	buttons.push_back(menu);
	buttons.push_back(exit);

	//Initializing
	sf::Vector2f position(this->position.x + ((this->size.x - size.x) / 2), this->position.y + 64);
	buttons[0].Init(position, size);
	buttons[1].Init(position + sf::Vector2f(0, 40), size);
	audio.Init(sf::Vector2f(this->position.x + 32, position.y + 100), this->size.x - 64, "Audio: ");
	resolution.Init(position + sf::Vector2f(0, 140), size, "Resolution:");
	buttons[4].Init(position + sf::Vector2f(0, 180), size);
	buttons[5].Init(position + sf::Vector2f(0, 220), size);
	buttons[6].Init(position + sf::Vector2f(0, 260), size);

	buttons[focus].SetFocus();
}

void SettUI::DrawButtons(sf::RenderTarget& target) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Draw(target);
	}
	audio.Draw(target);
	resolution.Draw(target);
}

void SettUI::Update(int change) {
	buttons[focus].RemoveFocus();
	audio.RemoveFocus();
	resolution.RemoveFocus();

	focus = focus + change;
	if (focus < 0) focus = buttons.size() + focus;
	else focus = focus % (buttons.size());
	if (focus == 2) {
		audio.SetFocus();
	}
	else if (focus == 3) {
		resolution.SetFocus();
	}
	else {
		buttons[focus].SetFocus();
	}
}

void SettUI::Call() {
	//Obsługa Przycisków
	if (focus == 0) std::cout << "* Save Game *" << std::endl;
	if (focus == 1) std::cout << "* Load Game *" << std::endl;
	if (focus == 4) std::cout << "* Credits: *\n\t-Lukasz Kedziora \n\t-Maciej Tomaszewski" << std::endl;
	if (focus == 5) std::cout << "* Main Menu *" << std::endl;
	if (focus == 6) std::cout << "* Exit Game *" << std::endl;
}

void SettUI::AudioManager(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::A) audio.Decrease(0.1);
	if (key.code == sf::Keyboard::D) audio.Increase(0.1);
}

void SettUI::ResolutionManager(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::A) resolution.Previous();
	if (key.code == sf::Keyboard::D) resolution.Next();
	Engine::ResizeWindow(window, resolution.getResolution());
}

void SettUI::ProcessKey(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::W) Update(-1);
	else if (key.code == sf::Keyboard::S) Update(1);
	else if (key.code == sf::Keyboard::Space) Call();
	else if (key.code == sf::Keyboard::A or key.code == sf::Keyboard::D) {
		if (focus == 2) AudioManager(key);
		if (focus == 3) ResolutionManager(key);
	}
}

sf::Vector2f SettUI::getTextSize(sf::Text object, std::string text) {
	return sf::Vector2f(object.findCharacterPos(text.size() - 1) - object.findCharacterPos(0));
}