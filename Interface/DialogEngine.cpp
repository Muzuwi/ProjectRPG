#include <cassert>
//#include <sol/sol.hpp>
#include "DialogEngine.hpp"
#include "Entity/Script.hpp"
#include "OptionWindow.hpp"

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
	sf::Vector2f windowSize = target.getView().getSize();
	int ChoicesNum = dialog.getChoices().size();

	Vec2f instance_position;
	Vec2f instance_size;

	if(dialog.getDialogType() == Dialog_Choice) {
		int i = 0;
		instance_size = sf::Vector2f((windowSize.x / 1.2), (ChoicesNum * 52 + 16));
		instance_position = sf::Vector2f(((windowSize.x - instance_size.x) / 2), (windowSize.y - instance_size.y - 16) );
		dialogWindow.Init(instance_position, sf::Vector2f(instance_size.x / 1.5, instance_size.y));
		for(auto& choice : dialog.getChoices()) {
			OptionWindow choiceWindow;
			Vec2f selfSize{ (float)(instance_size.x - (instance_size.x / 1.5) + 4), 64.0 };

			if (i == selection) choiceWindow.SetFocus();
			else choiceWindow.RemoveFocus();

			choiceWindow.Init(instance_position + sf::Vector2f(instance_size.x / 1.5, 52 * i++), selfSize, "quote_window");
			choiceWindow.SetMessage(choice);
			choiceWindow.Draw(target);
		}
	}
	else {
		instance_size = sf::Vector2f((windowSize.x / 1.2), (windowSize.y / 4 + 16) );
		instance_position = sf::Vector2f(((windowSize.x - instance_size.x) / 2), (windowSize.y - instance_size.y - 16));
		dialogWindow.Init(instance_position, instance_size);
	}

	dialogWindow.Draw(target);

	sf::Text text{dialog.getText(), font, 30};
	text.setPosition(instance_position + Vec2f{10.0, 5.0});
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
