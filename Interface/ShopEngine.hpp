#pragma once
#include "Entity/Player.hpp"

struct ShopItem {
	std::string designator;
	unsigned count;
	unsigned price;
};

struct SellItem {
	std::string designator;
	double priceMultiplier;
};

struct Shop {
	std::vector<ShopItem> shopItems;
	std::vector<SellItem> sellBonuses;
	std::string traderName;
};

class ShopEngine {
	friend class Script;

	static ShopEngine* instance;

	Script* caller {nullptr};
	const nlohmann::json& itemlist_cache;
	Player& player;
	Shop currentShop;
	const sf::Font& font;

	unsigned calculate_limit_for_item(const ShopItem&) const;
	bool handleItemBuy();
	void handleShopClose();
public:
	ShopEngine(Player& _player);
	void initializeShop(Shop, Script*);
	void draw(sf::RenderTarget&);
	void handleKeyEvent(const sf::Event::KeyEvent&);
	bool isShopOpen();
};