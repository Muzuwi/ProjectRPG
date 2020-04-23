#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

enum class Rarity : unsigned {
	Common    = 0,
	Uncommon  = 1,
	Rare      = 2,
	Legendary = 3,
	Epic      = 4
};


enum class ItemType : unsigned {
	Generic = 0,
	QuestItem = 1,
	Consumable = 2,

	ArmorHelmet = 30,
	ArmorChest  = 31,
	ArmorPants  = 32,
	ArmorBoots  = 33,

	EquipRing      = 50,
	EquipNecklace  = 51,

	WeaponSword    = 70,
	WeaponBow      = 71,
};

class Script;

class Item {
	std::string designator;
	std::shared_ptr<Script> itemScript;
	Rarity rarity;
	ItemType type;
	unsigned value;
	unsigned stackCount;
	unsigned maxStack;
public:
	Item(const std::string& itemDesignator);
	Item(const std::string& itemDesignator, unsigned count);

	unsigned getValue() const { return value; }
	unsigned getStack() const { return stackCount; }
	unsigned getMaxStack() const { return maxStack; }
	Rarity getRarity() const { return rarity; }
	ItemType getType() const { return type; }
	const std::string& getDesignator() const { return designator; }

	void onUse();
	void onEquip(bool remove = false);
	unsigned addStack(unsigned count);

	std::string getName() const { return "Name here"; }
	std::string getDescription() const { return "Desc here"; }
	std::string getStats() const { return "Stats here"; }

	void draw(sf::RenderTarget& target, Vec2f pos, sf::Color color = sf::Color::White) const;

	static sf::Color getRarityColor(Rarity);
	static std::string getRarityString(Rarity);
	static std::string getTypeString(ItemType);
};

bool operator==(const Item&, const Item&);
std::ostream& operator<<(std::ostream& os, const Item& item);
std::ostream& operator<<(std::ostream& os, const Rarity& item);
std::ostream& operator<<(std::ostream& os, const ItemType& item);