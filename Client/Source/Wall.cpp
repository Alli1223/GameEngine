#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
	Sprite = ResourceManager::GetAtlasTexture("roguelike", 123);
	NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 123);

	std::string directory = IconSpriteDirectory + "ShopDisplayShelf.png";
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
	json data;
	data["Type"] = itemName;
	return json();
}
