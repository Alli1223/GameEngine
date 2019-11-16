#include "stdafx.h"
#include "Kiosk.h"

Kiosk::Kiosk()
{
	Sprite = ResourceManager::GetAtlasTexture("roguelike", 321);
	NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 321);

	std::string directory = IconSpriteDirectory + "ShopDisplayShelf.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	renderLayer = 1;
	bodyType = b2BodyType::b2_staticBody;
}

Kiosk::Kiosk(json data)
{

}

Kiosk::~Kiosk()
{

}

json Kiosk::GetJson()
{
	json data;
	data["Type"] = itemName;

	return json();
}
