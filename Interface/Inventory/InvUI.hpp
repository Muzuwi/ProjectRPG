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

	//Static Titles
	sf::Text title_eq, title_inv, title_char;

	//Indexes
	int focus;			//current focus
	int action_index;	//focus of action (FE moving)
	
	//Flags
	bool sub;	//Subwindow is active? (ItemUI)
	bool mov;	//Moving an item?

	//Section flags
	section sec_focus;		//Where focus is? (Inv / Eq)
	section action_source;	//From where action is comming? (Inv / Eq)

	//Holding Item
	std::shared_ptr<ItemUI> subWin;	//to display info
	std::shared_ptr<Item> to_move;	//to move

	sf::Vector2f focusCellPos;	//Position of focused cell

	//Icons
	sf::Sprite eq_legend;
	sf::Sprite stat_icons;
	sf::Sprite hero_face;

	//PLAYER
	Player& player;								//Player
	std::map<std::string, int>& statistics;		//Player's statistics
	std::map<std::string, int>& player_info;	//Player's data info
	PlayerInventory& inventory;					//Player's inventory
	PlayerEquipment& equipment;					//Player's equipment

	//Self Operation
	void DrawSelf(sf::RenderTarget&)override;
	void SelfInit();
public:
	InvUI(Player&);
	//Drawing Functions
	void DrawInventory(sf::RenderTarget&);	//draw eq cells
	void DrawEquipment(sf::RenderTarget&);
	void DrawSeparator(sf::RenderTarget&);
	void DrawIcon(sf::RenderTarget&, sf::Sprite&, int, sf::Vector2f, sf::Vector2f);
	void DrawEqCell(sf::RenderTarget&, std::shared_ptr<Item>, int, sf::Vector2f, sf::Vector2f);
	void DrawActorFace(sf::RenderTarget&, sf::Vector2f, sf::Vector2f);
	void DrawPlayerInfo(sf::RenderTarget&, sf::Vector2f, int);
	void DrawStatistics(sf::RenderTarget&, sf::Vector2f, int);
	void DrawLine(sf::RenderTarget&, sf::Vector2f, sf::Text, sf::Color = sf::Color::Black);
	void DrawBar(sf::RenderTarget&, sf::Vector2f, int, int, sf::Vector2f, sf::Color = sf::Color::White);
	//Procesing Functions
	void ProcessKey(sf::Event::KeyEvent);
	void Update(int);
	//Parsing Functions
	sf::Text ParseText(int value1, int value2, int = 16, std::string = "", std::string = "", std::string = "");
	sf::Text ParseText(int value, int = 16, std::string = "", std::string = "");
	//Other
	sf::Vector2f getTextSize(sf::Text, std::string);
};

