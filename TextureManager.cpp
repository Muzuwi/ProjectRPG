#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager() {
	instance = this;
};

TextureManager::~TextureManager() {

}

/*
 *  Importuje nową spritesheet z dysku
 *  Pobiera teksturę z pliku graficznego, i (ewentualnie) z dodatkowego pliku configu obok pliku graficznego, który mówi
 *  jakie są parametry spritesheeta (rozmiar sprite'a, ilość animacji, ...)
 *  (notka: Resource niekoniecznie musi być nazwą pliku, może to być nazwa, np. playersprite, a funkcja sama odnajduje
 *  plik graficzny, np. playersprite.png, wtedy pobieranie tekstur odbywa się za pomocą samej nazwy a nie nazwy pliku)
 */
bool TextureManager::addSpritesheet(const std::string &resource) {
	sf::Texture texture;
	if(!texture.loadFromFile(resource)) return false;

	Spritesheet spritesheet(std::move(texture), {32, (resource == "playersprite.png") ? 48u : 32u});
	spritesheets[resource] = spritesheet;

	return true;
}

/*
 *  Pobiera z menedżera tekstur spritesheet pod podaną nazwą 'resource'
 *  Jeżeli nie istnieje, narazie wywalamy wyjątek. Może powinniśmy dać jakąś defaultową error-teksture?
 */
const Spritesheet &TextureManager::getSpritesheet(const std::string &resource) {
	if(spritesheets.find(resource) == spritesheets.end())
		throw std::runtime_error("Requested non-existant spritesheet");
	return spritesheets[resource];
};