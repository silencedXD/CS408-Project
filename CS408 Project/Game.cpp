#include "Game.h"

Game::Game(GraphicsUnit* graphics_, AudioUnit* audio_) {
	graphics = graphics_;
	audio = audio_;
	gameActive = false;
	menuManager = NULL;
}

void Game::updateLoop() {
	if (gameActive) {
		std::cout << "Game active\n";
		gameActive = false;
	}
	else {
		if (menuManager == NULL) {
			menuManager = new LoopManager(graphics, audio);
		}
		menuManager->updateLoop();
		level = menuManager->getState() - controlsOptions;	//ControlsOptions is the last MenuCode before the level codes
		if (level >= 1) {
			gameActive = true;
			delete menuManager;
			menuManager = NULL;
		}
	}
}

void Game::updatePlayer() {}
void Game::updateObjects() {}
void Game::checkCollisions() {}

void Game::updateView() {}
void Game::garbageCollection() {
	gameActive = false;
}