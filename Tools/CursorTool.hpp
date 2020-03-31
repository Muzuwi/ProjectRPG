#pragma once
#include "Tool.hpp"

class CursorTool : public Tool {

public:
	CursorTool(Map& map)
	: Tool(map) { }

	void drawToolWindow(Vec2u hoverCoords, sf::RenderTarget& target) override {
		sf::RectangleShape hover;
		hover.setPosition(Vec2f(hoverCoords * Tile::dimensions()));
		hover.setSize(Vec2f(Tile::dimensions(), Tile::dimensions()));
		hover.setFillColor(sf::Color::Transparent);
		hover.setOutlineThickness(2.0);
		hover.setOutlineColor(sf::Color::Green);
		target.draw(hover);
	}
	
	bool onToolUse(Vec2u coords, Array2D<unsigned> &tiles) override { return true; }
	bool toolRepeats() override { return true; }
	bool handleKbMouse(sf::Event &event) override { return true; }
};