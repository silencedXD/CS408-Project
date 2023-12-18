#pragma once
#include "KeyCode.h"
#include "GraphicsUnit.h"
#include "SpriteObject.h"

class Player : public SpriteObject {
public:
	Player(int centre, float x_, float y_, std::string id_, sf::Texture* texture_);
	~Player();
	void Move(KeyCode command);
	void Update();
	void ScorePoint(int point);
	void UpdateSpeed();
	void UpdatePosition();
	void DecaySpeed();
	void StopMomentum();

	int decayRate;
	int zeroAtValue;
	int rotationFactor;
	float currentSpeed;
	float maxSpeed;
	int centre;
	int momentum;
	int moveFactor;
	bool isHit;
	int scoreMultiplier;
	int score;

};