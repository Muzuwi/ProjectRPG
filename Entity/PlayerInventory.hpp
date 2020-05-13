#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "World/Item.hpp"
#include "Entity/PlayerEquipment.hpp"

class PlayerInventory {
	static const unsigned defaultSize = 64;
	std::vector<std::shared_ptr<Item>> backpack;
	PlayerEquipment equipment;

	unsigned findFirstFree() const {
		for(unsigned i = 0; i < backpack.size(); i++) {
			if(!backpack[i]) return i;
		}
		return backpack.size();
	}
public:
	PlayerInventory() {
		backpack.resize(defaultSize);
	}

	const std::vector<std::shared_ptr<Item>>& getBackpack() const {
		return backpack;
	}

	std::vector<std::shared_ptr<Item>>& getBackpack() {
		return backpack;
	}

	const PlayerEquipment& getEquipment() const {
		return equipment;
	}

	PlayerEquipment& getEquipment() {
		return equipment;
	}

	std::shared_ptr<Item> getItem(unsigned index) {
		assert(index < backpack.size());
		return backpack[index];
	}

	unsigned addItem(const Item& item) {
		for(auto& backItem : backpack) {
			if(!backItem) continue;
			if(*backItem == item) {
				if(backItem->getStack() == backItem->getMaxStack()) continue;
				unsigned overflow = backItem->addStack(item.getStack());
				if(overflow == 0) return 0;
				if(overflow > 0) return addItem(item);
			}
		}

		for(auto& backItem : backpack) {
			if(!backItem) {
				backItem = std::make_shared<Item>(item);
				return 0;
			}
		}

		std::cerr << "Failed to insert into inventory, inventory full\n";
		return backpack.size();
	}

	void swapItems(unsigned index1, unsigned index2) {
		assert(index1 < backpack.size() && index2 < backpack.size());
		std::swap(backpack[index1], backpack[index2]);
	}

	bool findItem(const Item& item) {
		return std::find_if(backpack.begin(),backpack.end(),[&](std::shared_ptr<Item>& a){
			return *a == item;
		}) != backpack.end();
	}

	bool deleteItem(unsigned toDelete) {
		if (!backpack[toDelete]) return false;
		else {
			backpack[toDelete] = nullptr;
			return true;
		}
	}

	bool useItem(unsigned toUse) {
		if (!backpack[toUse]) return false;
		else {
			std::cout << "Uzyto przedmiotu: " << backpack[toUse]->getName() << "." << std::endl;
			this->tryEquipFromBackpack(toUse);
			return true;
		}
	}

	bool tryEquipFromBackpack(unsigned slot) {
        if(slot > backpack.size()) return false;
        auto& item = backpack[slot];
        if(!item) return false;

        auto type = item->getType();
        EquipmentSlot eqSlot;
        switch(type) {
        	case ItemType::WeaponSword: eqSlot = EquipmentSlot::RightHand; break;
	        case ItemType::WeaponBow: eqSlot = EquipmentSlot::RightHand; break;
        	case ItemType::ArmorHelmet: eqSlot = EquipmentSlot::Helmet; break;
	        case ItemType::ArmorBoots: eqSlot = EquipmentSlot::Boots; break;
	        case ItemType::ArmorChest: eqSlot = EquipmentSlot::Chest; break;
	        case ItemType::ArmorPants: eqSlot = EquipmentSlot::Pants; break;
	        case ItemType::EquipRing: eqSlot = EquipmentSlot::Ring; break;
	        case ItemType::EquipNecklace: eqSlot = EquipmentSlot::Amulet; break;
	        case ItemType::EquipGloves: eqSlot = EquipmentSlot::Gloves; break;
	        case ItemType::EquipBraces: eqSlot = EquipmentSlot::Braces; break;
	        default: return false;
        }

		auto eqItem = equipment.getEquipmentBySlot(eqSlot);
		if(!eqItem) {
			assert(equipment.setEquipment(eqSlot, item));
			item = nullptr;
			return true;
		} else {
			assert(equipment.setEquipment(eqSlot, item));
			item = eqItem;
			return true;
		}
	}

};
