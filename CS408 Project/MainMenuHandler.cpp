#include "MainMenuHandler.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>


MainMenuHandler::MainMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {


    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            sf::Vector2u windowSize = graphics->getWindowSize();

            oFactory->objects[i]->getSprite()->setScale(0.5, 0.5);
            break;
        }
    }


    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Options", 0, 0);
    graphics->makeLabel("Level Editor", 0, windowSize.y * 0.25);
    graphics->makeLabel("Level Select", 0, windowSize.y * 0.5);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.75);
}

MenuCode MainMenuHandler::updateState() {
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            sf::Vector2u windowSize = graphics->getWindowSize();

            oFactory->objects[i]->setPos(windowSize.x / 2.0, (windowSize.y / 40.0 * selector) - windowSize.y / 4.0);
            break;
        }
    }

    switch (selector) {
    case 15:
        return settings;
        break;

    case 25:
        return levelEditor;
        break;

    case 35:
        return levelSelect;
        break;

    case 45:
        return quit;
        break;

    default:
        return mainMenu;
        break;
    }
}