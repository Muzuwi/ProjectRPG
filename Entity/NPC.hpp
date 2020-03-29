#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "Graphics/RenderableObject.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Entity/Actor.hpp"

class NPC : public Actor, public RenderableObject {
	std::string scriptName;
	std::reference_wrapper<const Spritesheet> spritesheet;
public:
	NPC(const std::string& texture, Vec2u worldPos, const std::string& scriptName);

	void draw(sf::RenderTarget &target) const override;
	Vec2u getDimensions() const override;
	void frameTick() override;

	void onMove(Direction dir) override;
	void onUpdate() override;
	void onInteract(Direction dir) override;
	void onStep() override;

	friend class Script;
};