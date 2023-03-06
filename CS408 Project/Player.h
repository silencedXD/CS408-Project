#pragma once
#include "KeyCode.h"

class Player {
public:
	Player();
	void Move(KeyCode command);
	void update();

	int moveCounter;
	int x;
	int y;
	bool isMoving;
	bool isHit;
};