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

LoopManager::LoopManager(GraphicsUnit* graphics_, AudioUnit* audio_) {
    selectedLevel = 0;
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
        
        case sf::Event::KeyReleased:
            handler->keyReleased(event);
            break;

        default:
            break;
        }
    }
   
    sf::Time elapsed = clock.restart();
    MenuCode tempState = handler->updateState(elapsed);
    
    graphics->update(oFactory->objects);

    if (tempState != state) {
        if (pausedGame != NULL && tempState == mainMenu) {changeState(pausedGame->getState());}   //Redirects back to game if game was paused

        else { changeState(tempState); }
    }
}

void LoopManager::changeState(MenuCode state_) {
    if ((state == level1 || state == level2 || state == level3) && state_ != mainMenu) {    //This means the game is being paused so game data should be preserved unless the game is over
        pausedGame = handler;
        handler = NULL;
    }
    
    delete handler;
    graphics->clearText();
    state = state_;

    switch (state_) {
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
        if (pausedGame != NULL) {
            handler = pausedGame;
            pausedGame = NULL;
        }
        else {
            handler = new GameHandler(graphics, oFactory, audio, 1);
        }
        break;

    case level2:
        if (pausedGame != NULL) {
            handler = pausedGame;
            pausedGame = NULL;
        }
        else {
            handler = new GameHandler(graphics, oFactory, audio, 2);
        }
        break;

    case level3:
        if (pausedGame != NULL) {
            handler = pausedGame;
            pausedGame = NULL;
        }
        else {
            handler = new GameHandler(graphics, oFactory, audio, 3);
        }
        break;

    default:
        break;
    }
}

MenuCode LoopManager::getState() { return state; }

int LoopManager::getSelectedLevel() { return selectedLevel; }