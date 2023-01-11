#include "LevelSelectHandler.h"
#include <iostream>

LevelSelectHandler::LevelSelectHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_) : InputHandler(graphics_, oFactory_) {

    sf::Vector2u windowSize = graphics->getWindowSize();

    graphics->makeLabel("Level One", 0, 0);
    graphics->makeLabel("Level Two", 0 , windowSize.y * 0.25);
    graphics->makeLabel("Level Three", 0, windowSize.y * 0.5);
    graphics->makeLabel("Go Back", 0, windowSize.y * 0.75);
}


MenuCode LevelSelectHandler::updateState() {
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            sf::Vector2u windowSize = graphics->getWindowSize();

            oFactory->objects[i]->setPos(windowSize.x / 2.0, (windowSize.y / 40.0 * selector) - windowSize.y / 4.0);
            break;
        }
    }


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