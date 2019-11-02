#pragma once
#include "NPC.h"
#include "PathFinder.h"

class Villager : public NPC
{
public:
	//! Constructor / Destructor
	Villager();
	~Villager();

	//! Generate the NPC with random values
	void GenerateVillager();
	//! Pathfinder path
	std::vector<glm::ivec2> path;
	//! Get a shared pointer to this object
	void Update();
	// Render the NPC
	void Render(GL_Renderer& renderer);


	std::shared_ptr<Pathfinder> pathfinder;

	//! Pointers to current level
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

protected:
	// Render the body with the sprite index
	void RenderBody(int index);

	//pathfinding
	int pathPointIterator = 0;

	std::shared_ptr<Villager> thisVillagerPointer = nullptr;

	virtual void UpdatePathPosition();


	float walkSpeed = 5.0f;
	//! TODO: needs

	//! If the villager has nothing to do
	bool isWondering = true;
	bool isTravelingToShop = false;

	// List of actions the villager can perform in the world
	enum WorldActions
	{
		none,
		toShop,
		toHome,
		wondering
	} w_action;

	// List of actions the Villager can perform in the shop
	enum ShopActions
	{
		browsing,
		lookAtItem,
		paying,
		exiting

	} s_action;


	bool isInShop = false;


	// total time npc spends in shop
	int shopTimeout = 50000; // in ms

	//! Money (proportional to how well the town is doing?)
	unsigned int money = 0;

};

