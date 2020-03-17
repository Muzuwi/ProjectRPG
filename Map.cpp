#include <fstream>
#include "Map.hpp"

/*
 *  Ładuje mapę z pliku i zwraca go w obiekcie klasy Map
 *
 *  Narazie mapa jest hardcodowana, ale ewentualnie będziemy tu ładować mapę z pliku.
 */
Map Map::from_file(const std::string&) {
//	size_t fileSize = 0;
//
//	std::ifstream file;
//	file.open(path);
//
//	file.seekg(0, std::ios::end);
//	fileSize = file.tellg();
//	file.seekg(0, std::ios::beg);
//
//	file.close();
	Map newMap;
	newMap.size = {100 , 100};
	newMap.tiles.resize(100, 100);
	for(size_t i = 0; i < 100; i++) {
		for(size_t j = 0; j < 100; j++) {
			unsigned type = 0;
			if(i == 0 || j == 0 || i == 99 || j == 99) type = 1;
			if(i % 8 == 0) type = 1;
			if(i == 10 && j == 10) type = 2;

			newMap.tiles[i][j] = Tile(type, 0, false);
		}
	}
	return newMap;
}

Map::Map(const Map &map) {
	this->size = map.size;
	this->tiles = map.tiles;
}
