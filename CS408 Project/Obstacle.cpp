#include "Obstacle.h"

Obstacle::Obstacle(int x_, int y_, int distance_, int speed_, std::string type_) {
	x = x_;
	y = y_;
	distance = distance_;
	speed = speed_;
	type = type_;
	deleteFlag = false;
}

void Obstacle::Move() {
	distance -= speed;	//Time is considered to be constant so distance is just decremented based on speed
}