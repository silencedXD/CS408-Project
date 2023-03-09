#include "LoseHandler.h"

LoseHandler::LoseHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_) : InputHandler(graphics_, oFactory_, audio_) {
    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Level Failed", 0, 0);
    graphics->makeLabel("Retry", 0, windowSize.y * 0.25);
    graphics->makeLabel("Main Menu", 0, windowSize.y * 0.5);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.75);
    levelCode = levelCode_;
    totalMenuItems = 4;

    audio->playConcurrentSound("level_failed");
}

MenuCode LoseHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        return levelCode;

    case 25:
        return mainMenu;

    case 35:
        return quit;

    default:
        return lose;
    }
}

void LoseHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        audio->playSound("level_failed");
        break;

    case 10:
        audio->playSound("retry");
        break;

    case 20:
        audio->playSound("main_menu");
        break;

    case 30:
        audio->playSound("quit");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}