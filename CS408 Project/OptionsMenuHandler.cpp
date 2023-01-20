#include "OptionsMenuHandler.h"
#include <iostream>

OptionsMenuHandler::OptionsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {
	totalMenuItems = 1;
}

void OptionsMenuHandler::keyPressed(sf::Event event) {}

MenuCode OptionsMenuHandler::updateState() {
	std::cout << "Options selected\n";
	return mainMenu;
}

void OptionsMenuHandler::playTextPrompt() {
	switch (selector) {//TODO CREATE SOUND FILES AND ADD THEM
		/*
	case 0:
			audio->playSound("options");
			break;

		case 10:
			audio->playSound("display");
			break;

		case 20:
			audio->playSound("audio");
			break;

		case 30:
			audio->playSound("controls");
			break;

		case 40:
			audio->playSound("quit");
			break;
			*/
		default:
			break;
	}
}