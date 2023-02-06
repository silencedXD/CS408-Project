#include "GraphicsUnit.h"
#include <iostream>


GraphicsUnit::GraphicsUnit(sf::RenderWindow* window_, std::string fontName_, int fontSize) {
    window = window_;
    loadFont(fontName_);
    fontName = fontName_;
    changeFontSize(fontSize);
    textureLocations["arrow"] = "Images/SelectionArrow.png";
}

bool GraphicsUnit::loadFont(std::string fontName) {
    fontName = "Misc/" + fontName + ".ttf";
    if (!font.loadFromFile(fontName)) {
        std::cout << "Error font not loaded";
        return false;
    }
    else {
        return true;
    }
}

void GraphicsUnit::closeWindow() {
    window->close();
}

void GraphicsUnit::clearWindow() {
    window->clear(sf::Color::Black);
}

void GraphicsUnit::clearText() {
    messages.clear();
}

sf::Texture* GraphicsUnit::loadTexture(std::string objectName) {
    sf::Texture* temp;
    try {
        if (!textures.count(objectName)) {
            sf::Texture objectTexture;
            objectTexture.loadFromFile(textureLocations.at(objectName));	//If this is the first object of its kind the texture will first be loaded
            textures[objectName] = objectTexture;
            temp = &objectTexture;
            return temp;
        }
        else {
            temp = &textures[objectName];	//If object has already been created the texture will be stored in the map
            return temp;
        }
    }
    catch (...) {
        std::cout << objectName + " texture either failed to load or location is missing";	//If the texture fails to load the program exits
        window->close();
    }
}

void GraphicsUnit::update(std::vector<GameObject*> objects) {
    clearWindow();

    for (int i = 0; i < objects.size(); i++) {
         window->draw(*(objects[i]->getSprite()));
    }
    for (int i = 0; i < messages.size(); i++) {
        window->draw(messages[i]);
    }
    window->display();
}

void GraphicsUnit::makeLabel(std::string message_, float x_, float y_) {
    sf::Text temp(message_, font, fontSize);
    temp.setPosition(x_, y_);
    messages.push_back(temp);
}

void GraphicsUnit::removeLastLabel() {
    messages.pop_back();
}

sf::Text GraphicsUnit::getLastLabel() {
    return messages.back();
}

sf::Vector2u GraphicsUnit::getWindowSize() { return window->getSize();}

std::string GraphicsUnit::getFontType() { return fontName;}

int GraphicsUnit::getFontSize() { return fontSize;}

void GraphicsUnit::changeDisplaySize(std::tuple<unsigned int, unsigned int, unsigned int> displaySize_)
{
    window->create(sf::VideoMode(std::get<0>(displaySize_), std::get<1>(displaySize_), std::get<2>(displaySize_)), "Game", sf::Style::Close);
}

void GraphicsUnit::changeFontType(std::string fontName_)
{
    loadFont(fontName_);
}

void GraphicsUnit::changeFontSize(int size) {
    fontSize = size;
    for (int i = 0; i < messages.size(); i++) {
        messages[i].setCharacterSize(fontSize);
    }
}