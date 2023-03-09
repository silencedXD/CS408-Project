#pragma once
#include <string>
#include <SFML/Audio.hpp>

class Obstacle { 
public:
	Obstacle(int x_, int y_, std::string soundName_);
	void Move();

	int x;
	int y;

	bool soundNotPlayed;
	std::string soundName;
	bool deleteFlag;
};