#pragma once
#include "InputHandler.h"
#include "Player.h"
#include "Obstacle.h"

class GameHandler : public InputHandler
{
public:
	GameHandler(UIUnit* UI, AudioUnit* audio_, MenuCode levelCode_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
	void keyPressed(sf::Event event);
	int getScore();

private:
	bool isNearPlayer(Obstacle* obstacle);

	void generateLevel();
	void updateKeys();
	void checkCollisions();
	bool checkWinCondition();
	bool checkLoseCondition();
	void displayStats();
	void updateGraphics();

	int level;
	int hearingRange;
	MenuCode levelCode;
	bool paused;
	Player player;
	std::vector<Obstacle*> obstacles;
};