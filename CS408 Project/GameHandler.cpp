#include "GameHandler.h"
#include <iostream>
#include <math.h>

GameHandler::GameHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, int level_) : InputHandler(graphics_, oFactory_, audio_) {
	paused = false;
	level = level_;
	levelHeight = 20;
	levelWidth = 10;
	player = new Player(levelHeight);
	int frameCounter = 0;
	generateLevel();

}

void GameHandler::generateLevel() {
	int totalRocks = 2;
	//int totalObstacles = int(level * 0.75 * 5);
	sf::SoundBuffer* buffer = NULL;

	for (int i = 0; i < totalRocks; i++) {
		//int type = rand() % 3;
		int type = 0;
		switch (type) {
		case 0:
			buffer = audio->getBuffer("medium_piano_note");
			break;
		
		case 1:
			buffer = audio->getBuffer("iron_near");
			break;

		case 2:
			buffer = audio->getBuffer("diamond_near");
			break;
		}
		//rocks.push_back(new Rock(rand() % levelSize, rand() % levelSize, rand() % levelSize, type, buffer));
	}
	rocks.push_back(new Rock(5, 5, 0, 0, buffer));
	rocks.push_back(new Rock(12, 12, 0, 0, buffer));
	rocks.push_back(new Rock(24, 24, 0, 0, buffer));
	rocks.push_back(new Rock(36, 36, 0, 0, buffer));
	rocks.push_back(new Rock(48, 48, 0, 0, buffer));
	//Yeet



}

MenuCode GameHandler::updateState(sf::Time elapsed) {

	sf::Time gap = sf::milliseconds(100/6) - elapsed;	//This locks the framerate at 60fps which should also somewhat locks the game speed too
	if (gap.asMilliseconds() > 0) { sf::sleep(gap); }	//which should allow us to assumpe that 1 second in real life equates to 60 game cycles
	frameCounter = (frameCounter + 1) % 60;

	if (paused) {
		paused = false;
		return options;
	}

	if (rocks.empty()) {
		std::cout << "All rocks mined, you win!";
		std::cout << "You scored: " << player->points << " points! Well Done!";
		return mainMenu;
	}


	//We're going to need this to get the sound properly spatialised:
	//https://www.sfml-dev.org/tutorials/2.5/audio-spatialization.php
	
	
	checkCollisions();


	if (frameCounter % 10 == 0) {
		player->xPos = (player->xPos + player->x_momentum + levelWidth) % levelWidth;
		player->yPos = (player->yPos + player->y_momentum + levelHeight) % levelHeight;
		displayStats();
	}

	return getState();
}

void GameHandler::checkCollisions() {
	std::vector<Rock*>::iterator it = rocks.begin();
	
	while (it != rocks.end()) {
		Rock* currentRock = *it;

		if (currentRock->checkCollision(player->xPos, player->yPos, player->zPos)) {
			player->BreakRock(currentRock->type);
			switch (currentRock->type) {
			case 0:
				audio->playConcurrentSound("copper_break");
				break;

			case 1:
				audio->playConcurrentSound("iron_break");
				break;

			case 2:
				audio->playConcurrentSound("diamond_break");
				break;

			default:
				std::cout << "Error: Unkown rock type, can't find break sound";
				break;
			}
			
			delete currentRock;
			it = rocks.erase(it);	//Deleting the element automatically moves the iterator to the following element
		}
		else {
			++it;	//This moves to the next element if it hasn't been deleted
		}
	}
}


void GameHandler::keyPressed(sf::Event event) {
	if (event.key.code == keyMappings.at(UP)) { player->Move(UP); }
	if (event.key.code == keyMappings.at(DOWN)) { player->Move(DOWN); }

	if (event.key.code == keyMappings.at(LEFT)) { player->Move(LEFT); }
	if (event.key.code == keyMappings.at(RIGHT)) { player->Move(RIGHT); }

	if (event.key.code == keyMappings.at(ENTER)) { player->Move(ENTER); }
	if (event.key.code == keyMappings.at(PAUSE)) { paused = true; }
}

void GameHandler::keyReleased(sf::Event event) {
	if (event.key.code == keyMappings.at(LEFT) || event.key.code == keyMappings.at(RIGHT)) {
		player->stopX();
	}
	if (event.key.code == keyMappings.at(UP) || event.key.code == keyMappings.at(DOWN)) {
		player->stopY();
	}
}

void GameHandler::displayStats() {
	std::cout << "\nPlayer x: " << std::to_string(player->xPos);
	std::cout << "   y: " << std::to_string(player->yPos);
	std::cout << "   z: " << std::to_string(player->zPos);

	//for (int i = 0; i < rocks.size(); i++) {

	//	std::cout << "\nObstacle" << i;
	//	std::cout << "\n  x: " << std::to_string(rocks[i]->x);
	//	std::cout << "\n  y: " << std::to_string(rocks[i]->y);
	//	std::cout << "\n  z: " << std::to_string(rocks[i]->z);
	//	std::cout << "\n\n";
	//}
}

bool GameHandler::isNearPlayer(Rock* obstacle) {
	if (obstacle->x == player->xPos) {
		if (obstacle->y == player->yPos) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

void GameHandler::playTextPrompt() {
}

MenuCode GameHandler::getState() {
	switch (level) {
	case 1:
		return level1;

	case 2:
		return level2;

	case 3:
		return level3;

	default:
		std::cout << "Error: Unknown level code";
		return mainMenu;
	}
}