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
    soundLocations["1920_1080"] = "Text_To_Speech/1920_1080.ogg";
    soundLocations["1680_1050"] = "Text_To_Speech/1680_1050.ogg";
    soundLocations["1600_900"] = "Text_To_Speech/1600_900.ogg";
    soundLocations["1280_1024"] = "Text_To_Speech/1280_1024.ogg";
    soundLocations["1280_720"] = "Text_To_Speech/1280_720.ogg";
    soundLocations["1024_768"] = "Text_To_Speech/1024_768.ogg";
    soundLocations["800_600"] = "Text_To_Speech/800_600.ogg";
    soundLocations["640_480"] = "Text_To_Speech/640_480.ogg";
    soundLocations["arial"] = "Text_To_Speech/arial.ogg";
    soundLocations["open-dyslexic"] = "Text_To_Speech/open_dyslexic.ogg";
    soundLocations["comic"] = "Text_To_Speech/comic_sans.ogg";
    soundLocations["60"] = "Text_To_Speech/60.ogg";
    soundLocations["48"] = "Text_To_Speech/48.ogg";
    soundLocations["36"] = "Text_To_Speech/36.ogg";
    soundLocations["30"] = "Text_To_Speech/30.ogg";
    soundLocations["24"] = "Text_To_Speech/24.ogg";
    soundLocations["20"] = "Text_To_Speech/20.ogg";

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