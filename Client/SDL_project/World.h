#pragma once
#include "Chunk.h"
#include "Bug.h"
#include "Player.h"
#include "PlayerShop.h"
#include "Projectile.h"
#include "InfiniteWorld.h"
#include "NPCHouse.h"
#include "Instance.h"
class World
{
public:
	World();
	~World();

	
	//! Gets a cell from the infinite world
	std::shared_ptr<Cell>& GetCell(float x, float y);

	//! Render the world
	void Render(GL_Renderer& renderer);

	void InitiliseWorld(GL_Renderer& renderer);

	void LoadInstance(std::shared_ptr<Instance> instance);

	std::shared_ptr<Instance> currentInstance;

	//! List of instances
	std::shared_ptr<Instance> instances;

	//! Player shop
	PlayerShop playerShop;

	//! All the buildings in the world
	std::vector<std::shared_ptr<Building>> buildings;

	NPCHouse testHouse;
	//! List of bugs in the world
	std::vector<std::shared_ptr<Bug>> insects;
	//! List of projectiles in the world
	std::vector<Projectile> projectiles;

	//! The player
	
	Player player;

	// Stores all the cells for the infinite world
	//InfiniteWorld InfiniWorld(*player);

	//std::shared_ptr<Player> player;

	void OrientateTillage(glm::vec2 worldPos);

	int getCellSize() { return cellSize; }
	int getChunkSize() { return chunkSize; }

	enum Direction
	{
		left, right,
		up, down
	};

private:
	int cellSize = 100;
	int chunkSize = 8;

	
	

	bool CheckIfTilled(glm::vec2 pos, Direction direction);

};

