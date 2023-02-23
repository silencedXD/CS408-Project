#include "VideoOptionsHandler.h"
#include <sstream>


VideoOptionsHandler::VideoOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_)
{
    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Video options", 0, 0);
    graphics->makeLabel("Display size", 0, windowSize.y * 0.25);
    graphics->makeLabel("Font type", 0, windowSize.y * 0.45);
    graphics->makeLabel("Font size", 0, windowSize.y * 0.65);
    graphics->makeLabel("Go back", 0, windowSize.y * 0.85);

    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(1920, 1080, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(1680, 1050, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(1600, 900, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(1280, 1024, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(1280, 720, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(1024, 768, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(800, 600, 32));
    displayModes.push_back(std::tuple<unsigned int, unsigned int, unsigned int>(640, 480, 32));
    displayModeSounds.push_back("1920_1080");
    displayModeSounds.push_back("1680_1050");
    displayModeSounds.push_back("1600_900");
    displayModeSounds.push_back("1280_1024");
    displayModeSounds.push_back("1280_720");
    displayModeSounds.push_back("1024_768");
    displayModeSounds.push_back("800_600");
    displayModeSounds.push_back("640_480");

    fontTypes.push_back("arial");
    fontTypes.push_back("open-dyslexic");
    fontTypes.push_back("comic");

    fontSizes.push_back(60);
    fontSizes.push_back(48);
    fontSizes.push_back(36);
    fontSizes.push_back(30);
    fontSizes.push_back(24);
    fontSizes.push_back(20);
    fontSizeSounds.push_back("60");
    fontSizeSounds.push_back("48");
    fontSizeSounds.push_back("36");
    fontSizeSounds.push_back("30");
    fontSizeSounds.push_back("24");
    fontSizeSounds.push_back("20");

    state = empty;
    currentDisplaySize = std::tuple<unsigned int, unsigned int, unsigned int> (windowSize.x, windowSize.y, 32);
    currentFontType = graphics->getFontType();
    currentFontSize = graphics->getFontSize();

    displaySizeFlag = false;
    fontTypeFlag = false;
    fontSizeFlag = false;

    optionPointer = -1;
    arrowPos = sf::Vector2f(0, 0);
;}

void VideoOptionsHandler::changeOption() {
    if (arrowPos.x > 10) {
        graphics->removeLastLabel();
    }
    else {
        arrowPos = setArrowPos(sf::Vector2f(4000, 4000));
    }
    switch (state) {
    case displaySize:
        graphics->makeLabel(std::to_string(std::get<0>(displayModes[optionPointer])) + " x " + std::to_string(std::get<1>(displayModes[optionPointer])), arrowPos.x, arrowPos.y);
        break;

    case fontType:
        graphics->makeLabel(fontTypes[optionPointer], arrowPos.x, arrowPos.y);
        break;

    case fontSize:
        graphics->makeLabel(std::to_string(fontSizes[optionPointer]), arrowPos.x, arrowPos.y);
        break;

    case empty:
        setArrowPos(arrowPos);
        arrowPos = sf::Vector2f(0, 0);
        break;

    default:
        std::cout << "Error unknown video option selected";
        break;
    }
}

void VideoOptionsHandler::keyPressed(sf::Event event) {
    switch (state) {
    case displaySize:
        if (event.key.code == keyMappings.at(DOWN)) {
            optionPointer = (optionPointer + 1) % optionTotal;
            graphics->changeDisplaySize(displayModes[optionPointer]);
            currentDisplaySize = displayModes[optionPointer];
            displaySizeFlag = true;
            changeOption();
            reloadLabels(graphics->getLastLabel().getString());
            playTextPrompt();
        }

        if (event.key.code == keyMappings.at(UP)) {
            optionPointer = (optionTotal + optionPointer - 1) % optionTotal;
            graphics->changeDisplaySize(displayModes[optionPointer]);
            currentDisplaySize = displayModes[optionPointer];
            displaySizeFlag = true;
            changeOption();
            reloadLabels(graphics->getLastLabel().getString());
            playTextPrompt();
        }
        if (event.key.code == keyMappings.at(ENTER)) {
            state = empty;
            changeOption();
        }
        break;


    case fontType:
        if (event.key.code == keyMappings.at(DOWN)) {
            optionPointer = (optionPointer + 1) % optionTotal;
            graphics->changeFontType(fontTypes[optionPointer]);
            currentFontType = fontTypes[optionPointer];
            fontTypeFlag = true;
            changeOption();
            playTextPrompt();
        }

        if (event.key.code == keyMappings.at(UP)) {
            optionPointer = (optionTotal + optionPointer - 1) % optionTotal;
            graphics->changeFontType(fontTypes[optionPointer]);
            currentFontType = fontTypes[optionPointer];
            fontTypeFlag = true;
            changeOption();
            playTextPrompt();
        }

        if (event.key.code == keyMappings.at(ENTER)) {
            state = empty;
            changeOption();
        }
        break;

    case fontSize:
        if (event.key.code == keyMappings.at(DOWN)) {
            optionPointer = (optionPointer + 1) % optionTotal;
            graphics->changeFontSize(fontSizes[optionPointer]);
            currentFontSize = fontSizes[optionPointer];
            fontSizeFlag = true;
            changeOption();
            playTextPrompt();
        }

        if (event.key.code == keyMappings.at(UP)) {
            optionPointer = (optionTotal + optionPointer - 1) % optionTotal;
            graphics->changeFontSize(fontSizes[optionPointer]);
            currentFontSize = fontSizes[optionPointer];
            fontSizeFlag = true;
            changeOption();
            playTextPrompt();
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
        std::cout << "Error unknown video state";
        break;
    }
}

void VideoOptionsHandler::reloadLabels(std::string lastLabel) {
    graphics->clearText();
    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Video options", 0, 0);
    graphics->makeLabel("Display size", 0, windowSize.y * 0.25);
    graphics->makeLabel("Font type", 0, windowSize.y * 0.45);
    graphics->makeLabel("Font size", 0, windowSize.y * 0.65);
    graphics->makeLabel("Go back", 0, windowSize.y * 0.85);
    graphics->makeLabel(lastLabel, arrowPos.x, arrowPos.y);
}

MenuCode VideoOptionsHandler::updateState(sf::Time elapsed) {

    if (state == empty) {
        if (arrowPos.x < 10){
            updateArrow();
        }
  
        switch (selector) {
        case 15:
            state = displaySize;
            optionTotal = displayModes.size();
            for (int i = 0; i < displayModes.size(); i++) {
                if (displayModes[i]._Myfirst._Val == currentDisplaySize._Myfirst._Val) {
                    optionPointer = i;
                    break;
                }
            }
            selector = 10;
            changeOption();
            return videoOptions;

        case 25:
            state = fontType;
            optionTotal = fontTypes.size();
            for (int i = 0; i < fontTypes.size(); i++) {
                if (fontTypes[i] == currentFontType) {
                    optionPointer = i;
                }
            }
            selector = 20;
            changeOption();
            return videoOptions;

        case 35:
            state = fontSize;
            optionTotal = fontSizes.size();
            for (int i = 0; i < fontSizes.size(); i++) {
                if (fontSizes[i] == currentFontSize) {
                    optionPointer = i;
                }
            }
            selector = 30;
            changeOption();
            return videoOptions;

        case 45:
            config = loadConfig();
            if (displaySizeFlag) {
                config["window_width"] = std::get<0>(currentDisplaySize);
                config["window_height"] = std::get<1>(currentDisplaySize);
                config["bpp"] = std::get<2>(currentDisplaySize);
            }
            if (fontTypeFlag) {
                config["font"] = currentFontType;
            }
            if (fontSizeFlag) {
                config["font_size"] = currentFontSize;
            }

            saveConfig(config);
            return options;

        default:
            return videoOptions;
        }
    }
    else {
        return videoOptions;
    }
}


void VideoOptionsHandler::playTextPrompt() {
    switch (state) {
    case displaySize:
        audio->playSound(displayModeSounds[optionPointer]);
        break;

    case fontType:
        audio->playSound(fontTypes[optionPointer]);
        break;

    case fontSize:
        audio->playSound(fontSizeSounds[optionPointer]);
        break;

    case empty:
        switch (selector) {

        case 10:
            audio->playSound("display_size");
            break;

        case 20:
            audio->playSound("font_type");
            break;

        case 30:
            audio->playSound("font_size");
            break;

        case 40:
            audio->playSound("go_back");
            break;

        default:
            std::cout << "Error tried to play text prompt when selector is out of bounds\n";
            break;
        }
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}
