#pragma once
#include <algorithm>
#include "Tool.hpp"
#include "imgui.h"
#include "imgui/imgui-SFML.h"
#include "AssetManager.hpp"
#include "Entity/NPC.hpp"

class NPCCreator : public Tool {
	std::vector<std::tuple<std::string, Vec2f>> sortedSpritesheets;
	std::string selectedSpritesheet;
	std::string scriptFilename;
	NPC* pointingAtNPC;
	NPC* selectedNPC;
	bool pickingLocation;

	void drawCreatorUI(Vec2u hoverCoords, sf::RenderTarget &target) {
		if(ImGui::BeginCombo("Spritesheet", selectedSpritesheet.c_str())) {
			for(const auto& key : sortedSpritesheets ) {
				auto sName = std::get<0>(key);
				auto res = std::get<1>(key);
				std::string name = sName + " (" + std::to_string((unsigned)res.x)
				                   + "x" + std::to_string((unsigned)res.y) + ")";
				if(ImGui::Selectable(name.c_str()))
					selectedSpritesheet = sName;

				if(sName == selectedSpritesheet)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		static char scriptFname[64];
		ImGui::InputText("Script File", &scriptFname[0], 64, ImGuiInputTextFlags_CharsNoBlank);

		if(ImGui::Button(selectedNPC ? "Update" : "Create")) {
			scriptFilename = std::string(scriptFname);
			if(!selectedSpritesheet.empty() && !scriptFilename.empty()) {
				if(selectedNPC) {
					selectedNPC->spritesheet = AssetManager::getCharacter(selectedSpritesheet);
					selectedNPC->scriptName = scriptFilename;
				}
				else pickingLocation = true;
			}
		}
		if(selectedNPC) {
			ImGui::SameLine();
			if(ImGui::Button("Delete")) {
				auto res = std::find_if(map.npcs.begin(), map.npcs.end(), [=](const std::shared_ptr<NPC>& npc){
					return npc.get() == selectedNPC;
				});

				map.npcs.erase(res);

				selectedNPC = nullptr;
			}
		}
	}

	void drawInfoUI(Vec2u hoverCoords, sf::RenderTarget &target) {
		if(!selectedNPC) return;

		ImGui::Text("World Position: %ix%i", selectedNPC->getWorldPosition().x, selectedNPC->getWorldPosition().y);
		ImGui::Text("Dimensions: %ix%i", selectedNPC->getDimensions().x, selectedNPC->getDimensions().y);
		ImGui::Text("Script: %s", selectedNPC->scriptName.c_str());
	}

public:
	NPCCreator(Map& map)
	: Tool(map), selectedSpritesheet(), scriptFilename() {
		pointingAtNPC = nullptr;
		selectedNPC = nullptr;
		pickingLocation = false;

		for(const auto& ch : AssetManager::getAllCharacters()) {
			sortedSpritesheets.emplace_back(
					std::tuple<std::string, Vec2f>(ch.first, ch.second.getSpriteSize())
					);
		}
		std::sort(sortedSpritesheets.begin(), sortedSpritesheets.end(),
		[](const std::tuple<std::string, Vec2f>& a, const std::tuple<std::string, Vec2f>& b) -> bool {
			return std::lexicographical_compare(std::get<0>(a).begin(), std::get<0>(a).end(),
			                                    std::get<0>(b).begin(), std::get<0>(b).end()
					);
		});
	}

	void drawToolWindow(Vec2u hoverCoords, sf::RenderTarget &target) override {
		ImGui::Begin("NPC Tool", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		this->drawCreatorUI(hoverCoords, target);

		pointingAtNPC = map.findNPC(hoverCoords);
		if(!pickingLocation) {
			if(pointingAtNPC) {
				Vec2f drawPosition = pointingAtNPC->getSpritePosition() - Vec2f((pointingAtNPC->getDimensions().x - Tile::dimensions()) / 2, pointingAtNPC->getDimensions().y - Tile::dimensions());
				sf::RectangleShape hover;
				hover.setPosition(drawPosition.x, drawPosition.y);
				hover.setSize(Vec2f(pointingAtNPC->getDimensions().x, pointingAtNPC->getDimensions().y));
				hover.setFillColor(sf::Color::Transparent);
				hover.setOutlineThickness(2.0);
				hover.setOutlineColor(sf::Color::Cyan);
				target.draw(hover);
			}
			if(selectedNPC) {
				Vec2f drawPosition = selectedNPC->getSpritePosition() - Vec2f((selectedNPC->getDimensions().x - Tile::dimensions()) / 2, selectedNPC->getDimensions().y - Tile::dimensions());
				sf::RectangleShape hover;
				hover.setPosition(drawPosition.x, drawPosition.y);
				hover.setSize(Vec2f(selectedNPC->getDimensions().x, selectedNPC->getDimensions().y));
				hover.setFillColor(sf::Color::Transparent);
				hover.setOutlineThickness(2.0);
				hover.setOutlineColor(sf::Color::Magenta);
				target.draw(hover);
			}
		} else {
			sf::RectangleShape hover;
			hover.setPosition(Vec2f(hoverCoords * Tile::dimensions()));
			hover.setSize(Vec2f(Tile::dimensions(), Tile::dimensions()));
			hover.setFillColor(sf::Color::Transparent);
			hover.setOutlineThickness(2.0);
			hover.setOutlineColor(sf::Color::Magenta);
			target.draw(hover);
		}


		if(selectedNPC) {
			ImGui::Separator();
			this->drawInfoUI(hoverCoords, target);
		}
		ImGui::End();
	}

	bool onToolUse(Vec2u coords, Array2D<unsigned> &tiles, unsigned) override {
		selectedNPC = pointingAtNPC;

		if(pickingLocation) {
			std::shared_ptr<NPC> ptr;
			try {
				ptr = std::make_shared<NPC>(selectedSpritesheet, coords, scriptFilename);
			} catch (std::runtime_error&) { }
			if(ptr)
				map.npcs.push_back(ptr);
			pickingLocation = false;
		}

		return false;
	}




	bool handleKbMouse(sf::Event &event) override { return false; }
	bool toolRepeats() override { return false; }
};