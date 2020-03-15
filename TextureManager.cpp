#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager() {
	instance = this;
};

TextureManager::~TextureManager() {

};

void TextureManager::AddTexture(std::string path) {
	sf::Texture texture;
	texture.loadFromFile(path);
	textureVector.push_back(texture);
}

sf::Texture& TextureManager::GetTexture(unsigned index) {
	return textureVector[index];
}