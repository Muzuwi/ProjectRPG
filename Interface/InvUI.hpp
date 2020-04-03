#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Interface/Window.hpp"
#include "Interface/Button.hpp"

class InvUI : public Window{
protected:
	sf::Text title;
	vector<Button> backpack;
	int focus;

	void DrawSelf(sf::RenderTarget&)override;
	void SelfInit();
public:
	InvUI();
	void SetButtons();
	void DrawButtons(sf::RenderTarget&);	//Basicly its eq KAPPA
	void Call();
	void ProcessKey(sf::Event::KeyEvent);
	void Update(int);
};

