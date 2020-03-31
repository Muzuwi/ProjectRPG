#pragma once
#include "Tool.hpp"
#include "imgui.h"
#include "imgui/imgui-SFML.h"
#include "Graphics/TextureManager.hpp"

class Brush : public Tool {
	bool isDecor;
	bool collision;
	bool del;
public:
	Brush(Map& map)
	: Tool(map), isDecor(false), collision(false), del(false) { }

	void drawToolWindow(Vec2u hoverCoords, sf::RenderTarget& target) override {
		ImGui::Begin("Brush", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Checkbox("Decor?", &isDecor);
		if(isDecor) {
			ImGui::SameLine();
			ImGui::Checkbox("Delete?", &del);
		}
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

	bool onToolUse(Vec2u coords, Array2D<unsigned>& tiles) override {
		//  If drawing decorations
		if(isDecor) {
			for(unsigned x = 0; x < tiles.getX(); ++x) {
				for(unsigned y = 0; y < tiles.getY(); ++y) {
					auto tileCoords = coords + Vec2u(x,y);
					if(tileCoords.x >= map.getWidth() || tileCoords.y >= map.getHeight()) continue;

					auto res = std::find_if(map.tileDecors.begin(),map.tileDecors.end(), [=](const Map::Decor& decor){
						return decor.pos == tileCoords;
					});

					if(del) {
						if (res != map.tileDecors.end()) map.tileDecors.erase(res);
						return false;
					}

					if(res == map.tileDecors.end())
						map.tileDecors.push_back(Map::Decor({tileCoords.x, tileCoords.y}, Tile(tiles[x][y], collision)));
					else
						*res = Map::Decor({tileCoords.x, tileCoords.y}, Tile(tiles[x][y], collision));
				}
			}
		} else {  //  If drawing ground tiles
			for(unsigned x = 0; x < tiles.getX(); ++x) {
				for(unsigned y = 0; y < tiles.getY(); ++y) {
					auto tileCoords = coords + Vec2u(x,y);
					if(tileCoords.x >= map.getWidth() || tileCoords.y >= map.getHeight()) continue;

					map.floorTiles[tileCoords.x][tileCoords.y] = Tile(tiles[x][y], collision);
					map.updateVertexAt(tileCoords);
				}
			}
		}

		return false;
	}

	bool toolRepeats() override { return true; }
	bool handleKbMouse(sf::Event &event) override { return false; }
};