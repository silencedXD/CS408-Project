#pragma once
#include "InputHandler.h"

class SettingsMenuHandler : public InputHandler
{
public:
	SettingsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	void keyPressed(sf::Event event);
	virtual MenuCode updateState();
	virtual void playTextPrompt();
};

