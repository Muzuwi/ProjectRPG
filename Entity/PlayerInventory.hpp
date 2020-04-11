#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "World/Item.hpp"

class PlayerInventory {
	static const unsigned defaultSize = 64;
	std::vector<std::shared_ptr<Item>> backpack;

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

};