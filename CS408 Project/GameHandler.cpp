#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) : InputHandler(graphics_, oFactory_, audio_) {
	paused = false;
	player = Player();
	int obstacleCount = 10;

	for (int i = 0; i < obstacleCount; i++) {
		obstacles.push_back(new Obstacle(rand() % 5, 1, rand() % 180 + 60, 1, "test"));
	}
}

MenuCode GameHandler::updateState(sf::Time elapsed) {

	sf::Time gap = sf::milliseconds(100/6) - elapsed;	//This locks the framerate at 60fps which should also lock the game speed too
	if (gap.asMilliseconds() > 0) { sf::sleep(gap); }

	if (paused) {
		paused = false;
		return options;
	}

	if (obstacles.empty()) {
		std::cout << "All obstacles dodged, you win!";
		return mainMenu;
	}

	checkCollisions();

	if (player.isHit) {
		std::cout << "Game Over";

		return mainMenu;
	}
	else {
		displayStats();

		return game;
	}
}

void GameHandler::checkCollisions() {
	std::vector<Obstacle*>::iterator it = obstacles.begin();

	while (it != obstacles.end()) {
		Obstacle* currentObstacle = *it;
		currentObstacle->Move();

		if (currentObstacle->distance == 0) {
			if (isInfrontOf(currentObstacle)) {
				player.isHit = true;
				//audio->playConcurrentSound("crash");
			}
		}

		if (currentObstacle->distance < 0) {
			delete currentObstacle;
			it = obstacles.erase(it);	//Deleting the element automatically moves the iterator to the following element
		}
		else {
			if (isInfrontOf(currentObstacle) && currentObstacle->distance < 60)	//Since game is at roughly 60fps, a distance of 60 should be about 1 second away from collision
			{
				//audio->playConcurrentSound("Nearby");
			}
			++it;	//This moves to the next element if it hasn't been deleted
		}
	}
}


void GameHandler::keyPressed(sf::Event event) {
	if (event.key.code == keyMappings.at(UP)) { player.Move(UP); }
	if (event.key.code == keyMappings.at(DOWN)) { player.Move(DOWN); }
	if (event.key.code == keyMappings.at(LEFT)) { player.Move(LEFT); }
	if (event.key.code == keyMappings.at(RIGHT)) { player.Move(RIGHT); }
	if (event.key.code == keyMappings.at(ENTER)) { player.Move(ENTER); }
	if (event.key.code == keyMappings.at(PAUSE)) { paused = true; }
}

void GameHandler::displayStats() {
	std::cout << "\nPlayer x: " << std::to_string(player.x);
	std::cout << "   y: " << std::to_string(player.y);/*
	std::cout << "     isHit: " << std::to_string(player.isHit) << "\n";
	for (int i = 0; i < obstacles.size(); i++) {
		std::cout << "\n Obstacle" << i << "  distance: " << std::to_string(obstacles[i]->distance);
		std::cout << "  x: " << std::to_string(obstacles[i]->x);
		std::cout << "  y: " << std::to_string(obstacles[i]->y) << "\n";
	}*/
}

bool GameHandler::isInfrontOf(Obstacle* obstacle) {
	if (obstacle->x == player.x) {
		if (obstacle->y == player.y) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

void GameHandler::playTextPrompt() {
}