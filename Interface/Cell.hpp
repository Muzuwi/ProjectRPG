#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Interface/Frame.hpp"

class Cell : public Frame {
protected:
	//Item* item;
	string temporary;

	void SelfDraw(sf::RenderTarget&)override;
	void SelfInit()override;
public:
	Cell(string /*Item*/ );
	string Info() { return temporary; }	//'Return Item info to subwindow'
};