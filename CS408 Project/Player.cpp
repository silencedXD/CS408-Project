#include "Player.h"

Player::Player(int centre_, float x_, float y_, std::string id_, sf::Texture* texture_) : SpriteObject(x_, y_, id_, texture_){
	isHit = false;
	momentum = 0;
	scoreMultiplier = 1;
	score = 0;
	centre = centre_;
	currentSpeed = 0;
	maxSpeed = 10;
	rotationFactor = 5;
	moveFactor = 5;
	zeroAtValue = 20;
	decayRate = 1;
}

Player::~Player() {}

void Player::Update() {

	UpdateSpeed();
}

void Player::UpdateSpeed() {
	currentSpeed += momentum * moveFactor;
	if (currentSpeed > maxSpeed) {
		currentSpeed = maxSpeed;
	}
	if (currentSpeed < -maxSpeed) {
		currentSpeed = -maxSpeed;
	}
	if (std::abs(currentSpeed) >= maxSpeed / zeroAtValue) {
		UpdatePosition();
		DecaySpeed();
	}
	else {
		currentSpeed = 0;
	}
}

void Player::UpdatePosition() {
	float pi = 3.1415926535897;
	float rotation = sprite.getRotation();
	float xDif = currentSpeed * std::cos(pi / 180 * (rotation - 90));
	float yDif = currentSpeed * std::sin(pi / 180 * (rotation - 90));
	sprite.move(sf::Vector2f(xDif, yDif));

}

void Player::DecaySpeed() {
	if (currentSpeed > maxSpeed / 10) {
		currentSpeed -= decayRate;
	}
	else if (currentSpeed < -maxSpeed / 10) {
		currentSpeed += decayRate;
	}
	else {
		currentSpeed = 0;
	}
}

void Player::ScorePoint(int point) {
	score += point * scoreMultiplier;
}

void Player::Move(KeyCode command) {
	sf::Vector2f pos = getPos();
	float rotation = sprite.getRotation();
	switch (command) {
	case LEFT:
		sprite.rotate(-rotationFactor);
		break;

	case RIGHT:
		sprite.rotate(rotationFactor);
		break;

	case UP:
		momentum = 1;
		break;

	case DOWN:
		momentum = -1;
		break;
		
	default:
		break;
	}
}

void Player::StopMomentum()
{
	momentum = 0;
}