#include "Hud.hpp"

Hud::Hud() { }

void Hud::draw(sf::RenderTarget& target, int HP, int MP, int maxHP, int maxMP) {
	auto hp = TextureManager::get()->getSpritesheet("hp_fill").getSprite();
	auto mp = TextureManager::get()->getSpritesheet("mp_fill").getSprite();
	auto hud = TextureManager::get()->getSpritesheet("hud_empty").getSprite();
	auto cricle = TextureManager::get()->getSpritesheet("hud_cricle").getSprite();

	hud.setPosition(Vec2f(0.f, 300.f));
	hp.setPosition(Vec2f(1.f, 466.f));
	mp.setPosition(Vec2f(669.f, 464.f));

	target.draw(hud);
	float shiftHP = 131 - 131 * ( HP / double(maxHP) );
	float shiftMP = 131 - 131 * ( MP / double(maxMP) );

	hp.setTextureRect(sf::IntRect(0, shiftHP, 131, 131));
	hp.setPosition(-1, 467 + shiftHP);
	
	target.draw(hp);

	mp.setTextureRect(sf::IntRect(0, shiftMP, 131, 131));
	mp.setPosition(669, 468 + shiftMP);

	target.draw(mp);

	cricle.setPosition(Vec2f(-1.f, 467.f));
	target.draw(cricle);
	cricle.setPosition(Vec2f(669.f, 468.f));
	target.draw(cricle);
}