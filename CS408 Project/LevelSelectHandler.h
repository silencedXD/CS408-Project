#pragma once
#include "InputHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

class LevelSelectHandler : public InputHandler
{
public:
	LevelSelectHandler(UIUnit* UI, ObjectFactory* oFactory, AudioUnit* audio_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
};

