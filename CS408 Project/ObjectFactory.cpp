#include "ObjectFactory.h"
#include <iostream>

ObjectFactory::ObjectFactory(GraphicsUnit* unit){
	graphics = unit;
	textureLocations["arrow"] = "SelectionArrow.png";
}

void ObjectFactory::makeObject(std::string objectName, float posX, float posY) {
		sf::Texture* temp;
		try {
			if (!textures.count(objectName)) {
				sf::Texture objectTexture;
				objectTexture.loadFromFile(textureLocations.at(objectName));	//If this is the first object of its kind the texture will first be loaded
				textures[objectName] = objectTexture;
				temp = &objectTexture;
				objectCount[objectName] = 0;
				objects.push_back(new SpriteObject(posX, posY, objectName + std::to_string(objectCount[objectName]), temp));
			}
			else {
				temp = &textures[objectName];	//If object has already been created the texture will be stored in the map
				objectCount[objectName]++;
				objects.push_back(new SpriteObject(posX, posY, objectName + std::to_string(objectCount[objectName]), temp));
			}

		}
		catch (...) {
			std::cout << objectName + " texture either failed to load or location is missing";	//If the texture fails to load the program exits
			graphics->closeWindow();
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