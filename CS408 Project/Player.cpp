#include "Player.h"

Player::Player() {
	x = 2;
	y = 1;
	isHit = false;
}

void Player::Move(KeyCode command) {
	switch (command) {
	case LEFT:
		if (x > 0) { x--; }
		break;

	case RIGHT:
		if (x < 5) { x++; }
		break;

	case UP:
		if (y < 5) { y++; }
		break;

	case DOWN:
		if (y > 1) { y--; }
		break;

	case ENTER:
		x = 2;
		y = 1;

	default:
		break;
	}
}