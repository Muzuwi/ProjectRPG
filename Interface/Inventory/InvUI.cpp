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
	sf::Vector2f ghost_pos;

	unsigned i = 0;
	//  Przelatujemy przez wszystkie wskaźniki na itemki w backpacku
	for(auto& item : inventory.getBackpack()) {
		Cell itemCell {item};
		itemCell.Init(position + sf::Vector2f((i % 8 * 32), (i / 8 * 32)), size);

		if (i == focus) {
			itemCell.SetFocus();
			if (subWin and subWin->MovFlag()) {
				ghost_pos = itemCell.GetPosition() + sf::Vector2f(5, 5);
			}
		}
		else itemCell.RemoveFocus();

		itemCell.Draw(target);

		if(item != nullptr) {
			item->draw(target, itemCell.GetPosition());
		}

		if(item != nullptr && item->getMaxStack() != 1){
			unsigned counterSize = 10;
			auto offset = Vec2f {2.0, 2.0};

			auto& font = AssetManager::getFont("ConnectionSerif");
			std::string count = std::to_string(item->getStack());

			sf::Text itemCount;
			itemCount.setFont(font);
			itemCount.setString(count);
			itemCount.setFillColor(sf::Color::White);
			itemCount.setOutlineColor(sf::Color::Black);
			itemCount.setOutlineThickness(1.2);
			itemCount.setCharacterSize(counterSize);

			auto endPos = itemCount.findCharacterPos(count.size());
			Vec2f textPos = itemCell.GetPosition() + itemCell.GetSize() - Vec2f{endPos.x,(float)counterSize} - offset;
			itemCount.setPosition(textPos);

			target.draw(itemCount);
		}

		++i;
	}

	if (subWin and subWin->MovFlag() and to_move) {
		to_move->draw(target, ghost_pos, sf::Color(255, 255, 255, 200));
	}
}

void InvUI::Update(int change) {
	focus = (focus + change) % inventory.getBackpack().size();
}

void InvUI::ProcessKey(sf::Event::KeyEvent key) {
	if (!subWin || (subWin && !subWin->isActive())) {
		if (key.code == sf::Keyboard::W) Update(-8);
		else if (key.code == sf::Keyboard::S) Update(8);
		else if (key.code == sf::Keyboard::A) Update(-1);
		else if (key.code == sf::Keyboard::D) Update(1);
		if (key.code == sf::Keyboard::Space) {
			if (subWin and subWin->MovFlag()) {
				inventory.swapItems(focus, action_index);
				subWin->SetMovFlag(false);
			}
			else {
				if (inventory.getItem(focus) != nullptr) {
					subWin = std::make_shared<ItemUI>(*inventory.getItem(focus));

					sf::Vector2f offset(520, 50);
					Vec2f windowPos(offset + sf::Vector2f((focus % 8 * 32), (focus / 8 * 32)));
					subWin->Init(windowPos, sf::Vector2f(0, 0));
					subWin->ProcessKey(key);
					action_index = focus;
				}
			}
		}
	}
	else{
		subWin->ProcessKey(key);
		if (subWin->MovFlag()) {
			to_move = inventory.getItem(focus);
		}
	}

	if (subWin and subWin->DelFlag()) {
		inventory.deleteItem(action_index);
		subWin->SetDelFlag(false);
	}
	if (subWin and subWin->UseFlag()) {
		inventory.useItem(action_index);
		subWin->SetUseFlag(false);
	}
}