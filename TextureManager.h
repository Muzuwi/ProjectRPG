#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

using namespace std;

class TextureManager
{
private:
	vector<sf::Texture> textureVector;

public:
	TextureManager();
	~TextureManager();

	void AddTexture(sf::Texture&);
	sf::Texture& GetTexture(int);
};

