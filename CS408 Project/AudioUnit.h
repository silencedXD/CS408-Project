#pragma once
#include <SFML/Audio.hpp>
#include <map>

class AudioUnit
{
public:
	AudioUnit();
	void loadSound(std::string soundName);
	void playSound(std::string soundName);
private:
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, std::string> soundLocations;
	std::vector<sf::SoundBuffer*> buffers;
	int bufferCount;
};