#pragma once
#include <cmath>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Slider {
protected:
	const sf::Font& font;
	sf::Text header;
	std::string prefix;
	sf::Sprite final;
	sf::Vector2f position;
	double width, level; // 0.0 ~ 1.0
	bool focus;

public:
	Slider(double = 0.8);
	void Init(sf::Vector2f, double, std::string);

	void Draw(sf::RenderTarget&);
	void DrawSlider(sf::RenderTarget&);
	void DrawPointer(sf::RenderTarget&);
	void DrawHeader(sf::RenderTarget&);

	sf::Vector2f GetPosition() { return position; };
	sf::Vector2f GetSize() { return sf::Vector2f(width, 32); }

	void SetFocus() { focus = true; }
	void RemoveFocus() { focus = false; }

	void Increase(float offset) { level = (level + offset); if (level > 1.0) level = 1.0; }
	void Decrease(float offset) { level = (level - offset); if (level < 0.0) level = 0.0; }
};