#pragma once
#include <SFML/Graphics.hpp>
#include "Interface/Window.hpp"

class InvUI : public Window{
protected:
	sf::Text title;

	void DrawSelf(sf::RenderTarget&)override;
public:
	InvUI();
};

