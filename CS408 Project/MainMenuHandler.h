#pragma once
#include "InputHandler.h"

class MainMenuHandler : public InputHandler
{
public:
	MainMenuHandler(UIUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
};

