#pragma once
#include "InputHandler.h"

class LoseHandler : public InputHandler
{
public:
	LoseHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, int level_);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
	
private:
	int level;
};

