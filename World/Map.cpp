#include <fstream>
#include <memory>
#include "Graphics/TextureManager.hpp"
#include "Map.hpp"
#include "Tools/json.hpp"
#include "JsonOverloads.hpp"

/*
 *  Ładuje mapę z pliku i zwraca go w obiekcie klasy Map
 *
 *  Narazie mapa jest hardcodowana, ale ewentualnie będziemy tu ładować mapę z pliku.
 */
Map Map::from_file(const std::string& mapName) {
	//  Ładowanie z pliku
	std::ifstream file;
	file.open("GameContent/Map/"+mapName+".json");
	if(!file.good())
		throw std::runtime_error("Could not load map '" + mapName + "' from file. Is the map present in your GameContent/Maps folder?");
	std::string mapJson((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	//  Parsowanie danych json
	json js = json::parse(mapJson);
	auto size = js["mapConfig"]["size"].get<Vec2u>();
	std::string tilesetName = js["mapConfig"]["tileset"];
	if(tilesetName.empty())
		throw std::runtime_error("Map does not specify Tileset to use");
	Map newMap {{size.x, size.y}, tilesetName};

	auto npcData = js["mapData"]["npcs"];
	if(!npcData.is_null()) {
		auto data = npcData.get<std::vector<NPCData>>();
		for(auto& v : data) {
			newMap.npcs.push_back(std::make_shared<NPC>(v.spritesheetName, Vec2u{v.worldPosition.x, v.worldPosition.y}, v.scriptName));
		}
	}

	//  3 warstwy - każda x na y
	std::vector<std::vector<std::vector<unsigned>>> tileData = js["mapData"]["tile"];

	//  Za mało warstw
	if(tileData.size() != 3)
		throw std::runtime_error("Tried loading malformed map! Expected 3 layers, got " + std::to_string(tileData.size()));

	for(unsigned layer = 0; layer < 3; ++layer) {
		//  Zla ilosc x
		if(tileData[layer].size() != size.x) {
			throw std::runtime_error("Tried loading malformed map! Expected tileData size.x of "
							+ std::to_string(size.x) + ", got " + std::to_string(tileData[layer].size()));
		}

		for(unsigned x = 0; x < size.x; ++x) {
			//  Zla ilosc y
			if(tileData[layer][x].size() != size.y) {
				throw std::runtime_error("Tried loading malformed map! Expected tileData size.y of "
				                         + std::to_string(size.y) + ", got " + std::to_string(tileData[layer][x].size()));
			}

			for(unsigned y = 0; y < size.y; ++y) {
				newMap.floorTiles[layer][x][y] = tileData[layer][x][y];
			}
		}
	}

	return newMap;
}

/*
 *  Dokonuje zapisu mapy do wskazanego pliku w folderze 'GameContent/Map/'
 */
void Map::serializeToFile(const std::string &filename) {
	//  Otwieranie pliku
	std::ofstream file;
	file.open("GameContent/Map/"+filename+".json");
	if(!file.good())
		throw std::runtime_error("Failed to serialize map. Could not open file " + filename + " for writing");

	json j;
	j["mapConfig"]["size"] = this->size;
	j["mapConfig"]["tileset"] = this->tilesetName;

	unsigned i = 0;
	for(auto& npc : npcs) {
		NPCData data;
		data.worldPosition = npc->getWorldPosition();
		data.scriptName = npc->getScriptName();
		data.spritesheetName = npc->getSpritesheetName();
		data.movementSpeed = npc->getMoveSpeed();
		j["mapData"]["npcs"][i++] = data;
	}

	for(unsigned layer = 0; layer < 3; ++layer) {
		for(unsigned x = 0; x < size.x; ++x) {
			for(unsigned y = 0; y < size.y; ++y) {
				j["mapData"]["tile"][layer][x][y] = floorTiles[layer][x][y];
			}
		}
	}

	file << j.dump(1, '\t');
	file.close();
}


Map::Map(const Map &map)
: tileset(TextureManager::get()->getSpritesheet("Tileset")) {
	this->tilesetName = map.tilesetName;
	this->size = map.size;
	for(unsigned layer = 0; layer < 3; layer++) {
		this->floorTiles[layer] = map.floorTiles[layer];
		this->animatedTiles[layer] = map.animatedTiles[layer];
	}
	this->vertices = map.vertices;
	this->npcs = map.npcs;
}

void Map::draw(sf::RenderTarget &target, const Player& player) {
	this->drawTiles(target);
	this->drawEntities(target, player);
}

void Map::initializeVertexArrays() {
	vertices = sf::VertexArray(sf::Quads, 3 * size.x*size.y*4);

	for(unsigned layer = 0; layer < 3; ++layer) {
		for(unsigned i = 0; i < size.x; i++) {
			for(unsigned j = 0; j < size.y; j++) {
				this->updateVertexAt(Vec2u(i, j), layer);

				//  Zapisz wszystkie animowane kafle do osobnego wektora
				auto tile = tileset.getTile(floorTiles[layer][i][j]);
				//  FIXME:
//				if(tile.isAnimated()) {
//					animatedTiles.push_back({i, j});
//				}
			}
		}
	}
}

void Map::updateVertexAt(Vec2u pos, unsigned layer) {
	assert(layer < 3);
	auto i = pos.x,
		 j = pos.y;

	sf::Vertex* quad = &vertices[(layer * size.x * size.y * 4) + (i+j*100)*4];
	quad[0].position = sf::Vector2f(i * Tile::dimensions(), j * Tile::dimensions());
	quad[1].position = sf::Vector2f((i + 1) * Tile::dimensions(), j * Tile::dimensions());
	quad[2].position = sf::Vector2f((i + 1) * Tile::dimensions(), (j + 1) * Tile::dimensions());
	quad[3].position = sf::Vector2f(i * Tile::dimensions(), (j + 1) * Tile::dimensions());

	auto& tileType = floorTiles[layer][i][j];
	auto textureCoords = tileset.getSpritesheet().getTextureCoordinates(tileType);
	quad[0].texCoords = sf::Vector2f(textureCoords.left, textureCoords.top);
	quad[1].texCoords = sf::Vector2f(textureCoords.left+textureCoords.width, textureCoords.top);
	quad[2].texCoords = sf::Vector2f(textureCoords.left+textureCoords.width, textureCoords.top+textureCoords.height);
	quad[3].texCoords = sf::Vector2f(textureCoords.left, textureCoords.top+textureCoords.height);
}


bool Map::checkCollision(Vec2u pos, Direction dir, Actor& ref) {
	assert(pos.x < size.x && pos.y < size.y);

	bool tileCollision = false;
	for(auto& layer : floorTiles)
		tileCollision |= tileset.getTile(layer[pos.x][pos.y]).collisionCheck(dir);

	if(tileCollision) return true;

	for(auto& npc : npcs) {
		//  TODO:  Może NPC powinny mieć hitboxy?
		if(npc->getWorldPosition() == pos && ref.getWorldPosition() != npc->getWorldPosition()) {
			return true;
		}
	}

	return false;
}

NPC* Map::findNPC(Vec2u pos) {
	for(auto& npc : npcs) {
		if(npc->getWorldPosition() == pos)
			return npc.get();
	}

	return nullptr;
}


/*
 *  Rysowanie wszystkich kafli mapy
 */
void Map::drawTiles(sf::RenderTarget &target) {
	target.draw(vertices, &tileset.getTexture());
}

/*
 *  Rysowanie kafli tylko podanej warstwy
 */
void Map::drawTiles(sf::RenderTarget &target, unsigned layer) {
	assert(layer < 3);
	target.draw(vertices, &tileset.getTexture());
}


/*
 *  Rysuje wszystkie NPC mapy oraz gracza
 *  Konieczne jest przekazanie tu gracza, by rysować wszystkie tekstury w prawidłowej kolejności
 *  W przeciwnym wypadku tekstury mogą na siebie nachodzić w złych momentach
 */
void Map::drawEntities(sf::RenderTarget &target, const Player& player) {
	std::sort(npcs.begin(), npcs.end(), [](const std::shared_ptr<const NPC>& one, const std::shared_ptr<const NPC>& two) {
		return one->getSpritePosition().y < two->getSpritePosition().y;
	});

	bool playerDrawn = false;
	for(auto& npc : npcs) {
		if(npc->getSpritePosition().y > player.getSpritePosition().y && !playerDrawn) {
			player.draw(target);
			playerDrawn = true;
		}

		npc->draw(target);
	}

	if(!playerDrawn) player.draw(target);
}

/*
 *  Tworzy pustą mapę o podanych rozmiarach
 *  Domyślny tileID to 0
 */
Map Map::make_empty(Vec2u size, unsigned defType, const std::string& tilesetName) {
	Map newMap {size, tilesetName};

	newMap.tilesetName = tilesetName;
	for(unsigned layer = 0; layer < 3; layer++) {
		for(unsigned i = 0; i < size.x; i++) {
			for(unsigned j = 0; j < size.y; j++) {
				newMap.floorTiles[layer][i][j] = (layer == 0) ? defType : 0;
			}
		}
	}

	return newMap;
}

Map::Map(Vec2u size, const std::string &tileset)
: tileset(TextureManager::get()->getSpritesheet(tileset)){
	assert(size.x != 0 && size.y != 0);

	this->size = size;

	for(auto &layer : floorTiles)
		layer.resize(size.x, size.y);
}

/*
 *  Aktualizuje wszystkie NPC na mapie
 */
void Map::updateActors() {
	for(auto& npc : npcs) {
		while(npc->wantsToMove()) {
			moveActor(*npc, npc->popMovement());
		}
		npc->update();
	}
}

/*
 *  Sprawdza czy aktor może poruszyć się ze swojej obecnej pozycji w danym kierunku,
 *  i przesuwa go gdy to możliwe
 */
bool Map::moveActor(Actor &actor, Direction dir) {
	auto actorPos = actor.getWorldPosition();
	bool invalidMovements = (actorPos.x == 0 && dir == Direction::Left) ||
	                        (actorPos.y == 0 && dir == Direction::Up) ||
	                        (actorPos.x == getWidth() - 1 && dir == Direction::Right) ||
	                        (actorPos.y == getHeight() - 1 && dir == Direction::Down);

	if(!invalidMovements) {
		bool nextTileCollision = checkCollision(Tile::offset(actorPos, dir), Actor::flipDirection(dir), actor);
		bool currTileCollision = checkCollision(actorPos, dir, actor);
		if(!nextTileCollision && !currTileCollision) {
			actor.move(dir);
			return true;
		}
	}

	actor.setFacing(dir);
	return false;
}