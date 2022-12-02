#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Game.h"
#include <iostream>


void startLevel(int level_);

void checkMenuInput(sf::Event, int* selector_, int totalMenuItems);

enum menuCode { optionsMenu, levelEditorMenu, levelSelectMenu };

void runMenu(menuCode code_, sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture);

void openOptionsMenu(sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture);

void openLevelEditorMenu(sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture);

void openLevelSelectMenu(sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture);

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
    if (!arrowTexture.loadFromFile("SelectionArrow.png")) {
        std::cout << "Arrow image not loaded";
        return -1;
    }


    sf::Sprite arrow(arrowTexture);
    arrow.setScale(sf::Vector2f(0.5, 0.5));
    arrow.setPosition((float)windowSize.x / 2, 0);
    int selector = 10;

    while (window.isOpen()) {



        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                break;

            case sf::Event::KeyReleased:
                checkMenuInput(event, &selector, 4);
                break;
            default:
                break;
            }
        }

        switch (selector) {
        case 15:
            runMenu(optionsMenu, &window, &font, &arrowTexture);
            selector = 10;
            break;
        case 25:
            runMenu(levelEditorMenu, &window, &font, &arrowTexture);
            selector = 20;
            break;
        case 35:
            runMenu(levelSelectMenu, &window, &font, &arrowTexture);
            selector = 30;
            break;
        case 45:
            return 0;
        default:
            break;
        }
        window.setTitle("Main Menu");

        arrow.setPosition((float)windowSize.x / 2, (float) (windowSize.y / 40 * selector) - windowSize.y / 4);


        window.clear();

        for (int i = 0; i < rectangles.size(); i++) {
            window.draw(rectangles.at(i));
        }

        for (int i = 0; i < messages.size(); i++) {
            window.draw(messages.at(i));
        }
        window.draw(arrow);

        window.display();
    }

    return 0;
}

void runMenu(menuCode code_, sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture) {
    switch (code_) {
    case optionsMenu:
        openOptionsMenu(window, font, arrowTexture);
        break;
    case levelEditorMenu:
        openLevelEditorMenu(window, font, arrowTexture);
        break;
    case levelSelectMenu:
        openLevelSelectMenu(window, font, arrowTexture);
        break;
    default:
        break;
    }
}




void openOptionsMenu(sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture) {
    window->setTitle("Options Selected");
    std::cout << "Options Selected\n";
}

void openLevelEditorMenu(sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture) {
    window->setTitle("Level Editor Selected");
    std::cout << "Level Editor Selected\n";
}

void openLevelSelectMenu(sf::RenderWindow* window, sf::Font* font, sf::Texture* arrowTexture) {
    window->setTitle("Level Select Selected");
    bool exit = false;
    int fontSize = 50;
    sf::Vector2u windowSize = window->getSize();

    std::vector<sf::Text> messages;
    sf::Text level1("Level One", *font, fontSize);
    messages.push_back(level1);
    sf::Text level2("Level Two", *font, fontSize);
    level2.setPosition(0, windowSize.y * 1 / 4);
    messages.push_back(level2);
    sf::Text level3("Level Three", *font, fontSize);
    level3.setPosition(0, windowSize.y * 2 / 4);
    messages.push_back(level3);
    sf::Text goBack("Go Back", *font, fontSize);
    goBack.setPosition(0, windowSize.y * 3 / 4);
    messages.push_back(goBack);


    sf::Sprite arrow(*arrowTexture);
    arrow.setScale(sf::Vector2f(0.5, 0.5));
    arrow.setPosition((float)windowSize.x / 2, 0);


    int selector = 10;

    while (!exit) {


        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                break;

            case sf::Event::KeyReleased:
                checkMenuInput(event, &selector, 4);
                break;
            default:
                break;
            }
        }

        switch (selector) {
        case 15:
            std::cout << "Level One selected";
            selector = 10;
            break;
        case 25:
            std::cout << "Level Two selected";
            selector = 20;
            break;
        case 35:
            std::cout << "Level Three selected";
            selector = 30;
            break;
        case 45:
            exit = true;
        default:
            break;
        }
        window->setTitle("Level Select");

        arrow.setPosition((float)windowSize.x / 2, (float)(windowSize.y / 40 * selector) - windowSize.y / 4);


        window->clear();


        for (int i = 0; i < messages.size(); i++) {
            window->draw(messages.at(i));
        }
        window->draw(arrow);

        window->display();
    }


    
}

void checkMenuInput(sf::Event event, int* selector_, int totalMenuItems){
    if (event.key.code == sf::Keyboard::Down) {
        if (*selector_ < totalMenuItems * 10) {
            *selector_ = *selector_ + 10;
        }
    }
    if (event.key.code == sf::Keyboard::Up) {
        if (*selector_ > 10) {
            *selector_ = *selector_ - 10;
        }
    }
    if (event.key.code == sf::Keyboard::Enter) {
        *selector_ = *selector_ + 5;
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