#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"

class GraphicsUnit {

public:
	sf::Texture* loadTexture(std::string objectName);
	void setBackgroundColour(sf::Color colour);

private:
	sf::RenderWindow* window;
	sf::Color backgroundColour;

	std::map<std::string, sf::Texture> textures;
	std::map<std::string, std::string> textureLocations;
};