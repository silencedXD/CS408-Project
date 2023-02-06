#pragma once
#include <SFML/Window/Event.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "jsoncpp\dist\json\json.h"
#include "GraphicsUnit.h"
#include "MenuCode.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "AudioUnit.h"


class InputHandler
{
public:
	InputHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual void keyPressed(sf::Event event);
	virtual MenuCode updateState() = 0;
	virtual void playTextPrompt() = 0;

	void updateArrow();
	sf::Vector2f setArrowPos(sf::Vector2f newPos_);

	Json::Value loadConfig();
	void saveConfig(Json::Value config_);
protected:
	GraphicsUnit* graphics;
	ObjectFactory* oFactory;
	AudioUnit* audio;
	int selector;
	int totalMenuItems;
};

