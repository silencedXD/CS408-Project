#include "Game.h"

Game::Game(GraphicsUnit* graphics_, AudioUnit* audio_) {
	graphics = graphics_;
	audio = audio_;
	paused = true;
	levelNotLoaded = true;
	menuManager = NULL;
	gFactory = NULL;
	level = 0;
	srand(time(NULL));
	window = graphics->getWindow();
}

void Game::updateLoop() {

	if (paused) {
		if (menuManager == NULL) {
			menuManager = new LoopManager(graphics, audio);
		}
		menuManager->updateLoop();
		level = menuManager->getState() - game;	//ControlsOptions is the last MenuCode before the level codes
		if (level >= 1) {
			paused = false;
			delete menuManager;
			menuManager = NULL;
		}
	}
	else {
		if (levelNotLoaded) {
			gFactory = new ObjectFactory(graphics);	//Having an object factory that is separate to the menu system keeps them out of scope of eachother
			generateLevel();
			levelNotLoaded = false;
		}
	
		updateGame();

		std::cout << "Game active\n";
		
		//TODO: remove this once actual game is implemented
		paused = true;
	}
}

void Game::generateLevel() {
	player = Player();
	int obstacleCount = 5;

	for (int i = 0; i < obstacleCount; i++) {
		obstacles.push_back(new Obstacle(rand() % 5, 1, rand() % 10 + 5, 1, "test"));
	}
}

void Game::loadLevel() {
	//Same as loading config files
	std::string level_dir = "Levels/level" + std::to_string(level) + ".json";
	std::ifstream file(level_dir);
	Json::Value level_contents;
	Json::Reader jsonReader;
	jsonReader.parse(file, level_contents);
	
	//First we read in the platforms
	int totalPlatforms = level_contents["total_platforms"].asInt();
	for (int i = 0; i < totalPlatforms; i++) {
		std::string platformName = "platform" + std::to_string(i);
		float x_pos = level_contents[platformName]["x"].asFloat();
		float y_pos = level_contents[platformName]["y"].asFloat();
		float length = level_contents[platformName]["length"].asFloat();
		gFactory->makeObject("platform", x_pos, y_pos, length, 1);
	}
}

void Game::updateGame() {
	//graphics->update(gFactory->objects);


}

void Game::updatePlayer() {}
void Game::updateObjects() {}
void Game::checkCollisions() {}

void Game::updateView() {}
void Game::garbageCollection() {}