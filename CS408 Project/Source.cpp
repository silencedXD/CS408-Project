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
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f standardSize((float)windowSize.x, (float)windowSize.y / 4);
    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::Text> messages;
    sf::Font font;
    int fontSize = 36;

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error font not loaded";
        return -1;
    }
    

    sf::RectangleShape optionsRect(standardSize);
    optionsRect.setFillColor(sf::Color::Yellow);
    sf::Text optionsLabel("Options", font, fontSize);
    rectangles.push_back(optionsRect);
    messages.push_back(optionsLabel);


    sf::RectangleShape levelEditorRect(standardSize);
    levelEditorRect.setPosition(sf::Vector2f(0, windowSize.y * 1 / 4));
    levelEditorRect.setFillColor(sf::Color::Green);
    sf::Text levelEditorLabel("Level Editor", font, fontSize);
    levelEditorLabel.setPosition(sf::Vector2f(0, windowSize.y * 1 / 4));
    rectangles.push_back(levelEditorRect);
    messages.push_back(levelEditorLabel);
    

    sf::RectangleShape levelSelectRect(standardSize);
    levelSelectRect.setPosition(sf::Vector2f(0, windowSize.y * 2 / 4));
    levelSelectRect.setFillColor(sf::Color::Blue);
    sf::Text levelSelectLabel("Level Select", font, fontSize);
    levelSelectLabel.setPosition(sf::Vector2f(0, windowSize.y * 2 / 4));
    rectangles.push_back(levelSelectRect);
    messages.push_back(levelSelectLabel);

    sf::RectangleShape quitRect(standardSize);
    quitRect.setPosition(sf::Vector2f(0, windowSize.y * 3 / 4));
    quitRect.setFillColor(sf::Color::Red);
    sf::Text quitLabel("Quit", font, fontSize);
    quitLabel.setPosition(sf::Vector2f(0, windowSize.y * 3 / 4));
    rectangles.push_back(quitRect);
    messages.push_back(quitLabel);


    sf::Texture arrowTexture;
    if (arrowTexture.loadFromFile("SelectionArrow.png")) {
        std::cout << "Arrow image not loaded";
        return -1;
    }
    sf::Sprite arrow(arrowTexture);
    arrow.setPosition((float)windowSize.x / 2, (float)windowSize.y / 5);

    while (window.isOpen()) {
             


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        
        }



        window.clear();

        for (int i = 0; i < rectangles.size(); i++) {
            window.draw(rectangles.at(i));
        }

        for (int i = 0; i < messages.size(); i++) {
            window.draw(messages.at(i));
        }
        window.draw(arrow);

        window.display();
    
        //std::cout << "Please Select from the menu\n";
        //std::cout << "Options\n";
        //std::cout << "Level Editor\n";
        //std::cout << "Level Select\n";
        //std::cout << "Quit\n";
        //int selection;
        //std::cin >> selection;

        //switch (selection)
        //{
        //case 1:
        //    goToOptions();
        //    break;
        //case 2:
        //    goToLevelEditor();
        //    break;
        //case 3:
        //    goToLevelSelect();
        //    break;
        //case 4:
        //    return 0;
        //default:
        //    break;
        //}
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
    Game game(level_);

    while (game.gameActive()) {

        game.updatePlayer();
        game.updateObjects();
        game.checkCollisions();
        game.updateSound();
        game.updateView();
        game.garbageCollection();
        std::cout << "Level " << level_ << "\n";

    }
}