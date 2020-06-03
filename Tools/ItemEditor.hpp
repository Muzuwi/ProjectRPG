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
		static bool editing_sprite = false;

		if(editing_sprite) {
			ImGui::Begin("Item Sprites", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
			auto itemCount = Vec2u {item_sheet.getTexture().getSize().x / 32,
						            item_sheet.getTexture().getSize().y / 32 };
			std::cout << itemCount.x << " " << itemCount.y << "\n";

			for(unsigned j = 0; j < itemCount.y; ++j) {
				for(unsigned i = 0; i < itemCount.x; ++i) {
					unsigned index = j*itemCount.x + i;

					ImGui::PushID(index);
					if(ImGui::ImageButton(item_sheet.getSprite(j, i), {32.0, 32.0})) {
						(*EditingItem.json_node)["itemSprite"] = index;
						stop_editing();
						editing_sprite = false;
					}
					ImGui::PopID();

					if(i != itemCount.x - 1) ImGui::SameLine(0.0, 1.0f);
				}
			}
			ImGui::End();
		}

		{
			ImGui::Begin("Item List", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

			if(ImGui::Button("Create Item")) {
				ImGui::OpenPopup("New Item");
			}
			if(ImGui::BeginPopup("New Item", ImGuiWindowFlags_Popup)) {
				static char buf[64];
				ImGui::InputText("Item ID", buf, 64);
				ImGui::SameLine();
				auto buf_str = std::string(buf);
				if(ImGui::Button("Create") && !buf_str.empty() ) {
					itemlist_json[buf_str] = json{};
					EditingItem.json_node = &(itemlist_json[buf_str]);
					itemlist_json[buf_str]["name"] = "";
					itemlist_json[buf_str]["description"] = "";
					itemlist_json[buf_str]["itemSprite"] = 0;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			if(ImGui::BeginPopup("Modify Item", ImGuiWindowFlags_Popup)) {
				static char namebuf[64];
				static char descrbuf[64];

				ImGui::InputText("Name", namebuf, 64);
				ImGui::InputText("Description", descrbuf, 64);

				if(ImGui::Button("Modify")) {
					std::string namestr {namebuf};
					std::string descrstr {descrbuf};
					if(!namestr.empty() && !descrstr.empty()) {
						(*EditingItem.json_node)["name"] = namestr;
						(*EditingItem.json_node)["description"] = descrstr;
						stop_editing();
						ImGui::CloseCurrentPopup();
					} else {
						ImGui::BeginTooltip();
						ImGui::Text("Name/Description cannot be empty");
						ImGui::End();
					}
				}

				ImGui::EndPopup();
			}


			auto iterator_to_remove = itemlist_json.end();
			unsigned i = 0;
			for(auto it = itemlist_json.begin(); it != itemlist_json.end(); ++it) {
				ImGui::PushID(i);

				std::string key = it.key();
				const auto& val = it.value();

				std::string name = val["name"];
				std::string descr = val["description"];
				unsigned itemIndex = val["itemSprite"];

				auto bgColor {sf::Color(0xbd, 0xbd, 0xbd)};
				if(editing_sprite && EditingItem.json_node == &it.value())
					bgColor = sf::Color::Magenta;

				if(ImGui::ImageButton(item_sheet.getSprite(itemIndex), -1, bgColor)) {
					start_editing(it.value());
					editing_sprite = true;
				}

				ImGui::SameLine(); ImGui::Text("ID: %s", key.c_str());
				ImGui::Text("Name: %s", name.c_str());
				ImGui::Text("Description: %s", descr.c_str());

				if(ImGui::Button("Remove")) {
					iterator_to_remove = it;
				}

				ImGui::SameLine();
				if(ImGui::Button("Modify")) {
					ImGui::PopID();
					ImGui::OpenPopup("Modify Item");
					ImGui::PushID(i);
					start_editing(*it);
				}

				i++;

				ImGui::PopID();
				ImGui::Separator();
			}
			
			if(iterator_to_remove != itemlist_json.end())
				itemlist_json.erase(iterator_to_remove);

			ImGui::End();
		}
	}

};
