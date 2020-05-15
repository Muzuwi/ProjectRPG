#include "InvUI.hpp"

InvUI::InvUI(Player& entity)
: player(entity), statistics(entity.getStatistics()), inventory(entity.getInventory()), equipment(inventory.getEquipment()), font(AssetManager::getFont("ConnectionSerif")), sec_focus(section::INVENTORY)
{

}

void InvUI::DrawSelf(sf::RenderTarget& target) {
	DrawSeparator(target);
	DrawInventory(target);
	DrawEquipment(target);
	DrawActorFace(target, sf::Vector2f(position.x + 16, title_char.getPosition().y + 32), sf::Vector2f(97,97));
	DrawName(target, position + sf::Vector2f(120, title_char.getPosition().y + 16), player.getName());
	DrawLine(target, position + sf::Vector2f(120, title_char.getPosition().y + 48), ParseStatistic("Poziom_ ", player.getPlayerInfo()["lvl"], 16));
	DrawStatistics(target, sf::Vector2f(position.x + 16, title_char.getPosition().y + 144), 16);

	//Draw Ghost while moving item
	sf::Vector2f ghost_pos;
	if (subWin and subWin->MovFlag() and to_move) {
		ghost_pos = focusCellPos + sf::Vector2f(5, 5);
		to_move->draw(target, ghost_pos, sf::Color(255, 255, 255, 200));
	}

	//static titles
	target.draw(title_eq);
	target.draw(title_inv);
	target.draw(title_char);

	//Draw subwin(ItemInfo)
	if (subWin && subWin->isActive()) {
		subWin->Draw(target);
	}
}

void InvUI::SelfInit() {
	//EQ_legend
	eq_legend.setTexture(AssetManager::getUI("eq_back").getTexture());

	//Hero_face
	hero_face.setTexture(AssetManager::getUI("player_face").getTexture());

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

void InvUI::SetButtons() {	//ARTIFACT
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
	
	//R-hand
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::RightHand), 0, equipment_offset, cell_size);
	//L-hand
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::LeftHand), 1, equipment_offset + sf::Vector2f(32,0), cell_size);
	//Helmet
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::Helmet), 2, equipment_offset + sf::Vector2f(64, 0), cell_size);
	//Gloves
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::Gloves), 3, equipment_offset + sf::Vector2f(96, 0), cell_size);
	//Chest
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::Chest), 4, equipment_offset + sf::Vector2f(128, 0), cell_size);
	//Boots
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::Boots), 5, equipment_offset + sf::Vector2f(160, 0), cell_size);
	//Necklace
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::Amulet), 6, equipment_offset + sf::Vector2f(192, 0), cell_size);
	//Ring
	DrawEqCell(target, equipment.getEquipmentBySlot(EquipmentSlot::Ring), 7, equipment_offset + sf::Vector2f(224, 0), cell_size);
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
			//MOVING
			if (key.code == sf::Keyboard::W) Update(-8);
			else if (key.code == sf::Keyboard::S) Update(8);
			else if (key.code == sf::Keyboard::A) Update(-1);
			else if (key.code == sf::Keyboard::D) Update(1);
			//ACTION
			if (key.code == sf::Keyboard::Space) {
				//MOV FLAG IS SET
				if (subWin and subWin->MovFlag()) {
					//MOV TO INVENTORY...
					if (sec_focus == INVENTORY) {
						//...FROM EQUIPMENT
						if (action_source == EQUIPMENT) {
							std::shared_ptr<Item> temp = equipment.getEquipmentBySlot((EquipmentSlot)action_index);
							if (equipment.setEquipment((EquipmentSlot)action_index, inventory.getItem(focus))) {
								inventory.getBackpack()[focus] = temp;
							}
						}
						//...FROM INVENTORY
						else inventory.swapItems(focus, action_index);
					}
					//MOV TO EQUIPMENT...
					else if (sec_focus == EQUIPMENT) {
						//...FROM INVENTORY
						if (action_source == INVENTORY) {
							std::shared_ptr<Item> temp = equipment.getEquipmentBySlot((EquipmentSlot)focus);
							if (equipment.setEquipment((EquipmentSlot)focus, inventory.getItem(action_index))) {
								inventory.getBackpack()[action_index] = temp;
							}
						}
						//...FROM EQUIPMENT
						else {
							//nop
						}

					}
					subWin->SetMovFlag(false);
				}
				//MOV FLAG IS NOT SET
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

void InvUI::DrawIcon(sf::RenderTarget& target, sf::Sprite& object, int index, sf::Vector2f position, sf::Vector2f size) {
	object.setTextureRect(sf::IntRect(index*32, 0, size.x, size.y));
	object.setColor(sf::Color(255,255,255,160));
	object.setPosition(position);
	target.draw(object);
}

void InvUI::DrawEqCell(sf::RenderTarget& target, std::shared_ptr<Item> item, int index, sf::Vector2f position, sf::Vector2f size) {
	Cell object{ item };
	object.Init(position, size);
	if (sec_focus == EQUIPMENT and focus == index) {
		object.SetFocus();
		focusCellPos = object.GetPosition();
	}
	else { object.RemoveFocus(); }
	object.Draw(target);
	if (!object.getItem()) DrawIcon(target, eq_legend, index, object.GetPosition(), object.GetSize());
}

void InvUI::DrawActorFace(sf::RenderTarget& target, sf::Vector2f position, sf::Vector2f size) {
	Button frame("");
	frame.Init(position, size);
	frame.Draw(target);
	hero_face.setPosition(position + sf::Vector2f(1, 1));
	target.draw(hero_face);
}

void InvUI::DrawName(sf::RenderTarget& target, sf::Vector2f position, std::string name) {
	sf::Text toDisp(name, font, 21);
	toDisp.setFillColor(sf::Color::Black);
	toDisp.setPosition(position);
	target.draw(toDisp);
}

void InvUI::DrawStatistics(sf::RenderTarget& target, sf::Vector2f offset, int font_size) {
	/*
	std::vector<std::string> statNames{ "HP","MaxHP",
										"MP","MaxMP",
										"MinPhysical","MaxPhysical",
										"MinFire","MaxFire",
										"MinIce","MaxIce",
										"MinThunder","MaxThunder",
										"MinPoison","MaxPoison",
										"Crit",
										"Precision",
										"Armor",
										"Dodge",
										"FireRes","IceRes","ThunderRes","PoisonRes",
										"Strength",
										"Vitality",
										"Agility",
										"Intelligence"
	};
	*/

	DrawLine(target, offset, ParseStatistic("Zycie:_", statistics["HP"], statistics["MaxHP"], "/", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Mana:_", statistics["MP"], statistics["MaxMP"], "/", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Obrazenia fizyczne:_", statistics["MinPhysical"], statistics["MaxPhysical"], "-", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Obrazenia od ognia:_", statistics["MinFire"], statistics["MaxFire"], "-", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Obrazenia od lodu:_", statistics["MinIce"], statistics["MaxIce"], "-", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Obrazenia od blyskawic:_", statistics["MinThunder"], statistics["MaxThunder"], "-", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Obrazenia od trucizny:_", statistics["MinPoison"], statistics["MaxPoison"], "-", font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Trafienie krytyczne:_", statistics["Crit"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Celnosc:_", statistics["Precision"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Pancerz:_", statistics["Armor"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Unik:_", statistics["Dodge"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Odp. na ogien:_", statistics["FireRes"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Odp. na lod:_", statistics["IceRes"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Odp. na blyskawice:_", statistics["ThunderRes"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Odp. na trucizne:_", statistics["PoisonRes"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Sila:_", statistics["Strength"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Kondycja:_", statistics["Vitality"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Zrecznosc:_", statistics["Agility"], font_size));
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseStatistic("Intelekt:_", statistics["Intelligence"], font_size));
}

sf::Text InvUI::ParseStatistic(std::string prefix, int value1, int value2, std::string separator, int fontSize) {
	std::string line = prefix + std::to_string(value1) + separator + std::to_string(value2);
	return sf::Text(line, font, fontSize);
}

sf::Text InvUI::ParseStatistic(std::string prefix, int value, int fontSize) {
	std::string line = prefix + std::to_string(value);
	return sf::Text(line, font, fontSize);
}

void InvUI::DrawLine(sf::RenderTarget& target, sf::Vector2f position, sf::Text text) {
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setPosition(position);
	target.draw(text);
}