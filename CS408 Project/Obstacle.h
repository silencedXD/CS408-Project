#pragma once
#include <string>
#include <SFML/Audio.hpp>

class Obstacle { 
public:
	Obstacle(int x_, int y_, std::string type_);
	void Move();

	int x;
	int y;

	std::string type;
	bool deleteFlag;
	sf::Sound sound;
};