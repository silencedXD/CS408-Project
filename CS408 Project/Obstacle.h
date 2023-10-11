#pragma once
#include <string>

class Obstacle { 
public:
	Obstacle(int x_, int y_, std::string soundName_);

	int x;
	int y;

	bool soundNotPlayed;
	std::string soundName;
};