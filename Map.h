#pragma once
#include <vector>
#include "Tile.h"

class Map
{
private:
	std::vector<std::vector<Tile*>> map;
	int w, h;	//width and height in tiles

	void SetDimensions(int, int);
public:
	Map(int, int);
	~Map();

	void AddTile(int, int, Tile*);
	Tile* GetTile(int, int);

	void LoadMap();
	
	int GetWidth();
	int GetHeight();
};

