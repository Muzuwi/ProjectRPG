#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Button.hpp"
#include "Interface/Window.hpp"

class SettUI : public Window {
private:
	sf::Text title;

	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
	//Buttons
	int focus; // Focus index
	vector<Button> buttons;
public:
	SettUI();
	void SetButtons();
	void Update(int);	//Changing focus
	void Call();
	void DrawButtons(sf::RenderTarget&);
	void ProcessKey(sf::Event::KeyEvent);
};