#include "Hud.hpp"

Hud::Hud() { }

void Hud::Init() {
	hp = TextureManager::get()->getSpritesheet("hp_fill").getSprite();
	mp = TextureManager::get()->getSpritesheet("mp_fill").getSprite();
	base = TextureManager::get()->getSpritesheet("hud_empty").getSprite();
	cricleL = TextureManager::get()->getSpritesheet("hud_cricle").getSprite();
	cricleR = TextureManager::get()->getSpritesheet("hud_cricle").getSprite();

	base.setPosition(Vec2f(0.f, 300.f));
	hp.setPosition(Vec2f(1.f, 466.f));
	mp.setPosition(Vec2f(669.f, 464.f));
	cricleL.setPosition(Vec2f(-1.f, 467.f));
	cricleR.setPosition(Vec2f(669.f, 468.f));
}

void Hud::draw(sf::RenderTarget& target, int HP, int MP, int maxHP, int maxMP) {

	target.draw(base);
	float shiftHP = 131 - 131 * ( HP / double(maxHP) );
	float shiftMP = 131 - 131 * ( MP / double(maxMP) );

	hp.setTextureRect(sf::IntRect(0, shiftHP, 131, 131));
	hp.setPosition(-1, 467 + shiftHP);
	
	target.draw(hp);

	mp.setTextureRect(sf::IntRect(0, shiftMP, 131, 131));
	mp.setPosition(669, 468 + shiftMP);

	target.draw(mp);

	target.draw(cricleL);
	target.draw(cricleR);
}