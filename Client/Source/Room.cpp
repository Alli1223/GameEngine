#include "stdafx.h"
#include "Room.h"
#include "RoomDesigner.h"

Room::Room()
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
}
Room::Room(json data)
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
	for (int x = 0; x < roomSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < roomSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(I_Physics.get(), x, y, "WoodFloor");
			cell.setSize({ tileSize, tileSize });
			cell.setCellSize(tileSize);
			cell.setPosition(x * tileSize, y * tileSize);
			cell.isWalkable = true;
			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}

	json levelData = data.at("TileData");
	// Get the tiles from file and assign them
	for (auto& tile : levelData)
	{
		Cell newCell(I_Physics.get(),tile);
		//newCell.setSize(cellSize, cellSize);
		this->tiles[newCell.getX()][newCell.getY()] = std::make_shared<Cell>(newCell);
	}
};



Room::~Room()
{
}

json Room::GetJson()
{
	json instanceJson;

	instanceJson["Type"] = "Shop";

	json tilesData;
	json npcData;
	for each (auto npc in npcs)
	{
		npcData.push_back(npc->GetJson());
	}

	// Get the level data
	for (int x = 0; x < tiles.size(); x++)
		for (int y = 0; y < tiles[x].size(); y++)
		{
			tilesData.push_back(tiles[x][y]->GetJson());
		}

	instanceJson["TileData"] = tilesData;
	instanceJson["npcData"] = npcData;

	return instanceJson;
}


void Room::InstanceSetup(Player& player)
{
	player.isInBuilding = true;
	player.getBody()->SetTransform({ 1,1 }, 0.0f);


	for (int x = 0; x < roomSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < roomSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(I_Physics.get(), x, y, "WoodFloor");
			cell.setSize({ tileSize, tileSize });
			cell.setCellSize(tileSize);
			cell.setPosition(x * tileSize, y * tileSize);
			cell.isWalkable = true;
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
				Wall wall;
				SetCellItem(x, y, wall.getSharedPointer(), b2BodyType::b2_staticBody);
				tiles[x][y]->isWalkable = false;
				//tiles[x][y]->CellItem = wall.getSharedPointer();
				//tiles[x][y]->isWalkable = false;
				//tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 300);
				//tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 300);
				// Door
				//if (x == (tiles.size() - 1) / 2 && y == tiles[x].size() - 1)
				//{
				//	tiles[x][y]->isWood = true;
				//	tiles[x][y]->isWalkable = true;
				//	tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 120);
				//	tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 120);
				//}
				//if (x == tiles.size() / 2 && y == tiles[x].size() - 1)
				//{
				//	tiles[x][y]->isWood = true;
				//	tiles[x][y]->isWalkable = true;
				//	tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 120);
				//	tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 120);
				//}
			}
		}
}


void Room::Render(GL_Renderer& renderer)
{
	renderer.currentInstanceCellSize = tileSize;
	// Camera to players position
	glm::vec2 halfCameraSize = { renderer.camera.windowSize.x / 2, renderer.camera.windowSize.y / 2 };
	renderer.camera.Lerp_To(I_player.getPosition() - halfCameraSize, renderer.camera.getCameraSpeed());

	I_player.Update();
	I_player.Render(renderer);
	glm::ivec2 cellsInScreen = renderer.camera.windowSize / (float)tileSize;

	for (int x = (renderer.camera.getX() / tileSize); x <= (renderer.camera.getX() / tileSize)  + cellsInScreen.x + 1; x++)
		for (int y = (renderer.camera.getY() / tileSize); y <= (renderer.camera.getY() / tileSize) + cellsInScreen.y + 2; y++)
		{
			if (x >= 0 && y >= 0 && x < roomSize && y < roomSize)
			{
				tiles[x][y]->Render(renderer);
			}
			
		}

	//for (int x = 0; x < roomSize; x++)
	//{
	//	for (int y = 0; y < roomSize; y++)
	//	{
	//		tiles[x][y]->Render(renderer);
	//	}
	//}
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs[i]->Render(renderer);
	}
}

void Room::Update()
{
	// Update NPCs
	bool npcSelected = false;
	for (auto npc : npcs)
	{
		npc->Update();
		if (npc->isSelected)
		{
				selectedNPC = npc;
				npcSelected = true;
		}
	}
	if (!npcSelected)
		selectedNPC = nullptr;

	// Get refresh rate
	I_Physics->Step(1.0f / 100.0f, 6, 2);
}

std::shared_ptr<Cell>& Room::GetCell(int x, int y)
{
	if (x > 0 && y > 0 && x < tiles.size() && y < tiles[0].size())
	{
		return tiles[x][y];
	}
}

void Room::SetCellItem(int x, int y, std::shared_ptr<Item> item)
{
	if (x >= 0 && y >= 0 && x < tiles.size() && y < tiles[0].size())
	{
		if (item != nullptr)
		{
			item->setPosition(tiles[x][y]->getPosition());
			item->setSize(tiles[x][y]->getSize());
			tiles[x][y]->CellItem = item;
		}
		else
		{
			tiles[x][y]->CellItem = nullptr;
		}
	}
}

void Room::SetCellItem(int x, int y, std::shared_ptr<Item> item, b2BodyType type)
{
	if (x >= 0 && y >= 0 && x < tiles.size() && y < tiles[0].size())
	{
		item->setPosition(tiles[x][y]->getPosition());
		item->setSize(tiles[x][y]->getSize());
		item->InitPhysics(I_Physics.get(), type, 10.0f, 1.0f);
		if (type == b2BodyType::b2_staticBody)
			tiles[x][y]->isWalkable = false;
		tiles[x][y]->CellItem = item;
	}
}

void Room::SpawnNPC(std::shared_ptr<NPC> npc)
{
	if (npc->characterType == "Shopkeeper")
	{
		auto shopkeeper = std::dynamic_pointer_cast<Shopkeeper>(npc);
		shopkeeper->setPosition(500, 500);
		shopkeeper->setSize(shopkeeper->getSize() / 8.0f);
		shopkeeper->InitPhysics(I_Physics.get(), shopkeeper->bodyType, 10.0f, 1.0f);
		shopkeeper->setSize(shopkeeper->getSize() * 8.0f);
		shopkeeper->GenerateVillager();
		shopkeeper->tiles = tiles;
		npcs.push_back(shopkeeper);
	}
}
