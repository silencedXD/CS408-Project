#pragma once
#include "InputHandler.h"

class OptionsMenuHandler : public InputHandler
{
public:
	OptionsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	void keyPressed(sf::Event event);
	virtual MenuCode updateState();
	virtual void playTextPrompt();
};

