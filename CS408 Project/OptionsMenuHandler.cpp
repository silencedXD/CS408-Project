#include "OptionsMenuHandler.h"
#include <iostream>

OptionsMenuHandler::OptionsMenuHandler(UIUnit* graphics_, AudioUnit* audio_) : InputHandler(graphics_, audio_) {
	sf::Vector2f windowSize = sf::Vector2f(UI->getWindowSize().x, UI->getWindowSize().y);
	UI->makeLabel("Options", 0, 0);
	UI->makeLabel("Video", 0, windowSize.y * 0.25f);
	UI->makeLabel("Audio", 0, windowSize.y * 0.45f);
	UI->makeLabel("Controls", 0, windowSize.y * 0.65f);
	UI->makeLabel("Go back", 0, windowSize.y * 0.85f);
}



MenuCode OptionsMenuHandler::updateState(sf::Time elapsed) {
	updateArrow();

	switch (selector) {
	case 15:
		return videoOptions;

	case 25:
		return audioOptions;

	case 35:
		return controlsOptions;

	case 45:
		return mainMenu;

	default:
		return options;
	}
}

void OptionsMenuHandler::playTextPrompt() {
	switch (selector) {
	case 0:
		audio->playSound("options");
		break;

	case 10:
		audio->playSound("video");
		break;

	case 20:
		audio->playSound("audio");
		break;

	case 30:
		audio->playSound("controls");
		break;

	case 40:
		audio->playSound("go_back");
		break;
			
	default:
		std::cout << "Error tried to play text prompt when selector is out of bounds\n";
		break;
	}
}