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
	float x = data.at("X");
	float y = data.at("Y");
	float w = data.at("W");
	float h = data.at("H");
	setPosition({ x, y });
	setSize({ w,h });
}

Wall::~Wall()
{

}


json Wall::GetJson()
{
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