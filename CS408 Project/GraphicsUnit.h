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
private:
	sf::RenderWindow* window;
	sf::Font font;
	int fontSize;	
	std::vector<sf::Text> messages;
};

