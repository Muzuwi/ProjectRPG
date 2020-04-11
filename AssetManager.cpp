#include <filesystem>
#include <fstream>
#include "AssetManager.hpp"


/*
 *  Importuje nową spritesheet z dysku
 *  Pobiera teksturę z pliku graficznego, i (ewentualnie) z dodatkowego pliku configu obok pliku graficznego, który mówi
 *  jakie są parametry spritesheeta (rozmiar sprite'a, ilość animacji, ...)
 *  (notka: Resource niekoniecznie musi być nazwą pliku, może to być nazwa, np. playersprite, a funkcja sama odnajduje
 *  plik graficzny, np. playersprite.png, wtedy pobieranie tekstur odbywa się za pomocą samej nazwy a nie nazwy pliku)
 */
bool AssetManager::addSpritesheet(const std::string &resourcePath, std::unordered_map<std::string, Spritesheet>& map, Vec2u (*partitioner)(Vec2u textureSize)) {
	sf::Texture texture;
	if (!texture.loadFromFile(resourcePath)) return false;

	std::string resourceName = AssetManager::getFilenameFromPath(resourcePath);

	Vec2u defaultDimensions {};
	if(!partitioner) {
		defaultDimensions = texture.getSize();
	} else {
		defaultDimensions = partitioner(texture.getSize());
	}

	Spritesheet spritesheet(std::move(texture), defaultDimensions);
	map[resourceName] = spritesheet;

	return true;
}


bool AssetManager::addJsonFile(const std::string &resourcePath) {
	std::ifstream file;
	file.open(resourcePath);
	if(!file.good()) {
		file.close();
		std::cerr << "AssetManager::addJsonFile() failed loading '" << resourcePath << "'\n";
		std::cerr << "Details: Error reading from file\n";
		return false;
	}
	std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	std::string name = AssetManager::getFilenameFromPath(resourcePath);

	try {
		auto j = nlohmann::json::parse(json);
		config[name] = j;
	} catch (std::exception& ex) {
		std::cerr << "AssetManager::addJsonFile() failed loading '" << resourcePath << "'\n";
		std::cerr << "Details: " << ex.what() << "\n";
		return false;
	}

	return true;
}


/*
 *  Automatycznie ładuje z folderu GameContent wszystkie możliwe tekstury
 */
void AssetManager::autoload() {
	namespace fs = std::filesystem;
	sf::Context context;

	//  Ładowanie Tileset'ow
	for(const auto& entry : fs::directory_iterator("GameContent/Tilesets/")) {
		if(entry.is_regular_file()) {
			if(entry.path().extension() == ".png") {
				std::cout << "AssetManager::autoload()/ Adding tileset " << entry.path().filename() << "\n";
				addSpritesheet(entry.path().string(), tilesets, [](Vec2u) -> Vec2u{
					return Vec2u{32, 32};
				});
			} else if(entry.path().extension() == ".json") {
				std::cout << "AssetManager::autoload()/ Adding tileset configuration " << entry.path().filename() << "\n";
				addJsonFile(entry.path().string());
			}
		}
	}

	//  Ładowanie postaci
	for(const auto& entry : fs::directory_iterator("GameContent/Characters/")) {
		if(entry.is_regular_file() && entry.path().extension() == ".png") {
			std::cout << "AssetManager::autoload()/ Adding character " << entry.path().filename() << "\n";
			addSpritesheet(entry.path().string(), characters, [](Vec2u textureSize) -> Vec2u{
				return textureSize/4u;
			});
		}
	}

	//  Ładowanie elementów UI
	for(const auto& entry : fs::directory_iterator("GameContent/UI/")) {
		if(entry.is_regular_file() && entry.path().extension() == ".png") {
			std::cout << "AssetManager::autoload()/ Adding UI element " << entry.path().filename() << "\n";
			addSpritesheet(entry.path().string(), UI);
		}
	}
}

std::string AssetManager::getFilenameFromPath(const std::string &path) {
	std::string name = path;

	if(name.find_last_of('/') != std::string::npos)
		name = name.substr(name.find_last_of('/') + 1);

	if(name.find_last_of('.') != std::string::npos)
		name = name.substr(0, name.find_last_of('.'));

	return name;
}
