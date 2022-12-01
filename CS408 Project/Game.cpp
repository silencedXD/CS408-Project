#include "Game.h"

Game::Game(int level_) {
	level = level_;
	gameState = true;

}

bool Game::gameActive() {
	return gameState;
}

void Game::updatePlayer() {}
void Game::updateObjects() {}
void Game::checkCollisions() {}
void Game::updateSound() {}
void Game::updateView() {}
void Game::garbageCollection() {
	gameState = false;
}