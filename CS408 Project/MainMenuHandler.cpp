#include "MainMenuHandler.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>


MainMenuHandler::MainMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Main menu", 0, 0);
    graphics->makeLabel("Options", 0, windowSize.y * 0.25);
    graphics->makeLabel("Level Editor", 0, windowSize.y * 0.45);
    graphics->makeLabel("Select Level", 0, windowSize.y * 0.65);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.85);

    audio->playSound("main_menu");
}

MenuCode MainMenuHandler::updateState() {
    updateArrow();

    switch (selector) {

    case 15:
        return options;

    case 25:
        return levelEditor;

    case 35:
        return levelSelect;

    case 45:
        return quit;

    default:
        return empty;
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