#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Game.h"
#include "LoopManager.h"
#include "MainMenuHandler.h"
#include "MenuCode.h"
#include "GraphicsUnit.h"
#include "AudioUnit.h"
#pragma comment(lib, "openal32.lib")



void startLevel(int level_);

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    GraphicsUnit graphics(&window, "arial.ttf", 36);
    AudioUnit audio;
    LoopManager loopManager(&window, &graphics, &audio);

    while (window.isOpen()) {
        loopManager.updateLoop();
    }

    return 0;
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