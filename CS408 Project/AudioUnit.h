#pragma once
#include <SFML/Audio.hpp>
#include <map>

class AudioUnit
{
public:
	AudioUnit();
	void playSound(std::string soundName);
private:
	void loadSound(std::string soundName);
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, std::string> soundLocations;
	std::vector<sf::SoundBuffer*> buffers;
	int bufferCount;
	sf::Sound* previousSound;
};