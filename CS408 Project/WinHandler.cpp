#include "WinHandler.h"

WinHandler::WinHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_, int playerScore, int highscore) : InputHandler(graphics_, oFactory_, audio_) {
    
    activated = false;
    audio->playConcurrentSound("level_complete");

    if (playerScore >= highscore) {
        audio->playConcurrentSound("new_highscore");
        graphics->makeLabel("New Highscore!!!", 0, 0);
    }

    sf::sleep(sf::milliseconds(100));
    audio->playSound("your_highscore_is");
    //for ()

    //graphics->makeLabel("Your highscore is: " + )
    //TODO: Display highscore

    sf::Vector2f windowSize = sf::Vector2f(graphics->getWindowSize().x, graphics->getWindowSize().y);
    graphics->makeLabel("Level Complete", 0, 0);
    graphics->makeLabel("Retry", 0, windowSize.y * 0.25f);
    graphics->makeLabel("Select level", 0, windowSize.y * 0.45f);
    graphics->makeLabel("Main Menu", 0, windowSize.y * 0.65f);
    graphics->makeLabel("Quit", 0, windowSize.y * 0.85f);
    levelCode = levelCode_;

}

MenuCode WinHandler::updateState(sf::Time elapsed) {
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
        return win;
    }
}

void WinHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        audio->playSound("level_complete");
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