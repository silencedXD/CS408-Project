#include "Game.h"

Game::Game(GraphicsUnit* graphics_, AudioUnit* audio_) {
	graphics = graphics_;
	audio = audio_;
	paused = true;
	levelNotLoaded = true;
	menuManager = NULL;
	gFactory = NULL;
	level = 0;
}

void Game::updateLoop() {

	if (paused) {
		if (menuManager == NULL) {
			menuManager = new LoopManager(graphics, audio);
		}
		menuManager->updateLoop();
		level = menuManager->getState() - controlsOptions;	//ControlsOptions is the last MenuCode before the level codes
		if (level >= 1) {
			paused = false;
			delete menuManager;
			menuManager = NULL;
		}
	}
	else {
		if (levelNotLoaded) {
			gFactory = new ObjectFactory(graphics);	//Having an object factory that is separate to the menu system keeps them out of scope of eachother
			loadLevel();
			levelNotLoaded = false;
		}
		else{
			updateGame();
		}
		std::cout << "Game active\n";
		
		//TODO: remove this once actual game is implemented
		paused = true;
	}
}

void Game::loadLevel() {
	//Same as loading config files
	std::string level_dir = "level" + std::to_string(level) + ".json";
	std::ifstream file(level_dir);
	Json::Value level_contents;
	Json::Reader jsonReader;
	jsonReader.parse(file, level_contents);
	
	//First we read in the platforms
	for (int i = 0; i < level_contents["total_platforms"].asInt(); i++) {
		std::string platformName = "platform" + std::to_string(i);
		float x_pos = level_contents[platformName]["x"].asFloat();
		float y_pos = level_contents[platformName]["y"].asFloat();
		float length = level_contents[platformName]["length"].asFloat();
		gFactory->makeObject("platform", x_pos, y_pos, length);
	}
}

void Game::updateGame() {}

void Game::updatePlayer() {}
void Game::updateObjects() {}
void Game::checkCollisions() {}

void Game::updateView() {}
void Game::garbageCollection() {}