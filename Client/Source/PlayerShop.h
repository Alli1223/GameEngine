#pragma once
#include "Building.h"
#include "LightSource.h"
#include "ShopDisplayShelf.h"
#include "ItemChest.h"
#include "NPC.h"

class PlayerShop : public Building
{
public:
	//! Constructor
	PlayerShop();
	PlayerShop(b2World* physicsWorld);
	//! Construct shop from json file
	PlayerShop(b2World* physicsWorld, json shopData);
	//! Destructor
	~PlayerShop();

	ItemChest chestTest;
	//! Add display with grid cell coordinates
	bool AddShopDisplay(std::shared_ptr<ShopDisplayShelf>& counter);

	void AddCustomer(std::shared_ptr<NPC> npc);

	void RemoveCustomer(int ID);

	
	//! Physics world
	//std::unique_ptr<b2World> p_World;

	// Player
	//std::shared_ptr<Player> player = nullptr;
	
	LightSource outsideLantern;
	//! Polymorphed function
	void Render(GL_Renderer& renderer);
	void Update(World& world);

	//Player* player;

	//! Render interior
	void RenderInterior(GL_Renderer& renderer);

	std::vector<std::shared_ptr<NPC>> customers;

	std::shared_ptr<Building> PlayerShop::getSharedPointer();
	std::vector<std::shared_ptr<ShopDisplayShelf>> shopDisplays;
private:
	std::shared_ptr<Building> thisuildingPointer = nullptr;

};

