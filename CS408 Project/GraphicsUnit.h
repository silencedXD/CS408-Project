#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"

class GraphicsUnit {

public:
	GraphicsUnit(sf::RenderWindow* window_);

	void CloseWindow();
	void ClearWindow();
	void SetupFrame(sf::Vector2f pos);
	void Draw(sf::Sprite* sprite);
	void Display();
	sf::Texture* LoadTexture(std::string objectName);
	void SetBackgroundColour(sf::Color colour);

private:
	void LoadTextureLocations();
	sf::RenderWindow* window;
	sf::Color backgroundColour;

	std::map<std::string, sf::Texture> textures;
	std::map<std::string, std::string> textureLocations;
};