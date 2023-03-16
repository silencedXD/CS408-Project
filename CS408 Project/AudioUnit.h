#pragma once
#include <SFML/Audio.hpp>
#include <map>

class AudioUnit
{
public:
	AudioUnit(float general, float text, float game);
	void playSound(std::string soundName);
	void playNonRepeatingSound(std::string soundName);
	void playConcurrentSound(std::string soundName);

	void playQueue();
	void enqueueSound(std::string soundName, int delay);
	void enqueueSound(std::string soundName);
	void emptyQueue();
	
	float getGeneralVolume();
	float getTextVolume();
	float getGameVolume();
	void setVolume(float general, float text, float game);
	sf::SoundBuffer* getBuffer(std::string soundName);

private:
	void startQueue();
	void loadSound(std::string soundName);
	void resetVolume();

	sf::Mutex soundLock;
	sf::Thread soundQueueThread;
	std::vector<std::string> soundQueue;
	std::vector<int> delayQueue;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, std::string> soundLocations;
	std::map<std::string, sf::SoundBuffer*> buffers;
	int bufferCount;
	sf::Sound* previousSound;
	float generalVolume;
	float textVolume;
	float gameVolume;
};