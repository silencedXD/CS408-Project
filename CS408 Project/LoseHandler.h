#pragma once
#include "InputHandler.h"

class LoseHandler : public InputHandler
{
public:
	LoseHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_, bool newHighScore);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
	
private:
	MenuCode levelCode;
};

