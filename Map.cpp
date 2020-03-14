#include <vector>
#include "Map.h"
#include "Tile.h"

void Map::SetDimensions(int w, int h) {
	map.resize(w);

	for (int i = 0; i < w; i++) {
		map.at(i).resize(h, 0);
	}
}

Map::Map(int w, int h) {
	SetDimensions(w, h);
	this->w = w;
	this->h = h;
}

Map::~Map() {

}

void Map::AddTile(int x, int y, Tile* tile) {
	map[x][y] = tile;
}

Tile* Map::GetTile(int x, int y) {
	return map[x][y];
}

void Map::LoadMap() {
	//
}

int Map::GetWidth() {
	return w;
}

int Map::GetHeight() {
	return h;
}