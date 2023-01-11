#include "SettingsMenuHandler.h"
#include <iostream>

SettingsMenuHandler::SettingsMenuHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_) : InputHandler(graphics_, oFactory_) {
	totalMenuItems = 1;
}

void SettingsMenuHandler::keyPressed(sf::Event event) {}

MenuCode SettingsMenuHandler::updateState() {
	std::cout << "Options selected\n";
	return mainMenu;
}