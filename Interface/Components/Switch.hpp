#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Switch {
protected:
	const sf::Font& font;
	sf::Text header, content;
	std::string prefix;
	sf::Sprite final;
	sf::Vector2f position, size;
	std::vector<std::pair<unsigned int, unsigned int>> resolutions;
	unsigned int current;
	bool focus;

public:
	Switch();
	void Init(sf::Vector2f, sf::Vector2f, std::string);

	void Draw(sf::RenderTarget&);
	void DrawArrows(sf::RenderTarget&);
	void DrawContent(sf::RenderTarget&);
	void DrawHeader(sf::RenderTarget&);

	sf::Vector2f GetPosition() { return position; };
	sf::Vector2f GetSize() { return size; }
	sf::Vector2f getTextSize(sf::Text);
	sf::Vector2f getMiddleCords(sf::Text, int = 0, int = 0);

	std::pair<unsigned int, unsigned int> getResolution() { return resolutions[current]; }

	void SetFocus() { focus = true; }
	void RemoveFocus() { focus = false; }

	void Next() { if (current < resolutions.size() - 1) current++; }
	void Previous() { if (current > 0) current--; }
};