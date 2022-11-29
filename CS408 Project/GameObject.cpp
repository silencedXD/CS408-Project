#include "GameObject.h"

GameObject::GameObject(int x_, int y_) {
	x = x_;
	y = y_;
	image = sf::CircleShape (100.f);
	image.setPosition(100, 100);
}