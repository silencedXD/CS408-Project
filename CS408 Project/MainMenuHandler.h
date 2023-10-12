#pragma once
#include "InputHandler.h"

class MainMenuHandler : public InputHandler
{
public:
	MainMenuHandler(UIUnit* graphics_, AudioUnit* audio_);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
};

