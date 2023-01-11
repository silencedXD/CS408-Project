#pragma once
#include "InputHandler.h"

class MainMenuHandler : public InputHandler
{
public:
	MainMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_);
	virtual MenuCode updateState();
};

