#include "GraphicsUnit.h"
#include <iostream>

GraphicsUnit::GraphicsUnit(sf::RenderWindow* window_) {
    window = window_;
}

void GraphicsUnit::draw(sf::Sprite* sprite)
{
    window->draw(*sprite);
}

void GraphicsUnit::display()
{
    window->display();
}

sf::Texture* GraphicsUnit::loadTexture(std::string objectName) {
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
        catch (...) {
            std::cout << "\"MissingTexture\" texture either failed to load or location is missing";
            window->close();
            return NULL;
        }
    }
}

void GraphicsUnit::setBackgroundColour(sf::Color colour) { backgroundColour = colour; }

void GraphicsUnit::closeWindow() {
    window->close();
}

void GraphicsUnit::clearWindow() {
    window->clear(backgroundColour);
}