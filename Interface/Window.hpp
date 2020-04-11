#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Window {
protected:
	sf::Sprite final;
	sf::Vector2f position, size;
	sf::Font font;
	virtual void DrawSelf(sf::RenderTarget&) { }
	virtual void SelfInit() { }
public:
	Window();
	~Window();
	void Init(sf::Vector2f, sf::Vector2f);
	void Draw(sf::RenderTarget&);
	void DrawBackground(sf::RenderTarget&);
	void DrawFrame(sf::RenderTarget&);
};