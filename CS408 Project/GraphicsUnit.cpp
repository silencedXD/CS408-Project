#include "GraphicsUnit.h"
#include <iostream>

GraphicsUnit::GraphicsUnit(sf::RenderWindow* window_) {
    window = window_;
    LoadTextureLocations();
}

void GraphicsUnit::LoadTextureLocations() {
    textureLocations["player"] = "Images/car.png";
    textureLocations["obstacle"] = "Images/obstacle.png";
}

void GraphicsUnit::Draw(sf::Sprite* sprite)
{
    window->draw(*sprite);
}

void GraphicsUnit::Display()
{
    window->display();
}

sf::Texture* GraphicsUnit::LoadTexture(std::string objectName) {
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
            return nullptr;
        }
    }
}

void GraphicsUnit::SetBackgroundColour(sf::Color colour) { backgroundColour = colour; }

void GraphicsUnit::CloseWindow() {
    window->close();
}

void GraphicsUnit::ClearWindow() {
    window->clear(backgroundColour);
}

void GraphicsUnit::SetupFrame(sf::Vector2f pos)
{
    ClearWindow();
    window->setView(sf::View(sf::Vector2f(pos.x, pos.y), sf::Vector2f(window->getSize())));
}
