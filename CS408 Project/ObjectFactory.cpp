#include "ObjectFactory.h"
#include <iostream>

ObjectFactory::ObjectFactory(UIUnit* unit){
	std::ifstream file("config.json");
	Json::Value config;
	Json::Reader jsonReader;
	jsonReader.parse(file, config);
	
	UI = unit;
	playerColour = parseToColour(config["player_colour"].asString());
	platformColour = parseToColour(config["platform_colour"].asString());
}

void ObjectFactory::makeObject(std::string objectName, float posX, float posY) {
	sf::Texture* temp = UI->loadTexture(objectName);

	objects.push_back(new SpriteObject(posX, posY, objectName + std::to_string(objectCount[objectName]), temp));
	if (objectName == "player") {
		objects.back()->getSprite()->setColor(playerColour);
	}
	if (objectName == "platform") {
		objects.back()->getSprite()->setColor(platformColour);
	}
	if (objectCount.count(objectName)) {
		objectCount[objectName]++;
	}
	else {
		objectCount[objectName] = 0;
	}
}

void ObjectFactory::makeObject(std::string objectName, float posX, float posY, float xScale, float yScale) {
	sf::Texture* temp = UI->loadTexture(objectName);
	sf::Vector2f windowSize = sf::Vector2f(UI->getWindowSize().x, UI->getWindowSize().y);
	float xUnit = windowSize.x / 5;
	float yUnit = windowSize.y / 5;

	objects.push_back(new SpriteObject(posX * xUnit, posY * yUnit, objectName + std::to_string(objectCount[objectName]), temp));
	objects.back()->getSprite()->scale(xScale, yScale);	//Scales' the sprite

	if (objectName == "player") {
		objects.back()->getSprite()->setColor(playerColour);
	}
	if (objectName == "platform") {
		objects.back()->getSprite()->setColor(platformColour);
		objects.back()->getSprite()->scale(xScale, yScale);
	}
	if (objectCount.count(objectName)) {
		objectCount[objectName]++;
	}
	else {
		objectCount[objectName] = 0;
	}
}

void ObjectFactory::deleteObjects() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects.at(i)->deleteFlag) { delete objects[i]; }
	}
}

void ObjectFactory::clearObjects() {
	objects.clear();
}

void ObjectFactory::setPlayerColour(sf::Color colour) {
	playerColour = colour;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->id == "player") { objects[i]->getSprite()->setColor(playerColour); }
	}
}

void ObjectFactory::setPlatformColour(sf::Color colour) {
	platformColour = colour;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->id == "platform") { objects[i]->getSprite()->setColor(platformColour); }
	}
}

sf::Color ObjectFactory::parseToColour(std::string colour) {
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