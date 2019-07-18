#include "stdafx.h"
#include "World.h"


World::World()
{
	//buildings.push_back(playerShop.getSharedPointer());
	testHouse.CreateOccupants(0);
}


World::~World()
{
}




std::shared_ptr<Cell>& World::GetCell(float x, float y)
{
	std::shared_ptr<Cell> cell;
	return cell;
	// TODO: insert return statement here
}

void World::Render(GL_Renderer& renderer)
{
	// Buildings
	for (auto& house : buildings)
	{
		
		// Check if player entered a house
		if (player.collidesWith(house->entrance) && player.pressingUseKey)
		{
			house->spawn.previousLocation = { player.getPosition().x, player.getPosition().y + 80.0f }; // set last position
			player.getBody()->SetTransform(b2Vec2({ house->spawn.getPosition().x * player.physicsScaleDown, house->spawn.getPosition().y * player.physicsScaleDown }), 0.0f);	// move to spawn
			renderer.camera.SetPos(player.getX(), player.getY()); // move camera to player
			house->playerIsInside = true;
			player.isInBuilding = true;
			renderer.isPlayerInWorld = false;
			renderer.lights.clear();
			house->OnEnter();
		}

		else if (player.collidesWith(house->exit) && player.pressingUseKey)
		{
			player.getBody()->SetTransform(b2Vec2({ house->spawn.previousLocation.x * player.physicsScaleDown, house->spawn.previousLocation.y * player.physicsScaleDown }), 0.0f);
			player.setPosition(house->spawn.previousLocation - 30.0f);	// get last position
			renderer.camera.SetPos(player.getX(), player.getY());
			house->playerIsInside = false;
			player.isInBuilding = false;
			renderer.isPlayerInWorld = true;
			house->OnExit();
		}

		house->Render(renderer);
	}
	// Player Shop
	{	
		if (player.collidesWith(playerShop.entrance) && player.pressingUseKey)
		{
			playerShop.spawn.previousLocation = { player.getPosition().x, player.getPosition().y + 80.0f }; // set last position
			player.getBody()->SetTransform(b2Vec2({ playerShop.spawn.getPosition().x * player.physicsScaleDown, playerShop.spawn.getPosition().y * player.physicsScaleDown }), 0.0f);	// move to spawn
			renderer.camera.SetPos(player.getX(), player.getY()); // move camera to player
			playerShop.playerIsInside = true;
			player.isInBuilding = true;
			renderer.isPlayerInWorld = false;
			renderer.lights.clear();
			playerShop.OnEnter();
		}

		else if (player.collidesWith(playerShop.exit) && player.pressingUseKey)
		{
			player.getBody()->SetTransform(b2Vec2({ playerShop.spawn.previousLocation.x * player.physicsScaleDown, playerShop.spawn.previousLocation.y * player.physicsScaleDown }), 0.0f);
			player.setPosition(playerShop.spawn.previousLocation - 30.0f);	// get last position
			renderer.camera.SetPos(player.getX(), player.getY());
			playerShop.playerIsInside = false;
			player.isInBuilding = false;
			renderer.isPlayerInWorld = true;
			playerShop.OnExit();
		}

		playerShop.Render(renderer);
	}

	testHouse.setPosition(800, -1000);
	testHouse.setSize(200, 200);
	testHouse.Render(renderer);
	for (auto& occupant : testHouse.occupants)
	{
		if (occupant != nullptr)
			occupant->Update(*this);
	}
	

	// If player is in the open world
	//if (renderer.isPlayerInWorld)
	//{
	//	// Chunk / Cells
	//	for (int x = ((renderer.camera.getX() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize()) - 1;
	//		x < ((renderer.camera.getX() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize()) + renderer.camera.ChunksOnScreen.x; x++)
	//		for (int y = (renderer.camera.getY() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize() - 1;
	//			y < ((renderer.camera.getY() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize()) + renderer.camera.ChunksOnScreen.y; y++)
	//	{
	//		if (!InfiniWorld.MainLevel[{x, y}].tiles.size() > 0)
	//		{
	//			Chunk chunk(InfiniWorld.I_Physics.get(), x, y);
	//			InfiniWorld.setChunSize(chunk.getChunkSize());
	//			InfiniWorld.MainLevel[{x, y}] = chunk;
	//		}
	//		InfiniWorld.MainLevel[{x, y}].Render(renderer);
	//	}
	//
	//	// Bugs
	//	for (int i = 0; i < insects.size(); i++)
	//	{
	//		insects[i]->Render(renderer);
	//	}
	//	// Projectiles
	//	for (int i = 0; i < projectiles.size(); i++)
	//	{
	//		if (projectiles[i].experationTimer.getTicks() > projectiles[i].AliveTime)
	//			projectiles.erase(projectiles.begin() + i);
	//		else
	//			projectiles[i].Render(renderer);
	//	}
	//}

}

void World::InitiliseWorld(GL_Renderer & renderer)
{
	InfiniteWorld newworld;
	std::shared_ptr<InfiniteWorld> p(&newworld);
	p->CreateInfiniWorld(renderer);
	renderer.camera.SetPos(player.getPosition().x, player.getPosition().y);
	instances = p;
	//instances.push_back(std::move(p));
	LoadInstance(instances);
}

void World::LoadInstance(std::shared_ptr<Instance> instance)
{
	if(currentInstance != nullptr)
		currentInstance->OnExit(player);
	instance->OnEnter(player);
	currentInstance = instance;
}



bool World::CheckIfTilled(glm::vec2 worldPos, Direction direction)
{
	float CTSize = 49.9;
	glm::vec2 location = (worldPos + (float)cellSize / 2) / (float)cellSize;
	float cellOffset = (CTSize / (float)cellSize);
	try
	{
		switch (direction)
		{
			// LEFT
		case Direction::left:
			if (GetCell(location.x - cellOffset, location.y)->cropSquare != nullptr)
				if (GetCell(location.x - cellOffset, location.y)->GetCropSquare().GetCropTile({ worldPos.x - CTSize, worldPos.y }) != nullptr)
				{
					if (GetCell(location.x - cellOffset, location.y)->GetCropSquare().GetCropTile({ worldPos.x - CTSize, worldPos.y })->isTilled)
						return true;
					else
						return false;
				}
				else
					return false;
			return false;
			break;

			// RIGHT
		case Direction::right:
			if (GetCell(location.x + cellOffset, location.y)->cropSquare != nullptr)
				if (GetCell(location.x + cellOffset, location.y)->GetCropSquare().GetCropTile({ worldPos.x + CTSize, worldPos.y }) != nullptr)
				{
					if (GetCell(location.x + cellOffset, location.y)->GetCropSquare().GetCropTile({ worldPos.x + CTSize, worldPos.y })->isTilled)
						return true;
					else
						return false;
				}
				else
					return false;
			return false;
			break;
			// UP
		case Direction::up:
			if (GetCell(location.x, location.y - cellOffset)->cropSquare != nullptr)
				if (GetCell(location.x, location.y - cellOffset)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y - CTSize }) != nullptr)
				{
					if (GetCell(location.x, location.y - cellOffset)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y - CTSize })->isTilled)
						return true;
					else
						return false;
				}
				else
					return false;
			return false;
			break;

			// UP
		case Direction::down:
			if (GetCell(location.x, location.y + cellOffset)->cropSquare != nullptr)
				if (GetCell(location.x, location.y + cellOffset)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y + CTSize }) != nullptr)
				{
					if (GetCell(location.x, location.y + cellOffset)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y + CTSize })->isTilled)
						return true;
					else
						return false;
				}
				else
					return false;
			return false;
			break;
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error checking neighbour tile: " << e.what() << std::endl;
	}
}




void World::OrientateTillage(glm::vec2 worldPos)
{
	float CTSize = 50;
	glm::vec2 location = (worldPos + (float)cellSize / 2.0f) / (float)cellSize;

	if (GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y }) != nullptr)
	{
		// Top Left
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::topLeft);
					}
				}
			}
		}
		// Top Middle
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::topMiddle);
					}
				}
			}
		}
		// Top Right
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::topRight);
					}
				}
			}
		}
		// Middle Left
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::middleLeft);
					}
				}
			}
		}
		// Middle
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::middle);
					}
				}
			}
		}
		// Middle Right
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::middleRight);
					}
				}
			}
		}

		// Bottom Left
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::bottomLeft);
					}
				}
			}
		}

		// Bottom Middle
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::bottomMiddle);
					}
				}
			}
		}

		// Bottom Right
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::bottomRight);
					}
				}
			}
		}

		// Alone
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::alone);
					}
				}
			}
		}

		// Horizontal Middle
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::horizontalMiddle);
					}
				}
			}
		}

		// Horizontal Left
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::horizontalEndLeft);
					}
				}
			}
		}
		// Horizontal Right
		if (CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::horizontalEndRight);
					}
				}
			}
		}

		// Vertical Middle
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::verticalMiddle);
					}
				}
			}
		}

		// Vertical Top
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (!CheckIfTilled(worldPos, Direction::up))
				{
					if (CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::verticalEndTop);
					}
				}
			}
		}
		// Vertical Bottom
		if (!CheckIfTilled(worldPos, Direction::left))
		{
			if (!CheckIfTilled(worldPos, Direction::right))
			{
				if (CheckIfTilled(worldPos, Direction::up))
				{
					if (!CheckIfTilled(worldPos, Direction::down))
					{
						GetCell(location.x, location.y)->GetCropSquare().GetCropTile({ worldPos.x, worldPos.y })->SetOrientation(CropTile::Orientation::verticalEndBottom);
					}
				}
			}
		}





	}
}