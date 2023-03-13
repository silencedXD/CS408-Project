#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "GraphicsUnit.h"
#include "ObjectFactory.h"
#include "AudioUnit.h"


class LoopManager
{
public:
	LoopManager(GraphicsUnit* graphics_, AudioUnit* audio_);
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
	GraphicsUnit* graphics;
	ObjectFactory* oFactory;

	InputHandler* pausedGame;
	MenuCode selectedLevel;
};

