#include "GraphicsUnit.h"
#include <iostream>


GraphicsUnit::GraphicsUnit(sf::RenderWindow* window_, std::string fontName, int fontSize) {
    window = window_;
    loadFont(fontName);
    changeFontSize(fontSize);
    textureLocations["arrow"] = "Images/SelectionArrow.png";
}

bool GraphicsUnit::loadFont(std::string fontName) {
    if (!font.loadFromFile(fontName)) {
        std::cout << "Error font not loaded";
        return false;

    }
    else {
        return true;
    }
}

void GraphicsUnit::changeFontSize(int size) {
    fontSize = size;
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


sf::Vector2u GraphicsUnit::getWindowSize() { return window->getSize(); }