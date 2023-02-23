#pragma once
#include "LoopManager.h"
#include "GraphicsUnit.h"
#include "ObjectFactory.h"
#include "AudioUnit.h"
#include "Obstacle.h"
#include "Player.h"

class Game
{
public:
    Game(GraphicsUnit* graphics_, AudioUnit* audio_);

    void updateLoop();
    void loadLevel();
    void updateGame();
    void generateLevel();

    //TODO: implement listener so that blockUnit is updated if window size is changed
    //TODO: Add blockUnit conversion
    //BlockU

    void updatePlayer();
    void updateObjects();
    void checkCollisions();
    //void updateSound();
    void updateView();
    void garbageCollection();

private:
    //Game state variables
    int level;
    bool paused;
    bool levelNotLoaded;
    std::vector<Obstacle*> obstacles;
    Player player;

    sf::RenderWindow* window;
    std::map<KeyCode, sf::Keyboard::Key> keyMappings;

    //Program managment
    LoopManager* menuManager;
    AudioUnit* audio;
    GraphicsUnit* graphics;
    ObjectFactory* gFactory;
};

