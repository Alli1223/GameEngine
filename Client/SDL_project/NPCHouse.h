#pragma once
#include "Building.h"
#include "Villager.h"
class NPCHouse : public Building
{
public:
	NPCHouse();
	~NPCHouse();

	// List of NPCs living in the house
	std::vector<std::shared_ptr<NPC>> occupants;

	// Shared pointer
	std::shared_ptr<Building> getSharedPointer();

	//! Create some NPCs
	void CreateOccupants(int number);

	//! Remove an NPC
	void RemoveOccupant(int id);
	//! Render the interior of the building
	void RenderInterior(GL_Renderer & renderer);

	//! ID for the house
	std::string HouseID;

	//! Render the building
	void Render(GL_Renderer& renderer);


private:

	bool hasFirstFloor = false;
	
};

