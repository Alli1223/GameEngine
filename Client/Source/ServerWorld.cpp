#include "stdafx.h"
#include "ServerWorld.h"

NetworkInstance::NetworkInstance()
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
}

NetworkInstance::~NetworkInstance()
{
}

void NetworkInstance::onEnter(Player& player)
{
	if (GameSettings::currentInstance != nullptr)
		GameSettings::currentInstance->onExit(player);
	GameSettings::currentInstance = this;

	//player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	I_player = player;
	I_player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	InstanceSetup(I_player);
	
}

void NetworkInstance::InstanceSetup(Player& player)
{
	network->allPlayers = &networkPlayers;
}

void NetworkInstance::onExit(Player& player)
{
}

void NetworkInstance::Render(GL_Renderer& renderer)
{
	renderer.camera.Lerp_To(I_player.getPosition() - (glm::vec2)(GameSettings::GSInstance->windowSize / 2), 0.3f);
	// Render the world
	for (int x = renderer.camera.getX() / cellSize - 1; x < renderer.camera.getX() / cellSize + (GameSettings::GSInstance->windowSize.x / cellSize) + 1; x++)
		for (int y = renderer.camera.getY() / cellSize -1; y < renderer.camera.getY() / cellSize + (GameSettings::GSInstance->windowSize.y / cellSize) + 2; y++)
		{
			if (level[{x, y}] != nullptr)
			{
				level[{x, y}]->Render(renderer);
				if (!level[{x, y}]->orientated)
				{
					procGen.OrientateCells(level[{x, y}], &level);
					level[{x, y}]->orientated = true;
				}
			}
			else // Create cell
			{
				std::shared_ptr<Cell> cell = std::make_shared<Cell>();
				cell->setX(x), cell->setY(y);
				cell->setPosition(x * cell->getCellSize(), y * cell->getCellSize());
				cell->setSize(cell->getCellSize(), cell->getCellSize());
				procGen.generateGround(cell);
				
				
				//cell->Sprite = ResourceManager::LoadTexture("Resources\\External\\rpg-pack\\tiles\\generic-rpg-Slice.png");
				//cell->NormalMap = ResourceManager::LoadTexture("Resources\\External\\rpg-pack\\tiles\\generic-rpg-Slice.png");
				level[{x, y}] = cell;
			}
		}
	I_player.Render(renderer);
	for (int i = 0; i <networkPlayers.size(); i++)
	{
		networkPlayers[i].Render(renderer);
	}
	for (std::map<int, std::shared_ptr<Enemy>>::iterator it = network->allEnemies.begin(); it != network->allEnemies.end(); it++)
	{
		it->second->Render(renderer);
	}
	network->ProcessNetworkObjects(I_Physics.get(), I_player);
}

void NetworkInstance::Update()
{
	if(!networkUpdateTimer.isStarted())
		networkUpdateTimer.start();
	if (networkUpdateTimer.getTicks() > 200)
	{
		NetworkUpdate();
		networkUpdateTimer.restart();
		network->ProcessNetworkObjects(I_Physics.get(), I_player);
	}
	for (std::map<int, std::shared_ptr<Enemy>>::iterator it = network->allEnemies.begin(); it != network->allEnemies.end(); it++)
	{
		it->second->Update();
		std::cout << it->second->getBody()->GetPosition().x << std::endl;
	}
	I_Physics->Step(1.0f / 100.0f, 8, 3);
}

void NetworkInstance::NetworkUpdate()
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
				int x = element.at("X").get<int>();
				int y = element.at("Y").get<int>();

				//if (level[{x, y}] != nullptr)
				Cell newCell(I_Physics.get(), element);
				level[{newCell.getX(), newCell.getY()}] = std::make_shared<Cell>(newCell);
				level[{newCell.getX(), newCell.getY()}]->isWalkable = true;
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
