#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class UIUnit
{
public:
	UIUnit(sf::RenderWindow* window_, std::string fontName, int fontSize, sf::Color backgroundColour_);
	void closeWindow();
	void clearWindow();
	void update(std::vector<GameObject*> objects);
	sf::Vector2u getWindowSize();

	void makeLabel(std::string message_, float x_, float y_);
	void removeLastLabel();
	sf::Text getLastLabel();
	void clearText();
	sf::Texture* loadTexture(std::string objectName);
	
	sf::RenderWindow* getWindow();

	std::string getFontType();
	bool loadFont(std::string fontName);
	int getFontSize();
	void setBackgroundColour(sf::Color colour);


	void changeDisplaySize(std::tuple<unsigned int, unsigned int, unsigned int> displaySize_);
	void changeFontType(std::string fontName_);
	void changeFontSize(int size_);

private:
	sf::RenderWindow* window;
	sf::Font font;
	int fontSize;	
	std::vector<sf::Text> messages;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, std::string> textureLocations;
	std::string fontName;
	sf::Color backgroundColour;
};

