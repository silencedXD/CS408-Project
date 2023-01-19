#pragma once
#include "InputHandler.h"

class MainMenuHandler : public InputHandler
{
public:
	MainMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual MenuCode updateState();
	void playTextPrompt();
};

