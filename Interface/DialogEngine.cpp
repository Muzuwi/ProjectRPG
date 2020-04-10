#include <cassert>
//#include <sol/sol.hpp>
#include "DialogEngine.hpp"
#include "Entity/Script.hpp"

DialogEngine* DialogEngine::instance = nullptr;

DialogEngine::DialogEngine() {
	assert(font.loadFromFile("GameContent/Fonts/arial.ttf"));
	instance = this;
	selection = 0;
}

void DialogEngine::spawnDialog(const Dialog& dialog) {
	dialogBoxes.push_back(dialog);
}

void DialogEngine::update() {

}

void DialogEngine::draw(sf::RenderTarget &target) {
	if(!this->isDialogPresent()) return;

	Dialog dialog = dialogBoxes.front();

	Window dialogWindow;
	Vec2f size {600.0f, 150.0f};
	Vec2f pos {(800.0f - size.x) / 2.0f, (600 - size.y)};
	dialogWindow.Init(pos, size);
	dialogWindow.Draw(target);

	if(dialog.getDialogType() == Dialog_Choice) {
		Window choiceWindow;
		Vec2f selfSize {100.0, 50.0};
		selfSize.y *= dialog.getChoices().size();

		choiceWindow.Init(pos + size - selfSize, selfSize);
		choiceWindow.Draw(target);

		sf::RectangleShape shape;
		shape.setFillColor(sf::Color(255, 255, 255, 128));

		float perSelection = selfSize.y / (float)dialog.getChoices().size();

		shape.setPosition(pos+size-selfSize + (float)selection * Vec2f{0, perSelection});
		shape.setSize(Vec2f(100.0, 50.0));
		target.draw(shape);

		unsigned i = 0;
		for(auto& choice : dialog.getChoices()) {
			sf::Text text {choice, font, 30};
			text.setFillColor(sf::Color::White);
			text.setPosition(pos+size-selfSize + (float)(i++) * Vec2f{0.0, perSelection} + Vec2f{10.0f, 0.0f});
			target.draw(text);
		}
	}

	sf::Text text{dialog.getText(), font, 30};
	text.setFillColor(sf::Color::White);
	text.setPosition(pos + Vec2f{10.0, 5.0});
	target.draw(text);
}

void DialogEngine::handleKeyEvent(sf::Event::KeyEvent &event) {
	if(!this->isDialogPresent()) return;

	Dialog dialog = dialogBoxes.front();
	if(event.code == sf::Keyboard::Space) {
		dialogBoxes.pop_front();

		if(dialog.getOwner()) dialog.getOwner()->resumePausedCoroutine();
	} else if (event.code == sf::Keyboard::S) {
		if(dialog.getDialogType() != Dialog_Choice) return;

		if(selection == dialog.getChoices().size() - 1) selection = 0;
		else selection++;
	} else if (event.code == sf::Keyboard::W) {
		if(dialog.getDialogType() != Dialog_Choice) return;

		if(selection == 0) selection = dialog.getChoices().size() - 1;
		else selection--;
	}
}
