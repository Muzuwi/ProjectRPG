#include <algorithm>
#include "EditWindow.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

void EditWindow::start() {
	AssetManager::loadMaps();
	width = 1280;
	height = 720;
	sf::VideoMode mode;
	editorWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "RPGEditor");
	editorWindow->setFramerateLimit(60);
	ImGui::SFML::Init(*editorWindow);
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("GameContent/Fonts/arial-unicode-ms.ttf", 20.0f);
	ImGui::SFML::UpdateFontTexture();

	sf::Clock deltaClock;
	while(editorWindow->isOpen()) {
		eventPoll();
		ImGui::SFML::Update(*editorWindow, deltaClock.restart());
		editorWindow->clear();

		ImGui::PushFont(font);
		frameLoop();
		ImGui::PopFont();

		if(MouseMovement.leftClick) leftClickHandler();

		ImGui::SFML::Render(*editorWindow);
		editorWindow->display();

	}

	ImGui::SFML::Shutdown();
}

void EditWindow::frameLoop() {
	this->drawMenuBar();
	this->drawCommonWindows();

	if(EditingMap.isTileChosen || EditingMap.isLoaded) {
		picker.drawWindow();

		if(picker.getSelection().getX() == 1 && picker.getSelection().getY() == 1)
			tilesEditor.updateEditing(picker.getSelection()[0][0]);

		if(EditingMap.isLoaded)
			tilesEditor.drawWindow();
	}

	if(!EditingMap.isLoaded) return;

	Vec2i pos = mapPosition;
	if(MouseMovement.isMoving)
		pos = mapPosition + sf::Mouse::getPosition(*editorWindow) - MouseMovement.mouseStart;

	sf::View view(Vec2f(pos) + (Vec2f(width, height) / 2.0f), Vec2f(width, height));
	editorWindow->setView(view);

	mapTexture.clear(sf::Color::Transparent);
	sf::Sprite spr;
	spr.setTexture(mapTexture.getTexture());
	spr.setColor(sf::Color(255, 255, 255, 96));

	//  Przyciemniamy warstwy które nie są aktywne w edytorze
	if (EditingMap.editingLayer == 0) {
		EditingMap.mapData->drawTiles(*editorWindow, 0);
		EditingMap.mapData->drawTiles(mapTexture, 1);
		EditingMap.mapData->drawTiles(mapTexture, 2);
		mapTexture.display();
		editorWindow->draw(spr);
	} else if(EditingMap.editingLayer == 1) {
		EditingMap.mapData->drawTiles(mapTexture, 0);
		mapTexture.display();
		editorWindow->draw(spr);

		EditingMap.mapData->drawTiles(*editorWindow, 1);

		mapTexture.clear(sf::Color::Transparent);
		EditingMap.mapData->drawTiles(mapTexture, 2);
		mapTexture.display();
		editorWindow->draw(spr);
	} else {
		EditingMap.mapData->drawTiles(mapTexture, 0);
		EditingMap.mapData->drawTiles(mapTexture, 1);
		mapTexture.display();
		editorWindow->draw(spr);
		EditingMap.mapData->drawTiles(*editorWindow, 2);
	}
	EditingMap.mapData->drawEntities(*editorWindow);


	MouseMovement.hoverCoordinates = (pos + sf::Mouse::getPosition(*editorWindow)) / (int)Tile::dimensions();
	MouseMovement.hoverCoordinates.x = std::clamp(MouseMovement.hoverCoordinates.x, 0, EditingMap.width-1);
	MouseMovement.hoverCoordinates.y = std::clamp(MouseMovement.hoverCoordinates.y, 0, EditingMap.height-1);

	if(currentTool) currentTool->drawToolWindow(Vec2u(MouseMovement.hoverCoordinates),*editorWindow);
}

void EditWindow::eventPoll() {
	sf::Event event {};
	while (editorWindow->pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

		if(event.type == sf::Event::Resized) {
			this->width = event.size.width;
			this->height = event.size.height;
		}

		if (event.type == sf::Event::Closed) {
			editorWindow->close();
		}

		if(event.type == sf::Event::MouseButtonPressed) {
			if(ImGui::GetIO().WantCaptureMouse) continue;

			if(event.mouseButton.button == sf::Mouse::Button::Left)
				MouseMovement.leftClick = true;
			if(event.mouseButton.button == sf::Mouse::Button::Middle) {
				MouseMovement.mouseStart = sf::Mouse::getPosition(*editorWindow);
				MouseMovement.isMoving = true;
			}
		}

		if(event.type == sf::Event::MouseButtonReleased) {
			if(ImGui::GetIO().WantCaptureMouse) continue;

			if(event.mouseButton.button == sf::Mouse::Button::Left)
				MouseMovement.leftClick = false;
			if(event.mouseButton.button == sf::Mouse::Button::Middle) {
				mapPosition += sf::Mouse::getPosition(*editorWindow) - MouseMovement.mouseStart;
				MouseMovement.isMoving = false;
			}
		}
	}
}

void EditWindow::leftClickHandler() {
	if(EditingMap.isLoaded) {
		if(currentTool) currentTool->onToolUse(Vec2u(MouseMovement.hoverCoordinates), picker.getSelection(), EditingMap.editingLayer);
	}
}

bool EditWindow::drawCommonWindows() {
	if(EditingMap.isLoaded && ErrorWindow.open)
		this->drawErrorBox();

	if(!EditingMap.isLoaded)
		this->drawMapOpenDialog();

	return false;
}

void EditWindow::drawMenuBar() {
	if(ImGui::BeginMainMenuBar()) {
		bool thisFrame = false;
		if(ImGui::BeginMenu("File")) {
			if(ImGui::MenuItem("New Map...")) {
				EditingMap.isLoaded = false;
			}
			if(ImGui::MenuItem("Save to file")) {
				try {
					EditingMap.mapData->serializeToFile(EditingMap.fname);
				} catch (std::exception& ex) {
					ErrorWindow.open = true;
					ErrorWindow.text = "Saving map failed!\nDetails: " + std::string(ex.what()) + "\n";
				}
			}
			ImGui::EndMenu();
		}

#define TOOL_BUTTON(ptrName, buttonText) \
		if(currentTool && currentTool == ptrName) ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.56, 0.57f, 1.0f)); \
		if(ImGui::Button(buttonText) && currentTool != ptrName) { \
			thisFrame = true; \
			currentTool = ptrName; \
		} \
		if(currentTool && currentTool == ptrName && !thisFrame) ImGui::PopStyleColor(1);

		TOOL_BUTTON(Tools.cursor,"Cursor")
		TOOL_BUTTON(Tools.brush, "Brush")
		TOOL_BUTTON(Tools.creator, "NPC Tool")
		TOOL_BUTTON(Tools.connect, "Connections")

		if(ImGui::Button("Layer 0")) {
			EditingMap.editingLayer = 0;
		}
		if(ImGui::Button("Layer 1")) {
			EditingMap.editingLayer = 1;
		}
		if(ImGui::Button("Layer 2")) {
			EditingMap.editingLayer = 2;
		}

		ImGui::TextColored(ImVec4(255, 255, 0,255),"Coords: %ix%i", MouseMovement.hoverCoordinates.x, MouseMovement.hoverCoordinates.y);

		ImGui::EndMainMenuBar();
	}
}

void EditWindow::drawErrorBox() {
	ImGui::OpenPopup("Error");
	if(ImGui::BeginPopupModal("Error")) {
		ImGui::Text("%s", ErrorWindow.text.c_str());
		if(ImGui::Button("OK")) ErrorWindow.open = false;
		ImGui::EndPopup();
	}
}

void EditWindow::doMapLoadTasks() {
	EditingMap.mapData->bindPlayer(EditingMap.fakePlayer);
	EditingMap.width = EditingMap.mapData->size.x;
	EditingMap.height = EditingMap.mapData->size.y;
	EditingMap.isLoaded = true;
	picker.init(EditingMap.mapData->tilesetName);
	tilesEditor.init(EditingMap.mapData->tilesetName, EditingMap.mapData->tileset);

	Tools.brush = std::make_shared<Brush>(*EditingMap.mapData);
	Tools.cursor = std::make_shared<CursorTool>(*EditingMap.mapData);
	Tools.creator = std::make_shared<NPCCreator>(*EditingMap.mapData);
	Tools.connect = std::make_shared<ConnectionTool>(*EditingMap.mapData);

	assert(mapTexture.create(EditingMap.width * Tile::dimensions(), EditingMap.height*Tile::dimensions()));
}

void EditWindow::drawMapOpenDialog() {
	static char buf[128];
	static char existingBuf[32];
	static std::string selectedSpritesheet { };
	static std::string selectedMap {};
	static int width = 100, height = 100, type = 0;

	ImGui::OpenPopup("Enter map details");
	if (ImGui::BeginPopupModal("Enter map details", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputText("Filename", buf, 128);
		ImGui::InputInt("Width", &width);
		ImGui::InputInt("Height", &height);
		ImGui::InputInt("Default Tile", &type);
		if(ImGui::BeginCombo("Spritesheet", selectedSpritesheet.c_str())) {
			for(const auto& key : AssetManager::getAllTilesets() ) {
				std::string name = key.first + " (" + std::to_string(key.second.getSpriteSize().x)
				                   + "x" + std::to_string(key.second.getSpriteSize().y) + ")";
				if(ImGui::Selectable(name.c_str())) {
					selectedSpritesheet = key.first;
					if(!selectedSpritesheet.empty()) {
						picker.init(selectedSpritesheet);
						EditingMap.isTileChosen = true;
					}
				}

				if(key.first == selectedSpritesheet)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}


		ImGui::Dummy(ImVec2(ImGui::GetWindowWidth()-30, 0));
		if(ImGui::Button("Create") && width > 0 && height > 0) {
			EditingMap.fname = std::string(buf);
			EditingMap.mapData = std::make_shared<Map>(std::move(Map::make_empty(Vec2u(width, height), type, selectedSpritesheet)));
			EditingMap.mapData->initializeVertexArrays();
			this->doMapLoadTasks();
			ImGui::CloseCurrentPopup();
		}

		ImGui::Separator();
		if(ImGui::BeginCombo("Existing Maps", selectedMap.c_str())) {
			for(const auto& key : AssetManager::getAllMaps()) {
				auto name = key.first;

				if(ImGui::Selectable(name.c_str())) {
					selectedMap = name;
				}

				if(name == selectedMap)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if(ImGui::Button("Open") && !selectedMap.empty()) {
			try {
				EditingMap.fname = selectedMap;
				EditingMap.mapData = AssetManager::getMap(selectedMap);
				this->doMapLoadTasks();
			} catch (std::exception& ex) {
				EditingMap.isLoaded = false;
				ErrorWindow.open = true;
				ErrorWindow.text = "Map load failed!\nDetails: " + std::string(ex.what());
			}
		}

		if(ErrorWindow.open) this->drawErrorBox();

		ImGui::EndPopup();
	}
}
