#pragma once
#include "InputHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

class RLevelSelectHandler : public InputHandler
{
public:
	RLevelSelectHandler(GraphicsUnit* graphics, ObjectFactory* oFactory, AudioUnit* audio_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
};

