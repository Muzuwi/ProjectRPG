#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager() {
	instance = this;
};

TextureManager::~TextureManager() {

}

bool TextureManager::addSpritesheet(const std::string &resource) {
	sf::Texture texture;
	if(!texture.loadFromFile(resource)) return false;

	Spritesheet spritesheet(std::move(texture), {32, (resource == "playersprite.png") ? 64u : 32u});
	spritesheets[resource] = spritesheet;

	return true;
}

const Spritesheet &TextureManager::getSpritesheet(const std::string &resource) {
	if(spritesheets.find(resource) == spritesheets.end())
		throw std::runtime_error("Requested non-existant spritesheet");
	return spritesheets[resource];
};