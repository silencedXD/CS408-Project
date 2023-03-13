#pragma once
#include "KeyCode.h"

class Player {
public:
	Player();
	void Move(KeyCode command);
	void update();
	void scorePoint(int point);

	int moveCounter;
	int x;
	int y;
	bool isHit;
	int scoreMultiplier;
	int score;
};