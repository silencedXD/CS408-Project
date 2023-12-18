#include "LoopManager.h"
#include <iostream>
#include "MenuCode.h"
#include "MainMenuHandler.h"
#include "OptionsMenuHandler.h"
#include "LevelSelectHandler.h"
#include "VideoOptionsHandler.h"
#include "AudioOptionsHandler.h"
#include "ControlsOptionsHandler.h"
#include "GameHandler.h"
#include "EndOfLevelHandler.h"
#include "TutorialHandler.h"

LoopManager::LoopManager(UIUnit* UI_, AudioUnit* audio_) {
    audio = audio_;
    pausedGame = nullptr;
    UI = UI_;
    window = UI->GetWindow();
    sf::Vector2f windowSize = sf::Vector2f(UI->GetWindowSize().x, UI->GetWindowSize().y);
    handler = new MainMenuHandler(UI, audio);
    highscore = loadHighscore();
    changeState(mainMenu);
}

void LoopManager::updateLoop() {
    sf::Clock clock;


    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed:         //If the user closes the window by clicking the x button in the top right corner
            UI->CloseWindow();
            break;

        case sf::Event::KeyPressed:
            handler->keyPressed(event);
            break;

        default:
            break;
        }
    }
   
    sf::Time elapsed = clock.restart();
    MenuCode tempState = handler->updateState(elapsed);

    if (tempState != game)              
    {                                   
        UI->Update();
    }


    if (tempState != currentState) {
        if (pausedGame != nullptr && tempState == mainMenu) {changeState(game);}   //Redirects back to game if game was paused

        else { changeState(tempState); }
    }
}

void LoopManager::changeState(MenuCode newState) {
    playerScore = handler->getScore();
    if (currentState == game && newState != win && newState != lose) {    //This means the game is being paused so game data should be preserved unless the game is over
        pausedGame = handler;
        handler = nullptr;
    }

    delete handler;
   
    UI->ClearText();
    currentState = newState;
    sf::Event event;

    switch (newState) {
    case mainMenu:
        handler = new MainMenuHandler(UI, audio);
        break;

    case options:
        handler = new OptionsMenuHandler(UI, audio);
        break;

    case levelSelect:
        handler = new LevelSelectHandler(UI, audio);
        break;

    case quit:
        UI->CloseWindow();    //If the user exits using the quit button in a menu
        return;
        break;

    case videoOptions:
        handler = new VideoOptionsHandler(UI, audio);
        break;

    case audioOptions:
        handler = new AudioOptionsHandler(UI, audio);
        break;

    case controlsOptions:
        handler = new ControlsOptionsHandler(UI, audio);
        break;

    case level1:
    case level2:
    case level3:
    case practiseLevel1:
    case practiseLevel2:
    case practiseLevel3:
        selectedLevel = currentState;
        handler = new GameHandler(UI, audio, selectedLevel);
        handler->setArrowPos(sf::Vector2f(4000, 4000));	//This removes the arrow from the screen
        pausedGame = nullptr;
        currentState = game;
        break;

    case game:
        if (pausedGame != nullptr) {
            handler = pausedGame;
            pausedGame = nullptr;
        }
        else {
            handler = new GameHandler(UI, audio, selectedLevel);
        }
        handler->setArrowPos(sf::Vector2f(4000, 4000));	//This removes the arrow from the screen
        break;

    case win:
        while (window->pollEvent(event)){}//This consumes any input leftover from the game
        if (playerScore > highscore) {
            highscore = playerScore;
            saveHighscore(highscore);
        }
        
        handler = new EndOfLevelHandler(UI, audio, selectedLevel, true, playerScore, highscore);
        break;

    case lose:
        while (window->pollEvent(event)) {}//This consumes any input leftover from the game
        if (playerScore > highscore) {
            highscore = playerScore;
            saveHighscore(highscore);
        }

        handler = new EndOfLevelHandler(UI, audio, selectedLevel, false, playerScore, highscore);
        break;

    case tutorial:
        handler = new TutorialHandler(UI, audio);
        break;

    default:
        currentState = mainMenu;
        handler = new MainMenuHandler(UI, audio);
        break;
    }
}

MenuCode LoopManager::getState() { return currentState; }

Json::Value LoopManager::loadConfig() {
    std::ifstream file("config.json");
    Json::Value file_contents;
    Json::Reader jsonReader;
    jsonReader.parse(file, file_contents);
    return file_contents;
}

void LoopManager::saveHighscore(int highscore)
{
    Json::Value config = loadConfig();
    config["highscore"] = highscore;
    std::ofstream file;
    file.open("config.json");
    file << config;
    file.close();
}

int LoopManager::loadHighscore() {
    Json::Value config = loadConfig();
    return config["highscore"].asInt();
}