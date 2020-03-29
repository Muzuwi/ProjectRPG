#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Button.hpp"

class SettUI {
private:
	sf::Sprite UI;
	sf::Text title;
	sf::Font font;

	//Buttons
	int focus; // Focus index
	vector<Button> buttons;
public:
	SettUI();
	void Init();
	void SetButtons();
	void Update(int);	//Changing focus
	void Call();
	void draw(sf::RenderTarget&);
};