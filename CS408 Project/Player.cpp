#include "Player.h"

Player::Player(int centre_, float x_, float y_, std::string id_, sf::Texture* texture_) : SpriteObject(x_, y_, id_, texture_){
	isHit = false;
	moveSize = 0;
	scoreMultiplier = 1;
	score = 0;
	centre = centre_;
}

Player::~Player() {}

void Player::update() {
	if (moveSize != 0)
	{
		if (getPos().y == centre) 
		{ moveSize = 0; }
		else 
		{
			sprite.move(sf::Vector2f(0, -moveSize));
		}
	}
}

void Player::scorePoint(int point) {
	score += point * scoreMultiplier;
}

void Player::Move(KeyCode command) {
	sf::Vector2f pos = getPos();
	switch (command) {
	case LEFT:
		if (pos.x > 0) { sprite.move(sf::Vector2f(-1, 0)); }
		break;

	case RIGHT:
		sprite.move(sf::Vector2f(1, 0));
		break;

	case UP:
		if (pos.y <= centre) {
			moveSize = 5;
			sprite.move(sf::Vector2f(0, moveSize * 10));
		}
		break;

	case DOWN:
		if (pos.y >= centre) { 
			moveSize = -5;
			sprite.move(sf::Vector2f(0, moveSize * 10));
		}
		break;
		
	default:
		break;
	}
}