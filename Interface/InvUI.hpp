#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Interface/Window.hpp"
#include "Interface/Cell.hpp"
#include "Interface/ItemUI.hpp"
#include "Item.hpp"

class InvUI : public Window{
protected:
	sf::Text title;
	std::vector<Cell> backpack;
	int focus;
	bool sub;
	ItemUI subWin;

	void DrawSelf(sf::RenderTarget&)override;
	void SelfInit();
public:
	InvUI();
	void SetButtons();
	void DrawButtons(sf::RenderTarget&);	//Basicly its eq KAPPA
	void ProcessKey(sf::Event::KeyEvent);
	void Update(int);
};

