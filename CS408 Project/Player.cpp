#include "Player.h"

Player::Player() {
	x = 2;
	y = 2;
	isHit = false;
}

void Player::Move(KeyCode command) {
	switch (command) {
	case LEFT:
		x = (x - 1) % 5;
		break;

	case RIGHT:
		x = (x + 1) % 5;
		break;

	case UP:
		y = (y + 1) % 5;
		break;

	case DOWN:
		y = (y - 1) % 5;
		break;

	case ENTER:
		x = 2;
		y = 2;

	default:
		break;
	}
}