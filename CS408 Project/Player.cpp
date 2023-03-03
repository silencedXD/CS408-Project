#include "Player.h"

Player::Player() {
	x = 0;
	y = 1;
	isHit = false;
	moveCounter = 0;
}

void Player::update() {
	if (moveCounter > 0) { moveCounter--; }
	else {
		y = 1;
	}
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
		if (y == 1) { y = 2; }
		moveCounter = 30;
		break;

	case DOWN:
		if (y == 1) { y = 0; }
		moveCounter = 30;
		break;

	default:
		break;
	}
}