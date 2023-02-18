#pragma once
#include "LoopManager.h"
#include "GraphicsUnit.h"
#include "ObjectFactory.h"
#include "AudioUnit.h"

class Game
{
public:
    Game(GraphicsUnit* graphics_, AudioUnit* audio_);

    void updateLoop();

    void updatePlayer();
    void updateObjects();
    void checkCollisions();
    void updateSound();
    void updateView();
    void garbageCollection();

private:
    //Game state variables
    int level;
    bool gameActive;

    //Program managment
    LoopManager* menuManager;
    AudioUnit* audio;
    GraphicsUnit* graphics;
    ObjectFactory* oFactory;
};

