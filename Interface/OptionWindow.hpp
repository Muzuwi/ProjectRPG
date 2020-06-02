#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Interface/Components/RawWindow.hpp"

class OptionWindow : public RawWindow {
protected:
	sf::Text message;
	int fontsize;
public:
	void DrawSelf(sf::RenderTarget& target) override {
		final.setScale(1.0, (size.y) / 64);
		final.setTextureRect(sf::IntRect(212, 0, 44, 64));
		final.setPosition(position + sf::Vector2f(size.x,0));
		target.draw(final);
		message.setCharacterSize(fontsize);
		message.setPosition(position + sf::Vector2f(4, (size.y - fontsize)/4));
		target.draw(message);
	}
	void SelfInit(int fsiz)override {
		message = sf::Text(" ", font, 24);
		fontsize = fsiz;
		SetFontColor(sf::Color::Black);
		message.setPosition(position + sf::Vector2f(8, 8));
	}

	void SetMessage(sf::String mess) { 
		message.setString(mess); 
	}
	void SetColor(sf::Color color) { final.setColor(color); }
	void SetFontColor(sf::Color color) { message.setFillColor(color); }
	void SetFontSize(int size) { message.setCharacterSize(size); }
	void SetFocus() { SetColor(sf::Color(183, 149, 77)); }
	void RemoveFocus() { SetColor(sf::Color(94, 129, 209)); }
	sf::Vector2f GetPosition()override { return position + sf::Vector2f(0, 48); }
};