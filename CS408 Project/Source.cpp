#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Game.h"
#include "LoopManager.h"
#include "MainMenuHandler.h"
#include "MenuCode.h"
#include "GraphicsUnit.h"
#include "AudioUnit.h"
#include "jsoncpp\dist\json\json.h"
#include <fstream>
#pragma comment(lib, "openal32.lib")

Json::Value loadConfig();

void startLevel(int level_);

int main()
{
//First load the config file

    Json::Value config = loadConfig();

    sf::RenderWindow window(sf::VideoMode(config["window_width"].asInt(), config["window_height"].asInt()), "Game");
    
    GraphicsUnit graphics(&window, config["font"].asString(), config["font_size"].asInt());
    
    AudioUnit audio;
    
    LoopManager loopManager(&window, &graphics, &audio);

    while (window.isOpen()) {
        loopManager.updateLoop();
    }

    return 0;
}


Json::Value loadConfig() {
    std::ifstream file("config.json");
    Json::Value file_contents;
    Json::Reader jsonReader;
    jsonReader.parse(file, file_contents);
    return file_contents;
}

void startLevel(int level_) {
    /*Level currentLevel = loadLevel(level_);

    if (loadFail) {
        retryLoad();
    }*/
    Game game(level_);

    while (game.gameActive()) {

        game.updatePlayer();
        game.updateObjects();
        game.checkCollisions();
        game.updateSound();
        game.updateView();
        game.garbageCollection();
        std::cout << "Level " << level_ << "\n";

    }
}