#pragma once
#include "InputHandler.h"

class OptionsMenuHandler : public InputHandler
{
public:
	OptionsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual MenuCode updateState(sf::Time elapsed);
	virtual void playTextPrompt();
	MenuCode getState();
};

