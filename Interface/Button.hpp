#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class Button {
private:
	string file_name, text_name;
	int x, y;
	bool focus;

	sf::Sprite button;
	sf::Text text;
	sf::Font font;
public:
	Button(string, string, int, int);
	void Init();
	void draw(sf::RenderTarget&);
	void SetFocus();
	void RemoveFocus();
};