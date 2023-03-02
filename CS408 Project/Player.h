#pragma once
#include "KeyCode.h"
#include <SFML/Audio/Listener.hpp>

class Player {
public:
	Player(int level);
	void Move(KeyCode command);
	void Dig();
	void BreakRock(int type);
	void stopX();
	void stopY();

	int xPos;
	int yPos;
	int zPos;

	int points;
	int x_momentum;
	int y_momentum;

	int levelSize;
	bool isHit;
};