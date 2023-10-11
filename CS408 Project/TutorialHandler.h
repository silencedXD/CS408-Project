#pragma once
#include "InputHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

class TutorialHandler : public InputHandler
{
public:
	TutorialHandler(UIUnit* UI, ObjectFactory* oFactory, AudioUnit* audio_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
};

