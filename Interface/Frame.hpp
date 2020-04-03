#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"

class Frame {
protected:
	sf::Sprite final;
	sf::Vector2f position, size;
	bool focus;

	virtual void SelfDraw(sf::RenderTarget&) {}
	virtual void SelfInit() {}
public:
	Frame();
	void Init(sf::Vector2f, sf::Vector2f);

	void Draw(sf::RenderTarget&);
	void DrawFrame(sf::RenderTarget&);
	void DrawBackground(sf::RenderTarget&);

	void SetFocus() { focus = true; }
	void RemoveFocus() { focus = false; }
};