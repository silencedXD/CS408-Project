#include "AudioUnit.h"
#include <iostream>

AudioUnit::AudioUnit(float general, float text, float game) {
    soundLocations["6C"] = "Sound_Effects/piano6C.ogg";
    soundLocations["5C"] = "Sound_Effects/piano5C.ogg";
    soundLocations["4C"] = "Sound_Effects/piano4C.ogg";
    soundLocations["3C"] = "Sound_Effects/piano3C.ogg";
    soundLocations["pass"] = "Sound_Effects/pass.ogg";
    soundLocations["fail"] = "Sound_Effects/fail.ogg";

    soundLocations["main_menu"] = "Text_To_Speech/main_menu.ogg";
    soundLocations["reaction_game"] = "Text_To_Speech/reaction_game.ogg";
    soundLocations["melody_game"] = "Text_To_Speech/melody_game.ogg";
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
    soundLocations["UP"] = "Text_To_Speech/up.ogg";
    soundLocations["DOWN"] = "Text_To_Speech/down.ogg";
    soundLocations["LEFT"] = "Text_To_Speech/left.ogg";
    soundLocations["RIGHT"] = "Text_To_Speech/right.ogg";
    soundLocations["ENTER"] = "Text_To_Speech/enter.ogg";
    soundLocations["PAUSE"] = "Text_To_Speech/pause.ogg";
    soundLocations["reset_to_default"] = "Text_To_Speech/reset_to_default.ogg";
    soundLocations["level_complete"] = "Text_To_Speech/level_complete.ogg";
    soundLocations["level_failed"] = "Text_To_Speech/level_failed.ogg";
    soundLocations["retry"] = "Text_To_Speech/retry.ogg";

    soundLocations["1920_1080"] = "Text_To_Speech/1920_1080.ogg";
    soundLocations["1680_1050"] = "Text_To_Speech/1680_1050.ogg";
    soundLocations["1600_900"] = "Text_To_Speech/1600_900.ogg";
    soundLocations["1280_1024"] = "Text_To_Speech/1280_1024.ogg";
    soundLocations["1280_720"] = "Text_To_Speech/1280_720.ogg";
    soundLocations["1024_768"] = "Text_To_Speech/1024_768.ogg";
    soundLocations["800_600"] = "Text_To_Speech/800_600.ogg";
    soundLocations["640_480"] = "Text_To_Speech/640_480.ogg";

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
    sf::SoundBuffer* buffer = new sf::SoundBuffer;

    if (buffer->loadFromFile(soundLocations.at(soundName))) {
        buffers[soundName] = buffer;

        sounds[soundName] = temp;
        sounds[soundName].setBuffer(*buffer);

        if (soundLocations[soundName].at(0) == 'T') {                       //Individual volume is a percentage of the general volume
            sounds[soundName].setVolume(generalVolume * (textVolume / 100));
        }
        else{
            sounds[soundName].setVolume(generalVolume * (gameVolume / 100));
        }
    }
    else{
        std::cout << soundName + " sound either failed to load or location is missing";
    }   //If the sound fails to load the program exits
}

sf::SoundBuffer* AudioUnit::getBuffer(std::string soundName) { return buffers[soundName]; }

void AudioUnit::playSound(std::string soundName) {
    if (sounds.count(soundName))
    {
        previousSound->stop();                              //Stops previous sound so not to have them play ontop of eachother, useful for text prompts
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

void AudioUnit::playNonRepeatingSound(std::string soundName) {//For when multiple objects want to play the same sound effect at the same time to ensure it only plays once
    if (sounds.count(soundName))
    {
        if (sounds[soundName].getStatus() != sf::SoundSource::Playing) {
            sounds[soundName].play();
            previousSound = &sounds[soundName];
        }
    }
    else {
        loadSound(soundName);
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