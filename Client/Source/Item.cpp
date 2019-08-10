#include "stdafx.h"
#include "Item.h"
#include "World.h"

Item::Item()
{
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


Item::~Item()
{
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
json Fish::getItemJson()
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
//json Wheat::getItemJson()
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
	this->Sprite = ResourceManager::GetAtlasTexture("crops", 1);;
	this->NormalMap = ResourceManager::GetAtlasTexture("crops", 1);
	this->icon.Background = ResourceManager::GetAtlasTexture("crops", 1);
}
//! Get a shared pointer to this object
std::shared_ptr<Item> WheatSeeds::getSharedPointer()
{
	auto sharedItem = std::make_shared<WheatSeeds>(*this); // make shared Item
	return sharedItem;
}
json WheatSeeds::getItemJson()
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
json SunflowerSeeds::getItemJson()
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
json LavenderSeeds::getItemJson()
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