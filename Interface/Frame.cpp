#include "Frame.hpp"

Frame::Frame() { }

void Frame::Init(sf::Vector2f p, sf::Vector2f s) {
	position = p;
	size = s;
	final.setTexture(TextureManager::get()->getSpritesheet("windowskinv3").getTexture());
	this->SelfInit();
}


void Frame::Draw(sf::RenderTarget& target) {
	DrawBackground(target);
	DrawFrame(target);
	this->SelfDraw(target);
}

void Frame::DrawBackground(sf::RenderTarget& target) {
	//Background
	int x;
	if (focus == true) x = 161;
	else x = 129;

	final.setTextureRect(sf::IntRect(x, 65, 30, 30));
	final.setPosition(position);
	final.setScale(size.x / 30.0, size.y / 30.0);
	target.draw(final);
	final.setScale(1.0, 1.0);
}

void Frame::DrawFrame(sf::RenderTarget& target) {
	int x;
	if (focus == true) x = 160;
	else x = 128;

	//Top Frame
	final.setTextureRect(sf::IntRect(x, 64, 32, 1));
	final.setScale(size.x / 32.0, 1.0);
	final.setPosition(position);
	target.draw(final);
	//Bottom Frame
	final.setTextureRect(sf::IntRect(x, 64, 32, 1));
	final.setScale(size.x / 32.0, 1.0);
	final.setPosition(position + sf::Vector2f(0, size.y));
	target.draw(final);
	//Left Frame
	final.setTextureRect(sf::IntRect(x, 64, 1, 32));
	final.setScale(1.0, (size.y + 1) / 32.0);
	final.setPosition(position);
	target.draw(final);
	//Right Frame
	final.setTextureRect(sf::IntRect(x, 64, 1, 32));
	final.setScale(1.0, (size.y + 1) / 32.0);
	final.setPosition(position + sf::Vector2f(size.x, 0));
	target.draw(final);
}