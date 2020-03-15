#pragma once
#include <string>
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>

using namespace std;

class TextureManager
{
private:
	vector<sf::Texture> textureVector;
    static TextureManager* instance;

public:
	TextureManager();
	~TextureManager();

	static TextureManager* get() {
	    assert(instance);
	    return instance;
	}

	void AddTexture(std::string path);
	sf::Texture& GetTexture(unsigned);
};

