#pragma once
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
#include "Graphics/TextureManager.hpp"
#include "World/Tile.hpp"
#include "Types.hpp"

class TilePicker {
	const Spritesheet* spritesheet;
	std::string palettename;
	Array2D<unsigned> types;
	unsigned tilesetCountX;
	unsigned tilesetCountY;
public:
	TilePicker(const std::string& palette = "Tileset")
	:palettename(palette) {
		types.resize(1, 1);
		types[0][0] = 0;
	}

	void init() {
		spritesheet = &TextureManager::get()->getSpritesheet(palettename);
		auto* texture = spritesheet->getSprite().getTexture();
		tilesetCountX = (texture->getSize().x / spritesheet->getSpriteSize().x);
		tilesetCountY = (texture->getSize().y / spritesheet->getSpriteSize().y);
	}

	void drawWindow() {
		static Vec2i initPos {-1, -1};

		ImGui::Begin("Tileset Palette", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		for(unsigned i = 0; i < tilesetCountX*tilesetCountY; i++) {
			if(i % tilesetCountX != 0) ImGui::SameLine(0.0f, 1.0f);

			ImGui::PushID(i);
			bool found = false;
			for(unsigned tX = 0; tX < types.getX(); tX++) {
				for(unsigned tY = 0; tY < types.getY(); tY++) {
					if(types[tX][tY] == i) {
						ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.56, 0.57f, 1.0f));
						found = true;
						break;
					}
				}
				if(found) break;
			}

			if(ImGui::ImageButton(spritesheet->getSprite(i))) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && initPos.x != -1) {
					auto finalPos = Vec2i(i % tilesetCountX, i / tilesetCountX);
					auto offset = finalPos - initPos;
					auto dimensions = Vec2i{std::abs(offset.x)+1, std::abs(offset.y)+1};
					types.resize(dimensions.x, dimensions.y);

					Vec2i topLeft {};
					topLeft.x = std::min(initPos.x, finalPos.x);
					topLeft.y = std::min(initPos.y, finalPos.y);
					for(unsigned x = topLeft.x; x < topLeft.x + dimensions.x; ++x) {
						for(unsigned y = topLeft.y; y < topLeft.y + dimensions.y; ++y) {
							types[x-topLeft.x][y-topLeft.y] = y * tilesetCountX + x;
						}
					}

					initPos = {-1, -1};
				} else {
					initPos = Vec2i(i % tilesetCountX, i / tilesetCountX );
					types.resize(1,1);
					types[0][0] = i;
				}
			}
			if(found) ImGui::PopStyleColor(1);

			if(ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ImGui::Text("Type: %i", i);
				ImGui::EndTooltip();
			}

			ImGui::PopID();
		}
		ImGui::End();
	}

	Array2D<unsigned>& getSelection() {
		return types;
	}

};