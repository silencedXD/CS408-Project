#include "AudioOptionsHandler.h"

AudioOptionsHandler::AudioOptionsHandler(UIUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_)
{
    sf::Vector2f windowSize = sf::Vector2f(UI->getWindowSize().x, UI->getWindowSize().y);
    UI->makeLabel("Audio options", 0, 0);
    UI->makeLabel("General Volume", 0, windowSize.y * 0.25f);
    UI->makeLabel("Audio Prompt Volume", 0, windowSize.y * 0.45f);
    UI->makeLabel("Game Volume", 0, windowSize.y * 0.65f);
    UI->makeLabel("Go back", 0, windowSize.y * 0.85f);

    volumeSettings.push_back(100);
    volumeSettings.push_back(90);
    volumeSettings.push_back(80);
    volumeSettings.push_back(70);
    volumeSettings.push_back(60);
    volumeSettings.push_back(50);
    volumeSettings.push_back(40);
    volumeSettings.push_back(30);
    volumeSettings.push_back(20);
    volumeSettings.push_back(10);
    volumeSettings.push_back(0);

    currentGeneralVolume = audio->getGeneralVolume();
    currentTextVolume = audio->getTextVolume();
    currentGameVolume = audio->getGameVolume();

    generalFlag = false;
    textFlag = false;
    gameFlag = false;

    optionPointer = -1;
    state = empty;
    arrowPos = sf::Vector2f(0, 0);
}

void AudioOptionsHandler::changeOption() {               //Changes the setting label when an option is selected
    if (arrowPos.x > 10) {
        UI->removeLastLabel();
    }
    else {
        arrowPos = setArrowPos(sf::Vector2f(4000, 4000));//Function returns previous arrow position
    }
    if (state == empty) {
        setArrowPos(arrowPos);
        arrowPos = sf::Vector2f(0, 0);
    }
    else {
        UI->makeLabel(std::to_string(int(volumeSettings[optionPointer])), arrowPos.x, arrowPos.y);
    }
}

void AudioOptionsHandler::keyPressed(sf::Event event) {
    switch (state) {
    case general:
        if (event.key.code == keyMappings.at(DOWN)) {
            optionPointer = (optionPointer + 1) % volumeSettings.size();    //Volume is changed in real time so user can hear if it's the right setting
            changeOption();

            currentGeneralVolume = volumeSettings[optionPointer];              //Change volume
            audio->setVolume(currentGeneralVolume, -1, -1);
            
            generalFlag = true;
            playTextPrompt();
            audio->playConcurrentSound("3C");                //Play sound so user can hear the change
        }

        if (event.key.code == keyMappings.at(UP)) {
            optionPointer = (volumeSettings.size() + optionPointer - 1) % volumeSettings.size();
            changeOption();

            currentGeneralVolume = volumeSettings[optionPointer];
            audio->setVolume(currentGeneralVolume, -1, -1);
            
            generalFlag = true;
            playTextPrompt();
            audio->playConcurrentSound("3C");
        }

        if (event.key.code == keyMappings.at(ENTER)) {
            state = empty;
            changeOption();
        }
        break;


    case text:
        if (event.key.code == keyMappings.at(DOWN)) {
            optionPointer = (optionPointer + 1) % volumeSettings.size();
            changeOption();

            currentTextVolume = volumeSettings[optionPointer];
            audio->setVolume(-1, currentTextVolume, -1);

            textFlag = true;
            playTextPrompt();
            audio->playConcurrentSound("3C");
        }

        if (event.key.code == keyMappings.at(UP)) {
            optionPointer = (volumeSettings.size() + optionPointer - 1) % volumeSettings.size();
            changeOption();

            currentTextVolume = volumeSettings[optionPointer];
            audio->setVolume(-1, currentTextVolume, -1);

            textFlag = true;
            playTextPrompt();
            audio->playConcurrentSound("3C");
        }

        if (event.key.code == keyMappings.at(ENTER)) {
            state = empty;
            changeOption();
        }
        break;

    case game:
        if (event.key.code == keyMappings.at(DOWN)) {
            optionPointer = (optionPointer + 1) % volumeSettings.size();
            changeOption();

            currentGameVolume = volumeSettings[optionPointer];
            audio->setVolume(-1, -1, currentGameVolume);

            gameFlag = true;
            audio->playConcurrentSound("3C");
        }

        if (event.key.code == keyMappings.at(UP)) {
            optionPointer = (volumeSettings.size() + optionPointer - 1) % volumeSettings.size();
            changeOption();

            currentGameVolume = volumeSettings[optionPointer];
            audio->setVolume(-1, -1, currentGameVolume);

            gameFlag = true;
            playTextPrompt();
            audio->playConcurrentSound("3C");
        }

        if (event.key.code == keyMappings.at(ENTER)) {
            state = empty;
            changeOption();
        }
        break;

    case empty:
        InputHandler::keyPressed(event);
        break;

    default:
        std::cout << "Error unknown audio state";
        break;
    }
}

MenuCode AudioOptionsHandler::updateState(sf::Time elapsed) {

    if (state == empty) {
        if (arrowPos.x < 10) {
            updateArrow();
        }

        sf::Vector2u windowSize = UI->getWindowSize();
        switch (selector) {
        case 15:
            state = general;
            for (int i = 0; i < volumeSettings.size(); i++) {
                if (volumeSettings[i] == currentGeneralVolume) {
                    optionPointer = i;
                    break;
                }
            }
            selector = 10;
            changeOption();
            return audioOptions;

        case 25:
            state = text;
            for (int i = 0; i < volumeSettings.size(); i++) {
                if (volumeSettings[i] == currentTextVolume) {
                    optionPointer = i;
                }
            }
            selector = 20;
            changeOption();
            return audioOptions;

        case 35:
            state = game;
            for (int i = 0; i < volumeSettings.size(); i++) {
                if (volumeSettings[i] == currentGameVolume) {
                    optionPointer = i;
                }
            }
            selector = 30;
            changeOption();
            return audioOptions;

        case 45:
            config = loadConfig();
            if (generalFlag) {
                config["general_volume"] = currentGeneralVolume;
            }
            if (textFlag) {
                config["text_volume"] = currentTextVolume;
            }
            if (gameFlag) {
                config["game_volume"] = currentGameVolume;
            }
            saveConfig(config);
            return options;

        default:
            return audioOptions;
        }
    }
    else {
        return audioOptions;
    }
}


void AudioOptionsHandler::playTextPrompt() {
    if (state == empty) {
        switch (selector) {
        case 0:
            audio->playSound("audio_options");

        case 10:
            audio->playSound("general_volume");
            break;

        case 20:
            audio->playSound("text_volume");
            break;

        case 30:
            audio->playSound("game_volume");
            break;

        case 40:
            audio->playSound("go_back");
            break;

        default:
            std::cout << "Error tried to play text prompt when selector is out of bounds\n";
            break;
        }
    }
    else {
        audio->playSound(std::to_string(int(volumeSettings[optionPointer])));
    }

}
