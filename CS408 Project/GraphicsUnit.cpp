#include "GraphicsUnit.h"
#include <iostream>


GraphicsUnit::GraphicsUnit(sf::RenderWindow* window_, std::string fontName, int fontSize) {
    window = window_;
    loadFont(fontName);
    changeFontSize(fontSize);
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