#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class RawWindow {	//Without frame
protected:
	sf::Sprite final;
	sf::Vector2f position, size;
	const sf::Font& font;
	virtual void DrawSelf(sf::RenderTarget&) { }
	virtual void SelfInit(int) { }
public:
	RawWindow();
	~RawWindow();
	void Init(sf::Vector2f, sf::Vector2f, std::string, int);
	void Draw(sf::RenderTarget&);
	void SetPosition(sf::Vector2f pos) { position = pos; }
	void setSize(sf::Vector2f siz) { size = siz; }
	void SetWindowSkin(std::string);
	sf::Vector2f GetSize() { return size; }
	virtual sf::Vector2f GetPosition() { return position; }
};