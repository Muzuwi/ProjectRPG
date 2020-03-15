#include <fstream>
#include "Map.hpp"

Map Map::from_file(const std::string& path) {
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
	newMap.size = {10 , 10};
	newMap.tiles.resize(10, 10);
	for(size_t i = 0; i < 10; i++) {
		for(size_t j = 0; j < 10; j++) {
			newMap.tiles[i][j] = Tile((i == j) ? 1 : 0, 0, false);
		}
	}
	return newMap;
}