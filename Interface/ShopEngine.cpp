#include "Interface/ShopEngine.hpp"
#include "Interface/Components/Window.hpp"
#include "Interface/Components/UnsignedSwitch.hpp"
#include "Interface/OptionWindow.hpp"
#include "Sound/SoundEngine.hpp"
#include "Entity/Script.hpp"

enum class SelectedButton {
	Buy,
	AmountPicker
};

ShopEngine* ShopEngine::instance {nullptr};
static unsigned selectedItem {0};
static unsigned selectionOffset {0};
static bool shopOpen {false};
static std::vector<UnsignedSwitch> switchStates;

ShopEngine::ShopEngine(Player &_player)
: player(_player), itemlist_cache(AssetManager::getJSON("ItemList")), font(AssetManager::getFont("VCR_OSD_MONO"))
{ instance = this; }

void ShopEngine::initializeShop(Shop shop, Script* ptr) {
	std::cout << "ShopEngine initializing\n";
	for(auto& a : shop.shopItems) {
		std::cout << a.designator << ": " << a.count << " x " << a.price << "\n";
	}

	caller = ptr;
	currentShop = shop;
	shopOpen = true;
	selectedItem = 0;
	selectionOffset = 0;
	switchStates.clear();
	switchStates.resize(shop.shopItems.size());
}

void ShopEngine::draw(sf::RenderTarget& target) {
	if(!shopOpen) return;

	auto draw_item_at = [&](Vec2f pos, const std::string& id) {
		const auto index = itemlist_cache[id]["itemSprite"].get<unsigned>();
		auto sprite = AssetManager::getUI("ItemList").getSprite(index);
		sprite.setPosition(pos);
		target.draw(sprite);
	};

	auto draw_text_at = [&](Vec2f pos, const std::string& text, sf::Color color) -> Vec2f {
		sf::Text txt;
		txt.setCharacterSize(14);
		txt.setFont(font);
		txt.setString(text);
		txt.setFillColor(color);
		txt.setOutlineColor(color);

		auto ret = txt.findCharacterPos(text.size()+1);;
		ret.y = 14;
		txt.setPosition(pos);

		target.draw(txt);
		return ret;
	};

	auto item_name = [&](const std::string& id) -> std::string {
		return itemlist_cache[id]["name"].get<std::string>();
	};

	auto item_description = [&](const std::string& id) -> std::string {
		return itemlist_cache[id]["description"].get<std::string>();
	};

	auto item_rarity = [&](const std::string& id) -> unsigned {
		return itemlist_cache[id]["rarity"].get<unsigned>();
	};

	auto item_gold = [&](const std::string& id) -> unsigned {
		return itemlist_cache[id]["value"].get<unsigned>();
	};

	auto item_type = [&](const std::string& id) -> std::string {
		return Item::getTypeString((ItemType)itemlist_cache[id]["type"].get<unsigned>());
	};


	auto view = target.getView();
	const Vec2f windowSize {500, 400};
	const Vec2f windowPos = (view.getSize() - windowSize) / 2.0f;
	const Vec2f itemSize {32.0f, 32.0f};
	const Vec2f itemWindowPadding {0.0, 10.0f};
	const Vec2f itemWindowSize = Vec2f{windowSize.x - 40.0f, 80.0f};
	const Vec2f textStart {50.0, 10.0};

	Window window;
	window.Init(windowPos, windowSize);
	window.Draw(target);

	OptionWindow sellerWindow;
	const Vec2f sellerNameSize {100.0, 60.0};
	sellerWindow.Init((windowPos + Vec2f{windowSize.x, 0.0f}) - sellerNameSize/2.0f - Vec2f{40.0, 0.0}, sellerNameSize, "quote_window", 20);
	sellerWindow.SetMessage(currentShop.traderName);
	sellerWindow.Draw(target);



	Vec2f itemWindowOffset {20.0, 20.0};
	for(unsigned i = selectionOffset; i < currentShop.shopItems.size(); ++i) {
		const auto& item = currentShop.shopItems[i];

		const Vec2f itemWindowPos {windowPos + itemWindowOffset};
		const Vec2f itemPos {
			itemWindowPos.x + 10.0f,
			itemWindowPos.y + (itemWindowSize.y - itemSize.y) / 2.0f
		};
		const Vec2f itemWindowRB {itemWindowPos+itemWindowSize};

		if(itemWindowRB.y > windowPos.y + windowSize.y)
			break;

		itemWindowOffset.y += itemWindowSize.y + itemWindowPadding.y;

		auto color = Item::getRarityColor((Rarity)item_rarity(item.designator));
		Window itemWindow;
		itemWindow.Init(itemWindowPos, itemWindowSize);
		itemWindow.setTint(color);
		itemWindow.Draw(target);

		draw_item_at(itemPos, item.designator);

		Vec2f text_offset {0.0, 0.0};
		text_offset  = draw_text_at(itemWindowPos + textStart,
					               item_name(item.designator),
					               color);
						draw_text_at(itemWindowPos + textStart + Vec2f{text_offset.x + 10.0f, 0.0},
		                            "x" + std::to_string(item.count),
		                            sf::Color(0xffffffff));

		text_offset += draw_text_at(itemWindowPos + textStart + Vec2f{0.0, text_offset.y},
									item_description(item.designator),
									sf::Color::Black);
		text_offset += draw_text_at(itemWindowPos + textStart + Vec2f{0.0, text_offset.y},
		                            item_type(item.designator),
		                            sf::Color::Black);

		const Vec2f coinPos {itemWindowPos + itemWindowSize - Vec2f{160.0, 25.0}};
		sf::Sprite coinSprite = AssetManager::getUI("coin").getSprite();
		coinSprite.setPosition(coinPos);
		target.draw(coinSprite);
		draw_text_at(coinPos + Vec2f{25.0, 0.0}, std::to_string(item.price), sf::Color::Yellow);

		const Vec2f picker_position {itemWindowPos + itemWindowSize - Vec2f {80.0, 30.0}};
		auto& picker = switchStates[i];
		picker.setLimit(calculate_limit_for_item(item));
		picker.Init(picker_position, {60.0, 25.0});

		if(selectedItem == i) picker.SetFocus();
		else picker.RemoveFocus();

		picker.Draw(target);
	}
}

void ShopEngine::handleKeyEvent(const sf::Event::KeyEvent& event) {
	if(!shopOpen) return;

	switch(event.code) {
		case sf::Keyboard::Escape:
			this->handleShopClose();
			break;
		case sf::Keyboard::W:
			if(selectedItem > 0)
				selectedItem--;
			else
				break;

			if(selectionOffset > 0)
				selectionOffset--;

			break;
		case sf::Keyboard::S:
			if(selectedItem < currentShop.shopItems.size() - 1)
				selectedItem++;
			else
				break;

			if(selectedItem > 3)
				selectionOffset++;

			break;
		case sf::Keyboard::A:
			switchStates[selectedItem].Previous();
			break;
		case sf::Keyboard::D:
			switchStates[selectedItem].setLimit(
					calculate_limit_for_item(currentShop.shopItems[selectedItem])
			);
			switchStates[selectedItem].Next();
			break;
		case sf::Keyboard::Space:
			if(switchStates[selectedItem].value() > 0)
				handleItemBuy();
			break;
		default: break;
	}
}

bool ShopEngine::isShopOpen() {
	return shopOpen;
}

bool ShopEngine::handleItemBuy() {
	const auto& item = currentShop.shopItems[selectedItem];
	const unsigned price_per_unit = item.price;
	const unsigned item_count = switchStates[selectedItem].value() * item.count;
	const unsigned price = item_count * price_per_unit;

	if(player.getPlayerInfo()["gold"] < price)
		return false;

	auto& inventory = player.getInventory();
	auto invItem = std::make_shared<Item>(item.designator, item_count);
	if(inventory.addItem(*invItem) == inventory.getBackpack().size())
		return false;

	if(invItem->getMaxStack() == 1) {
		player.getPlayerInfo()["gold"] -= price_per_unit;
		for(unsigned i = 0; i < item_count - 1; ++i) {
			invItem = std::make_shared<Item>(item.designator, 1);
			if(inventory.addItem(*invItem) == inventory.getBackpack().size())
				return false;

			player.getPlayerInfo()["gold"] -= price_per_unit;
		}
	} else
		player.getPlayerInfo()["gold"] -= price;


	SoundEngine::get().playSound("coins");
	return true;
}

unsigned ShopEngine::calculate_limit_for_item(const ShopItem& item) const {
	unsigned val = player.getPlayerInfo()["gold"] / item.price;
	return val;
}

void ShopEngine::handleShopClose() {
	if(caller) {
		auto response = caller->resumePausedCoroutine();
		if(response != CoroutineStatus::YieldedToCaller)
			shopOpen = false;
	}
}
