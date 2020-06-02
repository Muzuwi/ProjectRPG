#include "Interface/Components/RawWindow.hpp"

RawWindow::RawWindow() : font(AssetManager::getFont("VCR_OSD_MONO")) {
}

RawWindow::~RawWindow() {

}

void RawWindow::Init(sf::Vector2f p, sf::Vector2f s, std::string n, int fontsize) {
	position = p;
	size = s;
	SetWindowSkin(n);
	this->SelfInit(fontsize);
}

void RawWindow::SetWindowSkin(std::string name) {
	final.setTexture(AssetManager::getUI(name).getTexture());
}

void RawWindow::Draw(sf::RenderTarget& target) {
	final.setTextureRect(sf::IntRect(0, 0, 128, 64));
	final.setPosition(position);
	final.setScale((size.x) / 128, (size.y) / 64);
	target.draw(final);
	this->DrawSelf(target);
}