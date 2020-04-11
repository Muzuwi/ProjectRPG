#pragma once
#include "Tool.hpp"
#include "imgui.h"
#include "imgui/imgui-SFML.h"
#include "AssetManager.hpp"

class Brush : public Tool {
	bool collision;
public:
	Brush(Map& map)
	: Tool(map), collision(false) { }

	void drawToolWindow(Vec2u hoverCoords, sf::RenderTarget& target) override {
		ImGui::Begin("Brush", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Checkbox("Collision?", &collision);
		ImGui::End();

		sf::RectangleShape hover;
		hover.setPosition(Vec2f(hoverCoords * Tile::dimensions()));
		hover.setSize(Vec2f(Tile::dimensions(), Tile::dimensions()));
		hover.setFillColor(sf::Color::Transparent);
		hover.setOutlineThickness(2.0);
		hover.setOutlineColor(sf::Color::Red);
		target.draw(hover);
	}

	bool onToolUse(Vec2u coords, Array2D<unsigned>& tiles, unsigned layer) override {
		for(unsigned x = 0; x < tiles.getX(); ++x) {
			for(unsigned y = 0; y < tiles.getY(); ++y) {
				auto tileCoords = coords + Vec2u(x,y);
				if(tileCoords.x >= map.getWidth() || tileCoords.y >= map.getHeight()) continue;

				map.floorTiles[layer][tileCoords.x][tileCoords.y] = tiles[x][y];
				map.updateVertexAt(tileCoords, layer);
			}
		}

		return false;
	}

	bool toolRepeats() override { return true; }
	bool handleKbMouse(sf::Event &event) override { return false; }
};