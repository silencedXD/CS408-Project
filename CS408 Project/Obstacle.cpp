#include "Obstacle.h"

Obstacle::Obstacle(int x_, int y_, std::string type_) {
	x = x_;
	y = y_;

	type = type_;
	deleteFlag = false;
}

void Obstacle::Move() {
	x--;	//Time is considered to be constant so distance is just decremented based on speed
}