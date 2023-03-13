#include "TutorialHandler.h"

TutorialHandler::TutorialHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {

    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Read Instructions", 0, 0);
    graphics->makeLabel("Practise Level One", 0, windowSize.y * 0.25);
    graphics->makeLabel("Practise Level Two", 0, windowSize.y * 0.45);
    graphics->makeLabel("Practise Level Three", 0, windowSize.y * 0.65);
    graphics->makeLabel("Go Back", 0, windowSize.y * 0.85);
}

MenuCode TutorialHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 5:
        selector = 0;
        return instructions;//TODO: create instructions including voice file and written instructions

    case 15:
        selector = 10;
        return practiseLevel1;

    case 25:
        selector = 20;
        return practiseLevel2;

    case 35:
        selector = 30;
        return practiseLevel3;

    case 45:
        return mainMenu;

    default:
        return levelSelect;
    }
}

void TutorialHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        audio->playSound("play_instructions");
        break;
    case 10:
        audio->playSound("practise_level_one");
        break;

    case 20:
        audio->playSound("practise_level_two");
        break;

    case 30:
        audio->playSound("practise_level_three");
        break;

    case 40:
        audio->playSound("go_back");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
};