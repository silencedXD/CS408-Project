#pragma once
#include "InputHandler.h"


class VideoOptionsHandler : public InputHandler
{
public:
	VideoOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	virtual MenuCode updateState();
	void playTextPrompt();
	void changeOption();
	void keyPressed(sf::Event event);

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

	std::tuple<unsigned int, unsigned int, unsigned int> currentDisplaySize;
	std::string currentFontType;
	int currentFontSize;

	bool displaySizeFlag;
	bool fontTypeFlag;
	bool fontSizeFlag;

	Json::Value config;
};