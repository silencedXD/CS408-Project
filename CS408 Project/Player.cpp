#include "Player.h"

Player::Player(float x_, float y_, std::string id_, sf::Texture* texture_) : SpriteObject(x_, y_, id_, texture_){
	isHit = false;
	moveCounter = 0;
	scoreMultiplier = 1;
	score = 0;
}

Player::~Player() {}

void Player::update() {
	if (moveCounter > 0) { moveCounter--; }
	else {
		sf::Vector2f pos = getPos();
		setPos(pos.x, 2);
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
		if (pos.y < 4) { sprite.move(sf::Vector2f(0, 1)); }
		moveCounter = 20;
		break;

	case DOWN:
		if (pos.y > 0) { sprite.move(sf::Vector2f(0, -1)); }
		moveCounter = 30;
		break;
		
	default:
		break;
	}
}