#pragma once
#include "InputHandler.h"

class ControlsOptionsHandler : public InputHandler
{
public:
	ControlsOptionsHandler(UIUnit* graphics_, AudioUnit* audio_);
	void changeOption();

	void keyPressed(sf::Event event);

	MenuCode updateState(sf::Time elapsed);

	void playTextPrompt();

private:
	enum controlsOptionsEnum { up, down, left, right, enter, pause, reset, empty };


	sf::Vector2f arrowPos;
	controlsOptionsEnum state;

	int optionPointer;

	bool upFlag;
	bool downFlag;
	bool leftFlag;
	bool rightFlag;
	bool enterFlag;
	bool pauseFlag;
};

