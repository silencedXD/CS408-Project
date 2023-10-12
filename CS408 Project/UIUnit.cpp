#include "UIUnit.h"
#include <iostream>


UIUnit::UIUnit(sf::RenderWindow* window_, std::string fontName_, int fontSize, sf::Color backgroundColour_) {
    window = window_;
    loadFont(fontName_);
    fontName = fontName_;
    changeFontSize(fontSize);

    arrowTexture.loadFromFile("Images/SelectionArrow.png");
    arrow = new SpriteObject(window->getSize().x / 2.0f, 0.0f, "UI Arrow", &arrowTexture);
    arrow->getSprite()->setScale(0.5, 0.5);
    backgroundColour = backgroundColour_;
}

UIUnit::~UIUnit() {
    delete arrow;
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


void UIUnit::update() {
    clearWindow();

    window->draw(*arrow->getSprite());

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