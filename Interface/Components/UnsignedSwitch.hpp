#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class UnsignedSwitch {
protected:
	const sf::Font& font;
	sf::Text content;
	sf::Text header;
	sf::Sprite final;
	sf::Vector2f position, size;

	int limit {-1};
	unsigned int current;
	bool focus;
public:
	UnsignedSwitch();
	void Init(sf::Vector2f, sf::Vector2f);

	void Draw(sf::RenderTarget&);
	void DrawArrows(sf::RenderTarget&);
	void DrawContent(sf::RenderTarget&);

	sf::Vector2f GetPosition() { return position; };
	sf::Vector2f GetSize() { return size; }
	sf::Vector2f getTextSize(sf::Text);
	sf::Vector2f getMiddleCords(sf::Text, int = 0, int = 0);

	void SetFocus() { focus = true; }
	void RemoveFocus() { focus = false; }

	unsigned value() const {
		return current;
	}
	void Next() {
		if(limit == -1 || (current < limit))
			current++;
	}
	void Previous() {
		if (current > 0) current--;
	}

	void setLimit(int limit_) {
		limit = limit_;
		if(limit != -1)
			current = std::clamp(current, 0u, (unsigned)limit_);
	}

	int getLimit() const {
		return limit;
	}
};