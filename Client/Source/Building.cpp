#include "stdafx.h"
#include "Building.h"



Building::Building()
{
}

Building::Building(b2World* physicsWorld)
{
	//b2Vec2 gravity(0.0f, 0.0f);
	//physics = std::make_unique<b2World>(gravity);

}

//void Building::BuildingUpdate(GL_Renderer & renderer, UserInput & userInput, GameSettings & gameSettings, GameUI & UI)
//{
//	// Camera Follow player
//	if (player != nullptr)
//	{
//		// Update input
//		userInput.HandleUserInput(renderer, *player, gameSettings, UI);
//		// Camera follow player
//		glm::vec2 halfCameraSize = { renderer.camera.windowSize.x / 2, renderer.camera.windowSize.y / 2 };
//		renderer.camera.Lerp_To(player->getPosition() - halfCameraSize, renderer.camera.getCameraSpeed());
//
//		// Update physics
//		p_World->Step(1.0f / 100.0f, 6, 2);
//
//		// Projectiles
//		for (int i = 0; i < projectiles.size(); i++)
//		{
//			if (projectiles[i]->experationTimer.getTicks() > projectiles[i]->AliveTime)
//				projectiles.erase(projectiles.begin() + i);
//			else
//				projectiles[i]->Render(renderer);
//		}
//
//		//Render
//		for (int x = renderer.camera.getX() / cellSize; x < (renderer.camera.getX() / cellSize) + (renderer.camera.windowSize.x / cellSize); x++)
//			for (int y = renderer.camera.getY() / cellSize; y < (renderer.camera.getY() / cellSize) + (renderer.camera.windowSize.y / cellSize); y++)
//			{
//				if (x >= 0 && y >= 0 && x < dungeonSize && y < dungeonSize)
//				{
//					tiles[x][y]->Render(renderer);
//				}
//			}
//
//		player->Render(renderer);
//	}
//}

void Building::RenderInterior(GL_Renderer& renderer)
{
	//if (!init)
	//	InitBuilding();
}

Building::Building(b2World* physicsWorld, json buildingData)
{

	//setSpawnPoint(getRoomSize() / 2 * getTileSize(), getRoomSize() / 2 * getTileSize());
	//setExitPoint(getRoomSize() / 2, getRoomSize());
	//x = buildingData.at("X").get<int>();
	//y = buildingData.at("Y").get<int>();
	//setPosition(x, y);
	//width = buildingData.at("Width").get<int>();
	//height = buildingData.at("Height").get<int>();
	//isVisable = buildingData.at("Visable").get<bool>();
	//entrancePoint.setPosition(buildingData.at("EntranceX").get<int>(), buildingData.at("EntranceY").get<int>());

	// Create the tiles to be overwitten
	//for (int x = 0; x < roomSize; x++)
	//{
	//	std::vector<std::shared_ptr<Cell>> column;
	//
	//	tiles.push_back(column);
	//	for (int y = 0; y < roomSize; y++)
	//	{
	//		// Populates the column with pointers to cells
	//		Cell cell(x, y);
	//
	//		cell.isWalkable = true;
	//
	//		auto sharedCell = std::make_shared<Cell>(cell);
	//		tiles[x].push_back(sharedCell);
	//	}
	//}


	//// Get the tiles
	//json tileData = buildingData.at("Tiles");
	//for (auto& tile : tileData)
	//{
	//	Cell newCell;
	//	newCell = Cell(tile);
	//	tiles[newCell.getX()][newCell.getY()] = std::make_shared<Cell>(newCell);
	//}
}

Building::Building(json building)
{
}



Building::~Building()
{
}

void Building::InitBuilding(b2World* physicsWorld)
{
	

}

void Building::OnEnter()
{

}

void Building::OnExit()
{
}
