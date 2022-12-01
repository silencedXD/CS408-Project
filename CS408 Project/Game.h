#pragma once
class Game
{
public:
    Game(int level_);

    bool gameActive();

    void updatePlayer();
    void updateObjects();
    void checkCollisions();
    void updateSound();
    void updateView();
    void garbageCollection();

private:
    int level;
    bool gameState;
};

