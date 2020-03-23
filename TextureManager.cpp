#include <filesystem>
#include "TextureManager.hpp"

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
bool TextureManager::addSpritesheet(const std::string &resourcePath, bool useConfigSize) {
	sf::Texture texture;
	if (!texture.loadFromFile(resourcePath)) return false;

	std::string resourceName = resourcePath;

	if(resourceName.find_last_of('/') != std::string::npos)
		resourceName = resourceName.substr(resourcePath.find_last_of('/') + 1);

	if(resourceName.find_last_of('.') != std::string::npos)
		resourceName = resourceName.substr(0, resourceName.find_last_of('.'));


	Vec2u defaultDimensions {};
	if(useConfigSize) {
		//  TODO:  Ładowanie z konfiguracji albo coś takiego
		if(resourceName == "playersprite") defaultDimensions = Vec2u(32, 48);
		else defaultDimensions = Vec2u(32, 32);
	} else {
		defaultDimensions = texture.getSize();
	}

	Spritesheet spritesheet(std::move(texture), defaultDimensions);
	spritesheets[resourceName] = spritesheet;

	return true;
}

/*
 *  Pobiera z menedżera tekstur spritesheet pod podaną nazwą 'resource'
 *  Jeżeli nie istnieje, narazie wywalamy wyjątek. Może powinniśmy dać jakąś defaultową error-teksture?
 */
const Spritesheet &TextureManager::getSpritesheet(const std::string &resource) {
	if(spritesheets.find(resource) == spritesheets.end())
		throw std::runtime_error("Requested non-existant spritesheet '" + resource + "'");
	return spritesheets[resource];
}

/*
 *  Automatycznie ładuje z folderu GameContent wszystkie możliwe tekstury
 */
void TextureManager::autoload() {
	namespace fs = std::filesystem;

	for(const auto& entry : fs::directory_iterator("GameContent/Spritesheet/")) {
		if(entry.is_regular_file() ) {
			std::cout << "TextureManager::autoload()/ Adding spritesheet " << entry.path().filename() << "\n";
			addSpritesheet(entry.path());
		}
	}

	for(const auto& entry : fs::directory_iterator("GameContent/UI/")) {
		if(entry.is_regular_file() ) {
			std::cout << "TextureManager::autoload()/ Adding UI element " << entry.path().filename() << "\n";
			addSpritesheet(entry.path(), false);
		}
	}
};