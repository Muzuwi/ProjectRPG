#pragma once
#include "World/Item.hpp"

enum class EquipmentSlot {
	LeftHand = 0,
	RightHand,
	Helmet,
	Chest,
	Pants,
	Boots,
	Ring,
	Amulet,
	Gloves,
	Braces
};

class PlayerEquipment {
	std::shared_ptr<Item> leftHanded;
	std::shared_ptr<Item> rightHanded;
	std::shared_ptr<Item> helmet;
	std::shared_ptr<Item> chest;
	std::shared_ptr<Item> pants;
	std::shared_ptr<Item> boots;
	std::array<std::shared_ptr<Item>, 4> accessories;
public:
	bool setEquipment(EquipmentSlot slot, const std::shared_ptr<Item>& item) {
		if(!item) return false;
		
		switch(slot) {
			case EquipmentSlot::LeftHand:
				if(!(item->getType() == ItemType::WeaponBow || item->getType() == ItemType::WeaponSword))
					return false;
				leftHanded = item;
				break;
			case EquipmentSlot::RightHand:
				if(!(item->getType() == ItemType::WeaponBow || item->getType() == ItemType::WeaponSword))
					return false;
				rightHanded = item;
				break;
			case EquipmentSlot::Helmet:
				if(item->getType() != ItemType::ArmorHelmet)
					return false;
				helmet = item;
				break;
			case EquipmentSlot::Chest:
				if(item->getType() != ItemType::ArmorChest)
					return false;
				chest = item;
				break;
			case EquipmentSlot::Pants:
				if(item->getType() != ItemType::ArmorPants)
					return false;
				pants = item;
				break;
			case EquipmentSlot::Boots:
				if(item->getType() != ItemType::ArmorBoots)
					return false;
				boots = item;
				break;
			case EquipmentSlot::Ring:
				if(item->getType() != ItemType::EquipRing)
					return false;
				accessories[0] = item;
				break;
			case EquipmentSlot::Amulet:
				if(item->getType() != ItemType::EquipNecklace)
					return false;
				accessories[1] = item;
				break;
			case EquipmentSlot::Gloves:
				if(item->getType() != ItemType::EquipGloves)
					return false;
				accessories[2] = item;
				break;
			case EquipmentSlot::Braces:
				if(item->getType() != ItemType::EquipBraces)
					return false;
				accessories[3] = item;
				break;
			default: return false;
		}

		return true;
	}

	std::shared_ptr<Item> getEquipmentBySlot(EquipmentSlot slot) {
		switch(slot) {
			case EquipmentSlot::LeftHand:
				return leftHanded;
			case EquipmentSlot::RightHand:
				return rightHanded;
			case EquipmentSlot::Helmet:
				return helmet;
			case EquipmentSlot::Chest:
				return chest;
			case EquipmentSlot::Pants:
				return pants;
			case EquipmentSlot::Boots:
				return boots;
			case EquipmentSlot::Ring:
				return accessories[0];
			case EquipmentSlot::Amulet:
				return accessories[1];
			case EquipmentSlot::Gloves:
				return accessories[2];
			case EquipmentSlot::Braces:
				return accessories[3];
		}

		return nullptr;
	}
};