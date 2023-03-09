#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, int level_) : InputHandler(graphics_, oFactory_, audio_) {
	paused = false;
	player = Player();
	frameCounter = 0;
	level = level_;
	hearingRange = 25 + (20 / level);
	int obstacleCount = level *  5;
	srand(time(NULL));

	for (int i = 0; i < obstacleCount; i++) {
		int yVal = rand() % 2;
		if (yVal == 0) {
			int xVal = rand() % 10;
			obstacles.push_back(new Obstacle(50 + (i * 75) + xVal, 0, "4C"));
		}
		else {
			int xVal = rand() % 10;
			obstacles.push_back(new Obstacle(50 + (i * 75) + xVal, 2, "5C"));
		}
	}
}

MenuCode GameHandler::updateState(sf::Time elapsed) {

	sf::Time gap = sf::milliseconds(100 / 6) - elapsed;	//This locks the framerate at 60fps which should also somewhat locks the game speed too
	if (gap.asMilliseconds() > 0) { sf::sleep(gap); }	//which should allow us to assumpe that 1 second in real life equates to 60 game cycles

	frameCounter = (frameCounter + 61) % 60;

	if (paused) {
		paused = false;
		return options;
	}

	updateKeys();
	player.update();
	checkCollisions();

	if (checkLoseCondition()) {
		return lose;
	}

	if (checkWinCondition()) {
		return win;
	}


	displayStats();
	return game;
}

bool GameHandler::checkWinCondition() {
	if (obstacles.empty()) {
		std::cout << "All obstacles dodged, you win!";
		setArrowPos(sf::Vector2f(0, 0));	//This moves the arrow back in vue for the menu system
		return true;
	}
	else {
		return false;
	}
}

bool GameHandler::checkLoseCondition() {
	if (player.isHit) {
		std::cout << "Game Over";
		setArrowPos(sf::Vector2f(0, 0));	//This moves the arrow back in vue for the menu system
		return true;
	}
	else{
		return false;
	}
}

void GameHandler::updateKeys() {
	if (sf::Keyboard::isKeyPressed(keyMappings.at(UP))) { player.Move(UP); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(DOWN))) { player.Move(DOWN); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(LEFT))) { player.Move(LEFT); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(RIGHT))) { player.Move(RIGHT); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(ENTER))) { player.Move(ENTER); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(PAUSE))) { paused = true; }
}

void GameHandler::checkCollisions() {
	std::vector<Obstacle*>::iterator it = obstacles.begin();

	while (it != obstacles.end()) {
		Obstacle* currentObstacle = *it;

		if (currentObstacle->x != player.x) {
			if (currentObstacle->y == player.y) {
				player.isHit = true;
				audio->playSound("fail");
				delete currentObstacle;
				it = obstacles.erase(it);
			}
		}
		else {
			if (isNearPlayer(currentObstacle)) {
				if (currentObstacle->soundNotPlayed) {
					audio->playNonRepeatingSound(currentObstacle->soundName);
					currentObstacle->soundNotPlayed = false;
				}

			}
			++it;	//This moves to the next element if it hasn't been deleted
		}
		
	}
}

bool GameHandler::isNearPlayer(Obstacle* obstacle) {
	int xDif = obstacle->x - player.x;
	if (0 < xDif && xDif < hearingRange) {
		return true;
	}
	else {
		return false;
	}
}


void GameHandler::keyPressed(sf::Event event) {
	//if (event.key.code == keyMappings.at(UP)) { player.Move(UP); }
	//if (event.key.code == keyMappings.at(DOWN)) { player.Move(DOWN); }
	//if (event.key.code == keyMappings.at(LEFT)) { player.Move(LEFT); }
	//if (event.key.code == keyMappings.at(RIGHT)) { player.Move(RIGHT); }
	//if (event.key.code == keyMappings.at(ENTER)) { player.Move(ENTER); }
	//if (event.key.code == keyMappings.at(PAUSE)) { paused = true; }
	

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
	if (obstacle->x == 0) {
		if (obstacle->y == player.y) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

void GameHandler::playTextPrompt() {
}