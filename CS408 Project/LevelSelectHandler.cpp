#include "LevelSelectHandler.h"

LevelSelectHandler::LevelSelectHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Select level", 0, 0);
    graphics->makeLabel("Level One", 0, windowSize.y * 0.25f);
    graphics->makeLabel("Level Two", 0, windowSize.y * 0.45f);
    graphics->makeLabel("Level Three", 0, windowSize.y * 0.65f);
    graphics->makeLabel("Go Back", 0, windowSize.y * 0.85f);
}


MenuCode LevelSelectHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        selector = 10;
        return level1;

    case 25:
        selector = 20;
        return level2;

    case 35:
        selector = 30;
        return level3;

    case 45:
        return mainMenu;

    default:
        return levelSelect;
    }
}

void LevelSelectHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        audio->playSound("select_level");
        break;
    case 10:
        audio->playSound("level_one");
        break;

    case 20:
        audio->playSound("level_two");
        break;

    case 30:
        audio->playSound("level_three");
        break;

    case 40:
        audio->playSound("go_back");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
};