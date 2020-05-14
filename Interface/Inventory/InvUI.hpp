#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Interface/Components/Window.hpp"
#include "Interface/Inventory/Cell.hpp"
#include "Interface/Inventory/ItemUI.hpp"
#include "Entity/Player.hpp"

enum section {
	EQUIPMENT = 0,
	INVENTORY = 1
};

class InvUI : public Window{
protected:
	const sf::Font& font;
	sf::Text title_eq, title_inv, title_char;
	int focus, action_index;
	bool sub;
	bool mov;
	section sec_focus;
	section action_source;
	std::shared_ptr<ItemUI> subWin;
	std::shared_ptr<Item> to_move;
	sf::Vector2f focusCellPos;
	sf::Sprite eq_legend;

	PlayerInventory& inventory;
	PlayerEquipment& equipment;

	void DrawSelf(sf::RenderTarget&)override;
	void SelfInit();
public:
	InvUI(Player& inventory);
	void SetButtons();
	void DrawInventory(sf::RenderTarget&);	//draw eq cells
	void DrawEquipment(sf::RenderTarget&);
	void DrawSeparator(sf::RenderTarget&);
	void ProcessKey(sf::Event::KeyEvent);
	void Update(int);
	void DrawIcon(sf::RenderTarget&, sf::Sprite&, int, sf::Vector2f, sf::Vector2f);
	void DrawEqCell(sf::RenderTarget&, std::shared_ptr<Item>, int, sf::Vector2f, sf::Vector2f);
};

