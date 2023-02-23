#pragma once
#include "KeyCode.h"

class Player {
public:
	Player();
	void Move(KeyCode command);

	int x;
	int y;
	bool isHit;
};