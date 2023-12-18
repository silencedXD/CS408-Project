#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "SpriteObject.h"


class UIUnit
{
public:
	UIUnit(sf::RenderWindow* window_, std::string fontName, int fontSize, sf::Color backgroundColour_);
	~UIUnit();
	void CloseWindow();
	void ClearWindow();
	void Update();
	sf::Vector2u GetWindowSize();

	void MakeLabel(std::string message_, float x_, float y_);
	void RemoveLastLabel();
	sf::Text GetLastLabel();
	void ClearText();
	
	sf::RenderWindow* GetWindow();

	std::string GetFontType();
	bool LoadFont(std::string fontName);
	int GetFontSize();
	void SetBackgroundColour(sf::Color colour);


	void ChangeDisplaySize(std::tuple<unsigned int, unsigned int, unsigned int> displaySize_);
	void ChangeFontType(std::string fontName_);
	void ChangeFontSize(int size_);

	SpriteObject* arrow;

private:
	sf::RenderWindow* window;
	sf::Font font;
	int fontSize;	
	std::vector<sf::Text> messages;
	sf::Texture arrowTexture;
	std::string fontName;
	sf::Color backgroundColour;
};

