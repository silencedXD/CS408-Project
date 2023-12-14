#pragma once
#include <string>
#include "SpriteObject.h"

class Obstacle : public SpriteObject { 
public:
	Obstacle(std::string sountName_, float x_, float y_, std::string id_, sf::Texture* texture_);

	bool soundNotPlayed;
	std::string soundName;
};