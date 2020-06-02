#include "BattleSystem/QueueUI.hpp"

void QueueUI::Draw(sf::RenderTarget& target) {
	SetPosition(sf::Vector2f((target.getView().getSize().x - size.x) / 2, 0));
	background.Draw(target);
	DrawQueue(target);
}

void QueueUI::DrawQueue(sf::RenderTarget& target) {
	sf::Vector2f offset = { 8,8 };
	enemy.setColor(sf::Color::Red);
	int i = 0;
	while (i < 15 and !queue.empty()) {
		Turn current = queue.front();
		if (current == PLAYER) {
			player.setPosition(position + offset);
			target.draw(player);
		}
		else if (current == ENEMY) {
			enemy.setPosition(position + offset);
			target.draw(enemy);
		}
		offset += sf::Vector2f{32,0};
		queue.pop();
		i++;
	}
}