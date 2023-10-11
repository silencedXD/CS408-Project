#pragma once
#include "UIUnit.h"
#include "GameObject.h"
#include "SpriteObject.h"
#include "jsoncpp\dist\json\json.h"
#include <fstream>

class ObjectFactory
{
public:
	ObjectFactory(UIUnit* unit);
	void makeObject(std::string objectName, float posX, float posY);//Standard object creation
	void makeObject(std::string objectName, float posX, float posY, float xScale, float yScale);//Same as above except sprite is scaled
	void deleteObjects();
	void clearObjects();
	void setPlayerColour(sf::Color colour);
	void setPlatformColour(sf::Color colour);
	std::vector<GameObject*> objects;

private:
	sf::Color parseToColour(std::string colour_);
	UIUnit* UI;
	std::map<std::string, int> objectCount;
	sf::Color playerColour;
	sf::Color backgroundColour;
	sf::Color platformColour;
};

