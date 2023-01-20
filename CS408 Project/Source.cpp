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
    sf::RenderWindow window;

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
            << mode.width << "x" << mode.height << " - "
            << mode.bitsPerPixel << " bpp" << std::endl;
    }



    if (config["window_style"].asString() == "fullscreen") {    //We can't save an enum to the Json so we just have to check the string value and make our own decision
        window.create(sf::VideoMode(config["window_width"].asInt(), config["window_height"].asInt(), config["bpp"].asInt()), "Game", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(config["window_width"].asInt(), config["window_height"].asInt()), "Game", sf::Style::Close);
    }

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