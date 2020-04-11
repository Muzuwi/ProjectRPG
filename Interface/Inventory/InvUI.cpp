#include "InvUI.hpp"

InvUI::InvUI(PlayerInventory& _inventory)
: inventory(_inventory)
{

}

void InvUI::DrawSelf(sf::RenderTarget& target) {
	target.draw(title);
	DrawButtons(target);
	if (subWin && subWin->isActive()) {
		subWin->Draw(target);
	}
}

void InvUI::SelfInit() {
	title.setFont(font);
	title.setString("Inventory");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(600.f, 15.f));
	SetButtons();
	sub = false;
}

void InvUI::SetButtons() {
	focus = 0;
}

void InvUI::DrawButtons(sf::RenderTarget& target) {
	sf::Vector2f size(32, 32);
	sf::Vector2f position(520, 50);

	unsigned i = 0;
	//  Przelatujemy przez wszystkie wskaźniki na itemki w backpacku
	for(auto& item : inventory.getBackpack()) {
		Cell itemCell {item};
		itemCell.Init(position + sf::Vector2f((i % 8 * 32), (i / 8 * 32)), size);

		if(i == focus) itemCell.SetFocus();
		else itemCell.RemoveFocus();

		itemCell.Draw(target);

		if(item != nullptr) {
			item->draw(target, itemCell.GetPosition());
		}

		++i;
	}

}

void InvUI::Update(int change) {
	focus = focus + change;
	if (focus < 0) focus = (int)inventory.getBackpack().size() + focus;
	else focus = focus % inventory.getBackpack().size();
}

void InvUI::ProcessKey(sf::Event::KeyEvent key) {
	if (!subWin || (subWin && !subWin->isActive())) {
		if (key.code == sf::Keyboard::W) Update(-8);
		else if (key.code == sf::Keyboard::S) Update(8);
		else if (key.code == sf::Keyboard::A) Update(-1);
		else if (key.code == sf::Keyboard::D) Update(1);
		if (key.code == sf::Keyboard::Space) {
			if(inventory.getItem(focus) != nullptr) {
				subWin = std::make_shared<ItemUI>(*inventory.getItem(focus));

				sf::Vector2f offset(520, 50);
				Vec2f windowPos (position + sf::Vector2f((focus % 8 * 32), (focus / 8 * 32)));
				subWin->Init(windowPos, sf::Vector2f(0, 0));
				subWin->ProcessKey(key);
			}
		}
	}
	else{
		subWin->ProcessKey(key);
	}
}