#include "AudioUnit.h"
#include <iostream>

AudioUnit::AudioUnit() {
    soundLocations["high_piano_note"] = "piano6C.ogg";
    soundLocations["medium_piano_note"] = "piano5C.ogg";
    soundLocations["low_piano_note"] = "piano4C.ogg";
    bufferCount = 0;
}

void AudioUnit::loadSound(std::string soundName) {
    sf::Sound temp;

        if (!sounds.count(soundName)) {
            buffers.push_back(new sf::SoundBuffer);
            if (buffers.back()->loadFromFile(soundLocations.at(soundName))) {
                sounds[soundName] = temp;
                sounds[soundName].setBuffer(*buffers[bufferCount]);
                bufferCount++;
            }
            else{
                std::cout << soundName + " sound either failed to load or location is missing";	//If the texture fails to load the program exits
            }
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