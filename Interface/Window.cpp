#include "Window.hpp"

Window::Window(){
	font.loadFromFile("GameContent/Fonts/arial.ttf");
}

Window::~Window() {

}

void Window::Init(sf::Vector2f p, sf::Vector2f s){
	position = p;
	size = s;
	final.setTexture(AssetManager::getUI("windowskinv3").getTexture());
	this->SelfInit();
}

void Window::Draw(sf::RenderTarget& target) {
	DrawBackground(target);
	DrawFrame(target);
	this->DrawSelf(target);
}

void Window::DrawBackground(sf::RenderTarget& target) {
	//Background
	final.setTextureRect(sf::IntRect(128, 0, 64, 64));
	final.setPosition(position + sf::Vector2f(2, 2));
	final.setScale((size.x - 4) / 64.0, (size.y - 4) / 64.0);
	target.draw(final);
	final.setScale(1.0, 1.0);
}

void Window::DrawFrame(sf::RenderTarget& target) {
	//Top - Left Corner
	final.setTextureRect(sf::IntRect(0, 0, 16, 16));
	final.setPosition(position);
	target.draw(final);
	//Top Frame
	final.setTextureRect(sf::IntRect(16, 0, 96, 16));
	final.setScale((size.x - 32) / 96.0, 1.0);
	final.setPosition(position + sf::Vector2f(16, 0));
	target.draw(final);
	//Top - Right Corner
	final.setScale(1.0, 1.0);
	final.setTextureRect(sf::IntRect(112, 0, 16, 16));
	final.setPosition(position + sf::Vector2f(size.x - 16, 0));
	target.draw(final);
	//Left Frame
	final.setTextureRect(sf::IntRect(0, 16, 16, 96));
	final.setScale(1.0, (size.y - 32) / 96.0);
	final.setPosition(position + sf::Vector2f(0, 16));
	target.draw(final);
	//Right Frame
	final.setTextureRect(sf::IntRect(112, 16, 16, 96));
	final.setPosition(position + sf::Vector2f(size.x - 16, 16));
	target.draw(final);
	//Bottom - Left Corner
	final.setScale(1.0, 1.0);
	final.setTextureRect(sf::IntRect(0, 112, 16, 16));
	final.setPosition(position + sf::Vector2f(0, size.y -16));
	target.draw(final);
	//Bottom - Right Corner
	final.setTextureRect(sf::IntRect(112, 112, 16, 16));
	final.setPosition(position + size - sf::Vector2f(16, 16));
	target.draw(final);
	//Bottom Frame
	final.setTextureRect(sf::IntRect(16, 112, 96, 16));
	final.setScale((size.x - 32) / 96.0, 1.0);
	final.setPosition(position + sf::Vector2f(16, size.y - 16));
	target.draw(final);
	//Draw exception staff
	this->DrawSelf(target);
}