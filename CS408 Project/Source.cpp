#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Game.h"
#include <iostream>

void goToOptions();

void goToLevelEditor();

void goToLevelSelect();

void startLevel(int level_);

int main()
{
    //Code Layout

    while (true) {
    
        std::cout << "Please Select from the menu\n";
        std::cout << "Options\n";
        std::cout << "Level Editor\n";
        std::cout << "Level Select\n";
        std::cout << "Quit\n";
        int selection;
        std::cin >> selection;

        switch (selection)
        {
        case 1:
            goToOptions();
            break;
        case 2:
            goToLevelEditor();
            break;
        case 3:
            goToLevelSelect();
            break;
        case 4:
            return 0;
        default:
            break;
        }
    }

    

                    //SFML test
    //sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    //sf::CircleShape shape(100.f);
    //GameObject object(1,2);
    //shape.setFillColor(sf::Color::Green);
    //object.image.setFillColor(sf::Color::Yellow);



    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //        
    //    }

    //    window.clear();
    //    window.draw(shape);
    //    window.draw(object.image);
    //    window.display();
    //}

    //return 0;
}

void goToOptions() {
    std::cout << "Options Selected\n";
}

void goToLevelEditor() {
    std::cout << "Level Editor Selected\n";
}

void goToLevelSelect() {

    bool exit = false;
    
    while (!exit) {
        std::cout << "Enter either 1, 2 or 3 for the level\n";
        std::cout << "Enter 9 to exit the level selector menu\n";
        int select;
        std::cin >> select;

        switch (select)
        {
        case 1:
            startLevel(1);
            break;
        case 2:
            startLevel(2);
            break;
        case 3:
            startLevel(3);
            break;
        case 9:
            exit = true;
        default:
            break;
        }
    }
}

void startLevel(int level_) {
    /*Level currentLevel = loadLevel(level_);

    if (loadFail) {
        retryLoad();
    }*/
    int currentLevel = level_;
    Game game(currentLevel);

    bool gameLoop = true;

    while (gameLoop) {

        game.updatePlayer();
        game.updateObjects();
        game.checkCollisions();
        game.updateSound();
        game.updateView();
        game.garbageCollection();
        std::cout << "Level " << currentLevel << "\n";
        gameLoop = false;
    }
}