#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Components/Button.hpp"
#include "Interface/Components/Window.hpp"

class SettUI : public Window {
private:
	sf::Text title;

	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
	//Buttons
	int focus; // Focus index
	std::vector<Button> buttons;
public:
	SettUI();
	void SetButtons();
	void Update(int);	//Changing focus
	void Call();
	void DrawButtons(sf::RenderTarget&);
	void ProcessKey(sf::Event::KeyEvent);
};