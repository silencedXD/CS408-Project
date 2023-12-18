#include "EndOfLevelHandler.h"

EndOfLevelHandler::EndOfLevelHandler(UIUnit* graphics_, AudioUnit* audio_, MenuCode levelCode_, bool win, int playerScore_, int highscore_) : InputHandler(graphics_, audio_) {

    totalMenuItems = 6;
    delay = 1000;
    levelCode = levelCode_;
    win_ = win;
    playerScore = playerScore_;
    highscore = highscore_;
    sf::Vector2u windowSize = UI->GetWindowSize();

    if (win) {
        audio->playSound("level_complete");
        UI->MakeLabel("Level complete!", 0, 0);
    }
    else {
        audio->playSound("game_over");
        UI->MakeLabel("Game Over", 0, 0);
    }

    UI->MakeLabel("Retry", 0, windowSize.y * 0.17f);

    if (playerScore >= highscore) {
        UI->MakeLabel("New Highscore!!!!!!!!", 0, windowSize.y * 0.34f);
    }
    else {
        UI->MakeLabel("The highscore is: " + std::to_string(highscore), 0, windowSize.y * 0.34f);
    }

    UI->MakeLabel("Your score is: " + std::to_string(playerScore), 0, windowSize.y * 0.52f);


    UI->MakeLabel("Select level", 0, windowSize.y * 0.68f);
    UI->MakeLabel("Main Menu", 0, windowSize.y * 0.85f);
}

MenuCode EndOfLevelHandler::updateState(sf::Time elapsed) {
    updateArrow();

    switch (selector) {
    case 15:
        return levelCode;

    case 45:
        if (levelCode > level3) {
            return tutorial;
        }
        else {
            return levelSelect;
        }

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
        audio->emptyQueue();
        if (win_){
            audio->playSound("level_complete");
        }
        else {
            audio->playSound("game_over");
        }
        break;

    case 10:
        audio->emptyQueue();
        audio->playSound("retry");
        break;

    case 20:
        audio->emptyQueue();    //Overrides any score that was previously being outputted
        
        if (playerScore >= highscore) {
            audio->enqueueSound("new_highscore");
        }
        else {
            audio->enqueueSound("the_highscore_is");
        }

        playScore(highscore);
        audio->playQueue();
        break;

    case 30:
        audio->emptyQueue();    //Overrides any score that was previously being outputted
        audio->enqueueSound("your_score_is");
        playScore(playerScore);
        audio->playQueue();
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

void EndOfLevelHandler::playScore(int score) {
    if (score == 0) {
        audio->enqueueSound("0");
        return;
    }
    if (score / 1000000 > 0) {
        audio->enqueueSound("over_a_million");
        return;
    }
    else {
        int thousandsScore = score / 1000;
        if (thousandsScore > 0) {
            
            if (thousandsScore > 99) {
                playHundreds(thousandsScore);
            }
            else {
                playTens(thousandsScore);
            }
            audio->enqueueSound("thousand", 500);
        }
        
        int hundredsScore = score % 1000;
        
        if (hundredsScore > 99) {
            playHundreds(hundredsScore);
        }
        else {
            if (hundredsScore > 0) {
                playTens(hundredsScore);
            }
        }
    }
    //audio->playQueue();         //All sound bits are queued together then played in a separate thread
}                               //so that pauses between sounds can occur while not freezing the rest of the game

void EndOfLevelHandler::playHundreds(int score) {
    audio->enqueueSound(std::to_string(score / 100), 300);
    audio->enqueueSound("hundred", 500);
    if (score % 100 > 0) {
        audio->enqueueSound("and", 500);
        playTens(score % 100);
    }
}

void EndOfLevelHandler::playTens(int score) {
    
    int digitsScore = score % 10;

    switch (score / 10) {
    case 0:
    case 1:
        playDigits(score);
        digitsScore = 0;    //Otherwise it would play twice
        break;

    case 2:
        audio->enqueueSound("20", 500);
        break;

    case 3:
        audio->enqueueSound("30", 500);
        break;

    case 4:
        audio->enqueueSound("40", 500);
        break;

    case 5:
        audio->enqueueSound("50", 500);
        break;

    case 6:
        audio->enqueueSound("60", 500);
        break;

    case 7:
        audio->enqueueSound("70", 500);
        break;

    case 8:
        audio->enqueueSound("80", 500);
        break;
    
    case 9:
        audio->enqueueSound("90", 500);
        break;

    default:
        std::cout << "Error: Unknown tens found";
        break;
    }

    
    if (digitsScore > 0) {
        playDigits(digitsScore);
    }
}

void EndOfLevelHandler::playDigits(int score) {
    switch (score) {
    case 1:
        audio->enqueueSound("1", 600);
        break;

    case 2:
        audio->enqueueSound("2", 600);
        break;

    case 3:
        audio->enqueueSound("3", 600);
        break;

    case 4:
        audio->enqueueSound("4", 600);
        break;

    case 5:
        audio->enqueueSound("5", 600);
        break;

    case 6:
        audio->enqueueSound("6", 600);
        break;

    case 7:
        audio->enqueueSound("7", 600);
        break;

    case 8:
        audio->enqueueSound("8", 600);
        break;

    case 9:
        audio->enqueueSound("9", 600);
        break;

    case 10:
        audio->enqueueSound("10", 600);
        break;

    case 11:
        audio->enqueueSound("11", 600);
        break;

    case 12:
        audio->enqueueSound("12", 600);
        break;

    case 13:
        audio->enqueueSound("13", 600);
        break;

    case 14:
        audio->enqueueSound("14", 600);
        break;

    case 15:
        audio->enqueueSound("15", 600);
        break;

    case 16:
        audio->enqueueSound("16", 600);
        break;

    case 17:
        audio->enqueueSound("17", 600);
        break;

    case 18:
        audio->enqueueSound("18", 600);
        break;

    case 19:
        audio->enqueueSound("19", 600);
        break;

    default:
        std::cout << "Error: unknown digit";
    }
}