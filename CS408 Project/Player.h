#pragma once
#include "KeyCode.h"
#include "GraphicsUnit.h"
#include "SpriteObject.h"

class Player : public SpriteObject {
public:
	Player(int centre, float x_, float y_, std::string id_, sf::Texture* texture_);
	~Player();
	void Move(KeyCode command);
	void update();
	void scorePoint(int point);

	int centre;
	int moveSize;
	bool isHit;
	int scoreMultiplier;
	int score;
};