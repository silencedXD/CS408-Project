#pragma once
#include "InputHandler.h"

class WinHandler : public InputHandler
{
public:
	WinHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, int level_);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();

private:
	int level;
};

