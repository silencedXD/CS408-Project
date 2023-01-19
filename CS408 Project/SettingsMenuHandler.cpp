#include "SettingsMenuHandler.h"
#include <iostream>

SettingsMenuHandler::SettingsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {
	totalMenuItems = 1;
}

void SettingsMenuHandler::keyPressed(sf::Event event) {}

MenuCode SettingsMenuHandler::updateState() {
	std::cout << "Options selected\n";
	return mainMenu;
}

void SettingsMenuHandler::playTextPrompt() {
	switch (selector) {
		case 10:
			std::cout << "Add text prompts";
			break;
		default:
			break;
	}
}