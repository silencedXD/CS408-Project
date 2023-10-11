#include "InputHandler.h"

InputHandler::InputHandler(UIUnit* graphics_, ObjectFactory* oFactory_, AudioUnit* audio_) {
    selector = 0;
    totalMenuItems = 5;
    UI = graphics_;
    oFactory = oFactory_;
    audio = audio_;
    config = loadConfig();
    loadKeyMappings();
}

int InputHandler::getScore() { return 0; }

void InputHandler::loadKeyMappings() {
    keyMappings[UP] = stringToKeyboard(config["UP"].asString());
    keyMappings[DOWN] = stringToKeyboard(config["DOWN"].asString());
    keyMappings[LEFT] = stringToKeyboard(config["LEFT"].asString());
    keyMappings[RIGHT] = stringToKeyboard(config["RIGHT"].asString());
    keyMappings[ENTER] = stringToKeyboard(config["ENTER"].asString());
    keyMappings[PAUSE] = stringToKeyboard(config["PAUSE"].asString());
}

void InputHandler::keyPressed(sf::Event event) {
    
    if (event.key.code == keyMappings.at(DOWN)) {
        selector = (selector + 10) % (totalMenuItems * 10);
        playTextPrompt();
    }
    if (event.key.code == keyMappings.at(UP)) {
        selector = (totalMenuItems * 10 + selector - 10) % (totalMenuItems * 10);
        playTextPrompt();
    }
    if (event.key.code == keyMappings.at(ENTER)) {
        if (selector % 10 == 0 && selector > 0)
        {
            selector = selector + 5;
        }
    }
}

void InputHandler::updateArrow() {
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {
            sf::Vector2f windowSize = sf::Vector2f(UI->getWindowSize().x, UI->getWindowSize().y);

            oFactory->objects[i]->setPos(windowSize.x / 2.0, (selector / 10) * (windowSize.y / totalMenuItems));
            break;
        }
    }
}

sf::Vector2f InputHandler::setArrowPos(sf::Vector2f newPos_)    //Sets the position of arrow while returning old value
{                                                               //Used to move arrow out of display to make it invisible
    for (int i = 0; i < oFactory->objects.size(); i++) {
        if (oFactory->objects[i]->id.substr(0, 5) == "arrow") {

            sf::Vector2f temp = oFactory->objects[i]->getPos();
            oFactory->objects[i]->setPos(newPos_.x,newPos_.y);
            return temp;
        }
    }
    return sf::Vector2f(0,0);
}

Json::Value InputHandler::loadConfig() {
    std::ifstream file("config.json");
    Json::Value file_contents;
    Json::Reader jsonReader;
    jsonReader.parse(file, file_contents);
    return file_contents;
}

void InputHandler::saveConfig(Json::Value config_) {
    std::ofstream file;
    file.open("config.json");
    file << config_;
    file.close();
}

sf::Keyboard::Key InputHandler::stringToKeyboard(std::string keyName) {
    if (keyName == "0") { return sf::Keyboard::A; }
    if (keyName == "1") { return sf::Keyboard::B; }
    if (keyName == "2") { return sf::Keyboard::C; }
    if (keyName == "3") { return sf::Keyboard::D; }
    if (keyName == "4") { return sf::Keyboard::E; }
    if (keyName == "5") { return sf::Keyboard::F; }
    if (keyName == "6") { return sf::Keyboard::G; }
    if (keyName == "7") { return sf::Keyboard::H; }
    if (keyName == "8") { return sf::Keyboard::I; }
    if (keyName == "9") { return sf::Keyboard::J; }
    if (keyName == "10") { return sf::Keyboard::K; }
    if (keyName == "11") { return sf::Keyboard::L; }
    if (keyName == "12") { return sf::Keyboard::M; }
    if (keyName == "13") { return sf::Keyboard::N; }
    if (keyName == "14") { return sf::Keyboard::O; }
    if (keyName == "15") { return sf::Keyboard::P; }
    if (keyName == "16") { return sf::Keyboard::Q; }
    if (keyName == "17") { return sf::Keyboard::R; }
    if (keyName == "18") { return sf::Keyboard::S; }
    if (keyName == "19") { return sf::Keyboard::T; }
    if (keyName == "20") { return sf::Keyboard::U; }
    if (keyName == "21") { return sf::Keyboard::V; }
    if (keyName == "22") { return sf::Keyboard::W; }
    if (keyName == "23") { return sf::Keyboard::X; }
    if (keyName == "24") { return sf::Keyboard::Y; }
    if (keyName == "25") { return sf::Keyboard::Z; }
    if (keyName == "73") { return sf::Keyboard::Up; }
    if (keyName == "74") { return sf::Keyboard::Down; }
    if (keyName == "71") { return sf::Keyboard::Left; }
    if (keyName == "72") { return sf::Keyboard::Right; }
    if (keyName == "53") { return sf::Keyboard::Backslash; }
    if (keyName == "67") { return sf::Keyboard::Add; }
    if (keyName == "59") { return sf::Keyboard::Backspace; }
    if (keyName == "49") { return sf::Keyboard::Comma; }
    if (keyName == "56") { return sf::Keyboard::Dash; }
    if (keyName == "66") { return sf::Keyboard::Delete; }
    if (keyName == "70") { return sf::Keyboard::Divide; }
    if (keyName == "63") { return sf::Keyboard::End; }
    if (keyName == "58") { return sf::Keyboard::Enter; }
    if (keyName == "55") { return sf::Keyboard::Equal; }
    if (keyName == "85") { return sf::Keyboard::F1; }
    if (keyName == "86") { return sf::Keyboard::F2; }
    if (keyName == "87") { return sf::Keyboard::F3; }
    if (keyName == "88") { return sf::Keyboard::F4; }
    if (keyName == "89") { return sf::Keyboard::F5; }
    if (keyName == "90") { return sf::Keyboard::F6; }
    if (keyName == "91") { return sf::Keyboard::F7; }
    if (keyName == "92") { return sf::Keyboard::F8; }
    if (keyName == "93") { return sf::Keyboard::F9; }
    if (keyName == "94") { return sf::Keyboard::F10; }
    if (keyName == "95") { return sf::Keyboard::F11; }
    if (keyName == "96") { return sf::Keyboard::F12; }
    if (keyName == "97") { return sf::Keyboard::F13; }
    if (keyName == "98") { return sf::Keyboard::F14; }
    if (keyName == "99") { return sf::Keyboard::F15; }
    if (keyName == "64") { return sf::Keyboard::Home; }
    if (keyName == "56") { return sf::Keyboard::Hyphen; }
    if (keyName == "65") { return sf::Keyboard::Insert; }
    if (keyName == "39") { return sf::Keyboard::LAlt; }
    if (keyName == "46") { return sf::Keyboard::LBracket; }
    if (keyName == "37") { return sf::Keyboard::LControl; }
    if (keyName == "38") { return sf::Keyboard::LShift; }
    if (keyName == "40") { return sf::Keyboard::LSystem; }
    if (keyName == "45") { return sf::Keyboard::Menu; }
    if (keyName == "69") { return sf::Keyboard::Multiply; }
    if (keyName == "26") { return sf::Keyboard::Num0; }
    if (keyName == "27") { return sf::Keyboard::Num1; }
    if (keyName == "28") { return sf::Keyboard::Num2; }
    if (keyName == "29") { return sf::Keyboard::Num3; }
    if (keyName == "30") { return sf::Keyboard::Num4; }
    if (keyName == "31") { return sf::Keyboard::Num5; }
    if (keyName == "32") { return sf::Keyboard::Num6; }
    if (keyName == "33") { return sf::Keyboard::Num7; }
    if (keyName == "34") { return sf::Keyboard::Num8; }
    if (keyName == "35") { return sf::Keyboard::Num9; }
    if (keyName == "75") { return sf::Keyboard::Numpad0; }
    if (keyName == "76") { return sf::Keyboard::Numpad1; }
    if (keyName == "77") { return sf::Keyboard::Numpad2; }
    if (keyName == "78") { return sf::Keyboard::Numpad3; }
    if (keyName == "79") { return sf::Keyboard::Numpad4; }
    if (keyName == "80") { return sf::Keyboard::Numpad5; }
    if (keyName == "81") { return sf::Keyboard::Numpad6; }
    if (keyName == "82") { return sf::Keyboard::Numpad7; }
    if (keyName == "83") { return sf::Keyboard::Numpad8; }
    if (keyName == "84") { return sf::Keyboard::Numpad9; }
    if (keyName == "62") { return sf::Keyboard::PageDown; }
    if (keyName == "61") { return sf::Keyboard::PageUp; }
    if (keyName == "100") { return sf::Keyboard::Pause; }
    if (keyName == "50") { return sf::Keyboard::Period; }
    if (keyName == "51") { return sf::Keyboard::Quote; }
    if (keyName == "43") { return sf::Keyboard::RAlt; }
    if (keyName == "47") { return sf::Keyboard::RBracket; }
    if (keyName == "41") { return sf::Keyboard::RControl; }
    if (keyName == "58") { return sf::Keyboard::Return; }
    if (keyName == "42") { return sf::Keyboard::RShift; }
    if (keyName == "44") { return sf::Keyboard::RSystem; }
    if (keyName == "48") { return sf::Keyboard::Semicolon; }
    if (keyName == "52") { return sf::Keyboard::Slash; }
    if (keyName == "57") { return sf::Keyboard::Space; }
    if (keyName == "68") { return sf::Keyboard::Subtract; }
    if (keyName == "60") { return sf::Keyboard::Tab; }
    if (keyName == "54") { return sf::Keyboard::Tilde; }
    if (keyName == "-1") { return sf::Keyboard::Unknown; }
    else { return sf::Keyboard::Unknown; }
}