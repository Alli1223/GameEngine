#include "stdafx.h"
#include "ServerWorld.h"

ServerWorld::ServerWorld()
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
}

ServerWorld::~ServerWorld()
{
}

void ServerWorld::onEnter(Player& player)
{
	if (GameSettings::currentInstance != nullptr)
		GameSettings::currentInstance->onExit(player);
	GameSettings::currentInstance = this;
	//player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	I_player = player;
	I_player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	InstanceSetup(I_player);
	
}

void ServerWorld::InstanceSetup(Player& player)
{
	network->allPlayers = &networkPlayers;
}

void ServerWorld::onExit(Player& player)
{
}

void ServerWorld::Render(GL_Renderer& renderer)
{
	renderer.camera.Lerp_To(I_player.getPosition() - (glm::vec2)(GameSettings::windowSize / 2), 0.3f);
	// Render the world
	for (int x = renderer.camera.getX() / cellSize; x < renderer.camera.getX() / cellSize + (GameSettings::windowSize.x / cellSize); x++)
		for (int y = renderer.camera.getY() / cellSize; y < renderer.camera.getY() / cellSize + (GameSettings::windowSize.y / cellSize); y++)
		{
			if (level[{x, y}] != nullptr)
			{
				level[{x, y}]->Render(renderer);
			}
		}
	I_player.Render(renderer);
}

void ServerWorld::Update()
{
	if(!networkUpdate.isStarted())
		networkUpdate.start();
	if (networkUpdate.getTicks() > 200)
	{
		NetworkUpdate();
		networkUpdate.restart();
		network->ProcessPlayerLocations(I_Physics.get(), I_player);
	}
	I_Physics->Step(1.0f / 100.0f, 6, 2);
}

void ServerWorld::NetworkUpdate()
{
	// IF there are cells to update
	if (updatedCells.size() > 0)
	{
		json cellsData;
		json updatedCellsarray;
		for (int i = 0; i < updatedCells.size(); i++)
		{
			json cellData = updatedCells[i]->GetJson();
			updatedCellsarray.push_back(cellData);
		}
		cellsData["CellDataArray"] = updatedCellsarray;
	
		network->sendTCPMessage("[CellData]" + cellsData.dump() + "\n");
		updatedCells.clear();
	}

	network->sendTCPMessage("[RequestMapUpdate]\n");
	//! What an empty map looks like
	std::string EmptyMap = "{\"MapData\":[]}\r\n";
	std::string newmapData = network->RecieveMessage();
	if (newmapData != EmptyMap && newmapData != mapData)
	{
		// Remove anything at the end of the json string that isn't suppose to be there
		mapData = newmapData;
		int endOfJsonString = mapData.find_last_of("}");
		int startOfJsonString = mapData.find_first_of("{");
		if (startOfJsonString >= 0)
			mapData.erase(mapData.begin(), mapData.begin() + startOfJsonString);
		int cellsUpdated = 0;

		try
		{
			json jsonData = json::parse(mapData.begin(), mapData.end());;
			json jmapData = jsonData.at("MapData");

			// Range-based for loop to iterate through the map data
			for (auto& element : jmapData)
			{

				Cell newCell(I_Physics.get(), element);
				//world.GetCell(newCell.getX(), newCell.getY()) = std::make_shared<Cell>(newCell);
				level[{newCell.getX(), newCell.getY()}] = std::make_shared<Cell>(newCell);

				level[{newCell.getX(), newCell.getY()}]->isWalkable = true;
				//newCell = level.GetCellFromJson(element);
				//level.SetCell(newCell.getX(), newCell.getY(), newCell);
				//world.GetCell(newce)
				//world.InfiniWorld.
				cellsUpdated++;
			}
			std::cout << "Cells Updated: " << cellsUpdated << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "Error processing map data: " << e.what() << std::endl;
		}
	}
}
