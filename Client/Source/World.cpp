#include "stdafx.h"
#include "World.h"


World::World()
{
	PlayerShop shop(I_Physics.get());
	playerShop = std::make_shared<PlayerShop>(shop);
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
}


World::~World()
{
}

void World::OnEnter(Player& player)
{
	
}

void World::OnExit(Player& player)
{
}

// Convert world pos into chunk vector value 
std::shared_ptr<Cell>& World::GetCell(float X, float Y)
{
	// Get the chunk
	float chunkSize = InfiniWorld.getChunkSize();
	int chunkX = (X / chunkSize);
	int chunkY = (Y / chunkSize);
	// Get the cell pos
	int cellX = X - (float)(chunkX * chunkSize);
	int cellY = Y - (float)(chunkY * chunkSize);

	if (cellX > chunkSize)
		cellX = cellX - (chunkX * chunkSize);
	if (cellY > chunkSize)
		cellY = cellY - (chunkY * chunkSize);
	
	// If the cell is negative then offset the position by chunksize
	if (X < 0.0f)
	{
		cellX += chunkSize - 1;
		chunkX -= 1;

	}
	if (Y < 0.0f)
	{
		cellY += chunkSize - 1;
		chunkY -= 1;
	}

	//std::cout << "Getting Chunk: " << chunkX << ", " << chunkY << " -- Cell: " <<cellX << ", " << cellY << std::endl;

	if (cellX < chunkSize && cellY < chunkSize)
	{
		// If tiles doesnt exist
		if (InfiniWorld.MainLevel[{ chunkX, chunkY }].tiles.size() == 0)
		{
			Chunk chunk(I_Physics.get(), chunkX, chunkY);
			InfiniWorld.MainLevel[{chunkX, chunkY}] = chunk;
			return InfiniWorld.MainLevel[{ chunkX, chunkY }].tiles[cellX][cellY];
		}
		// Return the tile
		else
		{
			return InfiniWorld.MainLevel[{ chunkX, chunkY }].tiles[cellX][cellY];
			
		}
	}
	
}




void World::Render(GL_Renderer& renderer)
{

	// Buildings
	for (auto& house : buildings)
	{

		// Check if player entered a house
		if (I_player.collidesWith(house->entrance) && I_player.pressingUseKey)
		{
			house->spawn.previousLocation = { I_player.getPosition().x, I_player.getPosition().y + 80.0f }; // set last position
			I_player.getBody()->SetTransform(b2Vec2({ house->spawn.getPosition().x * I_player.physicsScaleDown, house->spawn.getPosition().y * I_player.physicsScaleDown }), 0.0f);	// move to spawn
			renderer.camera.SetPos(I_player.getX(), I_player.getY()); // move camera to player
			I_player.isInBuilding = true;
			renderer.isPlayerInWorld = false;
			renderer.lights.clear();
			house->OnEnter();
		}

		else if (I_player.collidesWith(house->exit) && I_player.pressingUseKey)
		{
			I_player.getBody()->SetTransform(b2Vec2({ house->spawn.previousLocation.x * I_player.physicsScaleDown, house->spawn.previousLocation.y * I_player.physicsScaleDown }), 0.0f);
			I_player.setPosition(house->spawn.previousLocation - 30.0f);	// get last position
			renderer.camera.SetPos(I_player.getX(), I_player.getY());
			I_player.isInBuilding = false;
			renderer.isPlayerInWorld = true;
			house->OnExit();
		}

		house->Render(renderer);
	}
	// Player Shop
	{
		if (I_player.collidesWith(playerShop->entrance) && I_player.pressingUseKey)
		{
			playerShop->spawn.previousLocation = { I_player.getPosition().x, I_player.getPosition().y + 80.0f }; // set last position
			I_player.getBody()->SetTransform(b2Vec2({ playerShop->spawn.getPosition().x * I_player.physicsScaleDown, playerShop->spawn.getPosition().y * I_player.physicsScaleDown }), 0.0f);	// move to spawn
			renderer.camera.SetPos(I_player.getX(), I_player.getY()); // move camera to player
			I_player.isInBuilding = true;
			renderer.isPlayerInWorld = false;
			renderer.lights.clear();
			playerShop->OnEnter();
		}

		else if (I_player.collidesWith(playerShop->exit) && I_player.pressingUseKey)
		{
			I_player.getBody()->SetTransform(b2Vec2({ playerShop->spawn.previousLocation.x * I_player.physicsScaleDown, playerShop->spawn.previousLocation.y * I_player.physicsScaleDown }), 0.0f);
			I_player.setPosition(playerShop->spawn.previousLocation - 30.0f);	// get last position
			renderer.camera.SetPos(I_player.getX(), I_player.getY());
			I_player.isInBuilding = false;
			renderer.isPlayerInWorld = true;
			playerShop->OnExit();
		}

		//playerShop->Render(renderer);
	}

	glm::vec2 halfCameraSize = { renderer.camera.windowSize.x / 2, renderer.camera.windowSize.y / 2 };
	renderer.camera.Lerp_To(I_player.getPosition() - halfCameraSize, renderer.camera.getCameraSpeed());


	// Render the world
	for (int x = ((renderer.camera.getX() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize()) - 1;
		x < ((renderer.camera.getX() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize()) + renderer.camera.ChunksOnScreen.x; x++)
		for (int y = (renderer.camera.getY() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize() - 1;
			y < ((renderer.camera.getY() / InfiniWorld.getCellSize()) / InfiniWorld.getChunkSize()) + renderer.camera.ChunksOnScreen.y; y++)
	{
		if (!InfiniWorld.MainLevel[{x, y}].tiles.size() > 0)
		{
			Chunk chunk(I_Physics.get(), x, y);
			InfiniWorld.setChunSize(chunk.getChunkSize()); 
			InfiniWorld.OrientateCells(renderer.camera, x, y);
			//chunk.generator.populateTerrain(chunk.tiles);
			InfiniWorld.MainLevel[{x, y}] = chunk;
			
			
		}
		InfiniWorld.OrientateCells(renderer.camera, x, y);
		InfiniWorld.MainLevel[{x, y}].Render(renderer);
		
	}

	// Bugs
	for (int i = 0; i < insects.size(); i++)
	{
		insects[i]->Render(renderer);
	}
	// Projectiles
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].experationTimer.getTicks() > projectiles[i].AliveTime)
			projectiles.erase(projectiles.begin() + i);
		else
			projectiles[i].Render(renderer);
	}


	for (int i = 0; i < networkPlayers.size(); i++)
	{
		networkPlayers[i].Update();
		networkPlayers[i].Render(renderer);
	}

	I_player.Render(renderer);
}

void World::Update()
{

	I_Physics->Step(1.0f / 100.0f, 6, 2);
	//I_Physics->ClearForces();
}

void World::InitiliseWorld(GL_Renderer & renderer)
{
	
	//if (!I_player.hasPhysics)
	//{
	//	I_player.InitPhysics(I_Physics.get(),I_player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	//}
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