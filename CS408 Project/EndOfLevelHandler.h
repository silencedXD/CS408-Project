#pragma once
#include "InputHandler.h"

class EndOfLevelHandler : public InputHandler
{
public:
	EndOfLevelHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_, bool win, int playerScore_, int highscore_);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();

private:
	void playScore(std::string scoreName);
	MenuCode levelCode;
	bool win_;
	int highscore;
	int playerScore;
	int delay;
};
