#pragma once
#include <SFML/Window/Event.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "jsoncpp\dist\json\json.h"
#include "UIUnit.h"
#include "MenuCode.h"
#include "GameObject.h"
#include "AudioUnit.h"
#include "KeyCode.h"


class InputHandler
{
public:
	InputHandler(UIUnit* UI_, AudioUnit* audio_);
	virtual void keyPressed(sf::Event event);
	virtual MenuCode updateState(sf::Time elapsed) = 0;
	virtual void playTextPrompt() = 0;

	virtual int getScore();
	void updateArrow();
	sf::Vector2f setArrowPos(sf::Vector2f newPos_);

	Json::Value loadConfig();
	void saveConfig(Json::Value config_);
protected:
	void loadKeyMappings();
	sf::Keyboard::Key stringToKeyboard(std::string keyName);
	Json::Value config;
	std::map<KeyCode, sf::Keyboard::Key> keyMappings;
	UIUnit* UI;
	AudioUnit* audio;
	int selector;
	int totalMenuItems;
};

