#pragma once
#include "InputHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

class LevelSelectHandler : public InputHandler
{
public:
	LevelSelectHandler(GraphicsUnit* graphics, ObjectFactory* oFactory, AudioUnit* audio_);
	MenuCode updateState();
};

