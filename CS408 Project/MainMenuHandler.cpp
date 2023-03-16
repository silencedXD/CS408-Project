#include "MainMenuHandler.h"
#include <SFML/System/Vector2.hpp>


MainMenuHandler::MainMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2f windowSize = sf::Vector2f(graphics->getWindowSize().x, graphics->getWindowSize().y);
    graphics->makeLabel("Main menu", 0, 0);
    graphics->makeLabel("Start game", 0, windowSize.y * 0.25f);
    graphics->makeLabel("Tutorial", 0, windowSize.y * 0.45f);
    graphics->makeLabel("Options", 0, windowSize.y * 0.65f);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.85f);

    audio->playSound("main_menu");
}

MenuCode MainMenuHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        return levelSelect;

    case 25:
        return tutorial;

    case 35:
        return options;

    case 45:
        return quit;

    default:
        return mainMenu;
    }
}

void MainMenuHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        audio->playSound("main_menu");
        break;

    case 10:
        audio->playSound("start_game");
        break;

    case 20:
        audio->playSound("tutorial");
        break;

    case 30:
        audio->playSound("options");
        break;

    case 40:
        audio->playSound("quit");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}