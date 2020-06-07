#include "stdafx.h"
#include "Tool.h"
#include "World.h"

Tool::Tool()
{
}


Tool::~Tool()
{
}

void Tool::Use(GL_Renderer& renderer, World& world, Player& player)
{

}

//////////////////////////////////////////////////////////////////////////////////////
// HOE
//////////////////////////////////////////////////////////////////////////////////////
Hoe::Hoe()
{
	this->setSize(50, 50);
	this->rotation = -2.0f;
	std::string directory = ToolSpriteDirectory + "hoe.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	this->Sprite = ResourceManager::LoadTexture(directory.c_str());
	//highlightCell.Sprite = ResourceManager::GetAtlasTexture("roguelike", 10);
}

std::shared_ptr<Item> Hoe::getSharedPointer()
{
	auto sharedItem = std::make_shared<Hoe>(*this); // make shared Item
	return sharedItem;
}

void Hoe::Use(GL_Renderer& renderer, World& world, Player& player)
{
	if (!inUse)
	{
		inUse = true;
		int cellSize = world.InfiniWorld.getCellSize();
		if (player.direction == Player::MovementDirection::right)
			offset = 50, flipSprite = false;
		else if (player.direction == Player::MovementDirection::left)
			offset = -50, flipSprite = true;
		glm::vec2 location = { (player.getPosition().x + ((float)cellSize / 2.0f)) / (float)cellSize, (player.getPosition().y + ((float)cellSize / 2.0f)) / (float)cellSize };
		
		
		world.GetCell(location.x, location.y)->GetCropSquare().HoeGround(player.getPosition());
		// orientate the tillage around the cell
		for (int x = -1; x < 2; x++)
			for (int y = -1; y < 2; y++)
			{
				glm::vec2 area = { x * 50, y * 50 };
				world.OrientateTillage(player.getPosition() + area);
			}
		inUse = false;
	}
}
void Hoe::Render(GL_Renderer& renderer, World& world)
{
	if (isInFocus)
	{

	}


	if (inUse)
	{
		if (flipSprite)
			this->setRotation(this->getRotation() - 0.1f);
		else
			this->setRotation(this->getRotation() + 0.1f);
		glm::vec2 posi = { renderer.playerPosition.x + (float)offset, renderer.playerPosition.y };
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, posi, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { flipSprite, false });

		if (getRotation() < -3.0f || getRotation() > 4.0f)
		{
			inUse = false;
			setRotation(0.0f);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// BugNet
//////////////////////////////////////////////////////////////////////////////////////

BugNet::BugNet()
{
	this->setSize(50, 50);
	std::string directory = ToolSpriteDirectory + "fishingPole.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	this->Sprite = ResourceManager::LoadTexture(directory.c_str());
}
std::shared_ptr<Item> BugNet::getSharedPointer()
{
	auto sharedItem = std::make_shared<BugNet>(*this); // make shared Item
	return sharedItem;
}
void BugNet::Render(GL_Renderer& renderer, World& world)
{
	if (isInFocus)
	{
		this->setPosition(renderer.playerPosition);
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { flipSprite, false });
	}
}
void BugNet::Use(GL_Renderer& renderer, World& world, Player& player)
{
	for (int i = 0; i < world.insects.size(); i++)
	{
		if (this->collidesWith(*world.insects[i]))
		{
			//Wheat wheat;
			//player.inventory.add(wheat.getSharedPointer());
			renderer.lights.erase(world.insects[i]->light.getLightID());
			world.insects.erase(world.insects.begin() + i);
		}
	}
}



//////////////////////////////////////////////////////////////////////////////////////
// Scythe
//////////////////////////////////////////////////////////////////////////////////////
Scythe::Scythe()
{
	this->setSize(50, 50);
	std::string directory = ToolSpriteDirectory + "scythe.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	this->Sprite = ResourceManager::LoadTexture(directory.c_str());
}

std::shared_ptr<Item> Scythe::getSharedPointer()
{
	auto sharedItem = std::make_shared<Scythe>(*this); // make shared Item
	return sharedItem;
}

//! Render function
void Scythe::Render(GL_Renderer& renderer, World& world)
{
	if (isInFocus)
	{
		this->setPosition(renderer.playerPosition);
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { flipSprite, false });
	}
}
//! Use the item
void Scythe::Use(GL_Renderer& renderer, World& world, Player& player)
{
	if (world.GetCell(player.cellPos.x, player.cellPos.y)->vegetation.size() > 0)
	{
		for (int i = 0; i < world.GetCell(player.cellPos.x, player.cellPos.y)->vegetation.size(); i++)
		{
			if (this->collidesWith(*world.GetCell(player.cellPos.x, player.cellPos.y)->vegetation[i]))
			{
				// Collect wheat
				if (world.GetCell(player.cellPos.x, player.cellPos.y)->vegetation[i]->vegeType == Vegetation::VegeType::longGrass)
				{
					WheatSeeds wheatSeeds;
					player.inventory.add(wheatSeeds.getSharedPointer());
					world.GetCell(player.cellPos.x, player.cellPos.y)->vegetation.erase(world.GetCell(player.cellPos.x, player.cellPos.y)->vegetation.begin() + i);
				}

			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////
// Bow
//////////////////////////////////////////////////////////////////////////////////////
Bow::Bow()
{
	this->setSize(50, 50);
	std::string directory = ToolSpriteDirectory + "bow.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	this->Sprite = ResourceManager::LoadTexture(directory.c_str());
}

std::shared_ptr<Item> Bow::getSharedPointer()
{
	auto sharedItem = std::make_shared<Bow>(*this); // make shared Item
	return sharedItem;
}

//! Render function
void Bow::Render(GL_Renderer& renderer, World& world)
{
	if (isInFocus)
	{
		this->setPosition(renderer.playerPosition);
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { flipSprite, false });
	}
}
//! Use the item
void Bow::Use(GL_Renderer& renderer, World& world, Player& player)
{
	
}