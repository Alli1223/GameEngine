#pragma once
#include "NPC.h"


class Villager : public NPC
{
public:
	//! Constructor / Destructor
	Villager();
	~Villager();

	//! Generate the NPC with random values
	void GenerateVillager();

	//! Get a shared pointer to this object
	void Update();
	// Render the NPC
	void Render(GL_Renderer& renderer);


protected:
	// Render the body with the sprite index
	void RenderBody(int index);

	GL_Renderer* I_renderer;

	std::shared_ptr<Villager> thisVillagerPointer = nullptr;

	virtual void UpdatePathPosition();

	float walkSpeed = 1.0f;

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
		exiting,
		idle,
		movingToPostion

	} s_action;


	bool isInShop = false;


	// total time npc spends in shop
	int shopTimeout = 50000; // in ms

	//! Money (proportional to how well the town is doing?)
	unsigned int money = 0;

};

