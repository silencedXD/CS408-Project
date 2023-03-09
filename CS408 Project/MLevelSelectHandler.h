#pragma once
#include "InputHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

class MLevelSelectHandler : public InputHandler
{
public:
	MLevelSelectHandler(GraphicsUnit* graphics, ObjectFactory* oFactory, AudioUnit* audio_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
};

