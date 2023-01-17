#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) {
    selector = 10;
    totalMenuItems = 4;
    graphics = graphics_;
    oFactory = oFactory_;
    audio = audio_;
}

void InputHandler::keyPressed(sf::Event event) {
    if (event.key.code == sf::Keyboard::Down) {
        if (selector < totalMenuItems * 10) {
            selector = selector + 10;
        }
        std::cout << "Down Press\n";
        audio->playSound("low_piano_note");
    }
    if (event.key.code == sf::Keyboard::Up) {
        if (selector > 10) {
            selector = selector - 10;
        }
        std::cout << "Up Press\n";
        audio->playSound("high_piano_note");
    }
    if (event.key.code == sf::Keyboard::Enter) {
        selector = selector + 5;
        audio->playSound("medium_piano_note");
        std::cout << "Enter Press\n";
    }
}

MenuCode InputHandler::updateState() { return mainMenu; }
