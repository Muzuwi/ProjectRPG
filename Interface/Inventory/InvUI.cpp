#include "InvUI.hpp"

InvUI::InvUI(Player& entity)
: player(entity), statistics(entity.getStatistics()), player_info(entity.getPlayerInfo()), inventory(entity.getInventory()), equipment(inventory.getEquipment()), font(AssetManager::getFont("VCR_OSD_MONO")), sec_focus(section::INVENTORY)
{

}

void InvUI::DrawSelf(sf::RenderTarget& target) {
	//Draw Content
	DrawSeparator(target);
	DrawInventory(target);
	DrawEquipment(target);
	DrawActorFace(target, position + sf::Vector2f(16, 32), sf::Vector2f(97,97));
	DrawPlayerInfo(target, position + sf::Vector2f(120, 32), 18);
	DrawStatistics(target, position + sf::Vector2f(16, 160), 16);

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
	//Getting sprites
	eq_legend.setTexture(AssetManager::getUI("eq_back").getTexture());		//EQ_legend
	hero_face.setTexture(AssetManager::getUI("player_face").getTexture());	//Hero_face
	stat_icons.setTexture(AssetManager::getUI("stat_icons").getTexture());	//stat_icons

	//Title Inventory
	title_inv = sf::Text("Inventory", font, 21);
	title_inv.setFillColor(sf::Color::White);
	title_inv.setPosition(position + sf::Vector2f((size.x / 2.0) + ((size.x / 2.0) - getTextSize(title_inv, "Inventory").x) / 2.0, (size.y / 3.0) - 28));

	//Title Equipment
	title_eq = sf::Text("Equipment", font, 21);
	title_eq.setFillColor(sf::Color::White);
	title_eq.setPosition(position + sf::Vector2f((size.x / 2.0) + ((size.x / 2.0) - getTextSize(title_eq, "Equipment").x) / 2.0, 8));

	//Title Character
	title_char = sf::Text("Character", font, 21);
	title_char.setFillColor(sf::Color::White);
	title_char.setPosition(position + sf::Vector2f(((size.x / 2) - getTextSize(title_char, "Character").x) / 2, 6));

	//Other - flags
	focus = 0;
	sub = false;
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
	
	for (unsigned int index = 0; index < (unsigned int)EquipmentSlot::_DummyEnd; index++) {
		DrawEqCell(target, equipment.getEquipmentBySlot((EquipmentSlot)index), index, equipment_offset, cell_size);
		equipment_offset += sf::Vector2f(32, 0);
	}
}

void InvUI::Update(int change) {
	if (sec_focus == INVENTORY) {
		if (focus < 8 and change == -8) {
			//Change Section
			sec_focus = EQUIPMENT;
		}
		else {
			//Moving Exceprions
			if (focus >= 56 and change == 8) return;
			if (focus % 8 == 0 and change == -1) return;
			if (focus % 8 == 7 and change == 1) return;
			//Change focus
			focus = (focus + change) % inventory.getBackpack().size();
		}
	}
	else if (sec_focus == EQUIPMENT) {
		if (change == 8) {
			//Change Section
			sec_focus = INVENTORY;
		}
		else {
			//Moving Exceprions
			if (focus == 0 and change == -1) return;
			if (focus == 7 and change == 1) return;
			if (change == -8) return;
			//Change focus
			focus = (focus + change);
		}
	}
}

void InvUI::ProcessKey(sf::Event::KeyEvent key) {
	if (!subWin || (subWin && !subWin->isActive())) {
			//Basic jumping
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
		//IF SUBWIN IS ACTIVE
		subWin->ProcessKey(key);
		//REMEMBER ITEM TO MOVE
		if (subWin->MovFlag()) {
			if (action_source == INVENTORY) {
				to_move = inventory.getItem(focus);
			}
			else if (action_source == EQUIPMENT) {
				to_move = equipment.getEquipmentBySlot((EquipmentSlot)focus);
			}
		}
	}
	//DELETE ITEM
	if (subWin and subWin->DelFlag()) {
		if (action_source == INVENTORY) {
			inventory.deleteItem(action_index);
		}
		else if (action_source == EQUIPMENT) {
			equipment.setEquipment((EquipmentSlot)action_index, nullptr);
		}
		subWin->SetDelFlag(false);
	}
	//USE ITEM
	if (subWin and subWin->UseFlag()) {
		if (action_source == INVENTORY) {
			inventory.useItem(action_index);
		}
		else if (action_source == EQUIPMENT) {
			//nop feature
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

void InvUI::DrawPlayerInfo(sf::RenderTarget& target, sf::Vector2f offset, int font_size){
	//Name
	sf::Text name(player.getName(), font, font_size + 1);
	name.setFillColor(sf::Color::Black);
	name.setPosition(offset);
	target.draw(name);

	//Level
	offset += sf::Vector2f(0, font_size + 1);
	DrawLine(target, offset, ParseText(player_info["lvl"], font_size - 2, "level "), sf::Color::Green);

	//HP
	offset += sf::Vector2f(0, font_size );
	DrawIcon(target, stat_icons, 0, offset, sf::Vector2f(32, 32));
	DrawLine(target, offset + sf::Vector2f(32, 4), ParseText(statistics["HP"], statistics["MaxHP"], font_size - 2, "", "/"), sf::Color::Red);
	DrawBar(target, offset + sf::Vector2f(32, 24), statistics["HP"], statistics["MaxHP"], sf::Vector2f(size.x / 2 - 168, 4), sf::Color::Red);

	//MP
	offset += sf::Vector2f(0, 32);
	DrawIcon(target, stat_icons, 1, offset, sf::Vector2f(32, 32));
	DrawLine(target, offset + sf::Vector2f(32, 4), ParseText(statistics["MP"], statistics["MaxMP"], font_size - 2, "", "/"), sf::Color::Blue);
	DrawBar(target, offset + sf::Vector2f(32, 24), statistics["MP"], statistics["MaxMP"], sf::Vector2f(size.x / 2 - 168, 4), sf::Color::Blue);

	//EXP
	offset += sf::Vector2f(-104, 40);
	DrawBar(target, offset, player_info["current"], player_info["next"], sf::Vector2f(size.x / 2 - 32, 4), sf::Color::Yellow);
	DrawLine(target, offset + sf::Vector2f(0, 3), ParseText(player_info["current"], player_info["next"], font_size - 4, "EXP: ", "/"), sf::Color::White);
}

void InvUI::DrawStatistics(sf::RenderTarget& target, sf::Vector2f position, int font_size) {

//=============================== DATA ===============================//
	//KEYS FOR STATISTIC MAP
	std::vector<std::string> statIndex{ "HP","MaxHP",
										"MP","MaxMP",
										"MinPhysical","MaxPhysical",
										"MinMagical","MaxMagical",
										"MinPoison","MaxPoison",
										"Crit",
										"Precision",
										"Armor",
										"Dodge",
										"MagicalRes",
										"PoisonRes"
	};

	//KEYS TO DISPLAY
	std::vector<std::string> statNames{ "Life","",
										"Mana","",
										"Melee damage","",
										"Magical damage","",
										"Poison damage","",
										"Critical",
										"Precision",
										"Armor",
										"Dodge",
										"Magical Resistance",
										"Poison Resistance"
	};
//=========================== END OF DATA =============================//

	int icon_index = 2;
	//DRAW DOUBLE VALUE STATISTIC, (except 0 - 3) indexes 4 - 9
	for (int i = 4; i < 10; i += 2) {
		DrawIcon(target, stat_icons, i/2, position, sf::Vector2f(32, 32));
		DrawLine(target, position + sf::Vector2f(32, 8), ParseText(statistics[statIndex[i]], statistics[statIndex[i+1]], font_size, statNames[i] + ": ", "-"));
		position += sf::Vector2f(0, 28);
		if(i % 2 == 0) icon_index++;
	}
	//DRAW SINGLE VALUE STATISTIC, indexes 10 - to the end(13)
	for (int i = 10; i < statNames.size(); i++) {
		DrawIcon(target, stat_icons, icon_index, position, sf::Vector2f(32, 32));
		std::string sufix = "";
		if (statIndex[i] == "Crit" or statIndex[i] == "Precision" or statIndex[i] == "MagicalRes" or statIndex[i] == "PoisonRes") sufix = "%";
		DrawLine(target, position + sf::Vector2f(32, 8), ParseText(statistics[statIndex[i]], font_size, statNames[i] + ": ", sufix));
		position += sf::Vector2f(0, 28);
		icon_index++;
	}
}

void InvUI::DrawLine(sf::RenderTarget& target, sf::Vector2f position, sf::Text text, sf::Color color) {
	text.setFont(font);
	text.setColor(color);
	text.setPosition(position);
	target.draw(text);
}

void InvUI::DrawBar(sf::RenderTarget& target, sf::Vector2f position, int val1, int val2, sf::Vector2f size, sf::Color color) {
	//BACK
	Frame object_back;
	object_back.Init(position, size);
	object_back.Draw(target);
	//FILL
	double fill_width = (val1 / (double)val2) * (size.x - 2);
	sf::RectangleShape fill(sf::Vector2f(fill_width, size.y - 1));
	fill.setPosition(position + sf::Vector2f(1, 1));
	fill.setFillColor(color);
	target.draw(fill);
}

sf::Text InvUI::ParseText(int value1, int value2, int fontSize, std::string prefix, std::string separator, std::string sufix) {
	std::string line = prefix + std::to_string(value1) + separator + std::to_string(value2) + sufix;
	return sf::Text(line, font, fontSize);
}

sf::Text InvUI::ParseText(int value, int fontSize, std::string prefix, std::string sufix) {
	std::string line = prefix + std::to_string(value) + sufix;
	return sf::Text(line, font, fontSize);
}

sf::Vector2f InvUI::getTextSize(sf::Text object, std::string text) {
	return sf::Vector2f(object.findCharacterPos(text.size() - 1) - object.findCharacterPos(0));
}