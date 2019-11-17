#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
	Sprite = ResourceManager::GetAtlasTexture("roguelike", 123);
	NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 123);

	std::string directory = IconSpriteDirectory + "Grey.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	renderLayer = 1;
	bodyType = b2BodyType::b2_staticBody;
}

Wall::Wall(json data)
{

}

Wall::~Wall()
{

}



json Wall::GetJson()
{
	std::cout << "This is a Wall object" << std::endl;
	json itemData;
	itemData["Type"] = "Wall";
	itemData["X"] = getPosition().x;
	itemData["Y"] = getPosition().y;
	itemData["W"] = getSize().x;
	itemData["H"] = getSize().y;
	return itemData;
}

std::shared_ptr<Item> Wall::getSharedPointer()
{
	auto sharedItem = std::make_shared<Wall>(*this); // make shared Item
	return sharedItem;
}