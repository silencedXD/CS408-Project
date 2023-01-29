#pragma once
#include "InputHandler.h"
#include <fstream>
#include <iostream>
#include "jsoncpp\dist\json\json.h"

class VideoOptionsHandler : public InputHandler
{
public:
	VideoOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual MenuCode updateState();
	void playTextPrompt();
	void changeOption();
	void keyPressed(sf::Event event);
	Json::Value loadConfig();
	void saveConfig(Json::Value config_);

	enum videoOptionsEnum	{displaySize, fontType, fontSize, empty};
	std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> displayModes;
	std::vector<std::string> displayModeSounds;

	std::vector<std::string> fontTypes;

	std::vector<int> fontSizes;
	std::vector<std::string> fontSizeSounds;

	sf::Vector2f arrowPos;
	int optionPointer;
	int optionTotal;
	videoOptionsEnum state;
	std::tuple<unsigned int, unsigned int, unsigned int> tempDisplaySize;
	std::string tempFontType;
	int tempFontSize;
	Json::Value config;
};