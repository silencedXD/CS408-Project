#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_) : InputHandler(graphics_, oFactory_, audio_) {
	paused = false;
	player = Player();
	frameCounter = 0;
	levelCode = levelCode_;
	hearingRange = 30;
	srand(time(NULL));

	switch (levelCode) {	//Reaction levels have a smaller hearing range based on level
	case rLevel1:
		level = 1;
		hearingRange = 45 - (5 * level);
		generateLevel();
		break;
		
	case rLevel2:
		level = 2;
		hearingRange = 45 - (5 * level);
		generateLevel();
		break;

	case rLevel3:
		level = 3;
		hearingRange = 45 - (5 * level);
		generateLevel();
		break;

	case mLevel1:			//Melodic levels have the same hearing range
		level = 1;
		loadLevel();
		break;

	case mLevel2:
		level = 2;
		loadLevel();
		break;

	case mLevel3:
		level = 3;
		loadLevel();
		break;

	default:
		level = 1;
		std::cout << "Error: Unknown error code";
		break;
	}
}

void GameHandler::generateLevel() {
	int obstacleCount = level * 5;
	for (int i = 0; i < obstacleCount; i++) {
		int yVal = rand() % 2;
		int xVal = rand() % 10;
		if (yVal == 0) {
			obstacles.push_back(new Obstacle(50 + (i * 70) + xVal, 1, "4C"));
		}
		else {
			obstacles.push_back(new Obstacle(50 + (i * 70) + xVal, 3, "5C"));
		}
	}
}

void GameHandler::loadLevel() {
	//Same as loading config files
	std::string level_dir = "Levels/level" + std::to_string(level) + ".json";
	std::ifstream file(level_dir);
	Json::Value level_contents;
	Json::Reader jsonReader;
	jsonReader.parse(file, level_contents);

	//First we read in the obstacles
	int totalObstacles = level_contents["total_obstacles"].asInt();
	for (int i = 0; i < totalObstacles; i++) {
		std::string obstacleName = "obstacle" + std::to_string(i);

		int xPos = level_contents[obstacleName]["x"].asInt();
		int yPos = level_contents[obstacleName]["y"].asInt();
		std::string soundName = level_contents[obstacleName]["soundName"].asString();

		obstacles.push_back(new Obstacle(xPos, yPos, soundName));
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
	//Up and down keys are only processed when pressed so as to have single increments, whereas moving right needs to be continuous

	//if (sf::Keyboard::isKeyPressed(keyMappings.at(UP))) { player.Move(UP); }
	//if (sf::Keyboard::isKeyPressed(keyMappings.at(DOWN))) { player.Move(DOWN); }
	
	
	if (sf::Keyboard::isKeyPressed(keyMappings.at(LEFT))) { player.Move(LEFT); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(RIGHT))) { player.Move(RIGHT); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(ENTER))) { player.Move(ENTER); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(PAUSE))) { paused = true; }
}

void GameHandler::checkCollisions() {
	std::vector<Obstacle*>::iterator it = obstacles.begin();

	while (it != obstacles.end()) {
		Obstacle* currentObstacle = *it;

		if (currentObstacle->x == player.x) {
			if (currentObstacle->y != player.y) {
				player.isHit = true;
				audio->playSound("fail");
				return;
			}
			delete currentObstacle;
			it = obstacles.erase(it);
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
	if (event.key.code == keyMappings.at(UP)) { player.Move(UP); }
	if (event.key.code == keyMappings.at(DOWN)) { player.Move(DOWN); }
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