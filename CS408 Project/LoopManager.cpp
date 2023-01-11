#include "LoopManager.h"
#include <iostream>
#include "MenuCode.h"
#include "MainMenuHandler.h"
#include "SettingsMenuHandler.h"
#include "LevelSelectHandler.h"
#include "ObjectFactory.h"

LoopManager::LoopManager(sf::RenderWindow* window_, GraphicsUnit* unit) {
	window = window_;
	audio = 0;
    handler = nullptr;

    //TODO: font name and size should be loaded from config, not hard coded
    graphics = unit;

    oFactory = new ObjectFactory(graphics);
    oFactory->makeObject("arrow", window->getSize().x / 2.0, 0);
    oFactory->clearObjects();
    oFactory->makeObject("arrow", window->getSize().x / 2.0, 0);
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


    //TODO: Implement audio
    audio++;

    if (tempState != state) {
        changeState(tempState);
    }
}

void LoopManager::changeState(MenuCode state_) {
    switch (state_) {
    case mainMenu:
        delete handler;
        graphics->clearText();
        handler = new MainMenuHandler(graphics, oFactory);
        state = state_;
        break;
    case settings:
        delete handler;
        graphics->clearText();
        handler = new SettingsMenuHandler(graphics, oFactory);
        state = state_;
        break;
    case levelEditor:
        std::cout << "Level Editor Selected\n";
    case levelSelect:
        delete handler;
        graphics->clearText();
        handler = new LevelSelectHandler(graphics, oFactory);
        state = state_;
        break;
    case quit:
        window->close();    //If the user exits using the quit button in a menu
        return;
        break;
    default:
        break;
    }
}