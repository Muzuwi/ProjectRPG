#pragma once
#include "Tool.hpp"

class ConnectionTool : public Tool {
	struct {
		Vec2u pickPos {0, 0};
		bool pick;
	} Data;

public:
	ConnectionTool(Map& map)
	: Tool(map) { }

	void drawToolWindow(Vec2u hoverCoords, sf::RenderTarget& target) override {
		sf::RectangleShape hover;
		hover.setPosition(Vec2f(hoverCoords * Tile::dimensions()));
		hover.setSize(Vec2f(Tile::dimensions(), Tile::dimensions()));
		hover.setFillColor(sf::Color::Transparent);
		hover.setOutlineThickness(2.0);
		hover.setOutlineColor(sf::Color::Green);
		target.draw(hover);

		ImGui::Begin("Connection Tool");
		auto& conn = map.getConnections();
		for(auto& k : conn) {
			ImGui::Text("Connection map: %s", k.targetMap.c_str());
			ImGui::Text("Pos: %ix%i", k.targetPos.x, k.targetPos.y);

			ImGui::Separator();
		}
		ImGui::Separator();
		if(ImGui::Button("Pick")) {
			Data.pick = true;
		}

		static char buf[64];
		static int pos[2];
		ImGui::InputText("Connecting Map", &buf[0], 64);
		ImGui::InputInt2("Target Position", &pos[0]);
		ImGui::Text("Source Position: %ix%i", Data.pickPos.x, Data.pickPos.y);

		if(ImGui::Button("Add")) {
			std::string str {buf};
			Connection temp;
			temp.targetMap = str;
			temp.targetPos = Vec2u{(unsigned)pos[0], (unsigned)pos[1]};
			temp.sourcePos = Vec2u(Data.pickPos);

			if(!str.empty())
				map.connections.push_back(temp);
		}


		ImGui::End();
	}
	
	bool onToolUse(Vec2u coords, Array2D<unsigned> &tiles, unsigned) override {
		if(Data.pick) {
			Data.pickPos = coords;
			Data.pick = false;
		}
		return true;
	}
	bool toolRepeats() override { return true; }
	bool handleKbMouse(sf::Event &event) override { return true; }
};