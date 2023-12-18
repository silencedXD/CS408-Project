#include "UIUnit.h"
#include <iostream>


UIUnit::UIUnit(sf::RenderWindow* window_, std::string fontName_, int fontSize, sf::Color backgroundColour_) {
    window = window_;
    LoadFont(fontName_);
    fontName = fontName_;
    ChangeFontSize(fontSize);

    arrowTexture.loadFromFile("Images/SelectionArrow.png");
    arrow = new SpriteObject(window->getSize().x / 2.0f, 0.0f, "UI Arrow", &arrowTexture);
    arrow->getSprite()->setScale(0.5, 0.5);
    backgroundColour = backgroundColour_;
}

UIUnit::~UIUnit() {
    delete arrow;
}

bool UIUnit::LoadFont(std::string fontName) {
    fontName = "Misc/" + fontName + ".ttf";
    if (!font.loadFromFile(fontName)) {
        std::cout << "Error font not loaded";
        return false;
    }
    else {
        return true;
    }
}

void UIUnit::CloseWindow() {
    window->close();
}

void UIUnit::ClearWindow() {
    window->clear(backgroundColour);
}

void UIUnit::ClearText() {
    messages.clear();
}

void UIUnit::SetBackgroundColour(sf::Color colour) { backgroundColour = colour; }


void UIUnit::Update() {

    window->clear(sf::Color::Black);
    window->draw(*arrow->getSprite());

    for (int i = 0; i < messages.size(); i++) {
        window->draw(messages[i]);
    }
    window->display();
}

void UIUnit::MakeLabel(std::string message_, float x_, float y_) {
    sf::Text temp(message_, font, fontSize);
    temp.setPosition(x_, y_);
    messages.push_back(temp);
}

void UIUnit::RemoveLastLabel() {
    messages.pop_back();
}

sf::Text UIUnit::GetLastLabel() {
    return messages.back();
}

sf::RenderWindow* UIUnit::GetWindow() {
    return window;
}

sf::Vector2u UIUnit::GetWindowSize() { return window->getSize();}

std::string UIUnit::GetFontType() { return fontName;}

int UIUnit::GetFontSize() { return fontSize;}

void UIUnit::ChangeDisplaySize(std::tuple<unsigned int, unsigned int, unsigned int> displaySize_)
{
    window->create(sf::VideoMode(std::get<0>(displaySize_), std::get<1>(displaySize_), std::get<2>(displaySize_)), "Game", sf::Style::Close);
}

void UIUnit::ChangeFontType(std::string fontName_)
{
    LoadFont(fontName_);
}

void UIUnit::ChangeFontSize(int size) {
    fontSize = size;
    for (int i = 0; i < messages.size(); i++) {
        messages[i].setCharacterSize(fontSize);
    }
}