#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
	Sprite = ResourceManager::GetAtlasTexture("roguelike", 123);
	NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 123);

	std::string directory = IconSpriteDirectory + "ShopDisplayShelf.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
}

Wall::~Wall()
{
}
