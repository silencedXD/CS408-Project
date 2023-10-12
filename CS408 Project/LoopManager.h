#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "UIUnit.h"
#include "AudioUnit.h"


class LoopManager
{
public:
	LoopManager(UIUnit* UI_, AudioUnit* audio_);
	void updateLoop();
	void changeState(MenuCode state_);
	MenuCode getState();

private:
	Json::Value loadConfig();
	int loadHighscore();
	void saveHighscore(int highscore);
	int highscore;
	int playerScore;

	sf::RenderWindow* window;
	InputHandler* handler;
	MenuCode currentState;
	AudioUnit* audio;
	UIUnit* UI;

	InputHandler* pausedGame;
	MenuCode selectedLevel;
};