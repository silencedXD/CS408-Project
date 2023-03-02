#include <string>
#include "Player.h"

Player::Player(int level) {
	xPos = 0;
	yPos = 2;
	zPos = 0;
	levelSize = level;
	isHit = false;
	points = 0;
	x_momentum = 0;
	y_momentum = 0;
}

void Player::Move(KeyCode command) {
	switch (command) {
	case LEFT:
		x_momentum = -1;
		break;

	case RIGHT:
		x_momentum = 1;
		break;

	case UP:
		y_momentum = 1;
		break;

	case DOWN:
		y_momentum = -1;
		break;

	case ENTER:
		Dig();

	default:
		break;
	}
}

void Player::stopX() { x_momentum = 0; }
void Player::stopY() { y_momentum = 0; }

void Player::Dig() { zPos = (zPos + 1) % levelSize; }

void Player::BreakRock(int type) {
	switch (type) {
	case 0:		//Copper
		points += 100;
		break;

	case 1:		//Iron
		points += 250;
		break;

	case 2:		//Diamond
		points += 1000;
		break;
	}
}