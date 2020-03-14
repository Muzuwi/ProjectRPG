#include "TextureManager.h"

TextureManager::TextureManager() {

};

TextureManager::~TextureManager() {

};

void TextureManager::AddTexture(sf::Texture& toAdd) {
	textureVector.push_back(toAdd);
}

sf::Texture& TextureManager::GetTexture(int index) {
	return textureVector[index];
}