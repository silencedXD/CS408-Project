#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(int x_, int y_);
	int x;
	int y;
	sf::CircleShape image;
};

