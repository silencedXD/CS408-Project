#pragma once
#include "InputHandler.h"
#include "Player.h"
#include "Rock.h"

class GameHandler : public InputHandler
{
public:
	GameHandler(GraphicsUnit* graphics, ObjectFactory* oFactory, AudioUnit* audio_, int level_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
	void keyPressed(sf::Event event);
	void keyReleased(sf::Event event);
	MenuCode getState();

private:
	bool isNearPlayer(Rock* obstacle);
	void checkCollisions();
	void displayStats();
	void generateLevel();

	int frameCounter;
	int level;
	int levelWidth;
	int levelHeight;
	bool paused;
	Player* player;
	std::vector<Rock*> rocks;

};