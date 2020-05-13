#include "InvUI.hpp"

InvUI::InvUI(Player& entity)
: inventory(entity.getInventory()), equipment(inventory.getEquipment()), font(AssetManager::getFont("ConnectionSerif")), sec_focus(section::INVENTORY)
{

}

void InvUI::DrawSelf(sf::RenderTarget& target) {
	DrawSeparator(target);
	DrawInventory(target);
	DrawEquipment(target);

	sf::Vector2f ghost_pos;
	if (subWin and subWin->MovFlag()) {
		ghost_pos = focusCellPos + sf::Vector2f(5, 5);
	}
	if (subWin and subWin->MovFlag() and to_move) {
		to_move->draw(target, ghost_pos, sf::Color(255, 255, 255, 200));
	}

	//static titles
	target.draw(title_eq);
	target.draw(title_inv);
	target.draw(title_char);

	if (subWin && subWin->isActive()) {
		subWin->Draw(target);
	}
}

void InvUI::SelfInit() {
	//title_inv
	title_inv.setFont(font);
	title_inv.setString("Inventory");
	title_inv.setFillColor(sf::Color::Black);
	title_inv.setCharacterSize(21);

	sf::Vector2f stringSize = (title_inv.findCharacterPos(8) - title_inv.findCharacterPos(0));
	stringSize.y = 24.0;
	double offset_x = position.x + (size.x / 2.0) + ((size.x / 2.0) - stringSize.x) / 2.0;
	double offset_y = position.y + (size.y / 3.0) - stringSize.y - 8;

	title_inv.setPosition(sf::Vector2f(offset_x, offset_y));

	//title_eq
	title_eq.setFont(font);
	title_eq.setString("Equipment");
	title_eq.setFillColor(sf::Color::Black);
	title_eq.setCharacterSize(21);

	stringSize = (title_eq.findCharacterPos(8) - title_eq.findCharacterPos(0));
	stringSize.y = 24.0;
	offset_x = position.x + (size.x / 2.0) + ((size.x / 2.0) - stringSize.x) / 2.0;
	offset_y = position.y + 8;

	title_eq.setPosition(sf::Vector2f(offset_x, offset_y));

	//Title Stats
	title_char.setFont(font);
	title_char.setString("Character");
	title_char.setFillColor(sf::Color::Black);
	title_char.setCharacterSize(21);

	stringSize = (title_char.findCharacterPos(8) - title_char.findCharacterPos(0));
	stringSize.y = 24.0;
	offset_x = position.x + ((size.x / 2.0) - stringSize.x) / 2.0;
	offset_y = position.y + 8;

	title_char.setPosition(sf::Vector2f(offset_x, offset_y));

	//Other
	SetButtons();
	sub = false;
}

void InvUI::SetButtons() {
	focus = 0;
}

void InvUI::DrawInventory(sf::RenderTarget& target) {
	sf::Vector2f cell_size(32, 32);
	double offset_x = position.x + (size.x / 2.0) + ((size.x / 2.0) - 256.0) / 2.0;
	double offset_y = position.y + (size.y / 3.0);
	sf::Vector2f inventory_offset(offset_x, offset_y);

	unsigned i = 0;
	//  Przelatujemy przez wszystkie wskaźniki na itemki w backpacku
	for(auto& item : inventory.getBackpack()) {
		Cell itemCell {item};
		itemCell.Init(inventory_offset + sf::Vector2f((i % 8 * 32), (i / 8 * 32)), cell_size);

		if (sec_focus == INVENTORY and i == focus) {
			itemCell.SetFocus();
			focusCellPos = itemCell.GetPosition();
		}
		else itemCell.RemoveFocus();

		itemCell.Draw(target);

		++i;
	}
}

void InvUI::DrawSeparator(sf::RenderTarget& target) {
	sf::RectangleShape separator;
	sf::Vector2f sep_position = sf::Vector2f(position.x + (size.x / 2) , position.y + 8);
	sf::Vector2f sep_size = sf::Vector2f(2 , size.y - 16);
	separator.setFillColor(sf::Color::Black);
	separator.setPosition(sep_position);
	separator.setSize(sep_size);
	target.draw(separator);
}

void InvUI::DrawEquipment(sf::RenderTarget& target) {
	sf::Vector2f cell_size(32, 32);
	double offset_x = position.x + (size.x / 2.0) + ((size.x / 2.0) - 256.0) / 2.0;
	double offset_y = position.y + 44;
	sf::Vector2f equipment_offset(offset_x, offset_y);
	
	//L-hand
	equipment_offset += sf::Vector2f(0, 0);
	Cell L_hand{ equipment.getEquipmentBySlot(EquipmentSlot::LeftHand) };
	L_hand.Init(equipment_offset, cell_size);
	if (sec_focus == EQUIPMENT and focus == 0) { 
		L_hand.SetFocus(); 
		focusCellPos = L_hand.GetPosition();
	}
	else { L_hand.RemoveFocus(); }
	L_hand.Draw(target);

	//R-hand
	Cell R_hand{ equipment.getEquipmentBySlot(EquipmentSlot::RightHand) };
	R_hand.Init(equipment_offset + sf::Vector2f(32, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 1){ 
		R_hand.SetFocus(); 
		focusCellPos = R_hand.GetPosition();
	}
	else { R_hand.RemoveFocus(); }
	R_hand.Draw(target);

	//Helmet
	Cell Helmet{ equipment.getEquipmentBySlot(EquipmentSlot::Helmet) };
	Helmet.Init(equipment_offset + sf::Vector2f(64, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 2) { 
		Helmet.SetFocus(); 
		focusCellPos = Helmet.GetPosition();
	}
	else { Helmet.RemoveFocus(); }
	Helmet.Draw(target);

	//Gloves
	Cell Gloves{ equipment.getEquipmentBySlot(EquipmentSlot::Gloves) };
	Gloves.Init(equipment_offset + sf::Vector2f(96, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 3) { 
		Gloves.SetFocus(); 
		focusCellPos = Gloves.GetPosition();
	}
	else { Gloves.RemoveFocus(); }
	Gloves.Draw(target);

	//Chest
	Cell Chest{ equipment.getEquipmentBySlot(EquipmentSlot::Chest) };
	Chest.Init(equipment_offset + sf::Vector2f(128, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 4) { 
		Chest.SetFocus(); 
		focusCellPos = Chest.GetPosition();
	}
	else { Chest.RemoveFocus(); }
	Chest.Draw(target);

	//Boots
	Cell Boots{ equipment.getEquipmentBySlot(EquipmentSlot::Boots) };
	Boots.Init(equipment_offset + sf::Vector2f(160, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 5) { 
		Boots.SetFocus(); 
		focusCellPos = Boots.GetPosition();
	}
	else { Boots.RemoveFocus(); }
	Boots.Draw(target);

	//Necklace
	Cell Necklace{ equipment.getEquipmentBySlot(EquipmentSlot::Amulet) };
	Necklace.Init(equipment_offset + sf::Vector2f(192, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 6) { 
		Necklace.SetFocus(); 
		focusCellPos = Necklace.GetPosition();
	}
	else { Necklace.RemoveFocus(); }
	Necklace.Draw(target);

	//Ring
	Cell Ring{ equipment.getEquipmentBySlot(EquipmentSlot::Ring) };
	Ring.Init(equipment_offset + sf::Vector2f(224, 0), cell_size);
	if (sec_focus == EQUIPMENT and focus == 7) {
		Ring.SetFocus(); 
		focusCellPos = Ring.GetPosition();
	}
	else { Ring.RemoveFocus(); }
	Ring.Draw(target);
}

void InvUI::Update(int change) {
	if (sec_focus == INVENTORY) {
		if (focus < 8 and change == -8) {
			sec_focus = EQUIPMENT;
		}
		else {
			if (focus >= 56 and change == 8) return;
			if (focus % 8 == 0 and change == -1) return;
			if (focus % 8 == 7 and change == 1) return;

			focus = (focus + change) % inventory.getBackpack().size();
		}
	}
	else if (sec_focus == EQUIPMENT) {
		if (change == 8) {
			sec_focus = INVENTORY;
		}
		else {
			if (focus == 0 and change == -1) return;
			if (focus == 7 and change == 1) return;
			if (change == -8) return;
			focus = (focus + change);
		}
	}
}

void InvUI::ProcessKey(sf::Event::KeyEvent key) {
	if (!subWin || (subWin && !subWin->isActive())) {
			if (key.code == sf::Keyboard::W) Update(-8);
			else if (key.code == sf::Keyboard::S) Update(8);
			else if (key.code == sf::Keyboard::A) Update(-1);
			else if (key.code == sf::Keyboard::D) Update(1);
			if (key.code == sf::Keyboard::Space) {
				if (subWin and subWin->MovFlag()) {
					if (sec_focus == INVENTORY) {
						if (action_source == EQUIPMENT) {
							std::shared_ptr<Item> temp = equipment.getEquipmentBySlot((EquipmentSlot)action_index);
							if (equipment.setEquipment((EquipmentSlot)action_index, inventory.getItem(focus))) {
								inventory.getBackpack()[focus] = temp;
							}
						}
						else
							inventory.swapItems(focus, action_index);
					}
					else if (sec_focus == EQUIPMENT) {
						std::shared_ptr<Item> temp = equipment.getEquipmentBySlot((EquipmentSlot)focus);
						if (equipment.setEquipment((EquipmentSlot)focus, inventory.getItem(action_index))) {
							inventory.getBackpack()[action_index] = temp;
						}
					}
					subWin->SetMovFlag(false);
				}
				else {
					if (sec_focus == INVENTORY) {
						if (inventory.getItem(focus) != nullptr) {
							subWin = std::make_shared<ItemUI>(*inventory.getItem(focus));
							subWin->Init(focusCellPos, sf::Vector2f(0, 0));
							subWin->ProcessKey(key);
							action_index = focus;
							action_source = INVENTORY;
						}
					}
					else if (sec_focus == EQUIPMENT) {
						if (equipment.getEquipmentBySlot((EquipmentSlot)focus) != nullptr) {
							subWin = std::make_shared<ItemUI>(*equipment.getEquipmentBySlot((EquipmentSlot)focus));
							subWin->Init(focusCellPos, sf::Vector2f(0, 0));
							subWin->ProcessKey(key);
							action_index = focus;
							action_source = EQUIPMENT;
						}
					}
				}
			}
	}
	else{
		subWin->ProcessKey(key);
		if (subWin->MovFlag()) {
			if (action_source == INVENTORY) {
				to_move = inventory.getItem(focus);
			}
			else if (action_source == EQUIPMENT) {
				to_move = equipment.getEquipmentBySlot((EquipmentSlot)focus);
			}
		}
	}

	if (subWin and subWin->DelFlag()) {
		if (action_source == INVENTORY) {
			inventory.deleteItem(action_index);
		}
		else if (action_source == EQUIPMENT) {
			equipment.setEquipment((EquipmentSlot)action_index, nullptr);
		}
		subWin->SetDelFlag(false);
	}
	if (subWin and subWin->UseFlag()) {
		if (action_source == INVENTORY) {
			inventory.useItem(action_index);
		}
		else if (action_source == EQUIPMENT) {
			//nop
		}
		subWin->SetUseFlag(false);
	}
}