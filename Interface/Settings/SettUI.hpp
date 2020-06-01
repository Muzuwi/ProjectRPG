#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Components/Button.hpp"
#include "Interface/Components/Window.hpp"
#include "Interface/Components/Slider.hpp"
#include "Interface/Components/Switch.hpp"

class SettUI : public Window {
private:
	sf::Text title;

	void DrawSelf(sf::RenderTarget&);
	void SelfInit();
	
	//Buttons
	bool disp_credits;
	int focus; // Focus index
	std::vector<Button> buttons;
	Slider audio;
	Switch resolution;
	std::shared_ptr<sf::RenderWindow> window;
public:
	SettUI();
	void SetButtons();
	void Update(int);	//Changing focus
	void Call();
	void DrawButtons(sf::RenderTarget&);
	bool IsCreditsActive() { return disp_credits; }
	void ProcessKey(sf::Event::KeyEvent);
	void AudioManager(sf::Event::KeyEvent);
	void ResolutionManager(sf::Event::KeyEvent);
	void SetWindow(std::shared_ptr<sf::RenderWindow> win) { window = win; };
	sf::Vector2f getTextSize(sf::Text);
	sf::Vector2f getMiddleCords(sf::Text object, int offset_x, int offset_y);
	std::pair<unsigned int, unsigned int> getRezolution() { return resolution.getResolution(); }
};