#pragma once
#include "InputHandler.h"

class VideoOptionsHandler : public InputHandler
{
public:
	VideoOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual MenuCode updateState();
	void playTextPrompt();
};