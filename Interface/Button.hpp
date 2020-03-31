#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"

class Button {
protected:
	sf::Sprite final;
	sf::Text text;
	sf::Font font;
	sf::Vector2f position, size;

	string name;
	bool focus;
public:
	Button(string);
	void Init(sf::Vector2f, sf::Vector2f);

	void SetFocus() { focus = true; }
	void RemoveFocus() { focus = false; }

	void Draw(sf::RenderTarget&);
	void DrawFrame(sf::RenderTarget&);
	void DrawBackground(sf::RenderTarget&);
};