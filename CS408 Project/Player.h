#pragma once
#include "KeyCode.h"
#include <SFML/Graphics.hpp>

class Player {
public:
	Player();
	Player(sf::Sprite* sprite_);
	void Move(KeyCode command);
	void update();
	void scorePoint(int point);

	sf::Sprite* sprite;
	int moveCounter;
	int x;
	int y;
	bool isHit;
	int scoreMultiplier;
	int score;
};