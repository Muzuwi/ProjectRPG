#include "Hud.hpp"

Hud::Hud() { }

void Hud::Init() {
	hudT.loadFromFile("hud_empty.png");
	hpT.loadFromFile("hp_fill.png");
	mpT.loadFromFile("mp_fill.png");

	hud.setTexture(hudT);
	hud.setPosition(Vec2f(0.f, 300.f));

	hp.setTexture(hpT);
	hp.setPosition(Vec2f(1.f, 466.f));

	mp.setTexture(mpT);
	mp.setPosition(Vec2f(669.f, 464.f));
}

void Hud::draw(sf::RenderTarget& target, int HP, int MP, int maxHP, int maxMP) {
	target.draw(hud);
	float shiftHP = 131 - 131 * ( HP / double(maxHP) );
	float shiftMP = 131 - 131 * ( MP / double(maxMP) );

	sf::View view;
	
	hp.setTextureRect(sf::IntRect(0, shiftHP, 131, 131));
	hp.setPosition(1, 466 + shiftHP);
	
	target.draw(hp);

	mp.setTextureRect(sf::IntRect(0, shiftMP, 131, 131));
	mp.setPosition(669, 464 + shiftMP);

	target.draw(mp);
}