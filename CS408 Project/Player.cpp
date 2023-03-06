#include "Player.h"

Player::Player() {
	x = 0;
	y = 1;
	isHit = false;
	moveCounter = 0;
	isMoving = false;
}

void Player::update() {
	if (moveCounter > 0) { moveCounter--; }
	else {
		y = 1;
	}
	if (isMoving) {
		x++;
	}
}

void Player::Move(KeyCode command) {
	switch (command) {
	case UP:
		if (isMoving) {
			if (y == 1) { y = 2; }
			moveCounter = 30;
			break;
		}
		else {
			isMoving = true;
			break;
		}

	case DOWN:
		if (isMoving) {
			if (y == 1) { y = 0; }
			moveCounter = 30;
			break;
		}
		else {
			isMoving = true;
			break;
		}
		
	default:
		break;
	}
}