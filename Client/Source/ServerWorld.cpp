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
	I_player = player;
	I_player.InitPhysics(I_Physics.get(), b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	InstanceSetup(I_player);
}

void NetworkInstance::InstanceSetup(Player& player)
{
	network->allPlayers = &networkPlayers;
}

void NetworkInstance::onExit(Player& player)
{
}

void NetworkInstance::CreateCell(vec2 pos)
{
	std::shared_ptr<Cell> cell = std::make_shared<Cell>();
	cell->setX(pos.x), cell->setY(pos.y);
	cell->setPosition(pos.x * cell->getCellSize(), pos.y * cell->getCellSize());
	cell->setSize(cell->getCellSize(), cell->getCellSize());
	cell->orientationTimer.start();
	procGen.generateGround(cell);
	level[{pos.x, pos.y}] = cell;
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
					if (level[{x, y}]->orientationTimer.getTicks() > 1000)
					{
						procGen.OrientateCells(level[{x, y}], &level);
						level[{x, y}]->orientationTimer.stop();
					}
					level[{x, y}]->orientated = true;
				}
			}
			else // Create cell
			{
				CreateCell({ x,y });
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
	for (std::map<int, std::shared_ptr<Projectile>>::iterator it = network->allProjectiles.begin(); it != network->allProjectiles.end(); it++)
	{
		it->second->Render(renderer);
	}
	network->ProcessNetworkObjects(I_Physics.get(), I_player);
}

void NetworkInstance::Update()
{
	int x, y;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		std::cout << level[{x / cellSize, y / cellSize}]->orientation << std::endl;
		float delta_x = GameSettings::GSInstance->windowSize.x / 2 - x;
		float delta_y = GameSettings::GSInstance->windowSize.y / 2 - y;
		//if (delta_x > 10.0f)
		//	delta_x = 10.0f;
		//if (delta_y > 10.0f)
		//	delta_y = 10.0f;
		vec2 s_point = { -delta_x , -delta_y };
		Projectile proj(I_Physics.get(), I_player.getPosition() + s_point, b2Vec2(-delta_x / 10000.0f, -delta_y / 10000.0f));
		network->SawnEntity(proj.getSharedPointer());
	}

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
	}
	for (std::map<int, std::shared_ptr<Projectile>>::iterator it = network->allProjectiles.begin(); it != network->allProjectiles.end(); it++)
	{
		it->second->Update();
		if (it->second->AliveTime <= 0)
			network->allProjectiles.erase(it->first);
		break;
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