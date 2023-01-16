#pragma once
#include "GraphicsUnit.h"
#include "GameObject.h"
#include "SpriteObject.h"

class ObjectFactory
{
public:
	ObjectFactory(GraphicsUnit* unit);
	void makeObject(std::string objectName, float posX, float posY);
	void deleteObjects();
	void clearObjects();

	std::vector<GameObject*> objects;

private:
	GraphicsUnit* graphics;
	std::map<std::string, int> objectCount;
};

