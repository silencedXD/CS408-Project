#pragma once
#include "InputHandler.h"

class ControlsOptionsHandler : public InputHandler
{
public:
	ControlsOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	void changeOption();

	void keyPressed(sf::Event event);

	MenuCode updateState(sf::Time elapsed);

	void playTextPrompt();

	MenuCode getState();

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

