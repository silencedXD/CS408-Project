#include "SpriteObject.h"

SpriteObject::SpriteObject(float x_, float y_, std::string id_, sf::Texture* texture_){
	sprite.setTexture(*texture_);
	sprite.setPosition(x_, y_);
	id = id_;
	deleteFlag = false;
}


sf::Sprite* SpriteObject::getSprite() {
	return &sprite;
}

sf::Vector2f SpriteObject::getPos() {
	return sprite.getPosition();
}

void SpriteObject::setPos(float x_, float y_) {
	sprite.setPosition(x_, y_);
}