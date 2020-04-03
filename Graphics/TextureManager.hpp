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

public:
	TextureManager() {
		this->autoload();
	}

	~TextureManager() {}

	static TextureManager* get() {
		static TextureManager manager;
		return &manager;
	}

	bool addSpritesheet(const std::string& resourcePath, Vec2u (*partitioner)(Vec2u textureSize) = nullptr);
	const Spritesheet& getSpritesheet(const std::string& resource);

	const std::unordered_map<std::string, Spritesheet>& getAllSpritesheets() const;

	void autoload();
};