#pragma once
#include <string>
#include <cassert>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Graphics/Spritesheet.hpp"

using namespace std;

class TextureManager
{
private:
	//  Hashmapa spritesheetów, by móc odwoływać się do nich przez nazwy, np. 'player'
	unordered_map<std::string, Spritesheet> spritesheets;
    static TextureManager* instance;

public:
	TextureManager();
	~TextureManager();

	static TextureManager* get() {
	    assert(instance);
	    return instance;
	}

	bool addSpritesheet(const std::string& resource);
	const Spritesheet& getSpritesheet(const std::string& resource);
};

