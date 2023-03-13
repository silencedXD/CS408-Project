#include "Player.h"

Player::Player() {
	x = 0;
	y = 2;
	isHit = false;
	moveCounter = 0;
	scoreMultiplier = 1;
	score = 0;
}

void Player::update() {
	if (moveCounter > 0) { moveCounter--; }
	else {
		y = 2;
	}
}

void Player::scorePoint(int point) {
	score += point * scoreMultiplier;
}

void Player::Move(KeyCode command) {
	switch (command) {
	case LEFT:
		if (x > 0) { x--; }
		break;

	case RIGHT:
		x = x++;
		break;

	case UP:
		if (y < 4) { y++; }
		moveCounter = 20;
		break;

	case DOWN:
		if (y > 0) { y--; }
		moveCounter = 30;
		break;
		
	default:
		break;
	}
}