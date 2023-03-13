#include "EndOfLevelHandler.h"

EndOfLevelHandler::EndOfLevelHandler(GraphicsUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_, MenuCode levelCode_, bool win, int playerScore_, int highscore_) : InputHandler(graphics_, oFactory_, audio_) {

    totalMenuItems = 6;
    delay = 1000;
    levelCode = levelCode_;
    win_ = win;
    playerScore = playerScore_;
    highscore = highscore_;
    sf::Vector2u windowSize = graphics->getWindowSize();

    if (win) {
        audio->playConcurrentSound("level_complete");
        graphics->makeLabel("Level complete!", 0, 0);
    }
    else {
        audio->playConcurrentSound("level_failed");
        graphics->makeLabel("Level failed", 0, 0);
    }

    sf::sleep(sf::milliseconds(delay));       //Adds a pause between text prompts

    if (playerScore >= highscore) {
        graphics->makeLabel("New Highscore!!!!!!!!", 0, windowSize.y * 0.17);
        audio->playConcurrentSound("new_highscore");
        sf::sleep(sf::milliseconds(delay));
    }
    else {
        graphics->makeLabel("The highscore is: " + std::to_string(highscore), 0, windowSize.y * 0.17);
        audio->playConcurrentSound("the_highscore_is");
        sf::sleep(sf::milliseconds(delay));
        playScore(std::to_string(highscore));
    }

    graphics->makeLabel("Your score is: " + std::to_string(playerScore), 0, windowSize.y * 0.34);
    audio->playConcurrentSound("your_score_is");
    sf::sleep(sf::milliseconds(delay));
    playScore(std::to_string(playerScore));

    graphics->makeLabel("Retry", 0, windowSize.y * 0.52);
    graphics->makeLabel("Select level", 0, windowSize.y * 0.68);
    graphics->makeLabel("Main Menu", 0, windowSize.y * 0.85);
}

MenuCode EndOfLevelHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 35:
        return levelCode;

    case 45:
        return levelSelect;

    case 55:
        return mainMenu;

    default:
        if (win_) {
            return win;
        }
        else {
            return lose;
        }
    }
}

void EndOfLevelHandler::playTextPrompt() {
    switch (selector) {
    case 0:
        if (win_){
            audio->playSound("level_complete");
        }
        else {
            audio->playSound("level_failed");
        }
        break;

    case 10:
        audio->playSound("the_highscore_is");
        playScore(std::to_string(highscore));
        break;

    case 20:
        audio->playSound("your_score_is");
        playScore(std::to_string(playerScore));
        break;

    case 30:
        audio->playSound("retry");
        break;

    case 40:
        audio->playSound("select_level");
        break;

    case 50:
        audio->playSound("main_menu");
        break;

    default:
        std::cout << "Error tried to play text prompt when selector is out of bounds\n";
        break;
    }
}

void EndOfLevelHandler::playScore(std::string scoreName) {
    
    switch (scoreName.size()) {
    case 1: //Size 1 is from 0 - 9
        break;

    case 2: //Size 2 is from 10 - 99
        break;

    case 3: //Size 3 is from 100 - 999
        break;

    case 4: //Size 4 is from 1000 - 9999
        break;

    case 5: //Size 5 is from 10,000 - 99,999
        break;

    case 6: //Size 6 is from 100,000 - 999,999
        break;

    default:
        std::cout << "Error: It's over 9000!!!! (actually over 999,999)";
        //audio->playConcurrentSound("one_million");
        break;
    }/*
    for (int i = 0; i < scoreName.size(); i++) {
        std::string number = "" + scoreName[i];
        audio->playConcurrentSound(std::to_string(scoreName[i]));
        sf::sleep(sf::milliseconds(delay));
    }*/
}