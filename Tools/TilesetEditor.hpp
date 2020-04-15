#pragma once


class TilesetEditor {
	const Spritesheet *spritesheet;
	std::string palettename;
	Array2D<unsigned> types;
	unsigned tilesetCountX;
	unsigned tilesetCountY;

	TileSet* tileset;
	unsigned editingType;
public:
	TilesetEditor(const std::string &palette = "Tileset")
			: palettename(palette) {
		types.resize(1, 1);
		types[0][0] = 0;
		editingType = 0;
	}

	void init(const std::string &palette, TileSet& _tileset) {
		tileset = &_tileset;
		palettename = palette;
		spritesheet = &AssetManager::getTileset(palettename);
		auto *texture = spritesheet->getSprite().getTexture();
		tilesetCountX = (texture->getSize().x / spritesheet->getSpriteSize().x);
		tilesetCountY = (texture->getSize().y / spritesheet->getSpriteSize().y);
	}

	void drawWindow() {
		static Vec2i initPos{-1, -1};

		Tile& currTile = tileset->tiles[editingType];

		ImGui::Begin("Tileset Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Editing tile type %i", editingType);

		sf::Sprite sprite;
		ImGui::Image(spritesheet->getSprite(editingType), Vec2f(Tile::dimensions() * 2.0f, Tile::dimensions() * 2.0f));

		ImGui::Dummy(ImVec2(20.0f, 0.0f));
		ImGui::SameLine(); ImGui::Checkbox("U", &currTile.collision[(unsigned)Direction::Up]);

		ImGui::Checkbox("L", &currTile.collision[(unsigned)Direction::Left]);
		ImGui::SameLine();  ImGui::Dummy(ImVec2(5.0f, 0.0f));
		ImGui::SameLine();
		ImGui::Checkbox("R", &currTile.collision[(unsigned)Direction::Right]);

		ImGui::Dummy(ImVec2(20.0f, 0.0f));
		ImGui::SameLine();
		ImGui::Checkbox("D", &currTile.collision[(unsigned)Direction::Down]);

		ImGui::Text("Collisions");
		ImGui::Separator();

		ImGui::InputScalar("Priority", ImGuiDataType_U32, &currTile.priority);


		ImGui::SameLine();
		if(ImGui::Button("Save changes")) {
			tileset->serializeToFile();
		}
		ImGui::End();
	}

	void updateEditing(unsigned newType) {
		editingType = newType;
	}
};