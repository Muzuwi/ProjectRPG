#pragma once
#include "Types.hpp"
#include "World/Map.hpp"

class Tool {
protected:
	Map& map;
public:
	Tool(Map& m)
	: map(m) { }

	virtual void drawToolWindow(Vec2u hoverCoords, sf::RenderTarget&) = 0;
	virtual bool onToolUse(Vec2u coords, Array2D<unsigned>& tiles, unsigned layer) = 0;
	virtual bool toolRepeats() = 0;
	virtual bool handleKbMouse(sf::Event& event) = 0;
};