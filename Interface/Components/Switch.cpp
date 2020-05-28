#include "Switch.hpp"

Switch::Switch() : font(AssetManager::getFont("VCR_OSD_MONO")) { }

void Switch::Init(sf::Vector2f pos, sf::Vector2f siz, std::string title) {
	focus = false;
	current = 0;
	position = pos;
	size = siz;
	prefix = title;
	if (size.y < 32) size.y = 32;	//min h
	if (size.x < 128) size.x = 128;	//min w

	header = sf::Text("Resolution:", font, 16);
	header.setFillColor(sf::Color::White);
	header.setPosition(getMiddleCords(header, -4, -18));

	content = sf::Text("", font, 16); //dynamic string

	final.setTexture(AssetManager::getUI("windowskinv3").getTexture());

	//Compatible resolutions
	resolutions.push_back(std::pair(800, 600) );		// 4:3
	resolutions.push_back(std::pair(1024, 768) );		// 4:3
	resolutions.push_back(std::pair(1280, 720) );		// 16:9
	resolutions.push_back(std::pair(1280, 800) );		// 16:10
	resolutions.push_back(std::pair(1366, 768) );		// 16:9
	resolutions.push_back(std::pair(1440, 900) );		// 16:10
	resolutions.push_back(std::pair(1920, 1080) );		// 16:9
	resolutions.push_back(std::pair(1920, 1200) );		// 16:10
}


void Switch::Draw(sf::RenderTarget& target) {
	DrawHeader(target);
	DrawArrows(target);
	DrawContent(target);
}

void Switch::DrawArrows(sf::RenderTarget& target) {
	if (focus) final.setColor(sf::Color(102, 179, 255));
	else final.setColor(sf::Color(255, 255, 255));

	sf::Vector2f arrow_offset_y(0, (size.y - 16) / 2);

	//Left arrow
	final.setTextureRect(sf::Rect(129, 104, 8, 16));
	final.setPosition(position + arrow_offset_y);
	target.draw(final);

	//Right arrow
	final.setTextureRect(sf::Rect(151, 104, 8, 16));
	final.setPosition(position + arrow_offset_y + sf::Vector2f(size.x - 8, 0));
	target.draw(final);
}

void Switch::DrawContent(sf::RenderTarget& target) {
	if (focus) content.setColor(sf::Color(102, 179, 255));
	else content.setColor(sf::Color(255, 255, 255));

	std::string toDisp = std::to_string(resolutions[current].first) + " x " + std::to_string(resolutions[current].second);
	content.setString(toDisp);
	content.setPosition(getMiddleCords(content, -8));
	target.draw(content);
}

void Switch::DrawHeader(sf::RenderTarget& target) {
	header.setString(prefix);
	target.draw(header);
}

sf::Vector2f Switch::getTextSize(sf::Text object) {
	return sf::Vector2f(object.findCharacterPos(object.getString().getSize() - 1) - object.findCharacterPos(0));
}

sf::Vector2f Switch::getMiddleCords(sf::Text object, int offset_x, int offset_y) {	//offset_x by left, offset_y by top
	sf::Vector2f result;
	result.x = position.x + ((size.x - getTextSize(object).x) / 2) + offset_x;
	result.y = position.y + ((size.y - object.getCharacterSize()) / 2) + offset_y;
	return result;
}