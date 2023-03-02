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
#include "KeyCode.h"


class InputHandler
{
public:
	InputHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual void keyPressed(sf::Event event);
	virtual MenuCode updateState(sf::Time elapsed) = 0;
	virtual void playTextPrompt() = 0;
	virtual void keyReleased(sf::Event event);
	void updateArrow();
	sf::Vector2f setArrowPos(sf::Vector2f newPos_);

	Json::Value loadConfig();
	void saveConfig(Json::Value config_);
	virtual MenuCode getState() = 0;
protected:
	void loadKeyMappings();
	sf::Keyboard::Key stringToKeyboard(std::string keyName);
	Json::Value config;
	std::map<KeyCode, sf::Keyboard::Key> keyMappings;
	GraphicsUnit* graphics;
	ObjectFactory* oFactory;
	AudioUnit* audio;
	int selector;
	int totalMenuItems;
};

