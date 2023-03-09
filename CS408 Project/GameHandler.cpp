#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_) : InputHandler(graphics_, oFactory_, audio_) {
	paused = false;
	player = Player();
	levelCode = levelCode_;
	hearingRange = 40;
	srand(time(NULL));

	switch (levelCode) {
	case level1:
		level = 1;
		break;
		
	case level2:
		level = 2;
		break;

	case level3:
		level = 3;
		break;

	default:
		level = 1;
		std::cout << "Error: Unknown error code";
		break;
	}

	hearingRange = 45 - (5 * level);
	generateLevel();
}

void GameHandler::generateLevel() {
	int obstacleCount = level * 5;
	for (int i = 0; i < obstacleCount; i++) {
		int yVal = rand() % 2;
		int xVal = rand() % 10;
		if (yVal == 0) {
			obstacles.push_back(new Obstacle(50 + (i * 70) + xVal, 1, "3C"));
		}
		else {
			obstacles.push_back(new Obstacle(50 + (i * 70) + xVal, 3, "5C"));
		}
	}
}

MenuCode GameHandler::updateState(sf::Time elapsed) {

	//This locks the framerate at 60fps which should also somewhat locks the game speed too
	//which should allow us to assume that 1 second in real life equates to 60 game cycles

	sf::Time gap = sf::milliseconds(100 / 6) - elapsed;
	
	if (gap.asMilliseconds() > 0) { sf::sleep(gap); }

	//The game handler is stored to maintain the game's current state so once
	//the player has finished changing options and the game is resumed,
	//everything continues exactly as it was left
	if (paused) {
		paused = false;
		return options;
	}

	updateKeys();		//Check player input
	player.update();	//Then update player state
	checkCollisions();	//Then check if new player state is affected by the world (ie obstacles)

	if (checkLoseCondition()) {
		sf::sleep(sf::milliseconds(500));//Slight pause to allow a smoother transition
		return lose;
	}

	if (checkWinCondition()) {
		sf::sleep(sf::milliseconds(500));//Slight pause to allow a smoother transition
		return win;
	}

	//displayStats();//Useful for displaying the player's current state while visuals have yet to be implemented
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

void GameHandler::updateKeys() {//The keyPressed event isn't responsive enough so instead each frame we check the current state the keyboard is in since we don't care what happens inbetween frames
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

		if (currentObstacle->x == player.x) {
			if (currentObstacle->y != player.y) {//If the player isn't at the correct altitude they will collide with the obstacle
				player.isHit = true;
				audio->playSound("fail");
				return;
			}
			delete currentObstacle;				//Either way if the obstacle is past the player it needs to be deleted
			it = obstacles.erase(it);
		}
		else {
			if (isNearPlayer(currentObstacle)) {
				audio->playNonRepeatingSound(currentObstacle->soundName);
				if (currentObstacle->y == player.y) {//After some testing I concluded it felt smoother if the player could pass an obstacle
					delete currentObstacle;			 //as soon as they react as this also helps feedback to the player that they succeeded in passing
					it = obstacles.erase(it);		 //the obstacle as its sound effect will stop playing once passed
				}
				else {
					++it;//The iterator is moved to the next obstacle if no collision is detected
				}
			}
			else {
				++it;	 //The iterator is moved to the next obstacle if no collision is detected
			}
		}
	}
}

bool GameHandler::isNearPlayer(Obstacle* obstacle) {
	int xDif = obstacle->x - player.x;
	if (xDif < hearingRange) {
		return true;
	}
	else {
		return false;
	}
}


void GameHandler::keyPressed(sf::Event event) {//In case we need discrete (slower) player input

	//if (event.key.code == keyMappings.at(UP)) { player.Move(UP); }
	//if (event.key.code == keyMappings.at(DOWN)) { player.Move(DOWN); }
	//if (event.key.code == keyMappings.at(LEFT)) { player.Move(LEFT); }
	//if (event.key.code == keyMappings.at(RIGHT)) { player.Move(RIGHT); }
	//if (event.key.code == keyMappings.at(ENTER)) { player.Move(ENTER); }
	//if (event.key.code == keyMappings.at(PAUSE)) { paused = true; }
}

void GameHandler::displayStats() {//Debug tool

	std::cout << "\nPlayer x: " << std::to_string(player.x);
	std::cout << "   y: " << std::to_string(player.y);/*
	for (int i = 0; i < obstacles.size(); i++) {
		std::cout << "\n Obstacle" << i << "  distance: " << std::to_string(obstacles[i]->distance);
		std::cout << "  x: " << std::to_string(obstacles[i]->x);
		std::cout << "  y: " << std::to_string(obstacles[i]->y) << "\n";
	}*/
}

void GameHandler::playTextPrompt() {
}