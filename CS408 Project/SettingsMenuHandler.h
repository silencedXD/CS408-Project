#pragma once
#include "InputHandler.h"

class SettingsMenuHandler : public InputHandler
{
public:
	SettingsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_);
	void keyPressed(sf::Event event);
	virtual MenuCode updateState();

};

