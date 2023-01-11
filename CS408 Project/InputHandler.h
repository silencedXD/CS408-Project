#pragma once
#include <SFML/Window/Event.hpp>
#include <vector>
#include "GraphicsUnit.h"
#include "MenuCode.h"
#include "ObjectFactory.h"
#include "GameObject.h"

class InputHandler
{
public:
	InputHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_);
	void keyPressed(sf::Event event);
	virtual MenuCode updateState();

protected:
	GraphicsUnit* graphics;
	ObjectFactory* oFactory;
	int selector;
	int totalMenuItems;
};

