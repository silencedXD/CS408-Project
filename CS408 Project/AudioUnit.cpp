#include "AudioUnit.h"
#include <iostream>

AudioUnit::AudioUnit(float general, float text, float game) {
    //soundLocations["high_piano_note"] = "Sound_Effects/piano6C.ogg";
    soundLocations["medium_piano_note"] = "Sound_Effects/piano5C.ogg";
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
    soundLocations["general_volume"] = "Text_To_Speech/general volume.ogg";
    soundLocations["text_volume"] = "Text_To_Speech/audio prompt volume.ogg";
    soundLocations["game_volume"] = "Text_To_Speech/game volume.ogg";
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
    soundLocations["100"] = "Text_To_Speech/100.ogg";
    soundLocations["90"] = "Text_To_Speech/90.ogg";
    soundLocations["80"] = "Text_To_Speech/80.ogg";
    soundLocations["70"] = "Text_To_Speech/70.ogg";
    soundLocations["60"] = "Text_To_Speech/60.ogg";
    soundLocations["50"] = "Text_To_Speech/50.ogg";
    soundLocations["48"] = "Text_To_Speech/48.ogg";
    soundLocations["40"] = "Text_To_Speech/40.ogg";
    soundLocations["36"] = "Text_To_Speech/36.ogg";
    soundLocations["30"] = "Text_To_Speech/30.ogg";
    soundLocations["24"] = "Text_To_Speech/24.ogg";
    soundLocations["20"] = "Text_To_Speech/20.ogg";
    soundLocations["10"] = "Text_To_Speech/10.ogg";
    soundLocations["0"] = "Text_To_Speech/0.ogg";

    generalVolume = general;
    textVolume = text;
    gameVolume = game;

    bufferCount = 0;
    loadSound("main_menu");
    previousSound = &sounds["main_menu"];
    playSound("menu_controls");
    //sf::sleep(sf::seconds(4.2));
}

void AudioUnit::loadSound(std::string soundName) {
    sf::Sound temp;
    buffers.push_back(new sf::SoundBuffer);

    if (buffers.back()->loadFromFile(soundLocations.at(soundName))) {
        sounds[soundName] = temp;
        sounds[soundName].setBuffer(*buffers[bufferCount]);

        if (soundLocations[soundName].at(0) == 'T') {                       //Individual volume is a percentage of the general volume
            sounds[soundName].setVolume(generalVolume * (textVolume / 100));
        }
        else{
            sounds[soundName].setVolume(generalVolume * (gameVolume / 100));
        }
        bufferCount++;
    }
    else{
        std::cout << soundName + " sound either failed to load or location is missing";
    }   //If the sound fails to load the program exits
}

void AudioUnit::playSound(std::string soundName) {
    if (sounds.count(soundName))
    {
        previousSound->stop();                              //Stops previous sound so not to have them play ontop of eachother
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

void AudioUnit::playConcurrentSound(std::string soundName) {//To have sound effects and vocals we need multiple sounds at once
    if (sounds.count(soundName))
    {
        sounds[soundName].play();
        previousSound = &sounds[soundName];
    }
    else {
        loadSound(soundName);
        sounds[soundName].play();
        previousSound = &sounds[soundName];
    }
}

float AudioUnit::getGeneralVolume()
{
    return generalVolume;
}

float AudioUnit::getTextVolume()
{
    return textVolume;
}

float AudioUnit::getGameVolume()
{
    return gameVolume;
}

void AudioUnit::setVolume(float general_, float text_, float game_)
{
    bool changeFlag = false;
    if (general_ >= 0) {
        generalVolume = general_;
        changeFlag = true;
    }

    if (text_ >= 0) {
        textVolume = text_;
        changeFlag = true;
    }

    if (game_ >= 0) {
        gameVolume = game_;
        changeFlag = true;
    }
    
    if (changeFlag) {
        resetVolume();
    }
}

void AudioUnit::resetVolume()
{
    sounds.clear();
    buffers.clear();
    bufferCount = 0;
    loadSound("main_menu");
    previousSound = &sounds["main_menu"];
}