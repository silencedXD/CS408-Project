#pragma once
#include <SFML/Window/Event.hpp>
#include <vector>
#include "GraphicsUnit.h"
#include "MenuCode.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "AudioUnit.h"
#include <iostream>

class InputHandler
{
public:
	InputHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	void keyPressed(sf::Event event);
	virtual MenuCode updateState() = 0;
	virtual void playTextPrompt() = 0;
	void updateArrow();
protected:
	GraphicsUnit* graphics;
	ObjectFactory* oFactory;
	AudioUnit* audio;
	int selector;
	int totalMenuItems;
};

