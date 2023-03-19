#include "LoopManager.h"
#include <iostream>
#include "MenuCode.h"
#include "ObjectFactory.h"

#include "MainMenuHandler.h"
#include "OptionsMenuHandler.h"
#include "LevelSelectHandler.h"
#include "VideoOptionsHandler.h"
#include "AudioOptionsHandler.h"
#include "ControlsOptionsHandler.h"
#include "GameHandler.h"
#include "EndOfLevelHandler.h"
#include "TutorialHandler.h"

LoopManager::LoopManager(GraphicsUnit* graphics_, AudioUnit* audio_) {
    audio = audio_;
    pausedGame = NULL;
    graphics = graphics_;
    window = graphics->getWindow();
    sf::Vector2f windowSize = sf::Vector2f(graphics->getWindowSize().x, graphics->getWindowSize().y);
    oFactory = new ObjectFactory(graphics);                         //For some reason the arrow doesn't display on the first load
    oFactory->makeObject("arrow", windowSize.x / 2.0, 0);
    oFactory->clearObjects();
    oFactory->makeObject("arrow", windowSize.x / 2.0, 0);
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            oFactory->objects[i]->getSprite()->setScale(0.5, 0.5);  //Otherwise the arrow would be massive
            break;
        }
    }
    handler = new MainMenuHandler(graphics, oFactory, audio);
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
            graphics->closeWindow();
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
    
    graphics->update(oFactory->objects);

    if (tempState != currentState) {
        if (pausedGame != NULL && tempState == mainMenu) {changeState(game);}   //Redirects back to game if game was paused

        else { changeState(tempState); }
    }
}

void LoopManager::changeState(MenuCode newState) {
    playerScore = handler->getScore();
    if (currentState == game && newState != win && newState != lose) {    //This means the game is being paused so game data should be preserved unless the game is over
        pausedGame = handler;
        handler = NULL;
    }

    delete handler;
   
    graphics->clearText();
    currentState = newState;
    sf::Event event;

    switch (newState) {
    case mainMenu:
        handler = new MainMenuHandler(graphics, oFactory, audio);
        break;

    case options:
        handler = new OptionsMenuHandler(graphics, oFactory, audio);
        break;

    case levelSelect:
        handler = new LevelSelectHandler(graphics, oFactory, audio);
        break;

    case quit:
        graphics->closeWindow();    //If the user exits using the quit button in a menu
        return;
        break;

    case videoOptions:
        handler = new VideoOptionsHandler(graphics, oFactory, audio);
        break;

    case audioOptions:
        handler = new AudioOptionsHandler(graphics, oFactory, audio);
        break;

    case controlsOptions:
        handler = new ControlsOptionsHandler(graphics, oFactory, audio);
        break;

    case level1:
    case level2:
    case level3:
    case practiseLevel1:
    case practiseLevel2:
    case practiseLevel3:
        selectedLevel = currentState;
        handler = new GameHandler(graphics, oFactory, audio, selectedLevel);
        handler->setArrowPos(sf::Vector2f(4000, 4000));	//This removes the arrow from the screen
        pausedGame = NULL;
        currentState = game;
        break;

    case game:
        if (pausedGame != NULL) {
            handler = pausedGame;
            pausedGame = NULL;
        }
        else {
            handler = new GameHandler(graphics, oFactory, audio, selectedLevel);
        }
        handler->setArrowPos(sf::Vector2f(4000, 4000));	//This removes the arrow from the screen
        break;

    case win:
        while (window->pollEvent(event)){}//This consumes any input leftover from the game
        if (playerScore > highscore) {
            highscore = playerScore;
            saveHighscore(highscore);
        }
        
        handler = new EndOfLevelHandler(graphics, oFactory, audio, selectedLevel, true, playerScore, highscore);
        break;

    case lose:
        while (window->pollEvent(event)) {}//This consumes any input leftover from the game
        if (playerScore > highscore) {
            highscore = playerScore;
            saveHighscore(highscore);
        }

        handler = new EndOfLevelHandler(graphics, oFactory, audio, selectedLevel, false, playerScore, highscore);
        break;

    case tutorial:
        handler = new TutorialHandler(graphics, oFactory, audio);
        break;

    default:
        currentState = mainMenu;
        handler = new MainMenuHandler(graphics, oFactory, audio);
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