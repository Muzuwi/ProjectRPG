#include "AssetManager.hpp"
#include "Item.hpp"
#include "Entity/Script.hpp"

Item::Item(const std::string &itemDesignator)
: designator(itemDesignator)
{
	auto config = AssetManager::getJSON("ItemList")[itemDesignator];

	unsigned rare = 0;
	config["rarity"].get_to<unsigned>(rare);

	unsigned itType = 0;
	config["type"].get_to<unsigned>(itType);

	unsigned val = 0;
	config["value"].get_to<unsigned>(val);

	unsigned maxSt = 1;
	config["maxStack"].get_to<unsigned>(maxSt);

	std::string scriptName { };
	config["script"].get_to<std::string>(scriptName);

	if(!scriptName.empty()) {
		try {
			itemScript = std::make_shared<Script>(scriptName);
		} catch (std::exception& ex) {
			itemScript = nullptr;
		}
	}

	this->rarity = (Rarity)rare;
	this->type = (ItemType)itType;
	this->value = val;
	this->maxStack = maxSt;
	this->stackCount = 1;
	config["itemSprite"].get_to<unsigned>(this->itemSpriteIndex);
}

Item::Item(const std::string &itemDesignator, unsigned count)
: Item(itemDesignator)
{
	this->stackCount = std::min(this->maxStack, count);
}

void Item::onUse() {
	if(itemScript)
		itemScript->executeFunction("onUse");
}

void Item::onEquip(bool remove) {
	if(itemScript)
		itemScript->executeFunction("onEquip");
}

sf::Color Item::getRarityColor(Rarity rarity) {
	switch(rarity) {
		case Rarity::Common:
			return sf::Color::White;
		case Rarity::Uncommon:
			return sf::Color::Blue;
		case Rarity::Rare:
			return sf::Color::Green;
		case Rarity::Legendary:
			return sf::Color::Yellow;
		case Rarity::Epic:
			return sf::Color::Red;
	}

	return sf::Color::White;
}

std::string Item::getRarityString(Rarity rarity) {
	switch(rarity) {
		case Rarity::Common:
			return "Common";
			break;
		case Rarity::Uncommon:
			return "Uncommon";
			break;
		case Rarity::Rare:
			return "Rare";
			break;
		case Rarity::Legendary:
			return "Legendary";
			break;
		case Rarity::Epic:
			return "Epic";
			break;
	}

	return "undefined";
}

std::string Item::getTypeString(ItemType type) {
	switch(type) {
		case ItemType::Generic:
			return "Generic";
		case ItemType::QuestItem:
			return "Quest Item";
		case ItemType::Consumable:
			return "Consumable";
		case ItemType::ArmorHelmet:
			return "Helmet";
		case ItemType::ArmorChest:
			return "Chest";
		case ItemType::ArmorPants:
			return "Pants";
		case ItemType::ArmorBoots:
			return "Boots";
		case ItemType::EquipRing:
			return "Ring";
		case ItemType::EquipNecklace:
			return "Necklace";
		case ItemType::WeaponSword:
			return "Sword";
		case ItemType::WeaponBow:
			return "Bow";
		case ItemType::WeaponStaff:
			return "Staff";
		case ItemType::Shield:
			return "Shield";
		case ItemType::EquipGloves:
			return "Gloves";
	}

	return "undefined";
}

void Item::draw(sf::RenderTarget &target, Vec2f pos, sf::Color color) const {
	auto sprite = AssetManager::getUI("ItemList").getSprite(itemSpriteIndex);
	sprite.setPosition(pos);
	sprite.setColor(color);
	target.draw(sprite);
}

unsigned Item::addStack(unsigned count) {
	int overflow = (int)(stackCount + count) - maxStack;
	if(overflow > 0) {
		stackCount = maxStack;
		return overflow;
	} else {
		stackCount = (stackCount + count);
		return 0;
	}
}

std::string Item::getName() const {
	const auto& list = AssetManager::getJSON("ItemList");
	if(!list.contains(designator) || (!list[designator].contains("name")))
		return "undefined";

	return list[designator]["name"];
}

std::string Item::getDescription() const {
	const auto& list = AssetManager::getJSON("ItemList");
	if(!list.contains(designator) || (!list[designator].contains("description")))
		return "undefined";

	return list[designator]["description"];
}

int Item::getStat(std::string statistic) const {
	const auto& list = AssetManager::getJSON("ItemList");
	if (!list.contains(designator) || !list[designator].contains("stats") || !list[designator]["stats"].contains(statistic) )
		return 0;

	return list[designator]["stats"][statistic];
}

std::string Item::getStats() const {
	const auto& list = AssetManager::getJSON("ItemList");
	if(!list.contains(designator) || (!list[designator].contains("stats")))
		return "undefined";

	std::string text;
	const auto& stats = list[designator]["stats"];

	for(auto it = stats.begin(); it != stats.end(); ++it) {
		const auto val = it->get<int>();
		if(val > 0) text += '+';
		text += std::to_string(val) + " ";
		text += it.key();
		if(it != --stats.end()) text += '\n';
	}

	return text;
}

bool operator==(const Item& a, const Item& b) {
	return a.getDesignator() == b.getDesignator() &&
		   a.getRarity() == b.getRarity() &&
	       a.getType() == b.getType() &&
	       a.getValue() == b.getValue() &&
	       a.getMaxStack() == b.getMaxStack();
}

std::ostream &operator<<(std::ostream &os, const Item &item) {
	os << "Name: " << item.getDesignator() << ", rarity: "  << item.getRarity() << ", value: " << item.getValue() << "\n";
	os << "Type: " << item.getType() << ", stack: " << item.getStack() << ", maxStack: " << item.getMaxStack() << "\n";
	return os;
}

std::ostream &operator<<(std::ostream &os, const Rarity &rarity) {
	os << Item::getRarityString(rarity);
	return os;
}

std::ostream &operator<<(std::ostream &os, const ItemType &type) {
	os << Item::getTypeString(type);
	return os;
}
