#include "stdafx.h"
#include "NetworkInstance.h"

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
	cell->orientated = false;
	procGen.generateGround(cell);
	level[{pos.x, pos.y}] = cell;

	//Uncomment for saving the entire world rather than only changed cells
	UpdateCell(cell);
}

std::shared_ptr<Cell> NetworkInstance::GetCell(vec2 pos)
{
	std::shared_ptr<Cell> result = nullptr;
	if (level[{pos.x, pos.y}] != nullptr)
	{
		result = level[{pos.x, pos.y}];
	}
	return result;
}
std::shared_ptr<Cell> NetworkInstance::GetCell(float x, float y)
{
	std::shared_ptr<Cell> result = nullptr;
	if (level[{x, y}] != nullptr)
	{
		result = level[{x, y}];
	}
	return result;
}

void NetworkInstance::UpdateCell(std::shared_ptr<Cell> cell)
{
	updatedCells.push_back(cell);
}

void NetworkInstance::Render(GL_Renderer& renderer)
{
	// Move the camera to the player
	renderer.camera.Lerp_To(I_player.getPosition() - (glm::vec2)(GameSettings::GSInstance->windowSize / 2), 0.3f);

	// Render the world around the camera
	for (int x = renderer.camera.getX() / cellSize - 1; x < renderer.camera.getX() / cellSize + (GameSettings::GSInstance->windowSize.x / cellSize) + 1; x++)
		for (int y = renderer.camera.getY() / cellSize - 1; y < renderer.camera.getY() / cellSize + (GameSettings::GSInstance->windowSize.y / cellSize) + 2; y++)
		{
			if (level[{x, y}] != nullptr)
			{

				// Orientate cell
				if (refreshScreen)
				{
					procGen.OrientateCells(level[{x, y}], &level);
				}

				// Render cell
				level[{x, y}]->Render(renderer);
			}
			else // Otherwise create the cell
			{
				CreateCell({ x,y });
				procGen.OrientateCells(level[{x, y}], &level);
				level[{x, y}]->orientated = false;
			}
		}
	if (refreshScreen)
		refreshScreen = false;
	// Render player and other game objects
	I_player.Render(renderer);
	for (int i = 0; i < networkPlayers.size(); i++)
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
}

void NetworkInstance::Update()
{
	int x, y;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		//if (level[{x / cellSize, y / cellSize}] != nullptr)
		//{
		//	std::cout << level[{x / cellSize, y / cellSize}]->terrainElevationValue << std::endl;
		//	float delta_x = GameSettings::GSInstance->windowSize.x / 2 - x;
		//	float delta_y = GameSettings::GSInstance->windowSize.y / 2 - y;
		//	//if (delta_x > 10.0f)
		//	//	delta_x = 10.0f;
		//	//if (delta_y > 10.0f)
		//	//	delta_y = 10.0f;
		//	vec2 s_point = { -delta_x , -delta_y };
		//	Arrow proj(I_Physics.get(), I_player.getPosition() + s_point, b2Vec2(-delta_x / 100.0f, -delta_y / 100.0f));
		//	proj.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\SpriteSheets\\Items\\arrow.png");
		//	network->SawnEntity(proj.getSharedPointer());
		//}
	}

	if(!networkUpdateTimer.isStarted())
		networkUpdateTimer.start();
	/// <summary>
	/// NETWORK UPDATE
	/// </summary>
	if (networkUpdateTimer.getTicks() > updateRate)
	{
		NetworkUpdate();
		networkUpdateTimer.restart();
		network->NetworkUpdate(I_Physics.get(), I_player);
	}
	for (std::map<int, std::shared_ptr<Enemy>>::iterator it = network->allEnemies.begin(); it != network->allEnemies.end(); it++)
	{
		it->second->Update();
		if (it->second->removeObject)
		{
			network->allEnemies.erase(it->first);
			break;
		}
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
				long updateTime = element.at("UT").get<long>();
				if (level[{x, y}] != nullptr)
				{
					if (level[{x, y}]->updatedTime != updateTime)
					{
						Cell newCell(I_Physics.get(), element);
						level[{newCell.getX(), newCell.getY()}] = std::make_shared<Cell>(newCell);
						refreshScreen = true;
						cellsUpdated++;
					}
				}
				else
				{
					Cell newCell(I_Physics.get(), element);					
					level[{newCell.getX(), newCell.getY()}] = std::make_shared<Cell>(newCell);
					refreshScreen = true;
					procGen.OrientateCells(level[{newCell.getX(), newCell.getY()}], &level);
					cellsUpdated++;
				}
			}
			std::cout << "Cells Updated: " << cellsUpdated << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "Error processing map data: " << e.what() << std::endl;
		}
	}
}