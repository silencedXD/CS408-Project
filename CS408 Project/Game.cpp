#include "Game.h"

Game::Game(GraphicsUnit* graphics_, AudioUnit* audio_) {
	graphics = graphics_;
	audio = audio_;
	gameActive = false;
	menuManager = nullptr;
}

void Game::updateLoop() {
	if (gameActive) {
		std::cout << "Game active";
	}
	else {
		if (menuManager == nullptr) {
			menuManager = new LoopManager(graphics, audio);
		}
		menuManager->updateLoop();
	}
}

void Game::updatePlayer() {}
void Game::updateObjects() {}
void Game::checkCollisions() {}

void Game::updateView() {}
void Game::garbageCollection() {
	gameActive = false;
}