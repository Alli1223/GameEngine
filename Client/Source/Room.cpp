#include "stdafx.h"
#include "Room.h"

Room::Room()
{
	for (int x = 0; x < roomSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < roomSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(I_Physics.get(), x, y, "WoodFloor");

			cell.isWalkable = true;
			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}

	tiles.clear();
	for (int x = 0; x < roomSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;
		tiles.push_back(column);
		for (int y = 0; y < roomSize; y++)
		{
			Cell cell(I_Physics.get(), x, y, "WoodFloor");
			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}

	// Set the floor tiles
	for (int x = 0; x < tiles.size(); x++)
		for (int y = 0; y < tiles[x].size(); y++)
		{
			tiles[x][y]->isWood = true;
			tiles[x][y]->isWalkable = true;
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 120);
			tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 120);
			// Create walls
			if (x == 0 || y == 0 || x == tiles.size() - 1 || y == tiles[x].size() - 1)
			{
				tiles[x][y]->isWalkable = false;
				tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 300);
				tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 300);
				// Door
				if (x == (tiles.size() - 1) / 2 && y == tiles[x].size() - 1)
				{
					tiles[x][y]->isWood = true;
					tiles[x][y]->isWalkable = true;
					tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 120);
					tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 120);
				}
				if (x == tiles.size() / 2 && y == tiles[x].size() - 1)
				{
					tiles[x][y]->isWood = true;
					tiles[x][y]->isWalkable = true;
					tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 120);
					tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 120);
				}
			}
		}
};

Room::~Room()
{

}

void Room::Render(GL_Renderer* renderer)
{
}

void Room::Update()
{
}



