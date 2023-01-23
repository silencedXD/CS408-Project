#include "AudioUnit.h"
#include <iostream>

AudioUnit::AudioUnit() {
    //soundLocations["high_piano_note"] = "Sound_Effects/piano6C.ogg";
    //soundLocations["medium_piano_note"] = "Sound_Effects/piano5C.ogg";
    //soundLocations["low_piano_note"] = "Sound_Effects/piano4C.ogg";
    soundLocations["main_menu"] = "Text_To_Speech/main_menu.ogg";
    soundLocations["options"] = "Text_To_Speech/options.ogg";
    soundLocations["select_level"] = "Text_To_Speech/select_level.ogg";
    soundLocations["level_editor"] = "Text_To_Speech/level_editor.ogg";
    soundLocations["quit"] = "Text_To_Speech/quit.ogg";
    soundLocations["level_one"] = "Text_To_Speech/level_one.ogg";
    soundLocations["level_two"] = "Text_To_Speech/level_two.ogg";
    soundLocations["level_three"] = "Text_To_Speech/level_three.ogg";
    soundLocations["go_back"] = "Text_To_Speech/go_back.ogg";
    soundLocations["menu_controls"] = "Text_To_Speech/menu_controls.ogg";
    soundLocations["video"] = "Text_To_Speech/video.ogg";
    soundLocations["audio"] = "Text_To_Speech/audio.ogg";
    soundLocations["controls"] = "Text_To_Speech/controls.ogg";
    soundLocations["display_size"] = "Text_To_Speech/display_size.ogg";
    soundLocations["font_type"] = "Text_To_Speech/font_type.ogg";
    soundLocations["font_size"] = "Text_To_Speech/font_size.ogg";

    bufferCount = 0;
    loadSound("main_menu");
    previousSound = &sounds["main_menu"];
    playSound("menu_controls");
    //sf::sleep(sf::seconds(4.2));
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
        previousSound->stop();
        sounds[soundName].play();
        previousSound = &sounds[soundName];
    }
    else {
        loadSound(soundName);
        previousSound->stop();
        sounds[soundName].play();
        previousSound = &sounds[soundName];
    }
}