#include "ControlsOptionsHandler.h"

ControlsOptionsHandler::ControlsOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_)
{
    sf::Vector2u windowSize = graphics->getWindowSize();
    graphics->makeLabel("Controls", 0, 0);
    graphics->makeLabel("UP", 0, windowSize.y * 0.125);
    graphics->makeLabel("DOWN", 0, windowSize.y * 0.25);
    graphics->makeLabel("LEFT", 0, windowSize.y * 0.375);
    graphics->makeLabel("RIGHT", 0, windowSize.y * 0.5);
    graphics->makeLabel("ENTER", 0, windowSize.y * 0.625);
    graphics->makeLabel("PAUSE", 0, windowSize.y * 0.75);
    graphics->makeLabel("Go back", 0, windowSize.y * 0.875);

    totalMenuItems = 8;

    state = empty;
    optionPointer = -1;
    arrowPos = sf::Vector2f(0, 0);
}

void ControlsOptionsHandler::changeOption()
{
}

void ControlsOptionsHandler::keyPressed(sf::Event event)
{
}

MenuCode ControlsOptionsHandler::updateState()
{
	return MenuCode();
}

void ControlsOptionsHandler::playTextPrompt()
{
}
