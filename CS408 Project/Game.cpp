#include "Game.h"

Game::Game(GraphicsUnit* graphics_, AudioUnit* audio_) {
	graphics = graphics_;
	audio = audio_;
	paused = true;
	levelNotLoaded = true;
	menuManager = NULL;
}

void Game::updateLoop() {

	if (paused) {
		if (menuManager == NULL) {
			menuManager = new LoopManager(graphics, audio);
		}
		menuManager->updateLoop();
		level = menuManager->getState() - controlsOptions;	//ControlsOptions is the last MenuCode before the level codes
		if (level >= 1) {
			paused = false;
			delete menuManager;
			menuManager = NULL;
		}
	}
	else {
		if (levelNotLoaded) {
			loadLevel();
			levelNotLoaded = false;
		}
		else{
			updateGame();
		}
		std::cout << "Game active\n";
		
		//TODO: remove this once actual game is implemented
		paused = true;
	}
}

void Game::loadLevel() {
	
}

void Game::updateGame() {}

void Game::updatePlayer() {}
void Game::updateObjects() {}
void Game::checkCollisions() {}

void Game::updateView() {}
void Game::garbageCollection() {}