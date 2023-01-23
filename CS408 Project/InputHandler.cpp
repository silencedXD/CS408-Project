#include "InputHandler.h"

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
    }
    if (event.key.code == sf::Keyboard::Up) {
        if (selector >= 10) {
            selector = selector - 10;
            playTextPrompt();
        }
    }
    if (event.key.code == sf::Keyboard::Right) {
        if (selector % 10 == 0 && selector > 0)
        {
            selector = selector + 5;
        }
    }
}

void InputHandler::updateArrow() {
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            sf::Vector2u windowSize = graphics->getWindowSize();

            oFactory->objects[i]->setPos(windowSize.x / 2.0, (selector / 10) * (windowSize.y / totalMenuItems));
            break;
        }
    }
}