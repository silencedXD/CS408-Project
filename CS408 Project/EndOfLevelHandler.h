#pragma once
#include "InputHandler.h"

class EndOfLevelHandler : public InputHandler
{
public:
	EndOfLevelHandler(UIUnit* graphics_, AudioUnit* audio_, MenuCode levelCode_, bool win, int playerScore_, int highscore_);
	virtual MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();

private:
	void playScore(int score);
	void playHundreds(int score);
	void playTens(int score);
	void playDigits(int score);

	MenuCode levelCode;
	bool win_;
	int highscore;
	int playerScore;
	int delay;
};

