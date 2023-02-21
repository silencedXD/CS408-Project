#include "ObjectFactory.h"
#include <iostream>

ObjectFactory::ObjectFactory(GraphicsUnit* unit){
	graphics = unit;
}

void ObjectFactory::makeObject(std::string objectName, float posX, float posY) {
	sf::Texture* temp = graphics->loadTexture(objectName);

	objects.push_back(new SpriteObject(posX, posY, objectName + std::to_string(objectCount[objectName]), temp));
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
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->deleteFlag = true;
	}
	deleteObjects();
	objects.clear();
}