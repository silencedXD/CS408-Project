#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class GraphicsUnit
{
public:
	GraphicsUnit(sf::RenderWindow* window_, std::string fontName, int fontSize);
	bool loadFont(std::string fontName);
	void changeFontSize(int size);
	void closeWindow();
	void clearWindow();
	void update(std::vector<GameObject*> objects);
	sf::Vector2u getWindowSize();
	void makeLabel(std::string message_, float x_, float y_);
	void clearText();
	sf::Texture* loadTexture(std::string objectName);
private:
	sf::RenderWindow* window;
	sf::Font font;
	int fontSize;	
	std::vector<sf::Text> messages;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, std::string> textureLocations;
};

