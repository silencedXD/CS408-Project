#pragma once
#include "InputHandler.h"

class AudioOptionsHandler : public InputHandler
{
public:
	AudioOptionsHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_);
	void changeOption();

	void keyPressed(sf::Event event);

	MenuCode updateState();

	void playTextPrompt();

private:
	enum audioOptionsEnum { general, text, game, empty };

	sf::Vector2f arrowPos;
	audioOptionsEnum state;
	std::vector<float> volumeSettings;

	float currentGeneralVolume;
	float currentTextVolume;
	float currentGameVolume;

	bool generalFlag;
	bool textFlag;
	bool gameFlag;

	int optionPointer;
};

