#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) {
    selector = 0;
    totalMenuItems = 5;
    graphics = graphics_;
    oFactory = oFactory_;
    audio = audio_;

}

void InputHandler::keyPressed(sf::Event event) {
    std::cout << "Selector before:  " << selector << "\n";
    if (event.key.code == sf::Keyboard::Down) {
        if (selector < (totalMenuItems - 1) * 10) {
            selector = selector + 10;
            playTextPrompt();
        }
        else {
            selector = (totalMenuItems - 1) * 10;
        }
        std::cout << "Down Press\n";
        //audio->playSound("low_piano_note");
    }
    if (event.key.code == sf::Keyboard::Up) {
        if (selector >= 10) {
            selector = selector - 10;
            playTextPrompt();
        }
        std::cout << "Up Press\n";
        //audio->playSound("high_piano_note");
    }
    if (event.key.code == sf::Keyboard::Enter) {
        if (selector % 10 == 0 && selector > 0)
        {
            selector = selector + 5;
            std::cout << "Enter Press\n";
        }
        audio->playSound("medium_piano_note");
    }
    std::cout << "Selector after:  " << selector << "\n";
}
