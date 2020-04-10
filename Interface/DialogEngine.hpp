#pragma once
#include <string>
#include <deque>
#include <SFML/Graphics.hpp>
#include "Interface/Window.hpp"
#include "Dialog.hpp"
#include <sol/forward.hpp>

class DialogEngine {
	static DialogEngine* instance;

	std::deque<Dialog> dialogBoxes;
	unsigned selection;
	sf::Font font;
public:
	DialogEngine();

	void spawnDialog(const Dialog& dialog);
	bool isDialogPresent() const { return !dialogBoxes.empty(); }

	void handleKeyEvent(sf::Event::KeyEvent& event);
	void update();
	void draw(sf::RenderTarget&);

	friend class Script;
};