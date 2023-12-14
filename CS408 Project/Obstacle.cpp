#include "Obstacle.h"

Obstacle::Obstacle(std::string soundName_, float x_, float y_, std::string id_, sf::Texture* texture_) : SpriteObject(x_, y_, id_, texture_) {
	soundNotPlayed = true;
	soundName = soundName_;
}