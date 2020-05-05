#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Interface/Components/Window.hpp"
#include "Interface/Inventory/Cell.hpp"
#include "Interface/Inventory/ItemUI.hpp"
#include "Entity/Player.hpp"

class InvUI : public Window{
protected:
	sf::Text title;
	int focus, action_index;
	bool sub;
	bool mov;
	std::shared_ptr<ItemUI> subWin;
	std::shared_ptr<Item> to_move;

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
};

