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
    if (event.key.code == sf::Keyboard::Down) {
        if (selector < (totalMenuItems - 1) * 10) {
            selector = selector + 10;
            playTextPrompt();
        }
        else {
            selector = (totalMenuItems - 1) * 10;
        }
        //audio->playSound("low_piano_note");
    }
    if (event.key.code == sf::Keyboard::Up) {
        if (selector >= 10) {
            selector = selector - 10;
            playTextPrompt();
        }
        //audio->playSound("high_piano_note");
    }
    if (event.key.code == sf::Keyboard::Right) {
        if (selector % 10 == 0 && selector > 0)
        {
            selector = selector + 5;
        }
    }
}
