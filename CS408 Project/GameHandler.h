#pragma once
#include "InputHandler.h"
#include "Player.h"
#include "Obstacle.h"

class GameHandler : public InputHandler
{
public:
	GameHandler(GraphicsUnit* graphics, ObjectFactory* oFactory, AudioUnit* audio_);
	MenuCode updateState(sf::Time elapsed);
	void playTextPrompt();
	void keyPressed(sf::Event event);

private:
	bool isInfrontOf(Obstacle* obstacle);
	void checkCollisions();
	void displayStats();

	bool paused;
	Player player;
	std::vector<Obstacle*> obstacles;
};