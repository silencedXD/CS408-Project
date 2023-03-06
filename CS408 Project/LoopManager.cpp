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
#include "WinHandler.h"
#include "LoseHandler.h"

LoopManager::LoopManager(GraphicsUnit* graphics_, AudioUnit* audio_) {
    selectedLevel = 1;
    audio = audio_;
    handler = nullptr;
    pausedGame = NULL;
    graphics = graphics_;
    window = graphics->getWindow();
    oFactory = new ObjectFactory(graphics); //For some reason the arrow doesn't display on the first load
    oFactory->makeObject("arrow", graphics->getWindowSize().x / 2.0, 0);
    oFactory->clearObjects();
    oFactory->makeObject("arrow", graphics->getWindowSize().x / 2.0, 0);
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            oFactory->objects[i]->getSprite()->setScale(0.5, 0.5);  //Otherwise the arrow would be massive
            break;
        }
    }
    changeState(mainMenu);
}

void LoopManager::updateLoop() {
    sf::Clock clock;


    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed: //If the user closes the window by clicking the x button in the top right corner
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
    if (currentState == game && newState != win && newState != lose) {    //This means the game is being paused so game data should be preserved unless the game is over
        pausedGame = handler;
        handler = NULL;
    }
    
    if (handler != NULL); {
        delete handler;
    }
    
    graphics->clearText();
    currentState = newState;

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
        selectedLevel = 1;
        handler = new GameHandler(graphics, oFactory, audio, selectedLevel);
        handler->setArrowPos(sf::Vector2f(4000, 4000));	//This removes the arrow from the screen
        pausedGame = NULL;
        currentState = game;
        break;


    case level2:
        selectedLevel = 2;
        handler = new GameHandler(graphics, oFactory, audio, selectedLevel);
        handler->setArrowPos(sf::Vector2f(4000, 4000));	//This removes the arrow from the screen
        pausedGame = NULL;
        currentState = game;
        break;


    case level3:
        selectedLevel = 3;
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
        handler = new WinHandler(graphics, oFactory, audio, selectedLevel);
        break;

    case lose:
        handler = new LoseHandler(graphics, oFactory, audio, selectedLevel);
        break;

    default:
        currentState = mainMenu;
        handler = new MainMenuHandler(graphics, oFactory, audio);
        break;
    }
}

MenuCode LoopManager::getState() { return currentState; }

int LoopManager::getSelectedLevel() { return selectedLevel; }