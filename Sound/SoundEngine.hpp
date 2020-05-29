#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <list>
#include "Types.hpp"

class SoundEngine {
	static SoundEngine* instance;

	std::unordered_map<std::string, sf::SoundBuffer> buffers;
	std::list<sf::Sound> sounds;

	sf::Music currentBGM;

	bool loadBuffer(const std::string& name);
	bool isBuffered(const std::string& name);
public:
	static void setVolume(double volume);

	SoundEngine() { instance = this; }
	bool playSound(const std::string& name);
	void update();
	void playMusic(const std::string& name, bool looping);

	friend class Script;
};