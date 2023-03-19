#include "TutorialHandler.h"

TutorialHandler::TutorialHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2f windowSize = sf::Vector2f(graphics->getWindowSize().x, graphics->getWindowSize().y);
    graphics->makeLabel("Tutorial", 0, 0);
    graphics->makeLabel("Play Instructions", 0, windowSize.y * 0.17f);
    graphics->makeLabel("Practise Level One", 0, windowSize.y * 0.34f);
    graphics->makeLabel("Practise Level Two", 0, windowSize.y * 0.51f);
    graphics->makeLabel("Practise Level Three", 0, windowSize.y * 0.68f);
    graphics->makeLabel("Go Back", 0, windowSize.y * 0.85f);
    totalMenuItems = 6;
}

MenuCode TutorialHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        audio->playSound("instructions");
        selector = 10;
        return tutorial;

    case 25:
        selector = 20;
        return practiseLevel1;

    case 35:
        selector = 30;
        return practiseLevel2;

    case 45:
        selector = 40;
        return practiseLevel3;

    case 55:
        return mainMenu;

    default:
        return tutorial;
    }
}

void TutorialHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        audio->playSound("tutorial");
        break;

    case 10:
        audio->playSound("play_instructions");
        break;

    case 20:
        audio->playSound("practise_level_one");
        break;

    case 30:
        audio->playSound("practise_level_two");
        break;

    case 40:
        audio->playSound("practise_level_three");
        break;

    case 50:
        audio->playSound("go_back");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
};