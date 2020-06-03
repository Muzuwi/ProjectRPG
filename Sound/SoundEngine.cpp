#include "SoundEngine.hpp"

static double s_master_volume {1.0};
SoundEngine* SoundEngine::instance = nullptr;

bool SoundEngine::playSound(const std::string &name) {
	if(!isBuffered(name)) {
		if(!loadBuffer(name)) {
			std::cerr << "Could not load buffer for sound '" << name << "', not playing\n";
			return false;
		}
	}

	sounds.emplace_back(sf::Sound{buffers[name]});
	sounds.back().setVolume(s_master_volume*100.0);
	sounds.back().play();

	return true;
}

bool SoundEngine::isBuffered(const std::string &name) {
	auto ret = buffers.find(name);
	return ret != buffers.end();
}

bool SoundEngine::loadBuffer(const std::string &name) {
	sf::SoundBuffer buf;
	if(!buf.loadFromFile("GameContent/SFX/"+name+".wav")) {
		return false;
	}
	buffers[name] = buf;
	return true;
}

void SoundEngine::update() {
	auto it = sounds.begin();
	while(it != sounds.end()) {
		if(it->getStatus() == sf::Sound::Stopped) {
			auto del = it;
			++it;
			sounds.erase(del);
			continue;
		}
		++it;
	}
}

void SoundEngine::playMusic(const std::string &name, bool looping) {
	if(currentBGM.getStatus() == sf::SoundSource::Playing)
		currentBGM.stop();

	currentBGM.openFromFile("GameContent/BGM/"+name+".ogg");
	currentBGM.setLoop(looping);
	currentBGM.setVolume(s_master_volume * 100.0);
	currentBGM.play();
}

void SoundEngine::setVolume(double volume) {
	s_master_volume = volume;
	for(auto& sound : instance->sounds) {
		sound.setVolume(s_master_volume * 100.0);
	}
	if(instance->currentBGM.getStatus() == sf::Music::Playing)
		instance->currentBGM.setVolume(s_master_volume * 100.0);
}
