#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "GameObject.h"

class SpriteObject : public virtual GameObject
{
public:
	SpriteObject(float x_, float y_, std::string id_, sf::Texture* texture_);
	virtual sf::Sprite* getSprite();
	virtual sf::Vector2f getPos();
	virtual void setPos(float x_, float y_);
private:
	sf::Sprite sprite;
	std::vector<std::string> sounds;
};

