#include "UIUnit.h"
#include <iostream>


UIUnit::UIUnit(sf::RenderWindow* window_, std::string fontName_, int fontSize, sf::Color backgroundColour_) {
    window = window_;
    loadFont(fontName_);
    fontName = fontName_;
    changeFontSize(fontSize);
    textureLocations["arrow"] = "Images/SelectionArrow.png";
    textureLocations["platform"] = "Images/platform.png";
    backgroundColour = backgroundColour_;
}

bool UIUnit::loadFont(std::string fontName) {
    fontName = "Misc/" + fontName + ".ttf";
    if (!font.loadFromFile(fontName)) {
        std::cout << "Error font not loaded";
        return false;
    }
    else {
        return true;
    }
}

void UIUnit::closeWindow() {
    window->close();
}

void UIUnit::clearWindow() {
    window->clear(backgroundColour);
}

void UIUnit::clearText() {
    messages.clear();
}

void UIUnit::setBackgroundColour(sf::Color colour) { backgroundColour = colour; }

sf::Texture* UIUnit::loadTexture(std::string objectName) {
    sf::Texture* temp;
    try {
        if (!textures.count(objectName)) {
            sf::Texture objectTexture;
            objectTexture.loadFromFile(textureLocations.at(objectName));	//If this is the first object of its kind the texture will first be loaded
            textures[objectName] = objectTexture;
            return &textures[objectName];
        }
        else {
            temp = &textures[objectName];	//If object has already been created the texture will be stored in the map
            return temp;
        }
    }
    catch (...) {
        try {
            if (!textures.count("MissingTexture")) {
                sf::Texture objectTexture;
                objectTexture.loadFromFile(textureLocations.at("MissingTexture"));
                textures["MissingTexture"] = objectTexture;
                return &textures["MissingTexture"];
            }
            else {
                temp = &textures["MissingTexture"];
                return temp;
            }
        }
        catch (...){
            std::cout << "\"MissingTexture\" texture either failed to load or location is missing";
            window->close();
            return NULL;
        }
    }
}

void UIUnit::update(std::vector<GameObject*> objects) {
    clearWindow();

    for (int i = 0; i < objects.size(); i++) {
         window->draw(*(objects[i]->getSprite()));
    }
    for (int i = 0; i < messages.size(); i++) {
        window->draw(messages[i]);
    }
    window->display();
}

void UIUnit::makeLabel(std::string message_, float x_, float y_) {
    sf::Text temp(message_, font, fontSize);
    temp.setPosition(x_, y_);
    messages.push_back(temp);
}

void UIUnit::removeLastLabel() {
    messages.pop_back();
}

sf::Text UIUnit::getLastLabel() {
    return messages.back();
}

sf::RenderWindow* UIUnit::getWindow() {
    return window;
}

sf::Vector2u UIUnit::getWindowSize() { return window->getSize();}

std::string UIUnit::getFontType() { return fontName;}

int UIUnit::getFontSize() { return fontSize;}

void UIUnit::changeDisplaySize(std::tuple<unsigned int, unsigned int, unsigned int> displaySize_)
{
    window->create(sf::VideoMode(std::get<0>(displaySize_), std::get<1>(displaySize_), std::get<2>(displaySize_)), "Game", sf::Style::Close);
}

void UIUnit::changeFontType(std::string fontName_)
{
    loadFont(fontName_);
}

void UIUnit::changeFontSize(int size) {
    fontSize = size;
    for (int i = 0; i < messages.size(); i++) {
        messages[i].setCharacterSize(fontSize);
    }
}