#pragma once
#include <string>

class Obstacle { 
public:
	Obstacle(int x_, int y_, int distance_, int speed_, std::string type_);
	void Move();

	int x;
	int y;
	int distance;	//Distance from player
	int speed;
	std::string type;
	bool deleteFlag;
};