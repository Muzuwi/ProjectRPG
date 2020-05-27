#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Components/Button.hpp"
#include "Interface/Components/Window.hpp"
#include "Interface/Components/Slider.hpp"

class SettUI : public Window {
private:
	sf::Text title;

	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
	
	//Buttons
	int focus; // Focus index
	std::vector<Button> buttons;
	Slider audio;
public:
	SettUI();
	void SetButtons();
	void Update(int);	//Changing focus
	void Call();
	void DrawButtons(sf::RenderTarget&);
	void ProcessKey(sf::Event::KeyEvent);
	void AudioManager(sf::Event::KeyEvent key);
};