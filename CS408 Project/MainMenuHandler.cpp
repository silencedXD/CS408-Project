#include "MainMenuHandler.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>


MainMenuHandler::MainMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Options", 0, windowSize.y * 0.25);
    graphics->makeLabel("Level Editor", 0, windowSize.y * 0.45);
    graphics->makeLabel("Select Level", 0, windowSize.y * 0.65);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.85);

    audio->playSound("main_menu");
}

MenuCode MainMenuHandler::updateState() {
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            sf::Vector2u windowSize = graphics->getWindowSize();

            oFactory->objects[i]->setPos(windowSize.x / 2.0, (selector / 10) * (windowSize.y / totalMenuItems));
            break;
        }
    }

    switch (selector) {

    case 15:
        selector = 0;
        return options;
        break;

    case 25:
        selector = 0;
        return levelEditor;
        break;

    case 35:
        selector = 0;
        return levelSelect;
        break;

    case 45:
        selector = 0;
        return quit;
        break;

    default:
        return empty;
        break;
    }
}

void MainMenuHandler::playTextPrompt() {
    std::cout << "Selector: " << selector << "\n";
    switch (selector) {
    case 0:
        audio->playSound("main_menu");
        break;
    case 10:
        audio->playSound("options");
        break;

    case 20:
        audio->playSound("level_editor");
        break;

    case 30:
        audio->playSound("select_level");
        break;

    case 40:
        audio->playSound("quit");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}