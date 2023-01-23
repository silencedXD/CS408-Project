#include "LevelSelectHandler.h"
#include <iostream>

LevelSelectHandler::LevelSelectHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Select level", 0, 0);
    graphics->makeLabel("Level One", 0, windowSize.y * 0.25);
    graphics->makeLabel("Level Two", 0 , windowSize.y * 0.45);
    graphics->makeLabel("Level Three", 0, windowSize.y * 0.65);
    graphics->makeLabel("Go Back", 0, windowSize.y * 0.85);
}


MenuCode LevelSelectHandler::updateState() {
    updateArrow();

    switch (selector) {
    case 15:
        std::cout << "Level One selected";
        selector = 10;
        return levelSelect;
        break;
    case 25:
        std::cout << "Level Two selected";
        selector = 20;
        return levelSelect;
        break;
    case 35:
        std::cout << "Level Three selected";
        selector = 30;
        return levelSelect;
        break;
    case 45:
        return mainMenu;
        break;
    default:
        return levelSelect;
        break;
    }

}

void LevelSelectHandler::playTextPrompt() {
    std::cout << "Selector: " << selector << "\n";
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