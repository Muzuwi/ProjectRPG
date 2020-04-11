#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Interface/Components/Frame.hpp"
#include "Item.hpp"

class Cell : public Frame {
protected:
	Item item;
	bool empty;

	void SelfDraw(sf::RenderTarget&)override;
	void SelfInit()override;
public:
	Cell();
	void setItem(Item);
	Item& getItem() { return item; };
	bool isEmpty() { return empty; };
	//string Info() { return temporary; }	//'Return Item info to subwindow'
};