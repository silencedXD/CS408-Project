#pragma once
#include "InputHandler.h"

class ControlsOptionsHandler : public InputHandler
{
public:
	ControlsOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	void changeOption();

	void keyPressed(sf::Event event);

	MenuCode updateState();

	void playTextPrompt();

private:
	enum controlsOptionsEnum { UP, DOWN, LEFT, RIGHT, ENTER, PAUSE, empty };

	sf::Vector2f arrowPos;
	controlsOptionsEnum state;

	int optionPointer;

	Json::Value config;
};

