#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(UIUnit* UI_, AudioUnit* audio_, MenuCode levelCode_) : InputHandler(UI_, audio_) 
{
	graphics = new GraphicsUnit(UI_->getWindow());
	graphics->setBackgroundColour(sf::Color::Red);
	paused = false;
	levelCode = levelCode_;
	hearingRange = 40;
	srand(time(NULL));
	level = 1;
	switch (levelCode) {
	case level1:
		level = 11;
		break;
		
	case level2:
		level = 22;
		break;

	case level3:
		level = 33;
		break;

	case practiseLevel1:
		level = 1;
		break;

	case practiseLevel2:
		level = 2;
		break;

	case practiseLevel3:
		level = 3;
		break;

	default:
		level = 1;
		std::cout << "Error: Unknown error code";
		break;
	}

	player = new Player(10,10,"player1", graphics->loadTexture("player"));
	player->scoreMultiplier = level;			//The higher the level the higher the score
	hearingRange = 45 - (5 * (level % 10));	//The hearing range is smaller the higher the level
	generateLevel();						//Level 1 is the same as practise level 1 ect
}

GameHandler::~GameHandler() {
	delete graphics;
	while (!obstacles.empty()) {
		delete obstacles.front();
	}
	delete player;
}

void GameHandler::generateLevel() {

	sf::Texture* texture = graphics->loadTexture("obstacle");

	if (level < 10) {
		int obstacleCount = level * 5;
		for (int i = 0; i < obstacleCount; i++) {
			int yVal = rand() % 2;
			int xVal = rand() % 10;
			if (yVal == 0) {
				obstacles.push_back(new Obstacle("3C", 50 + (i * 70) + xVal, 1, "OB_3C_" + i, texture));
			}
			else {
				obstacles.push_back(new Obstacle("5C", 50 + (i * 70) + xVal, 3, "OB_5C_" + i, texture));
			}
		}
	}
	else {
		int obstacleCount = 100;
		for (int i = 0; i < obstacleCount; i++) {
			int yVal = rand() % 2;
			int xVal = rand() % 10;
			if (yVal == 0) {
				obstacles.push_back(new Obstacle("3C", 50 + (i * 70) + xVal, 1, "OB_3C_" + i, texture));
			}
			else {
				obstacles.push_back(new Obstacle("5C", 50 + (i * 70) + xVal, 3, "OB_5C_" + i, texture));
			}
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

	updateKeys();						//Check player input
	player->update();					//Then update player state
	checkCollisions();					//Then check if new player state is affected by the world (ie obstacles)

	graphics->setupFrame();
	graphics->draw(player->getSprite());
	for (Obstacle* obstacle : obstacles) {
		graphics->draw(obstacle->getSprite());
	}
	graphics->display();

	if (checkLoseCondition()) {
		sf::sleep(sf::milliseconds(500));//Slight pause to allow a smoother transition
		return lose;
	}

	if (checkWinCondition()) {
		sf::sleep(sf::milliseconds(500));//Slight pause to allow a smoother transition
		return win;
	}

	//displayStats();
	return game;
}

int GameHandler::getScore() { return player->score; }

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
	if (player->isHit) {
		std::cout << "Game Over";
		setArrowPos(sf::Vector2f(0, 0));	//This moves the arrow back in vue for the menu system
		return true;
	}
	else{
		return false;
	}
}

void GameHandler::updateKeys() {			//The keyPressed event isn't responsive enough so instead each frame we check the current state the keyboard is in since we don't care what happens inbetween frames
	if (sf::Keyboard::isKeyPressed(keyMappings.at(UP))) { player->Move(UP); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(DOWN))) { player->Move(DOWN); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(LEFT))) { player->Move(LEFT); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(RIGHT))) { player->Move(RIGHT); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(ENTER))) { player->Move(ENTER); }
	if (sf::Keyboard::isKeyPressed(keyMappings.at(PAUSE))) { paused = true; }
}

void GameHandler::checkCollisions() {
	std::vector<Obstacle*>::iterator it = obstacles.begin();

	while (it != obstacles.end()) {
		Obstacle* currentObstacle = *it;
		sf::Vector2f obstaclePos = currentObstacle->getPos();
		sf::Vector2f playerPos = player->getPos();

		if (obstaclePos.x == playerPos.x) {
			if (obstaclePos.y != playerPos.y) {//If the player isn't at the correct altitude they will collide with the obstacle
				player->isHit = true;
				audio->playSound("fail");
				return;
			}
			player->scorePoint(1);
			delete currentObstacle;				//Either way if the obstacle is past the player it needs to be deleted
			it = obstacles.erase(it);
		}
		else {
			if (isNearPlayer(currentObstacle)) {
				audio->playNonRepeatingSound(currentObstacle->soundName);
				if (obstaclePos.y == playerPos.y) {			//After some testing I concluded it felt smoother if the player could pass an obstacle
					int xDif = obstaclePos.x - playerPos.x;	//as soon as they react as this also helps feedback to the player that they succeeded in passing
					delete currentObstacle;						//the obstacle as its sound effect will stop playing once passed
					it = obstacles.erase(it);		
					player->scorePoint(xDif);					//Player scores more points the faster they react
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
	sf::Vector2f obstaclePos = obstacle->getPos();
	sf::Vector2f playerPos = player->getPos();
	int xDif = obstaclePos.x - playerPos.x;
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

void GameHandler::displayStats() {//Useful debug tool for displaying the player's current state when you can't rely on visuals
	sf::Vector2f playerPos = player->getPos();
	std::cout << "\nPlayer x: " << std::to_string(playerPos.x);
	std::cout << "   y: " << std::to_string(playerPos.y);/*
	for (int i = 0; i < obstacles.size(); i++) {
		std::cout << "\n Obstacle" << i << "  distance: " << std::to_string(obstacles[i]->distance);
		std::cout << "  x: " << std::to_string(obstacles[i]->x);
		std::cout << "  y: " << std::to_string(obstacles[i]->y) << "\n";
	}*/
}

void GameHandler::playTextPrompt() {
}