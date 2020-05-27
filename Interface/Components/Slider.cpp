#include "Slider.hpp"

Slider::Slider(double set) : level(set) { if (width < 128) width = 128; }

void Slider::Init(sf::Vector2f pos, double wid) {
	focus = false;
	position = pos;
	width = wid;
	final.setTexture(AssetManager::getUI("slider").getTexture());
}


void Slider::Draw(sf::RenderTarget& target) {
	DrawSlider(target);
	DrawPointer(target);
}

void Slider::DrawSlider(sf::RenderTarget& target) {
	if (focus) final.setColor(sf::Color(102, 179, 255));
	else final.setColor(sf::Color(255, 255, 255));

	//Left Edge
	final.setTextureRect(sf::IntRect(256, 0, 16, 32));
	final.setPosition(position);
	target.draw(final);

	//Middle section
	final.setTextureRect(sf::IntRect(0, 0, 256, 32));
	final.setScale((width - 32) / 256, 1.0);
	final.setPosition(position + sf::Vector2f(16, 0));
	target.draw(final);

	//Right Edge
	final.setTextureRect(sf::IntRect(272, 0, 16, 32));
	final.setScale(1.0, 1.0);
	final.setPosition(position + sf::Vector2f(width - 16, 0));
	target.draw(final);
}

void Slider::DrawPointer(sf::RenderTarget& target) {
	final.setTextureRect(sf::IntRect(288, 0, 32, 32));
	double offset = (level / 1.0) * (width - 32);
	final.setPosition(position + sf::Vector2f(offset, 0));
	target.draw(final);
}