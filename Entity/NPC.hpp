#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "Graphics/RenderableObject.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Entity/Actor.hpp"
#include "Entity/Script.hpp"

class NPC : public Actor, public RenderableObject {
	std::string scriptName;
	std::shared_ptr<Script> actorScript;
	std::reference_wrapper<const Spritesheet> spritesheet;

public:
	NPC(const std::string& texture, Vec2u worldPos, const std::string& scriptName);
	NPC(const NPC& npc);
	void draw(sf::RenderTarget &target) const override;

	Vec2u getDimensions() const override;
	void onMove(Direction dir) override;

	void onUpdate() override;
	void onInteract(Direction dir) override;
	void onStep() override;

	friend class Script;
	friend class NPCCreator;
};