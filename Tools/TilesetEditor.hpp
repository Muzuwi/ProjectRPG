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

		ImGui::Begin("Tileset Editor");
		ImGui::Text("Editing tile type %i", editingType);

		ImGui::Separator();
		ImGui::Columns(2);

		sf::Sprite sprite;
		ImGui::Image(spritesheet->getSprite(editingType), Vec2f(Tile::dimensions() * 2.0f, Tile::dimensions() * 2.0f));



		ImGui::Dummy(ImVec2(20.0f, 0.0f));
		ImGui::SameLine();
		if(ImGui::Checkbox("U", &currTile.collision[(unsigned)Direction::Up]))
			tileset->serializeToFile();


		if(ImGui::Checkbox("##Left", &currTile.collision[(unsigned)Direction::Left]))
			tileset->serializeToFile();

		ImGui::SameLine();
		if(ImGui::Button("x")) {
			currTile.collision[0] = true;
			currTile.collision[1] = true;
			currTile.collision[2] = true;
			currTile.collision[3] = true;
			tileset->serializeToFile();
		}
		ImGui::SameLine();
		if(ImGui::Checkbox("##Right", &currTile.collision[(unsigned)Direction::Right]))
			tileset->serializeToFile();

		ImGui::Dummy(ImVec2(20.0f, 0.0f));
		ImGui::SameLine();
		if(ImGui::Checkbox("D", &currTile.collision[(unsigned)Direction::Down]))
			tileset->serializeToFile();

		ImGui::Text("Collisions");
		ImGui::Separator();

		ImGui::NextColumn();
		if(ImGui::InputScalar("Priority", ImGuiDataType_U32, &currTile.priority))
			tileset->serializeToFile();

		ImGui::End();
	}

	void updateEditing(unsigned newType) {
		editingType = newType;
	}
};
