#include "LoopManager.h"
#include <iostream>
#include "MenuCode.h"
#include "MainMenuHandler.h"
#include "OptionsMenuHandler.h"
#include "LevelSelectHandler.h"
#include "ObjectFactory.h"

LoopManager::LoopManager(sf::RenderWindow* window_, GraphicsUnit* graphics_, AudioUnit* audio_) {
	window = window_;
	audio = audio_;
    handler = nullptr;
    graphics = graphics_;

    oFactory = new ObjectFactory(graphics); //For some reason the arrow doesn't display on the first load
    oFactory->makeObject("arrow", window->getSize().x / 2.0, 0);
    oFactory->clearObjects();
    oFactory->makeObject("arrow", window->getSize().x / 2.0, 0);
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
            window->close();
            break;

        case sf::Event::KeyPressed:
            handler->keyPressed(event);
            break;

        default:
            break;
        }
    }
   

    MenuCode tempState = handler->updateState();

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
        window->close();    //If the user exits using the quit button in a menu
        return;
        break;
    case empty:
    default:
        break;
    }
}