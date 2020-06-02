#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Interface/Components/Window.hpp"

enum Turn {
	PLAYER = 0,
	ENEMY = 1
};

class QueueUI{
protected:
	std::queue<Turn> queue;
	Window background;
	sf::Vector2f size, position;
	sf::Sprite player, enemy;
public:
	QueueUI() {}

	void Init(sf::Vector2f p, sf::Vector2f s, sf::Sprite pl, sf::Sprite en) { position = p; size = s; background.Init(p, s); player = pl; enemy = en; }
	void SetSize(sf::Vector2f s) { size = s; background.setSize(s); }
	void SetPosition(sf::Vector2f p) { position = p; background.setPosition(p); }
	void Draw(sf::RenderTarget&);
	void DrawQueue(sf::RenderTarget&);
	void SetQueue(std::queue<Turn> q) { queue = q; }
};