#include "Obstacle.h"

Obstacle::Obstacle(int x_, int y_, std::string soundName_) {
	x = x_;
	y = y_;
	soundNotPlayed = true;
	soundName = soundName_;
}

void Obstacle::Move() {
	x--;	//Time is considered to be constant so distance is just decremented based on speed
}