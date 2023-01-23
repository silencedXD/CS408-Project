#include "VideoOptionsHandler.h"


VideoOptionsHandler::VideoOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_)
{
    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Video options", 0, 0);
    graphics->makeLabel("Display size", 0, windowSize.y * 0.25);
    graphics->makeLabel("Font type", 0, windowSize.y * 0.45);
    graphics->makeLabel("Font size", 0, windowSize.y * 0.65);
    graphics->makeLabel("Go back", 0, windowSize.y * 0.85);
}

MenuCode VideoOptionsHandler::updateState() {
    updateArrow();
    //TODO: If an option is selected, make the arrow invisible and display the current config for that setting instead
    switch (selector) {
    case 15:
        return videoOptions;

    case 25:
        return videoOptions;

    case 35:
        return videoOptions;

    case 45:
        return options;

    default:
        return videoOptions;
    }
}

void VideoOptionsHandler::playTextPrompt() {
    switch (selector) {

    case 10:
        audio->playSound("display_size");
        break;

    case 20:
        audio->playSound("font_type");
        break;

    case 30:
        audio->playSound("font_size");
        break;

    case 40:
        audio->playSound("go_back");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}