#pragma once
#include <string>
#include <SFML/Audio.hpp>

class Rock { 
public:
	Rock(int x_, int y_, int z_, int type_, sf::SoundBuffer* buffer);

	bool checkCollision(int player_x, int player_y, int player_z);

	int x;
	int y;
	int z;
	int range;

	int type;
	bool deleteFlag;
private:
	int calcDistance(int x, int player_x);
	bool isNearPlayer(int player_x, int player_y, int player_z);
	sf::Sound sound;
};