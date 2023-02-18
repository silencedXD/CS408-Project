#include "LoopManager.h"
#include <iostream>
#include "MenuCode.h"
#include "MainMenuHandler.h"
#include "OptionsMenuHandler.h"
#include "LevelSelectHandler.h"
#include "ObjectFactory.h"
#include "VideoOptionsHandler.h"
#include "AudioOptionsHandler.h"
#include "ControlsOptionsHandler.h"

LoopManager::LoopManager(GraphicsUnit* graphics_, AudioUnit* audio_) {
	audio = audio_;
    handler = nullptr;
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
   

    MenuCode tempState = handler->updateState();
    
    //TODO: Measure frame intervals to ensure smoother framerate
    graphics->update(oFactory->objects);

    if (tempState != state) {
        changeState(tempState);
    }
}

void LoopManager::changeState(MenuCode state_) {
    switch (state_) {
    case mainMenu:
        delete handler;
        graphics->clearText();
        handler = new MainMenuHandler(graphics, oFactory, audio);
        state = state_;
        break;

    case options:
        delete handler;
        graphics->clearText();
        handler = new OptionsMenuHandler(graphics, oFactory, audio);
        state = state_;
        break;

    case levelEditor:
        std::cout << "Level Editor Selected\n";
    case levelSelect:
        delete handler;
        graphics->clearText();
        handler = new LevelSelectHandler(graphics, oFactory, audio);
        state = state_;
        break;

    case quit:
        graphics->closeWindow();    //If the user exits using the quit button in a menu
        return;
        break;

    case videoOptions:
        delete handler;
        graphics->clearText();
        handler = new VideoOptionsHandler(graphics, oFactory, audio);
        state = state_;
        break;

    case audioOptions:
        delete handler;
        graphics->clearText();
        handler = new AudioOptionsHandler(graphics, oFactory, audio);
        state = state_;
        break;

    case controlsOptions:
        delete handler;
        graphics->clearText();
        handler = new ControlsOptionsHandler(graphics, oFactory, audio);
        state = state_;
        break;

    default:
        break;
    }
}