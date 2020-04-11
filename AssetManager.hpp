#pragma once
#include <string>
#include <unordered_map>
#include "Tools/json.hpp"
#include "Graphics/Spritesheet.hpp"
#include "World/TileSet.hpp"

class AssetManager {
private:
	//  Hashmapa spritesheetów, by móc odwoływać się do nich przez nazwy, np. 'player'
	std::unordered_map<std::string, Spritesheet> UI;
	std::unordered_map<std::string, Spritesheet> tilesets;
	std::unordered_map<std::string, Spritesheet> characters;
	std::unordered_map<std::string, nlohmann::json> config;

	bool addSpritesheet(const std::string& resourcePath, std::unordered_map<std::string, Spritesheet>& map, Vec2u (*partitioner)(Vec2u textureSize) = nullptr);
	bool addJsonFile(const std::string& resourcePath);

	static std::string getFilenameFromPath(const std::string& path);
public:
	static AssetManager& get() {
		static AssetManager manager;
		return manager;
	}

	static const Spritesheet& getCharacter(const std::string& name) {
		if(get().characters.find(name) == get().characters.end()) {
			std::cerr << "Character spritesheet '" << name << "' does not exist!\n";
			throw std::runtime_error("Requested non-existant spritesheet '" + name + "'");
		}

		return get().characters[name];
	}

	static const Spritesheet& getTileset(const std::string& name) {
		if(get().tilesets.find(name) == get().tilesets.end()) {
			std::cerr << "Tileset spritesheet '" << name << "' does not exist!\n";
			throw std::runtime_error("Requested non-existant spritesheet '" + name + "'");
		}

		return get().tilesets[name];
	}

	static const Spritesheet& getUI(const std::string& name) {
		if(get().UI.find(name) == get().UI.end()) {
			std::cerr << "Character spritesheet '" << name << "' does not exist!\n";
			throw std::runtime_error("Requested non-existant spritesheet '" + name + "'");
		}

		return get().UI[name];
	}

	static const nlohmann::json& getJSON(const std::string& name) {
		if(get().config.find(name) == get().config.end()) {
			std::cerr << "JSON configuration '" << name << "' does not exist!\n";
			throw std::runtime_error("Requested non-existant JSON config '" + name + "'");
		}

		return get().config[name];
	}


	static const std::unordered_map<std::string, Spritesheet> getAllTilesets(){
		return get().tilesets;
	}

	static const std::unordered_map<std::string, Spritesheet> getAllCharacters(){
		return get().characters;
	}

	static const std::unordered_map<std::string, Spritesheet> getAllUI(){
		return get().UI;
	}


	AssetManager() {
		this->autoload();
	}

	~AssetManager() {}

	void autoload();
};