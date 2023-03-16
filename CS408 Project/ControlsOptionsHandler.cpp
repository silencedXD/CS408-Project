#include "ControlsOptionsHandler.h"

ControlsOptionsHandler::ControlsOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_)
{
    sf::Vector2f windowSize = sf::Vector2f(graphics->getWindowSize().x, graphics->getWindowSize().y);
    graphics->makeLabel("Controls", 0, 0);
    graphics->makeLabel("UP", 0, windowSize.y * 0.12f);
    graphics->makeLabel("DOWN", 0, windowSize.y * 0.23f);
    graphics->makeLabel("LEFT", 0, windowSize.y * 0.34f);
    graphics->makeLabel("RIGHT", 0, windowSize.y * 0.45f);
    graphics->makeLabel("ENTER", 0, windowSize.y * 0.56f);
    graphics->makeLabel("PAUSE", 0, windowSize.y * 0.67f);
    graphics->makeLabel("Reset to default", 0, windowSize.y * 0.78f);
    graphics->makeLabel("Go back", 0, windowSize.y * 0.89f);

    totalMenuItems = 9;

    state = empty;
    optionPointer = -1;

    config = loadConfig();

    upFlag = false;
    downFlag = false;
    leftFlag = false;
    rightFlag = false;
    enterFlag = false;
    pauseFlag = false;

    arrowPos = sf::Vector2f(0, 0);
}

void ControlsOptionsHandler::changeOption()
{
    if (arrowPos.x > 10) {
        graphics->removeLastLabel();
    }
    else {
        arrowPos = setArrowPos(sf::Vector2f(4000, 4000));//Function returns previous arrow position
    }
    switch (state) {
    case UP:
        graphics->makeLabel(config["UP"].asString(), arrowPos.x, arrowPos.y);
        break;
    
    case DOWN:
        graphics->makeLabel(config["DOWN"].asString(), arrowPos.x, arrowPos.y);
        break;

    case LEFT:
        graphics->makeLabel(config["LEFT"].asString(), arrowPos.x, arrowPos.y);
        break;

    case RIGHT:
        graphics->makeLabel(config["RIGHT"].asString(), arrowPos.x, arrowPos.y);
        break;

    case ENTER:
        graphics->makeLabel(config["ENTER"].asString(), arrowPos.x, arrowPos.y);
        break;

    case PAUSE:
        graphics->makeLabel(config["PAUSE"].asString(), arrowPos.x, arrowPos.y);
        break;

    case reset:
        break;

    case empty:
        setArrowPos(arrowPos);
        arrowPos = sf::Vector2f(0, 0);
        break;
    }
}

void ControlsOptionsHandler::keyPressed(sf::Event event)
{
    switch (state) {
    case up:
        keyMappings[UP] = event.key.code;
        upFlag = true;
        //audio->playSound("key_" + std::to_string(event.key.code));
        state = empty;
        changeOption();
        break;

    case down:
        keyMappings[DOWN] = event.key.code;
        downFlag = true;
        //audio->playSound("key_" + std::to_string(event.key.code));
        state = empty;
        changeOption();
        break;

    case left:
        keyMappings[LEFT] = event.key.code;
        leftFlag = true;
        //audio->playSound("key_" + std::to_string(event.key.code));
        state = empty;
        changeOption();
        break;

    case right:
        keyMappings[RIGHT] = event.key.code;
        rightFlag = true;
        //audio->playSound("key_" + std::to_string(event.key.code));
        state = empty;
        changeOption();
        break;

    case enter:
        keyMappings[ENTER] = event.key.code;
        enterFlag = true;
        //audio->playSound("key_" + std::to_string(event.key.code));
        state = empty;
        changeOption();
        break;

    case pause:
        keyMappings[PAUSE] = event.key.code;
        pauseFlag = true;
        //audio->playSound("key_" + std::to_string(event.key.code));
        state = empty;
        changeOption();
        break;

    case empty:
        InputHandler::keyPressed(event);
        break;

    default:
        std::cout << "Error unknown audio state";
        break;
    }
}

MenuCode ControlsOptionsHandler::updateState(sf::Time elapsed)
{
    if (state == empty) {
        if (arrowPos.x < 10) {
            updateArrow();
        }

        switch (selector) {
        case 15:
            state = up;
            selector = 10;
            changeOption();
            return controlsOptions;

        case 25:
            state = down;
            selector = 20;
            changeOption();
            return controlsOptions;

        case 35:
            state = left;
            selector = 30;
            changeOption();
            return controlsOptions;

        case 45:
            state = right;
            selector = 40;
            changeOption();
            return controlsOptions;

        case 55:
            state = enter;
            selector = 50;
            changeOption();
            return controlsOptions;
            
        case 65:
            state = pause;
            selector = 60;
            changeOption();
            return controlsOptions;

        case 75:
            selector = 70;
            keyMappings[UP] = stringToKeyboard(config["default_UP"].asString());
            keyMappings[DOWN] = stringToKeyboard(config["default_DOWN"].asString());
            keyMappings[LEFT] = stringToKeyboard(config["default_LEFT"].asString());
            keyMappings[RIGHT] = stringToKeyboard(config["default_RIGHT"].asString());
            keyMappings[ENTER] = stringToKeyboard(config["default_ENTER"].asString());
            keyMappings[PAUSE] = stringToKeyboard(config["default_PAUSE"].asString());
            upFlag = false;
            downFlag = false;
            leftFlag = false;
            rightFlag = false;
            enterFlag = false;
            pauseFlag = false;
            return controlsOptions;

        case 85:
            config = loadConfig();

            if (upFlag) {
                config["UP"] = keyMappings[UP];
            }
            if (downFlag) {
                config["DOWN"] = keyMappings[DOWN];
            }
            if (leftFlag) {
                config["LEFT"] = keyMappings[LEFT];
            }
            if (rightFlag) {
                config["RIGHT"] = keyMappings[RIGHT];
            }
            if (enterFlag) {
                config["ENTER"] = keyMappings[ENTER];
            }
            if (pauseFlag) {
                config["PAUSE"] = keyMappings[PAUSE];
            }
            saveConfig(config);
            return options;

        default:
            return controlsOptions;
        }
    }
    else {
        return controlsOptions;
    }
}

void ControlsOptionsHandler::playTextPrompt()
{
    if (state == empty) {
        switch (selector) {

        case 10:
            audio->playSound("UP");
            break;

        case 20:
            audio->playSound("DOWN");
            break;

        case 30:
            audio->playSound("LEFT");
            break;

        case 40:
            audio->playSound("RIGHT");
            break;

        case 50:
            audio->playSound("ENTER");
            break;

        case 60:
            audio->playSound("PAUSE");
            break;

        case 70:
            audio->playSound("reset_to_default");
            break;

        case 80:
            audio->playSound("go_back");
            break;

        default:
            std::cout << "Error tried to play text prompt when selector is out of bounds\n";
            break;
        }
    }
}

