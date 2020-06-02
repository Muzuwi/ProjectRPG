#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "AssetManager.hpp"

class ItemEditor {
	nlohmann::json itemlist_json;
	const Spritesheet& item_sheet;

	struct {
		bool editing {false};
		nlohmann::json* json_node {nullptr};
	} EditingItem;

	inline void start_editing(nlohmann::json& v) {
		EditingItem.editing = true;
		EditingItem.json_node = reinterpret_cast<nlohmann::json*>(&v);
	}

	inline void stop_editing() {
		EditingItem.editing = false;
		EditingItem.json_node = nullptr;

		std::ofstream file {"GameContent/ItemList.json"};
		if(!file.good()) {
			std::cerr << "Failed opening file\n";
			return;
		}
		std::string json {itemlist_json.dump(1, '\t')};
		file << json;
		file.close();
	}
public:
	ItemEditor()
	: item_sheet(AssetManager::getUI("ItemList")) {
		try {
			itemlist_json = AssetManager::getJSON("ItemList");
		} catch (std::exception&) {
			itemlist_json = {};
		}
	}

	void draw(sf::RenderTarget& t) {
		if(EditingItem.editing) {
			ImGui::Begin("Item Sprites", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
			auto itemCount = Vec2u {item_sheet.getTexture().getSize().x / 32,
						            item_sheet.getTexture().getSize().y / 32 };

			for(unsigned i = 0; i < itemCount.x; ++i) {
				for(unsigned j = 0; j < itemCount.y; ++j) {
					unsigned index = i*itemCount.y + j;

					ImGui::PushID(index);
					if(ImGui::ImageButton(item_sheet.getSprite(i, j), {32.0, 32.0})) {
						(*EditingItem.json_node)["itemSprite"] = index;
						stop_editing();
					}
					ImGui::PopID();

					if(j != itemCount.y - 1) ImGui::SameLine(0.0, 1.0f);
				}
			}
			ImGui::End();
		}

		{
			ImGui::Begin("Item List", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

			unsigned i = 0;
			for(auto it = itemlist_json.begin(); it != itemlist_json.end(); ++it) {
				std::string key = it.key();
				const auto& val = it.value();

				std::string name = val["name"];
				std::string descr = val["description"];
				unsigned itemIndex = val["itemSprite"];

				ImGui::PushID(i++);
				auto bgColor {sf::Color(0xbd, 0xbd, 0xbd)};
				if(EditingItem.editing && EditingItem.json_node == &it.value())
					bgColor = sf::Color::Magenta;

				if(ImGui::ImageButton(item_sheet.getSprite(itemIndex), -1, bgColor))
					start_editing(it.value());
				ImGui::PopID();

				ImGui::SameLine(); ImGui::Text("ID: %s", key.c_str());
				ImGui::Text("Name: %s", name.c_str());
				ImGui::Text("Description: %s", descr.c_str());
			}

			ImGui::End();
		}
	}

};