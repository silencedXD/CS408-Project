#include <iostream>
#include "AudioUnit.h"

void AudioUnit::loadSound(std::string soundName) {
    sf::Sound temp;
    try {
        if (!sounds.count(soundName)) {
            sf::SoundBuffer buffer;
            buffer.loadFromFile(soundLocations.at(soundName));
            sounds[soundName] = temp;
        }
    }
    catch (...) {
        std::cout << soundName + " sound either failed to load or location is missing";	//If the texture fails to load the program exits
    }
}

void AudioUnit::playSound(std::string soundName) {
    if (sounds.count(soundName))
    {
        sounds[soundName].play();
    }
    else {
        loadSound(soundName);
        sounds[soundName].play();
    }
}