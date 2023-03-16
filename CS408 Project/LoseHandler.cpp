#include "LoseHandler.h"

LoseHandler::LoseHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_, bool newHighscore) : InputHandler(graphics_, oFactory_, audio_) {

    audio->playConcurrentSound("level_failed");

    if (newHighscore) {
        audio->playConcurrentSound("new_highscore");
    }
    
    //TODO: Display highscore

    sf::Vector2f windowSize = sf::Vector2f(graphics->getWindowSize().x, graphics->getWindowSize().y);
    graphics->makeLabel("Level Failed", 0, 0);
    graphics->makeLabel("Retry", 0, windowSize.y * 0.25f);
    graphics->makeLabel("Select level", 0, windowSize.y * 0.45f);
    graphics->makeLabel("Main Menu", 0, windowSize.y * 0.65f);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.85f);
    levelCode = levelCode_;
    

}

MenuCode LoseHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        return levelCode;

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