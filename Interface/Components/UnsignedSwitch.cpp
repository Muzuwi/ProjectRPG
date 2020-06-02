#include "UnsignedSwitch.hpp"

UnsignedSwitch::UnsignedSwitch() : font(AssetManager::getFont("VCR_OSD_MONO")), focus(false), current(0) {}

void UnsignedSwitch::Init(sf::Vector2f pos, sf::Vector2f siz) {
	position = pos;
	size = siz;
//	if (size.y < 32) size.y = 32;	//min h
//	if (size.x < 128) size.x = 128;	//min w
	header = sf::Text("Buy:", font, 16);
	header.setFillColor(sf::Color::White);
	header.setPosition(getMiddleCords(header, 0, -18));

	content = sf::Text("", font, 16); //dynamic string

	final.setTexture(AssetManager::getUI("windowskin").getTexture());
}


void UnsignedSwitch::Draw(sf::RenderTarget& target) {
	DrawArrows(target);
	target.draw(header);
	DrawContent(target);
}

void UnsignedSwitch::DrawArrows(sf::RenderTarget& target) {
	if (focus) final.setColor(sf::Color(199, 174, 119));
	else final.setColor(sf::Color(255, 255, 255));

	sf::Vector2f arrow_offset_y(0, (size.y - 16) / 2);

	//Left arrow
	if(current > 0) {
		final.setTextureRect(sf::Rect(129, 104, 8, 16));
		final.setPosition(position + arrow_offset_y);
		target.draw(final);
	}

	//Right arrow
	if(limit == -1 || (current < limit)) {
		final.setTextureRect(sf::Rect(151, 104, 8, 16));
		final.setPosition(position + arrow_offset_y + sf::Vector2f(size.x - 8, 0));
		target.draw(final);
	}
}

void UnsignedSwitch::DrawContent(sf::RenderTarget& target) {
	if (focus) content.setColor(sf::Color(199, 174, 119));
	else content.setColor(sf::Color(255, 255, 255));

	content.setString(std::to_string(current));
	content.setPosition(getMiddleCords(content, -4));
	target.draw(content);
}

sf::Vector2f UnsignedSwitch::getTextSize(sf::Text object) {
	return sf::Vector2f(object.findCharacterPos(object.getString().getSize() - 1) - object.findCharacterPos(0));
}

sf::Vector2f UnsignedSwitch::getMiddleCords(sf::Text object, int offset_x, int offset_y) {	//offset_x by left, offset_y by top
	sf::Vector2f result;
	result.x = position.x + ((size.x - getTextSize(object).x) / 2) + offset_x;
	result.y = position.y + ((size.y - object.getCharacterSize()) / 2) + offset_y;
	return result;
}