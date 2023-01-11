#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	virtual sf::Sprite* getSprite() = 0;
	virtual sf::Vector2f getPos() = 0;
	virtual void setPos(float x_, float y_) = 0;
	std::string id;
	bool deleteFlag;
};

