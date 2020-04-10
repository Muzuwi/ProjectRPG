#include <fstream>
#include "JsonOverloads.hpp"
#include "TileSet.hpp"

/*
 *  Tutaj będziemy ładowali z pliku dane na temat kafli i ich kolizji
 */
TileSet::TileSet(const Spritesheet &mapSpritesheet, const std::string& _name)
: spritesheet(mapSpritesheet), setName(_name) {
	Vec2u size = {mapSpritesheet.getTexture().getSize().x / mapSpritesheet.getSpriteSize().x,
	              mapSpritesheet.getTexture().getSize().y / mapSpritesheet.getSpriteSize().y };

	std::ifstream file;
	file.open("GameContent/Tilesets/"+setName+".json");
	if(!file.good()) {
		std::cerr << "Failed to open Tileset configuration. Using defaults.\n";

		for(unsigned type = 0; type < size.x * size.y; ++type) {
			tiles.push_back(Tile(0));
		}

		return;
	}
	std::string tilesetJson((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	json js = json::parse(tilesetJson);
	std::vector<Tile> tileData = js["tiles"].get<std::vector<Tile>>();
	if(tileData.size() > size.x * size.y) {
		std::cerr << "Tileset data invalid! Expected " << size.x * size.y << " entries, got " << tileData.size() << "\n";
		std::cerr << "Excess entries will be ignored\n";
		tileData.resize(size.x * size.y);
	}

	tiles = tileData;
}

void TileSet::serializeToFile() {
	json js;
	js["tiles"] = this->tiles;

	std::ofstream file;
	file.open("GameContent/Tilesets/"+setName+".json");
	if(!file.good())
		throw std::runtime_error("Failed to serialize Tileset. Could not open file " + setName + " for writing");

	file << js.dump(1, '\t');
	file.close();
}

