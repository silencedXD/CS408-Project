#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "LoopManager.h"
#include "MainMenuHandler.h"
#include "MenuCode.h"
#include "GraphicsUnit.h"
#include "AudioUnit.h"
#include "jsoncpp\dist\json\json.h"
#include <fstream>
#pragma comment(lib, "openal32.lib")

Json::Value loadConfig();

sf::Color parseToColour(std::string colour);

int main()
{
//First load the config file
    /*std::cout << "1 % 1000 = " << std::to_string(1 % 1000) << "\n";
    std::cout << "12 % 1000 = " << std::to_string(12 % 1000) << "\n";
    std::cout << "230 % 1000 = " << std::to_string(230 % 1000) << "\n";
    std::cout << "3400 % 1000 = " << std::to_string(3400 % 1000) << "\n";
    std::cout << "45000 % 1000 = " << std::to_string(45000 % 1000) << "\n\n\n";

    std::cout << "10000 % 1000 = " << std::to_string(11000 % 1000) << "\n";
    std::cout << "10002 % 1000 = " << std::to_string(10002 % 1000) << "\n";
    std::cout << "20030 % 1000 = " << std::to_string(20030 % 1000) << "\n";
    std::cout << "30400 % 1000 = " << std::to_string(30400 % 1000) << "\n";
    std::cout << "45000 % 1000 = " << std::to_string(45000 % 1000) << "\n";

    std::cout << "\n\n\n";

    std::cout << "1 / 1000 = " << std::to_string(1 / 1000) << "\n";
    std::cout << "12 / 1000 = " << std::to_string(12 / 1000) << "\n";
    std::cout << "230 / 1000 = " << std::to_string(230 / 1000) << "\n";
    std::cout << "3400 / 1000 = " << std::to_string(3400 / 1000) << "\n";
    std::cout << "45000 / 1000 = " << std::to_string(45000 / 1000) << "\n\n\n";

    std::cout << "10000 / 1000 = " << std::to_string(10000 / 1000) << "\n";
    std::cout << "10002 / 1000 = " << std::to_string(10002 / 1000) << "\n";
    std::cout << "20030 / 1000 = " << std::to_string(20030 / 1000) << "\n";
    std::cout << "30400 / 1000 = " << std::to_string(30400 / 1000) << "\n";
    std::cout << "45000 / 1000 = " << std::to_string(45000 / 1000) << "\n";
*/

    Json::Value config = loadConfig();
    sf::RenderWindow window;

    /*
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
            << mode.width << "x" << mode.height << " - "
            << mode.bitsPerPixel << " bpp" << std::endl;
    }
    */
    

    window.create(sf::VideoMode(config["window_width"].asInt(), config["window_height"].asInt()), "Game", sf::Style::Close);

    GraphicsUnit graphics(&window, config["font"].asString(), config["font_size"].asInt(), parseToColour(config["background_colour"].asString()));
    
    AudioUnit audio(config["general_volume"].asFloat(), config["text_volume"].asFloat(), config["game_volume"].asFloat());

    LoopManager loopManager(&graphics, &audio);

    while (window.isOpen()) {
        loopManager.updateLoop();
    }

    return 0;
}


Json::Value loadConfig() {
    std::ifstream file("config.json");
    Json::Value file_contents;
    Json::Reader jsonReader;
    jsonReader.parse(file, file_contents);
    return file_contents;
}

sf::Color parseToColour(std::string colour) {
    if (colour == "white") { return sf::Color::White; }
    if (colour == "black") { return sf::Color::Black; }
    if (colour == "red") { return sf::Color::Red; }
    if (colour == "green") { return sf::Color::Green; }
    if (colour == "blue") { return sf::Color::Blue; }
    if (colour == "yellow") { return sf::Color::Yellow; }
    if (colour == "cyan") { return sf::Color::Cyan; }
    if (colour == "magenta") { return sf::Color::Magenta; }
    else { return sf::Color::Transparent; }
}