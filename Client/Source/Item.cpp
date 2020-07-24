#include "stdafx.h"
#include "Item.h"
#include "World.h"

Item::Item()
{
}

Item::Item(json jsonData)
{
	if (jsonData.count("Type") >= 0)
	{
		if (jsonData.at("Type") == "Wall")
		{
			Wall wall;

			float x = jsonData.at("X");
			float y = jsonData.at("Y");
			float w = jsonData.at("W");
			float h = jsonData.at("H");

			wall.setPosition({ x, y });
			wall.setSize({ w,h });
			*this = wall;
		}
		if (jsonData.at("Type") == "Wall")
		{
			Door door;

			float x = jsonData.at("X");
			float y = jsonData.at("Y");
			float w = jsonData.at("W");
			float h = jsonData.at("H");

			door.setPosition({ x, y });
			door.setSize({ w,h });
			*this = door;
		}
	}
}
std::shared_ptr<Item> Item::ConstructFromJson(json jsonData)
{
	if (jsonData.count("Type") >= 0)
	{
		if (jsonData.at("Type") == "Wall")
		{
			Wall wall;

			float x = jsonData.at("X");
			float y = jsonData.at("Y");
			float w = jsonData.at("W");
			float h = jsonData.at("H");

			wall.setPosition({ x, y });
			wall.setSize({ w,h });
			*this = wall;
			return wall.getSharedPointer();
		}
	}
}

void Item::Render(GL_Renderer& renderer)
{
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}
void Item::Render(GL_Renderer& renderer, World& world)
{
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}
void Item::Use(GL_Renderer& renderer, World& world, Player& player)
{

}

void Item::Selected(GL_Renderer & renderer, World & world, Player & player)
{
}

json Item::GetJson()
{
	std::cout << "This is a NULL object" << std::endl;
	json itemData;
	itemData["Type"] = "NULL";
	itemData["X"] = getPosition().x;
	itemData["Y"] = getPosition().y;
	return itemData;
}


Item::~Item()
{
}



glm::vec2 Item::setPosition(glm::vec2 newPosition)
{
	if (rigidBody != nullptr)
	{
		this->getBody()->SetTransform({ newPosition.x * physicsScaleDown, newPosition.y * physicsScaleDown }, getRotation());
	}
	return position = newPosition;
}

///////////////////////////////////////////////////////////////////////
// Fish
///////////////////////////////////////////////////////////////////////
Fish::Fish()
{
	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 728);
	this->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 728);
	this->icon.Background = ResourceManager::GetAtlasTexture("roguelike", 728);
}
json Fish::GetJson()
{
	std::cout << "This is a Fish object" << std::endl;
	json Item;
	Item["Type"] = itemName;
	Item["X"] = this->getPosition().x;
	Item["Y"] = this->getPosition().y;
	return Item;
}
std::shared_ptr<Item> Fish::getSharedPointer()
{
	auto sharedItem = std::make_shared<Fish>(*this); // make shared Item
	return sharedItem;
}


///////////////////////////////////////////////////////////////////////
// Wheat
///////////////////////////////////////////////////////////////////////
//Wheat::Wheat()
//{
//	this->Sprite = ResourceManager::GetAtlasTexture("crops", 7);;
//	this->NormalMap = ResourceManager::GetAtlasTexture("crops", 7);
//	this->icon.Background = ResourceManager::GetAtlasTexture("crops", 7);
//}
//std::shared_ptr<Item> Wheat::getSharedPointer()
//{
//	auto sharedItem = std::make_shared<Wheat>(*this); // make shared Item
//	return sharedItem;
//}
//json Wheat::GetJson()
//{
//	std::cout << "This is a Wheat object" << std::endl;
//	json Item;
//	Item["Type"] = itemName;
//	Item["X"] = this->getPosition().x;
//	Item["Y"] = this->getPosition().y;
//	return Item;
//}

///////////////////////////////////////////////////////////////////////
// Wheat Seeds
///////////////////////////////////////////////////////////////////////
WheatSeeds::WheatSeeds()
{
	this->Sprite = ResourceManager::GetAtlasTexture("crops", 1);
	this->NormalMap = ResourceManager::GetAtlasTexture("crops", 1);
	this->icon.Background = ResourceManager::GetAtlasTexture("crops", 1);
}
//! Get a shared pointer to this object
std::shared_ptr<Item> WheatSeeds::getSharedPointer()
{
	auto sharedItem = std::make_shared<WheatSeeds>(*this); // make shared Item
	return sharedItem;
}
json WheatSeeds::GetJson()
{
	std::cout << "This is a " << itemName.c_str() << " object" << std::endl;
	json Item;
	Item["Type"] = itemName;
	Item["X"] = this->getPosition().x;
	Item["Y"] = this->getPosition().y;
	return Item;
}
void WheatSeeds::Use(GL_Renderer& renderer, World& world, Player& player)
{
	if (world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition()) != nullptr)
	{
		if (world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition())->crop == nullptr)
		{
			WheatCrop wheat;
			
			world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition())->crop = wheat.getSharedPointer();

			player.inventory.removeItem(this->getSharedPointer());
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Sunflower Seeds
///////////////////////////////////////////////////////////////////////
SunflowerSeeds::SunflowerSeeds()
{
	this->Sprite = ResourceManager::GetAtlasTexture("seedBags", 1);;
	this->NormalMap = ResourceManager::GetAtlasTexture("seedBags", 1);
	this->icon.Background = ResourceManager::GetAtlasTexture("seedBags", 1);
}
//! Get a shared pointer to this object
std::shared_ptr<Item> SunflowerSeeds::getSharedPointer()
{
	auto sharedItem = std::make_shared<SunflowerSeeds>(*this); // make shared Item
	return sharedItem;
}
json SunflowerSeeds::GetJson()
{
	std::cout << "This is a " << itemName.c_str() << " object" << std::endl;
	json Item;
	Item["Type"] = itemName;
	Item["X"] = this->getPosition().x;
	Item["Y"] = this->getPosition().y;
	return Item;
}
void SunflowerSeeds::Use(GL_Renderer& renderer, World& world, Player& player)
{
	if (world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition()) != nullptr)
	{
		if (world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition())->crop == nullptr)
		{
			SunflowerCrop sunflower;

			world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition())->crop = sunflower.getSharedPointer();

			player.inventory.removeItem(this->getSharedPointer());
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Levender Seeds
///////////////////////////////////////////////////////////////////////
LavenderSeeds::LavenderSeeds()
{
	this->Sprite = ResourceManager::GetAtlasTexture("seedBags", 0);;
	this->NormalMap = ResourceManager::GetAtlasTexture("seedBags", 0);
	this->icon.Background = ResourceManager::GetAtlasTexture("seedBags", 0);
}
//! Get a shared pointer to this object
std::shared_ptr<Item> LavenderSeeds::getSharedPointer()
{
	auto sharedItem = std::make_shared<LavenderSeeds>(*this); // make shared Item
	return sharedItem;
}
json LavenderSeeds::GetJson()
{
	std::cout << "This is a " << itemName.c_str() << " object" << std::endl;
	json Item;
	Item["Type"] = itemName;
	Item["X"] = this->getPosition().x;
	Item["Y"] = this->getPosition().y;
	return Item;
}
void LavenderSeeds::Use(GL_Renderer& renderer, World& world, Player& player)
{
	if (world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition()) != nullptr)
		if (world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition())->crop == nullptr)
		{
			LavenderCrop crop;
			world.GetCell(player.cellPos.x, player.cellPos.y)->GetCropSquare().GetCropTile(player.getPosition())->crop = crop.getSharedPointer();
			player.inventory.removeItem(this->getSharedPointer());
		}
	
}