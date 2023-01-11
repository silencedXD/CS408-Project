#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "GraphicsUnit.h"
#include "ObjectFactory.h"

class LoopManager
{
public:
	LoopManager(sf::RenderWindow* window_, GraphicsUnit* unit);
	void updateLoop();
	void changeState(MenuCode state_);
private:
	sf::RenderWindow* window;
	InputHandler* handler;
	MenuCode state;
	int audio;
	GraphicsUnit* graphics;
	ObjectFactory* oFactory;
};

