#include <filesystem>
#include "TextureManager.hpp"

/*
 *  Importuje nową spritesheet z dysku
 *  Pobiera teksturę z pliku graficznego, i (ewentualnie) z dodatkowego pliku configu obok pliku graficznego, który mówi
 *  jakie są parametry spritesheeta (rozmiar sprite'a, ilość animacji, ...)
 *  (notka: Resource niekoniecznie musi być nazwą pliku, może to być nazwa, np. playersprite, a funkcja sama odnajduje
 *  plik graficzny, np. playersprite.png, wtedy pobieranie tekstur odbywa się za pomocą samej nazwy a nie nazwy pliku)
 */
bool TextureManager::addSpritesheet(const std::string &resourcePath, Vec2u (*partitioner)(Vec2u textureSize)) {
	sf::Texture texture;
	if (!texture.loadFromFile(resourcePath)) return false;

	std::string resourceName = resourcePath;

	if(resourceName.find_last_of('/') != std::string::npos)
		resourceName = resourceName.substr(resourcePath.find_last_of('/') + 1);

	if(resourceName.find_last_of('.') != std::string::npos)
		resourceName = resourceName.substr(0, resourceName.find_last_of('.'));

	Vec2u defaultDimensions {};
	if(!partitioner) {
		defaultDimensions = texture.getSize();
	} else {
		defaultDimensions = partitioner(texture.getSize());
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
	if(spritesheets.find(resource) == spritesheets.end()) {
		std::cerr << "Spritesheet '" << resource << "' does not exist!\n";
		throw std::runtime_error("Requested non-existant spritesheet '" + resource + "'");
	}

	return spritesheets[resource];
}

/*
 *  Automatycznie ładuje z folderu GameContent wszystkie możliwe tekstury
 */
void TextureManager::autoload() {
	namespace fs = std::filesystem;
	sf::Context context;
	for(const auto& entry : fs::directory_iterator("GameContent/Tilesets/")) {
		if(entry.is_regular_file() ) {
			std::cout << "TextureManager::autoload()/ Adding tileset " << entry.path().filename() << "\n";
			addSpritesheet(entry.path().string(), [](Vec2u) -> Vec2u{
				return Vec2u{32, 32};
			});
		}
	}

	for(const auto& entry : fs::directory_iterator("GameContent/Characters/")) {
		if(entry.is_regular_file() ) {
			std::cout << "TextureManager::autoload()/ Adding character " << entry.path().filename() << "\n";
			addSpritesheet(entry.path().string(), [](Vec2u textureSize) -> Vec2u{
				return textureSize/4u;
			});
		}
	}

	for(const auto& entry : fs::directory_iterator("GameContent/UI/")) {
		if(entry.is_regular_file() ) {
			std::cout << "TextureManager::autoload()/ Adding UI element " << entry.path().filename() << "\n";
			addSpritesheet(entry.path().string());
		}
	}
}

/*
 *  Zwraca wszystkie spritesheety załadowane do pamięci
 */
const std::unordered_map<std::string, Spritesheet>& TextureManager::getAllSpritesheets() const {
	return this->spritesheets;
}
