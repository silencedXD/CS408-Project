#include "LoseHandler.h"

LoseHandler::LoseHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, int level_) : InputHandler(graphics_, oFactory_, audio_) {
    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Level Failed", 0, 0);
    graphics->makeLabel("Retry", 0, windowSize.y * 0.25);
    graphics->makeLabel("Select Level", 0, windowSize.y * 0.45);
    graphics->makeLabel("Main Menu", 0, windowSize.y * 0.65);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.85);
    level = level_;

    audio->playConcurrentSound("level_failed");
}

MenuCode LoseHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        switch (level) {
        case 1:
            return level1;

        case 2:
            return level2;

        case 3:
            return level3;

        default:
            return level1;
        }

    case 25:
        return levelSelect;

    case 35:
        return mainMenu;

    case 45:
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
        audio->playSound("select_level");
        break;

    case 30:
        audio->playSound("main_menu");
        break;

    case 40:
        audio->playSound("quit");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}